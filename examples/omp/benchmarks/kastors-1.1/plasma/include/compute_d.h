/**
 *
 * @file compute_d.h
 *
 *  PLASMA auxiliary routines
 *  PLASMA is a software package provided by Univ. of Tennessee,
 *  Univ. of California Berkeley and Univ. of Colorado Denver
 *
 * @version 2.6.0
 * @author Jakub Kurzak
 * @author Mathieu Faverge
 * @date 2010-11-15
 * @generated d Tue Jan  7 11:45:15 2014
 *
 **/
#include <stdlib.h>

/***************************************************************************//**
 *  Declarations of parallel functions (dynamic scheduling) - alphabetical order
 **/
void plasma_pdgeqrf_quark(PLASMA_desc A, PLASMA_desc T, int ib);
void plasma_pdgetrf_rectil_quark(PLASMA_desc A, int *IPIV);
void plasma_pdlaswp_quark(PLASMA_desc B, const int *IPIV, int inc);
void plasma_pdplgsy_quark(double bump, PLASMA_desc A, unsigned long long int seed);
void plasma_pdpltmg_quark(PLASMA_desc A, unsigned long long int seed);
void plasma_pdpltmg_seq(PLASMA_desc A, unsigned long long int seed);
void plasma_pdpotrf_quark(PLASMA_enum uplo, PLASMA_desc A);
void plasma_pdtrsm_quark(PLASMA_enum side, PLASMA_enum uplo, PLASMA_enum transA, PLASMA_enum diag, double alpha, PLASMA_desc A, PLASMA_desc B);
void plasma_pdormqr_quark(PLASMA_enum side, PLASMA_enum trans, PLASMA_desc A, PLASMA_desc B, PLASMA_desc T, int ib);
