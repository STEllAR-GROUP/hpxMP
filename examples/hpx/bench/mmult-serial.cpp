#include <hpx/hpx_init.hpp>
#include <hpx/runtime/threads/topology.hpp>
#include <boost/format.hpp>

#include <sys/time.h>

#include "matrix_block.h"

using hpx::lcos::shared_future;
using hpx::lcos::future;
using std::vector;
using std::cout;
using std::endl;
using std::chrono::high_resolution_clock;
using time_point = std::chrono::system_clock::time_point;


int blocksize;

void print(block A) {
    for(int i = 0; i < A.height; i++) {
        for(int j = 0; j < A.width; j++) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

block rec_mult(block A, block B, block C);

block serial_mult(block A, block B, block C) {
    for (int i = 0; i < C.height; i++) {
        for (int j = 0; j < C.width; j++) {
            for (int k = 0; k < A.width;k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

block add_blocks(block A, block B, block result) {
    for(int i = 0; i < A.height; i++){
        for(int j = 0; j < A.width; j++) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
    return result;
}

block calc_c11(block A, block B, block C) {
    block tempC = C.block11();//scratch space
    tempC.add_scratch();
    block A11B11 = rec_mult(A.block11(), B.block11(), C.block11());
    block A12B21 = rec_mult(A.block12(), B.block21(), tempC);
    return add_blocks(A11B11, A12B21, C.block11());
}

block calc_c12(block A, block B, block C) {
    block tempC = C.block12();
    tempC.add_scratch();
    block A11B12 = rec_mult(A.block11(), B.block12(), C.block12());
    block A12B22 = rec_mult(A.block12(), B.block22(), tempC);
    return add_blocks(A11B12, A12B22, C.block12());
}

block calc_c21(block A, block B, block C) {
    block tempC = C.block21();
    tempC.add_scratch();
    block A21B11 = rec_mult(A.block21(), B.block11(), C.block21());
    block A22B21 = rec_mult(A.block22(), B.block21(), tempC);
    return add_blocks(A21B11, A22B21, C.block21());
}

block calc_c22(block A, block B, block C) {
    block tempC = C.block22();
    tempC.add_scratch();
    block A21B12 = rec_mult(A.block21(), B.block12(), C.block22());
    block A22B22 = rec_mult(A.block22(), B.block22(), tempC);
    return add_blocks(A21B12, A22B22, C.block22());
}

block rec_mult(block A, block B, block C) {
    if(C.width <= blocksize || C.height <= blocksize ) {
        return serial_mult(A, B, C);
    } 
    block C11 = calc_c11(A, B, C);
    block C12 = calc_c12(A, B, C);
    block C21 = calc_c21(A, B, C);
    block C22 = calc_c22(A, B, C);

    return C;
}

int hpx_main(int argc, char **argv) {
    blocksize = 100;
    int niter = 1, N = 1000;
    time_point time1, time2;
    srand(1);
    if(argc > 1)
        N = atoi(argv[1]);
    if(argc > 2)
        blocksize = atoi(argv[2]);
    if(argc > 3)
        niter = atoi(argv[3]);
     cout << "Recursive matrix multiplication" << endl;
     cout << "size " << N << endl;
     cout << "block size " << blocksize << endl;
     cout << "Number of iterations " << niter << endl;

    block a(N);
    block b(N);
    block c(new double[N*N], N);

    time1 = high_resolution_clock::now();
    rec_mult(a, b, c);
    time2 = high_resolution_clock::now();

     auto time = std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1).count();
     cout << "time "<< time << " microseconds" << endl;
    return hpx::finalize();
}

int main(int argc, char ** argv) {

    hpx::init(argc, argv);

    return 0;
}
