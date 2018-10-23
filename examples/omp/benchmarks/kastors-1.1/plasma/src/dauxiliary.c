/**
 *
 * @generated d Tue Jan  7 11:45:26 2014
 *
 **/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#ifdef USE_MKL
#include <mkl_cblas.h>
#include <mkl_lapacke.h>
#else
#include <cblas.h>
#include <lapacke.h>
#endif
#include "plasma.h"
#include <core_blas.h>
#include "auxiliary.h"

/*--------------------------------------------------------------
 * Check the solution
 */

double d_check_solution(int M, int N, int NRHS, double *A, int LDA,
                      double *B,  double *X, int LDB)
{
/*     int info_solution; */
    double Rnorm = -1.00;
    double zone  =  1.0;
    double mzone = -1.0;
    double *work = (double *)malloc(max(M, N)* sizeof(double));

    LAPACKE_dlange_work(LAPACK_COL_MAJOR, 'i', M, N,    A, LDA, work);
    LAPACKE_dlange_work(LAPACK_COL_MAJOR, 'i', M, NRHS, X, LDB, work);
    LAPACKE_dlange_work(LAPACK_COL_MAJOR, 'i', N, NRHS, B, LDB, work);

    cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, M, NRHS, N, (zone), A, LDA, X, LDB, (mzone), B, LDB);

    Rnorm = LAPACKE_dlange_work(LAPACK_COL_MAJOR, 'i', N, NRHS, B, LDB, work);

    free(work);

    return Rnorm;
}
