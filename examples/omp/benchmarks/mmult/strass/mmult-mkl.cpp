#include <cstdlib>
#include <vector>
#include <chrono>
#include <iostream>

#include "mkl_cblas.h"

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

     //cblas_dgemm(layout, transA, transB, m, n, k, alpha, a, lda, b, ldb, beta, c, ldc);
     auto layout = CblasRowMajor;
     auto transA = CblasNoTrans;
     auto transB = CblasNoTrans;
     int m = size, n = size, k = size;
     auto t1 = high_resolution_clock::now();
     cblas_dgemm(layout, transA, transB, m, n, k, 1, A.data(), size, B.data(), size, 1, R1.data(), size);
     auto t2 = high_resolution_clock::now();

    auto total_time = duration_cast<std::chrono::nanoseconds> (t2-t1).count();

    cout << "total time: " <<  total_time << " nanoseconds, "
         << " Gflops = " << (double)3*2.0*size * size * size / ((double)total_time) << endl;

}
