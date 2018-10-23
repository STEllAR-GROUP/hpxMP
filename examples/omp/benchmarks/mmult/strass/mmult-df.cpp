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


void serial_mmult( int numBlocks, int matrix_size, 
            vector<double> *result, const block R,
            vector<double> *input1, const block b1,
            vector<double> *input2, const block b2 ){
    int size = R.size;
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            for(int k = 0; k < size; k++) {
                (*result)[R.start + matrix_size*i + j] += (*input1)[b1.start + matrix_size*i + k] + (*input2)[b2.start + matrix_size*k + j];
            }
        }
    }
}

void RC_mult(int numBlocks, int matrix_size,
        vector<double> *result, const block R,
        vector<double> *input1, const block b1,
        vector<double> *input2, const block b2 ){

    int size = R.size;
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            for(int k = 0; k < size; k++) {
                (*result)[R.start + matrix_size*i + j] += (*input1)[b1.start + matrix_size*i + k] + (*input2)[b2.start + matrix_size*k + j];
            }
        }
    }
}
void mmult( int numBlocks, int matrix_size,
            vector<double> *result, block **blR,
            vector<double> *input1, block **bl1,
            vector<double> *input2, block **bl2 ){
    for(int i = 0; i < numBlocks; i++) {
        for(int j = 0; j < numBlocks; j++) {
            for(int k = 0; k < numBlocks; k++) {
#pragma omp task depend(inout: blR[i][j]) depend(  in: bl1[i][k], bl2[k][j])
                serial_mmult( numBlocks, matrix_size, result, blR[i][j], input1, bl1[i][k], input2, bl2[k][j]);
            }
        }
    }
}

int main(int argc, char **argv) 
{
    //for now, everything is square
    vector<double> A, B, C, D, R1, R2, R3;
    int size = 1024;
    int blocksize = 256;
    if(argc > 1)
        size = atoi(argv[1]);
    if(argc > 2)
        blocksize = atoi(argv[2]);

    cout << "size = " << size << ", block size = " << blocksize << endl;
    cout << "beginning initialization" << endl;
    std::srand(0);
    init_data_matrix(A, size);
    init_data_matrix(B, size);
    init_data_matrix(C, size);
    init_data_matrix(D, size);

    init_result_matrix(R1, size);
    init_result_matrix(R2, size);
    init_result_matrix(R3, size);

    block **blA = getBlockList(size, blocksize);
    block **blB = getBlockList(size, blocksize);
    block **blC = getBlockList(size, blocksize);
    block **blD = getBlockList(size, blocksize);
    block **blR1 = getBlockList(size, blocksize);
    block **blR2 = getBlockList(size, blocksize);
    block **blR3 = getBlockList(size, blocksize);
    cout << "initialization complete" << endl;

#pragma omp parallel
{
#pragma omp single
{
    //this is messy. I need to tie the matrix and it's blockList together better.
    int numBlocks = size/blocksize;
    auto t1 = high_resolution_clock::now();
    mmult(numBlocks, size, &R1, blR1, &A, blA, &B, blB);
    
    auto t2 = high_resolution_clock::now();
    mmult(numBlocks, size, &R2, blR2, &R1, blR1, &C, blC);

    auto t3 = high_resolution_clock::now();
    mmult(numBlocks, size, &R3, blR3, &R1, blR1, &R2, blR2);
#pragma omp taskwait

    auto tf = high_resolution_clock::now();

    auto total_time = duration_cast<std::chrono::nanoseconds> (tf-t1).count();
    auto time1 = duration_cast<std::chrono::nanoseconds> (t2-t1).count();
    auto time2 = duration_cast<std::chrono::nanoseconds> (t3-t2).count();
    auto time3 = duration_cast<std::chrono::nanoseconds> (tf-t3).count();

    cout << "total time: " <<  total_time << " nanoseconds, "
         << " Gflops = " << (double)3*2.0*size * size * size / ((double)total_time) << endl;

    cout << "time 1: " <<  time1 << " nanoseconds" << endl;
    cout << "time 2: " <<  time2 << " nanoseconds" << endl;
    cout << "time 3: " <<  time3 << " nanoseconds" << endl;
}}
}
