/**
 *
 * @file core_dblas.h
 *
 *  PLASMA auxiliary routines
 *  PLASMA is a software package provided by Univ. of Tennessee,
 *  Univ. of California Berkeley and Univ. of Colorado Denver
 *
 * @version 2.6.0
 * @author Jakub Kurzak
 * @author Hatem Ltaief
 * @author Mathieu Faverge
 * @author Azzam Haidar
 * @date 2010-11-15
 * @generated d Tue Jan  7 11:44:39 2014
 *
 **/
#ifndef _PLASMA_CORE_DBLAS_H_
#define _PLASMA_CORE_DBLAS_H_

#define REAL

#ifdef __cplusplus
extern "C" {
#endif
#include "plasma.h"

/** ****************************************************************************
 *  Declarations of serial kernels - alphabetical order
 **/
int  CORE_dgeqrt(int M, int N, int IB,
                 double *A, int LDA,
                 double *T, int LDT,
                 double *TAU, double *WORK);
int  CORE_dgetrf_rectil(const PLASMA_desc A, int *IPIV, int *info);
int  CORE_dlaswp_ontile( PLASMA_desc descA, int i1, int i2, const int *ipiv, int inc);
int CORE_dpamm(int op, PLASMA_enum side, PLASMA_enum storev,
               int M, int N, int K, int L,
               const double *A1, int LDA1,
                     double *A2, int LDA2,
               const double *V, int LDV,
                     double *W, int LDW);
int  CORE_dparfb(PLASMA_enum side, PLASMA_enum trans, PLASMA_enum direct, PLASMA_enum storev,
                 int M1, int N1, int M2, int N2, int K, int L,
                       double *A1, int LDA1,
                       double *A2, int LDA2,
                 const double *V, int LDV,
                 const double *T, int LDT,
                       double *WORK, int LDWORK);
void CORE_dplgsy(double bump, int m, int n, double *A, int lda,
                 int bigM, int m0, int n0, unsigned long long int seed );
void CORE_dplrnt(int m, int n, double *A, int lda,
                 int bigM, int m0, int n0, unsigned long long int seed );
int  CORE_dswptr_ontile(PLASMA_desc descA, int i1, int i2, const int *ipiv, int inc,
                        const double *Akk, int ldak);
int  CORE_dtsmqr(PLASMA_enum side, PLASMA_enum trans,
                 int M1, int N1, int M2, int N2, int K, int IB,
                 double *A1, int LDA1,
                 double *A2, int LDA2,
                 const double *V, int LDV,
                 const double *T, int LDT,
                 double *WORK, int LDWORK);
int  CORE_dtsqrt(int M, int N, int IB,
                 double *A1, int LDA1,
                 double *A2, int LDA2,
                 double *T, int LDT,
                 double *TAU, double *WORK);
int  CORE_dormqr(PLASMA_enum side, PLASMA_enum trans,
                 int M, int N, int K, int IB,
                 const double *V, int LDV,
                 const double *T, int LDT,
                 double *C, int LDC,
                 double *WORK, int LDWORK);


#ifdef __cplusplus
}
#endif

#undef COMPLEX

#endif
