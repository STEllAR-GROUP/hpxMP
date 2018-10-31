/*
 * Rectangular matrix multiplication, started from MIT Cilk matmul.cilk example
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "omp.h"

#include <pthread.h>
#include <string.h>

#ifdef USING_PAPI
#include <papi.h>
#endif
#define REAL double

void zero(REAL *A, int n);
void init(REAL *A, int n);
double maxerror(REAL *A, REAL *B, int n);
#ifdef USING_PAPI
PAPI_event_info_t* startPAPI(int *eventSet, int *nativeEventSet, unsigned int testEvents[], int numE);
#endif
void iter_matmul(REAL *A, REAL *B, REAL *C, int m, int n, int p, int bwidth);
void omp_matmul(REAL *A, REAL *B, REAL *C, int m , int n, int p, int bwidth);
void matmul_omp_task_caller(REAL *A, REAL *B, REAL *C, int m, int n, int p, int bw);
//void matmul_omp_task(REAL *A, REAL *B, REAL *C, int m, int n, int p, int ld, int add);
void matmul_recursive_tile_caller(REAL *A, REAL *B, REAL *C, int m, int n, int p, int ld);
void sequential_tiling_smallblockMul(REAL *A, REAL *B, REAL *C, int m, int n, int p, int bwidth);
void sequential_tiling(REAL *A, REAL *B, REAL *C, int m, int n, int p, int bwidth);
void omp_dtile(REAL *A, REAL *B, REAL *C, int m, int n, int p, int bwidth);
void omp_tile_rec(REAL *A, REAL *B, REAL *C, int m, int n, int p, int bwidth);

void mkl_call(REAL *A, REAL *B, REAL *C, int m, int n, int p, int bwidth);

