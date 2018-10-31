/**
 *
 * @file pdormqr.c
 *
 *  PLASMA auxiliary routines
 *  PLASMA is a software package provided by Univ. of Tennessee,
 *  Univ. of California Berkeley and Univ. of Colorado Denver
 *
 * @version 2.6.0
 * @author Hatem Ltaief
 * @author Jakub Kurzak
 * @author Mathieu Faverge
 * @author Azzam Haidar
 * @date 2010-11-15
 * @generated d Tue Jan  7 11:45:11 2014
 *
 **/
#include "common.h"
#include <alloca.h>

#define A(m,n) BLKADDR(A, double, m, n)
#define B(m,n) BLKADDR(B, double, m, n)
#define T(m,n) BLKADDR(T, double, m, n)

/***************************************************************************//**
 *  Parallel application of Q using tile V - QR factorization - dynamic scheduling
 **/
void plasma_pdormqr_quark(PLASMA_enum side, PLASMA_enum trans,
                          PLASMA_desc A, PLASMA_desc B, PLASMA_desc T, int ib)
{
    int k, m, n;
    int ldak, ldbk, ldam, ldan, ldbm;
    int tempkm, tempnn, tempkmin, tempmm, tempkn;
    int minMT, minM;

    if (A.m > A.n) {
        minM  = A.n;
        minMT = A.nt;
    } else {
        minM  = A.m;
        minMT = A.mt;
    }

    double *work = (double *)alloca(sizeof(double) * T.nb * ib);
    /*
     *  PlasmaLeft / PlasmaTrans
     */
    if (side == PlasmaLeft ) {
        if (trans == PlasmaTrans) {
            for (k = 0; k < minMT; k++) {
                tempkm   = k == B.mt-1 ? B.m-k*B.mb : B.mb;
                tempkmin = k == minMT-1 ? minM-k*A.nb : A.nb;
                ldak = BLKLDD(A, k);
                ldbk = BLKLDD(B, k);
                for (n = 0; n < B.nt; n++) {
                    tempnn = n == B.nt-1 ? B.n-n*B.nb : B.nb;
                    double *dA = A(k, k);
                    double *dT = T(k, k);
                    double *dB = B(k, n);
                    {
                        CORE_dormqr(side, trans, tempkm, tempnn, tempkmin, ib,
                                dA, ldak,
                                dT, T.mb,
                                dB, ldbk, work, T.nb);
                    }
                }
                for (m = k+1; m < B.mt; m++) {
                    tempmm = m == B.mt-1 ? B.m-m*B.mb : B.mb;
                    ldam = BLKLDD(A, m);
                    ldbm = BLKLDD(B, m);
                    for (n = 0; n < B.nt; n++) {
                        tempnn = n == B.nt-1 ? B.n-n*B.nb : B.nb;
                        double *dA = B(k, n);
                        double *dB = B(m, n);
                        double *dV = A(m, k);
                        double *dT = T(m, k);
                        {
                            CORE_dtsmqr(side, trans,
                                    B.mb, tempnn, tempmm, tempnn, tempkmin, ib,
                                    dA, ldbk,
                                    dB, ldbm,
                                    dV, ldam,
                                    dT, T.mb, work, (side == PlasmaLeft)?ib:T.nb);
                        }
                    }
                }
            }
        }
        /*
         *  PlasmaLeft / PlasmaNoTrans
         */
        else {
            for (k = minMT-1; k >= 0; k--) {
                tempkm = k == B.mt-1 ? B.m-k*B.mb : B.mb;
                tempkmin = k == minMT-1 ? minM-k*A.nb : A.nb;
                ldak = BLKLDD(A, k);
                ldbk = BLKLDD(B, k);
                for (m = B.mt-1; m > k; m--) {
                    tempmm = m == B.mt-1 ? B.m-m*B.mb : B.mb;
                    ldam = BLKLDD(A, m);
                    ldbm = BLKLDD(B, m);
                    for (n = 0; n < B.nt; n++) {
                        tempnn = n == B.nt-1 ? B.n-n*B.nb : B.nb;
                        double *dA = B(k, n);
                        double *dB = B(m, n);
                        double *dV = A(m, k);
                        double *dT = T(m, k);
                        {
                            CORE_dtsmqr(side, trans,
                                    B.mb, tempnn, tempmm, tempnn, tempkmin, ib,
                                    dA, ldbk,
                                    dB, ldbm,
                                    dV, ldam,
                                    dT, T.mb, work, (side == PlasmaLeft)?ib:T.nb);
                        }
                    }
                }
                for (n = 0; n < B.nt; n++) {
                    tempnn = n == B.nt-1 ? B.n-n*B.nb : B.nb;
                    double *dA = A(k, k);
                    double *dT = T(k, k);
                    double *dB = B(k, n);
                    {
                        CORE_dormqr(side, trans, tempkm, tempnn, tempkmin, ib,
                                dA, ldak,
                                dT, T.mb,
                                dB, ldbk, work, T.nb);
                    }
                }
            }
        }
    }
    /*
     *  PlasmaRight / PlasmaTrans
     */
    else {
        if (trans == PlasmaTrans) {
            for (k = minMT-1; k >= 0; k--) {
                tempkn = k == B.nt-1 ? B.n-k*B.nb : B.nb;
                tempkmin = k == minMT-1 ? minM-k*A.nb : A.nb;
                ldak = BLKLDD(A, k);
                ldbk = BLKLDD(B, k);
                for (n = B.nt-1; n > k; n--) {
                    tempnn = n == B.nt-1 ? B.n-n*B.nb : B.nb;
                    ldan = BLKLDD(A, n);
                    for (m = 0; m < B.mt; m++) {
                        tempmm = m == B.mt-1 ? B.m-m*B.mb : B.mb;
                        ldbm = BLKLDD(B, m);
                        double *dA = B(m, k);
                        double *dB = B(m, n);
                        double *dV = A(n, k);
                        double *dT = T(n, k);
                        {
                            CORE_dtsmqr(side, trans,
                                    tempmm, B.nb, tempmm, tempnn, tempkmin, ib,
                                    dA, ldbm,
                                    dB, ldbm,
                                    dV, ldan,
                                    dT, T.mb, work, (side == PlasmaLeft)?ib:T.nb);
                        }
                    }
                }
                for (m = 0; m < B.mt; m++) {
                    tempmm = m == B.mt-1 ? B.m-m*B.mb : B.mb;
                    ldbm = BLKLDD(B, m);
                    double *dA = A(k, k);
                    double *dT = T(k, k);
                    double *dB = B(m, k);
                    {
                        CORE_dormqr(side, trans, tempmm, tempkn, tempkmin, ib,
                                dA, ldak,
                                dT, T.mb,
                                dB, ldbm, work, T.nb);
                    }
                }
            }
        }
        /*
         *  PlasmaRight / PlasmaNoTrans
         */
        else {
            for (k = 0; k < minMT; k++) {
                tempkn   = k == B.nt-1 ? B.n-k*B.nb : B.nb;
                tempkmin = k == minMT-1 ? minM-k*A.nb : A.nb;
                ldak = BLKLDD(A, k); 
                for (m = 0; m < B.mt; m++) {
                    tempmm = m == B.mt-1 ? B.m-m*B.mb : B.mb;
                    ldbm = BLKLDD(B, m);
                    double *dA = A(k, k);
                    double *dT = T(k, k);
                    double *dB = B(m, k);
                    {
                        CORE_dormqr(side, trans, tempmm, tempkn, tempkmin, ib,
                                dA, ldak,
                                dT, T.mb,
                                dB, ldbm, work, T.nb);
                    }
                }
                for (n = k+1; n < B.nt; n++) {
                    tempnn = n == B.nt-1 ? B.n-n*B.nb : B.nb;
                    ldan = BLKLDD(A, n);
                    for (m = 0; m < B.mt; m++) {
                        tempmm = m == B.mt-1 ? B.m-m*B.mb : B.mb;
                        ldbm = BLKLDD(B, m);
                        double *dA = B(m, k);
                        double *dB = B(m, n);
                        double *dV = A(n, k);
                        double *dT = T(n, k);
                        {
                            CORE_dtsmqr(side, trans,
                                    tempmm, B.nb, tempmm, tempnn, tempkmin, ib,
                                    dA, ldbm,
                                    dB, ldbm,
                                    dV, ldan,
                                    dT, T.mb, work, (side == PlasmaLeft)?ib:T.nb);
                        }
                    }
                }
            }
        }
    }
}
