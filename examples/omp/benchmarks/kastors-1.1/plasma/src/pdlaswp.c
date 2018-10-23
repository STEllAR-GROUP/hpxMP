/**
 *
 * @file pdlaswp.c
 *
 *  PLASMA auxiliary routines
 *  PLASMA is a software package provided by Univ. of Tennessee,
 *  Univ. of California Berkeley and Univ. of Colorado Denver
 *
 * @version 2.6.0
 * @author Mathieu Faverge
 * @date 2010-11-15
 * @generated d Tue Jan  7 11:45:13 2014
 *
 **/
#include "common.h"

#define B(m, n) BLKADDR(B, double, m, n)
#define IPIV(k) &(IPIV[(int64_t)B.mb*(int64_t)(k)])

/***************************************************************************//**
 *  Parallel tile row interchanges - dynamic scheduling
 **/
void plasma_pdlaswp_quark(PLASMA_desc B, const int *IPIV, int inc)
{
    int m, n;
    int tempi, tempm, tempmm, tempnn;

    if ( inc > 0 )
    {
        for (m = 0; m < B.mt; m++) {
            tempi = m * B.mb;
            tempm = B.m - tempi;
            tempmm = m == B.mt-1 ? tempm : B.mb;

            for (n = 0; n < B.nt; n++) {
                tempnn = n == B.nt-1 ? B.n - n * B.nb : B.nb;
                const int *dipiv = IPIV(m);
                PLASMA_desc descA = plasma_desc_submatrix(B, tempi, n*B.nb, tempm, tempnn);
                CORE_dlaswp_ontile(descA, 1, tempmm, dipiv, inc);
            }
        }
    }
    else
    {
        abort();
    }
}
