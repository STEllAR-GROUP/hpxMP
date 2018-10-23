#include <hpx/hpx_init.hpp>
#include <hpx/hpx.hpp>
#include <hpx/runtime/threads/topology.hpp>
//#include <hpx/lcos/local/dataflow.hpp>

#include <boost/format.hpp>

#include <sys/time.h>

#include "matrix_block.h"

using hpx::lcos::future;
using hpx::util::unwrapped;
using hpx::async;
using hpx::lcos::local::dataflow;
using hpx::make_ready_future;

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
    future<block> A11B11 = async(rec_mult, A.block11(), B.block11(), C.block11());
    future<block> A12B21 = async(rec_mult, A.block12(), B.block21(), tempC);
    return add_blocks(A11B11.get(), A12B21.get(), C.block11());
}

block calc_c12(block A, block B, block C) {
    block tempC = C.block12();
    tempC.add_scratch();
    future<block> A11B12 = async(rec_mult, A.block11(), B.block12(), C.block12());
    future<block> A12B22 = async(rec_mult, A.block12(), B.block22(), tempC);
    return add_blocks(A11B12.get(), A12B22.get(), C.block12());
}

block calc_c21(block A, block B, block C) {
    block tempC = C.block21();
    tempC.add_scratch();
    future<block> A21B11 = async(rec_mult, A.block21(), B.block11(), C.block21());
    future<block> A22B21 = async(rec_mult, A.block22(), B.block21(), tempC);
    return add_blocks(A21B11.get(), A22B21.get(), C.block21());
}

block calc_c22(block A, block B, block C) {
    block tempC = C.block22();
    tempC.add_scratch();
    future<block> A21B12 = async(rec_mult, A.block21(), B.block12(), C.block22());
    future<block> A22B22 = async(rec_mult, A.block22(), B.block22(), tempC);
    return add_blocks(A21B12.get(), A22B22.get(), C.block22());
}

block combine_blocks(block b1, block b2, block b3, block b4, block C) {
    return C;
}

block rec_mult(block A, block B, block C) {
    if(C.width <= blocksize || C.height <= blocksize ) {
        return serial_mult(A, B, C);
    } 
    future<block> C11 = async(calc_c11, A, B, C);
    future<block> C12 = async(calc_c12, A, B, C);
    future<block> C21 = async(calc_c21, A, B, C);
    future<block> C22 = async(calc_c22, A, B, C);

    C11.wait();
    C12.wait();
    C21.wait();
    C22.wait();
    /*
       auto f_A = make_ready_future(A);
       auto f_B = make_ready_future(B);
       auto f_C = make_ready_future(C);
       future<block> C11 = dataflow(unwrapped(calc_c11), f_A, f_B, f_C);
       future<block> C12 = dataflow(unwrapped(calc_c12), f_A, f_B, f_C);
       future<block> C21 = dataflow(unwrapped(calc_c21), f_A, f_B, f_C);
       future<block> C22 = dataflow(unwrapped(calc_c22), f_A, f_B, f_C);

       future<block> result = dataflow(unwrapped(combine_blocks), C11, C12, C21, C22, f_C);
       */
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
