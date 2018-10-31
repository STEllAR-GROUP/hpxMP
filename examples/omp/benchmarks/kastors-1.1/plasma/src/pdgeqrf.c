/**
 *
 * @file pdgeqrf.c
 *
 *  PLASMA auxiliary routines
 *  PLASMA is a software package provided by Univ. of Tennessee,
 *  Univ. of California Berkeley and Univ. of Colorado Denver
 *
 * @version 2.6.0
 * @author Jakub Kurzak
 * @author Hatem Ltaief
 * @author Mathieu Faverge
 * @date 2010-11-15
 * @generated d Tue Jan  7 11:45:10 2014
 *
 **/
#include "common.h"
#if defined(USE_OMPEXT)
#include <omp_ext.h>
#endif

#define A(m,n) BLKADDR(A, double, m, n)
#define T(m,n) BLKADDR(T, double, m, n)

/***************************************************************************//**
 *  Parallel tile QR factorization - dynamic scheduling
 **/
void plasma_pdgeqrf_quark(PLASMA_desc A, PLASMA_desc T, int ib)
{

    int k, m, n;
    int ldak, ldam;
    int tempkm, tempkn, tempnn, tempmm;

    for (k = 0; k < min(A.mt, A.nt); k++) {
        tempkm = k == A.mt-1 ? A.m-k*A.mb : A.mb;
        tempkn = k == A.nt-1 ? A.n-k*A.nb : A.nb;
        ldak = BLKLDD(A, k);
        double *dA = A(k, k);
        double *dT = T(k, k);
#if defined(USE_OMPEXT)
omp_set_task_priority(1);
#endif
#pragma omp task depend(inout: dA[0:T.nb*T.nb]) depend(out:dT[0:ib*T.nb])
        {
            double tau[T.nb];
            double work[ib * T.nb];
            CORE_dgeqrt(tempkm, tempkn, ib, dA, ldak, dT, T.mb, &tau[0], &work[0]);
        }

        for (n = k+1; n < A.nt; n++) {
            tempnn = n == A.nt-1 ? A.n-n*A.nb : A.nb;
            double *dA = A(k, k);
            double *dT = T(k, k);
            double *dC = A(k, n);
#pragma omp task depend(in: dA[0:T.nb*T.nb], dT[0:ib*T.nb]) depend(inout:dC[0:T.nb*T.nb])
            {
                double work[T.nb * ib];
                CORE_dormqr(PlasmaLeft, PlasmaTrans,
                        tempkm, tempnn, tempkm, ib,
                        dA, ldak,
                        dT, T.mb,
                        dC, ldak,
                        &work[0], T.nb);
            }
        }
        for (m = k+1; m < A.mt; m++) {
            tempmm = m == A.mt-1 ? A.m-m*A.mb : A.mb;
            ldam = BLKLDD(A, m);
            double *dA = A(k, k);
            double *dB = A(m, k);
            double *dT = T(m, k);
#pragma omp task depend(inout:dA[0:T.nb*T.nb], dB[0:T.nb*T.nb]) depend(out:dT[0:ib*T.nb])
            {
                double tau[T.nb];
                double work[ib * T.nb];
                CORE_dtsqrt(tempmm, tempkn, ib,
                        dA, ldak,
                        dB, ldam,
                        dT, T.mb, &tau[0], &work[0]);
            }

            for (n = k+1; n < A.nt; n++) {
                tempnn = n == A.nt-1 ? A.n-n*A.nb : A.nb;
                double *dA = A(k, n);
                double *dB = A(m, n);
                double *dV = A(m, k);
                double *dT = T(m, k);
#pragma omp task depend(inout:dA[0:T.nb*T.nb], dB[0:T.nb*T.nb]) depend(in:dV[0:T.nb*T.nb], dT[0:ib*T.nb])
                {
                    double work[ib * T.nb];
                    CORE_dtsmqr(PlasmaLeft, PlasmaTrans,
                            A.mb, tempnn, tempmm, tempnn, A.nb, ib,
                            dA, ldak,
                            dB, ldam,
                            dV, ldam,
                            dT, T.mb, &work[0], ib);
                }
            }
        }
    }
}
