
//  Copyright (c) 2011-2013 Thomas Heller
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "jacobi.hpp"

#include <hpx/hpx.hpp>
#include <hpx/hpx_init.hpp>
#include <hpx/include/lcos.hpp>
#include <hpx/lcos/local/dataflow.hpp>
#include <hpx/util/high_resolution_timer.hpp>
#include <hpx/util/unwrapped.hpp>

using boost::shared_ptr;
using std::min;
using std::vector;
using hpx::make_ready_future;
using hpx::lcos::local::dataflow;
using hpx::lcos::shared_future;
using hpx::async;

using hpx::util::unwrapped;

struct block {
    double *src;
    double *dest;
    size_t matrix_size;
    size_t block_size;
    size_t col;
    size_t row;
};


namespace jacobi_smp {
    vector<double> matrix1;
    vector<double> matrix2;

    void jacobi_kernel_wrapper(range const & y_range, size_t n, vector<double> & dst, vector<double> const & src) {
        for(size_t y = y_range.begin(); y < y_range.end(); ++y) {
                  double * dst_ptr = &dst[y * n];
            const double * src_ptr = &src[y * n];
            jacobi_kernel( dst_ptr, src_ptr, n );
        }
    }
    void jacobi_serial(size_t n, size_t iterations, std::string output_filename) {
        hpx::util::high_resolution_timer t;
        matrix1.resize(n*n);
        matrix2.resize(n*n);
        for(size_t i = 1; i < iterations; ++i) {
            matrix2[0] = ( matrix1[0] + matrix1[1] + matrix1[n] ) / 3;//LB
            for(size_t i = 1; i < n-1; i++) {//bot
                matrix2[i] = ( matrix1[i  ] + matrix1[i-1] +
                               matrix1[i+1] + matrix1[i+n] ) * .25;
            }
            matrix2[n-1] = ( matrix1[ n-1 ] + matrix1[n-2] + matrix1[n+n-1] ) / 3;//RB
    
            for(size_t i = 1; i < n-1; i++) {
                matrix2[i*n] = ( matrix1[ i   *n] + matrix1[ i   *n+1] + 
                                 matrix1[(i-1)*n] + matrix1[(i+1)*n  ] 
                                 ) * .25;//left
                for(size_t j = 1; j < n-1; j++) {
                    matrix2[i*n+j] = ( matrix1[ i   *n+j  ] +  
                                       matrix1[ i   *n+j-1] + matrix1[ i   *n+j+1] +
                                       matrix1[(i-1)*n+j  ] + matrix1[(i+1)*n+j  ]
                                       ) * .2; //mid
                }
                matrix2[i*n+n-1] = ( matrix1[i*n+n-1] + matrix1[i*n+n-2] + 
                                     matrix1[i*n-1] + matrix1[(i+2)*n-1] 
                                     ) * .25;//right
            }
            matrix2[(n-1)*n] = ( matrix1[(n-1)*n] + matrix1[(n-1)*n+1] +
                                                    matrix1[(n-2)*n] ) / 3;//TL
            for(size_t i = 1; i < n-1; i++) {//top
                matrix2[(n-1)*n + i] = ( matrix1[(n-1)*n+i] + matrix1[(n-1)*n+i-1] +
                                                              matrix1[(n-1)*n+i+1] +
                                                              matrix1[(n-2)*n+i  ] ) * .25;
            }
            matrix2[n*n-1] = ( matrix1[n*n-1] + matrix1[n*n-2] + matrix1[n*n-1-n] ) / 3;//TR
        }
        report_timing(n, iterations, t.elapsed());
        //output_grid(output_filename, *grid_old, n);
    }
    
    block jacobi_kernel_mid(block previous, block left, block right, block below, block above) {
        size_t block_size = previous.block_size;
        size_t n = previous.matrix_size;

        for(size_t i = previous.row; i < previous.row + block_size; i++) {
            for(size_t j = previous.col; j < previous.col + block_size; j++) {
                previous.dest[i*n + j] = (previous.src[i*n     + j  ] + 
                                          previous.src[i*n     + j-1] +
                                          previous.src[i*n     + j+1] +
                                          previous.src[i*(n-1) + j  ] +
                                          previous.src[i*(n+1) + j  ] ) * 0.2;
            }
        }
        std::swap(previous.src, previous.dest);
        return previous;
    }

    block jacobi_kernel_top(block previous, block left, block right, block below){
        size_t block_size = previous.block_size;
        size_t n = previous.matrix_size;

        for(size_t i = previous.row; i < previous.row + block_size; i++) {
            for(size_t j = previous.col; j < previous.col + block_size; j++) {
                previous.dest[i*n + j] = (previous.src[i*n     + j  ] + 
                                          previous.src[i*n     + j-1] +
                                          previous.src[i*n     + j+1] +
                                          previous.src[i*(n-1) + j  ] ) * 0.25;
            }
        }
        std::swap(previous.src, previous.dest);
        return previous;
    }
    block jacobi_kernel_bot(block previous, block left, block right, block above){
        size_t block_size = previous.block_size;
        size_t n = previous.matrix_size;

        for(size_t i = previous.row; i < previous.row + block_size; i++) {
            for(size_t j = previous.col; j < previous.col + block_size; j++) {
                previous.dest[i*n + j] = (previous.src[i*n     + j  ] + 
                                          previous.src[i*n     + j-1] +
                                          previous.src[i*n     + j+1] +
                                          previous.src[i*(n+1) + j  ] ) * 0.25;
            }
        }
        std::swap(previous.src, previous.dest);
        return previous;
    }
    block jacobi_kernel_left (block previous, block right, block below, block above){
        size_t block_size = previous.block_size;
        size_t n = previous.matrix_size;

        for(size_t i = previous.row; i < previous.row + block_size; i++) {
            for(size_t j = previous.col; j < previous.col + block_size; j++) {
                previous.dest[i*n + j] = (previous.src[i*n     + j  ] + 
                                          previous.src[i*n     + j+1] +
                                          previous.src[i*(n-1) + j  ] +
                                          previous.src[i*(n+1) + j  ] ) * 0.25;
            }
        }
        std::swap(previous.src, previous.dest);
        return previous;
    }
    block jacobi_kernel_right(block previous, block left, block below, block above){
        size_t block_size = previous.block_size;
        size_t n = previous.matrix_size;

        for(size_t i = previous.row; i < previous.row + block_size; i++) {
            for(size_t j = previous.col; j < previous.col + block_size; j++) {
                previous.dest[i*n + j] = (previous.src[i*n     + j  ] + 
                                          previous.src[i*n     + j-1] +
                                          previous.src[i*(n-1) + j  ] +
                                          previous.src[i*(n+1) + j  ] ) * 0.25;
            }
        }
        std::swap(previous.src, previous.dest);
        return previous;
    }
    block jacobi_kernel_TL(block previous, block right, block below ){
        size_t block_size = previous.block_size;
        size_t n = previous.matrix_size;

        for(size_t i = previous.row; i < previous.row + block_size; i++) {
            for(size_t j = previous.col; j < previous.col + block_size; j++) {
                previous.dest[i*n + j] = (previous.src[i*n     + j  ] + 
                                          previous.src[i*n     + j+1] +
                                          previous.src[i*(n-1) + j  ] ) / 3.0;
            }
        }
        std::swap(previous.src, previous.dest);
        return previous;
    }
    block jacobi_kernel_TR(block previous, block left, block below ){
        size_t block_size = previous.block_size;
        size_t n = previous.matrix_size;

        for(size_t i = previous.row; i < previous.row + block_size; i++) {
            for(size_t j = previous.col; j < previous.col + block_size; j++) {
                previous.dest[i*n + j] = (previous.src[i*n     + j  ] + 
                                          previous.src[i*n     + j-1] +
                                          previous.src[i*(n-1) + j  ] ) / 3.0;
            }
        }
        std::swap(previous.src, previous.dest);
        return previous;
    }
    block jacobi_kernel_BL(block previous, block right, block above){
        size_t block_size = previous.block_size;
        size_t n = previous.matrix_size;

        for(size_t i = previous.row; i < previous.row + block_size; i++) {
            for(size_t j = previous.col; j < previous.col + block_size; j++) {
                previous.dest[i*n + j] = (previous.src[i*n     + j  ] + 
                                          previous.src[i*n     + j+1] +
                                          previous.src[i*(n+1) + j  ] ) / 3.0;
            }
        }
        std::swap(previous.src, previous.dest);
        return previous;
    }
    block jacobi_kernel_BR(block previous, block left, block above){
        size_t block_size = previous.block_size;
        size_t n = previous.matrix_size;

        for(size_t i = previous.row; i < previous.row + block_size; i++) {
            for(size_t j = previous.col; j < previous.col + block_size; j++) {
                previous.dest[i*n + j] = (previous.src[i*n     + j  ] + 
                                          previous.src[i*n     + j-1] +
                                          previous.src[i*(n-1) + j  ] ) / 3.0;
            }
        }
        std::swap(previous.src, previous.dest);
        return previous;
    }


    auto jacobi_op    = unwrapped(&jacobi_kernel_mid);
    auto jacobi_bot   = unwrapped(&jacobi_kernel_bot);
    auto jacobi_top   = unwrapped(&jacobi_kernel_top);
    auto jacobi_left  = unwrapped(&jacobi_kernel_left);
    auto jacobi_right = unwrapped(&jacobi_kernel_right);
    auto jacobi_BL    = unwrapped(&jacobi_kernel_BL);
    auto jacobi_BR    = unwrapped(&jacobi_kernel_BR);
    auto jacobi_TL    = unwrapped(&jacobi_kernel_TL);
    auto jacobi_TR    = unwrapped(&jacobi_kernel_TR);


    void block_init(vector< vector<block> > &blockList, size_t block_size, size_t matrix_size){
        size_t numBlocks = static_cast<size_t>(std::ceil(double(matrix_size)/block_size));
        size_t remainder = matrix_size % block_size;
        if(remainder == 0) {
            remainder = block_size;
        }

        matrix1.resize(matrix_size * matrix_size);
        matrix2.resize(matrix_size * matrix_size);

        blockList.resize(numBlocks);
        for(int i = 0; i < numBlocks; i++){
            blockList[i].resize(numBlocks);
            for(int j = 0; j < numBlocks; j++) {
                blockList[i][j].matrix_size = matrix_size;
                if(i == numBlocks - 1 || j == numBlocks -1) {
                    blockList[i][j].block_size = remainder;
                } else {
                    blockList[i][j].block_size = block_size;
                }
                blockList[i][j].dest = matrix2.data();
                blockList[i][j].src  = matrix1.data();
                blockList[i][j].col  = j*block_size;
                blockList[i][j].row  = i*block_size;
            }
        }
    }

    void jacobi_init(vector< vector< vector< hpx::shared_future<block> > > > &futureList, size_t n, size_t block_size) {
        vector< vector<block> > blockList;
        block_init(blockList, block_size, n);
        size_t numBlocks = blockList.size();

        futureList[0].resize(numBlocks);
        futureList[1].resize(numBlocks);

        for(int i = 0; i < numBlocks; i++){
            futureList[0][i].resize(numBlocks);
            futureList[1][i].resize(numBlocks);
        }
        
        const size_t curr = 1;
        
        futureList[curr][0][0] = async(
                jacobi_kernel_BL, blockList[0][0],
                                  blockList[0][1],
                                  blockList[1][0] );
        for(size_t j = 1; j < numBlocks - 1; j++) {
            futureList[curr][j][0] = async(
                    jacobi_kernel_left, blockList[j  ][0],
                                        blockList[j  ][1],
                                        blockList[j-1][0],
                                        blockList[j+1][0] );
        }
        futureList[curr][numBlocks-1][0] = async(
                jacobi_kernel_TL, blockList[numBlocks-1][0],
                                  blockList[numBlocks-1][1],
                                  blockList[numBlocks-2][0] );
        for(size_t j = 1; j < numBlocks - 1; j++) {
            futureList[curr][0][j] = async(
                    jacobi_kernel_bot, blockList[0][j  ], 
                                       blockList[0][j-1],
                                       blockList[0][j+1],
                                       blockList[1][j  ] );
            for(size_t k = 1; k < numBlocks - 1; k++) {
                futureList[curr][j][k] = async( 
                        jacobi_kernel_mid, blockList[k  ][j  ],
                                           blockList[k  ][j-1],
                                           blockList[k  ][j+1],
                                           blockList[k-1][j  ],
                                           blockList[k+1][j  ]);
            }
            futureList[curr][numBlocks-1][j] = async(
                    jacobi_kernel_top, blockList[numBlocks-1][j  ], 
                                       blockList[numBlocks-1][j-1],
                                       blockList[numBlocks-1][j+1],
                                       blockList[numBlocks-2][j  ] );
        }
        futureList[curr][0][numBlocks-1] = async(
                jacobi_kernel_BR, blockList[0][numBlocks-1],
                                  blockList[0][numBlocks-2],
                                  blockList[1][numBlocks-1]);
        for(size_t j = 1; j < numBlocks - 1; j++) {
            futureList[curr][j][numBlocks-1] = async(
                    jacobi_kernel_left, blockList[j ][numBlocks-1],
                                        blockList[j ][numBlocks-2],
                                        blockList[j-1][numBlocks-1],
                                        blockList[j+1][numBlocks-1]);
        }
        futureList[curr][numBlocks-1][numBlocks-1] = async(
                jacobi_kernel_TR, blockList[numBlocks-1][numBlocks-1],
                           blockList[numBlocks-1][numBlocks-2],
                           blockList[numBlocks-2][numBlocks-1]);

    }

    void jacobi( size_t n , size_t iterations, size_t block_size, std::string output_filename) {
        hpx::util::high_resolution_timer t;

        vector< vector< vector< shared_future<block> > > > blockList(2);
        jacobi_init(blockList, n, block_size);

        size_t numBlocks = blockList[0].size();

        for(size_t i = 1; i < iterations; ++i) {
            const size_t prev = i%2;
            const size_t curr = (i+1)%2;
            blockList[curr][0][0] = dataflow(
                    jacobi_BL, blockList[prev][0][0],
                               blockList[prev][0][1],
                               blockList[prev][1][0] );
            for(size_t j = 1; j < numBlocks - 1; j++) {
                blockList[curr][j][0] = dataflow(
                        jacobi_left, blockList[prev][j  ][0],
                                     blockList[prev][j  ][1],
                                     blockList[prev][j-1][0],
                                     blockList[prev][j+1][0] );
            }
            blockList[curr][numBlocks-1][0] = dataflow(
                    jacobi_TL, blockList[prev][numBlocks-1][0],
                               blockList[prev][numBlocks-1][1],
                               blockList[prev][numBlocks-2][0] );

            for(size_t j = 1; j < numBlocks - 1; j++) {
                blockList[curr][0][j] = dataflow(
                        jacobi_bot, blockList[prev][0][j  ], 
                                    blockList[prev][0][j-1],
                                    blockList[prev][0][j+1],
                                    blockList[prev][1][j  ] );
                for(size_t k = 1; k < numBlocks - 1; k++) {
                    blockList[curr][j][k] = dataflow( 
                            jacobi_op, blockList[prev][k  ][j  ],
                                       blockList[prev][k  ][j-1],
                                       blockList[prev][k  ][j+1],
                                       blockList[prev][k-1][j  ],
                                       blockList[prev][k+1][j  ]);
                }
                blockList[curr][numBlocks-1][j] = dataflow(
                        jacobi_top, blockList[prev][numBlocks-1][j  ], 
                                    blockList[prev][numBlocks-1][j-1],
                                    blockList[prev][numBlocks-1][j+1],
                                    blockList[prev][numBlocks-2][j  ] );
            }
            blockList[curr][0][numBlocks-1] = dataflow(
                    jacobi_BR, blockList[prev][0][numBlocks-1],
                               blockList[prev][0][numBlocks-2],
                               blockList[prev][1][numBlocks-1]);
            for(size_t j = 1; j < numBlocks - 1; j++) {
            blockList[curr][j][numBlocks-1] = dataflow(
                    jacobi_left, blockList[prev][j ][numBlocks-1],
                                 blockList[prev][j ][numBlocks-2],
                                 blockList[prev][j-1][numBlocks-1],
                                 blockList[prev][j+1][numBlocks-1]);
            }
            blockList[curr][numBlocks-1][numBlocks-1] = dataflow(
                    jacobi_TR, blockList[prev][numBlocks-1][numBlocks-1],
                               blockList[prev][numBlocks-1][numBlocks-2],
                               blockList[prev][numBlocks-2][numBlocks-1]);
        }
        for(int i = 0; i < blockList[(n-1)%2].size(); i++) {
            hpx::wait_all(blockList[(n-1)%2][i]);
        }

        report_timing(n, iterations, t.elapsed());
        //output_grid(output_filename, *grid_old, n);
   }
}
