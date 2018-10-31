/**
 *
 * @file pdtrsm.c
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
 * @generated d Tue Jan  7 11:45:11 2014
 *
 **/
#include "common.h"

#define A(m,n) BLKADDR(A, double, m, n)
#define B(m,n) BLKADDR(B, double, m, n)

/***************************************************************************//**
 *  Sequential tile triangular solve 
 **/
void plasma_pdtrsm_quark(PLASMA_enum side, PLASMA_enum uplo, PLASMA_enum trans, PLASMA_enum diag,
                         double alpha, PLASMA_desc A, PLASMA_desc B)
{
    int k, m, n;
    int lda, ldb;
    int tempkm, tempmm, tempnn;

    double zone       = (double) 1.0;
    double mzone      = (double)-1.0;
    double lalpha;

    /*
     *  PlasmaLeft / PlasmaUpper / PlasmaNoTrans
     */
    if (side == PlasmaLeft) {
        if (uplo == PlasmaUpper) {
            if (trans == PlasmaNoTrans) {
                for (k = 0; k < B.mt; k++) {
                    tempkm = k == 0 ? B.m-(B.mt-1)*B.mb : B.mb;
                    lda = BLKLDD(A, B.mt-1-k);
                    ldb = BLKLDD(B, B.mt-1-k);
                    lalpha = k == 0 ? alpha : zone;
                    for (n = 0; n < B.nt; n++) {
                        tempnn = n == B.nt-1 ? B.n-n*B.nb : B.nb;
                        double *dA = A(B.mt-1-k, B.mt-1-k);
                        double *dB = B(B.mt-1-k, n);
                        cblas_dtrsm(
                                CblasColMajor,
                                (CBLAS_SIDE)side, (CBLAS_UPLO)uplo,
                                (CBLAS_TRANSPOSE)trans, (CBLAS_DIAG)diag,
                                tempkm, tempnn,
                                lalpha, dA, lda,
                                dB, ldb);
                    }
                    for (m = k+1; m < B.mt; m++) {
                        for (n = 0; n < B.nt; n++) {
                            tempnn = n == B.nt-1 ? B.n-n*B.nb : B.nb;
                            double *dA = A(B.mt-1-m, B.mt-1-k);
                            double *dB = B(B.mt-1-k, n       );
                            double *dC = B(B.mt-1-m, n       );
                            cblas_dgemm(CblasColMajor, (CBLAS_TRANSPOSE)PlasmaNoTrans, (CBLAS_TRANSPOSE)PlasmaNoTrans,
                                    B.mb, tempnn, tempkm,
                                    mzone, dA, A.mb,
                                    dB, ldb,
                                    lalpha, dC, B.mb);
                        }
                    }
                }
            }
            /*
             *  PlasmaLeft / PlasmaUpper / Plasma[Conj]Trans
             */
            else {
                for (k = 0; k < B.mt; k++) {
                    tempkm = k == B.mt-1 ? B.m-k*B.mb : B.mb;
                    lda = BLKLDD(A, k);
                    ldb = BLKLDD(B, k);
                    lalpha = k == 0 ? alpha : zone;
                    for (n = 0; n < B.nt; n++) {
                        tempnn = n == B.nt-1 ? B.n-n*B.nb : B.nb;
                        double *dA = A(k, k);
                        double *dB = B(k, n);
                        cblas_dtrsm(
                                CblasColMajor,
                                (CBLAS_SIDE)side, (CBLAS_UPLO)uplo,
                                (CBLAS_TRANSPOSE)trans, (CBLAS_DIAG)diag,
                                tempkm, tempnn,
                                lalpha, dA, lda,
                                dB, ldb);
                    }
                    for (m = k+1; m < B.mt; m++) {
                        tempmm = m == B.mt-1 ? B.m-m*B.mb : B.mb;
                        ldb = BLKLDD(B, m);
                        for (n = 0; n < B.nt; n++) {
                            tempnn = n == B.nt-1 ? B.n-n*B.nb : B.nb;
                            double *dA = A(k, m);
                            double *dB = B(k, n);
                            double *dC = B(m, n);
                            cblas_dgemm(CblasColMajor, (CBLAS_TRANSPOSE)trans, (CBLAS_TRANSPOSE)PlasmaNoTrans,
                                    tempmm, tempnn, B.mb,
                                    mzone, dA, A.mb,
                                    dB, B.mb,
                                    lalpha, dC, ldb);
                        }
                    }
                }
            }
        }
        /*
         *  PlasmaLeft / PlasmaLower / PlasmaNoTrans
         */
        else {
            if (trans == PlasmaNoTrans) {
                for (k = 0; k < B.mt; k++) {
                    tempkm = k == B.mt-1 ? B.m-k*B.mb : B.mb;
                    lda = BLKLDD(A, k);
                    ldb = BLKLDD(B, k);
                    lalpha = k == 0 ? alpha : zone;
                    for (n = 0; n < B.nt; n++) {
                        tempnn = n == B.nt-1 ? B.n-n*B.nb : B.nb;
                        double *dA = A(k, k);
                        double *dB = B(k, n);
                        cblas_dtrsm(
                                CblasColMajor,
                                (CBLAS_SIDE)side, (CBLAS_UPLO)uplo,
                                (CBLAS_TRANSPOSE)trans, (CBLAS_DIAG)diag,
                                tempkm, tempnn,
                                lalpha, dA, lda,
                                dB, ldb);
                    }
                    for (m = k+1; m < B.mt; m++) {
                        tempmm = m == B.mt-1 ? B.m-m*B.mb : B.mb;
                        lda = BLKLDD(A, m);
                        ldb = BLKLDD(B, m);
                        for (n = 0; n < B.nt; n++) {
                            tempnn = n == B.nt-1 ? B.n-n*B.nb : B.nb;
                            double *dA = A(m, k);
                            double *dB = B(k, n);
                            double *dC = B(m, n);
                            cblas_dgemm(CblasColMajor, (CBLAS_TRANSPOSE)PlasmaNoTrans, (CBLAS_TRANSPOSE)PlasmaNoTrans,
                                    tempmm, tempnn, B.mb,
                                    mzone, dA, lda,
                                    dB, B.mb,
                                    lalpha, dC, ldb);
                        }
                    }
                }
            }
            /*
             *  PlasmaLeft / PlasmaLower / Plasma[Conj]Trans
             */
            else {
                for (k = 0; k < B.mt; k++) {
                    tempkm = k == 0 ? B.m-(B.mt-1)*B.mb : B.mb;
                    lda = BLKLDD(A, B.mt-1-k);
                    ldb = BLKLDD(B, B.mt-1-k);
                    lalpha = k == 0 ? alpha : zone;
                    for (n = 0; n < B.nt; n++) {
                        tempnn = n == B.nt-1 ? B.n-n*B.nb : B.nb;
                        double *dA = A(B.mt-1-k, B.mt-1-k);
                        double *dB = B(B.mt-1-k,        n);
                        cblas_dtrsm(
                                CblasColMajor,
                                (CBLAS_SIDE)side, (CBLAS_UPLO)uplo,
                                (CBLAS_TRANSPOSE)trans, (CBLAS_DIAG)diag,
                                tempkm, tempnn,
                                lalpha, dA, lda,
                                dB, ldb);
                    }
                    for (m = k+1; m < B.mt; m++) {
                        tempmm = m == B.mt-1 ? B.m-m*B.mb : B.mb;
                        for (n = 0; n < B.nt; n++) {
                            tempnn = n == B.nt-1 ? B.n-n*B.nb : B.nb;
                            double *dA = A(B.mt-1-k, B.mt-1-m);
                            double *dB = B(B.mt-1-k, n       );
                            double *dC = B(B.mt-1-m, n       );
                            cblas_dgemm(CblasColMajor, (CBLAS_TRANSPOSE)trans, (CBLAS_TRANSPOSE)PlasmaNoTrans,
                                    B.mb, tempnn, tempkm,
                                    mzone, dA, lda,
                                    dB, ldb,
                                    lalpha, dC, B.mb);
                        }
                    }
                }
            }
        }
    }
    /*
     *  PlasmaRight / PlasmaUpper / PlasmaNoTrans
     */
    else {
        abort();
    }
}
