#include "block.h"
#include <cstdlib>
#include <vector>
#include <chrono>
#include <iostream>

using std::cout;
using std::endl;
using std::vector;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;

vector<double> A, B, C, R1, R2;

void init_data_matrix(vector<double> &V, int size) {
    V.reserve(size*size);

    for(int i=0; i < size*size; i++) {
        V[i] = std::rand();
    }
}

void init_result_matrix( vector<double> &R, int size) {
    R.reserve(size*size);
    for(auto entry : R ) {
        entry = 0;
    }
}

void init(int size) {
    std::srand(0);
    init_data_matrix(A, size);
    init_data_matrix(B, size);
    init_data_matrix(C, size);

    init_result_matrix(R1, size);
    init_result_matrix(R2, size);

}

void serial_mmult( int numBlocks, int matrix_size, 
            vector<double> &result, block R,
            vector<double> &input1, block b1,
            vector<double> &input2, block b2 ){
    int size = R.size;
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            for(int k = 0; k < size; k++) {
                result[R.start + matrix_size*i + j] += input1[b1.start + matrix_size*i + k] + input2[b2.start + matrix_size*k + j];
            }
        }
    }

}

void mmult( int numBlocks, int matrix_size,
            vector<double> &result, block **blR,
            vector<double> &input1, block **bl1,
            vector<double> &input2, block **bl2 ){
    for(int i = 0; i < numBlocks; i++) {
        for(int j = 0; j < numBlocks; j++) {
            for(int k = 0; k < numBlocks; k++) {
                serial_mmult( numBlocks, matrix_size, result, blR[i][j], input1, bl1[i][k], input2, bl2[k][j]);
            }
        }
    }
}

int main(int argc, char **argv) 
{
    //for now, everything is square
    int size = 1024;
    int blocksize = 64;
    if(argc > 1)
        size = atoi(argv[1]);
    if(argc > 2)
        blocksize = atoi(argv[2]);

    init(size);
    block **blA = getBlockList(size, blocksize);
    block **blB = getBlockList(size, blocksize);
    block **blC = getBlockList(size, blocksize);
    block **blR1 = getBlockList(size, blocksize);
    block **blR2 = getBlockList(size, blocksize);

    //this is messy. I need to tie the matrix and it's blockList together better.
    int numBlocks = size/blocksize;
    auto t1 = high_resolution_clock::now();
    mmult(numBlocks, size, R1, blR1, A, blA, B, blB);
    
    mmult(numBlocks, size, R2, blR2, R1, blR1, C, blC);

    auto t2 = high_resolution_clock::now();

    cout << duration_cast<std::chrono::nanoseconds> (t2-t1).count() << " nanoseconds" << endl;
}
