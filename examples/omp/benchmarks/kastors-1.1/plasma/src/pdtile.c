/**
 *
 * @file dtile.c
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
#include "common.h"
#ifdef USE_MKL
#include <mkl_lapacke.h>
#else
#include <lapacke.h>
#endif
#include "auxiliary.h"
#include "tile.h"
/*#include "quark.h"*/

#define AF77(m, n) &(Af77[ ((int64_t)A.nb*(int64_t)lda*(int64_t)(n)) + (int64_t)(A.mb*(m)) ])
#define ABDL(m, n) BLKADDR(A, double, m, n)

/***************************************************************************//**
 *  Conversion from LAPACK F77 matrix layout to tile layout - dynamic scheduling
 **/
void plasma_pdtile_to_lapack_quark(PLASMA_desc A, double *Af77, int lda)
{
    double *f77;
    double *bdl;
    int X1, Y1;
    int X2, Y2;
    int n, m, ldt;
    for (m = 0; m < A.mt; m++)
    {
        ldt = BLKLDD(A, m);
        for (n = 0; n < A.nt; n++)
        {
            X1 = n == 0 ? A.j%A.nb : 0;
            Y1 = m == 0 ? A.i%A.mb : 0;
            X2 = n == A.nt-1 ? (A.j+A.n-1)%A.nb+1 : A.nb;
            Y2 = m == A.mt-1 ? (A.i+A.m-1)%A.mb+1 : A.mb;

            f77 = AF77(m, n);
            bdl = ABDL(m, n);
            LAPACKE_dlacpy_work(
                LAPACK_COL_MAJOR,
                lapack_const(PlasmaUpperLower),
                (Y2-Y1), (X2-X1),
                &(bdl[X1*lda+Y1]), ldt,
                &(f77[X1*lda+Y1]), lda);
        }
    }
}
