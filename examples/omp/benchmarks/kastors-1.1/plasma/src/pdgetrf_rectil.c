/**
 *
 * @file pdgetrf_rectil.c
 *
 *  PLASMA auxiliary routines
 *  PLASMA is a software package provided by Univ. of Tennessee,
 *  Univ. of California Berkeley and Univ. of Colorado Denver
 *
 * LU with Partial pivoting.
 *
 * @version 2.6.0
 * @author Mathieu Faverge
 * @author Hatem Ltaief
 * @date 2009-11-15
 *
 * @generated d Tue Jan  7 11:45:13 2014
 *
 **/
#include "common.h"

void CORE_dgetrf_rectil_init(void);

#define PARALLEL_KERNEL
#define A(m,n) BLKADDR(A, double, m, n)
#define IPIV(k) &(IPIV[(int64_t)A.mb*(int64_t)(k)])


/***************************************************************************//**
 *  Parallel tile LU factorization - dynamic scheduling - Right looking
 **/
void plasma_pdgetrf_rectil_quark(PLASMA_desc A, int *IPIV)
{
    int k, m, n;
    int tempk, tempm, tempkm, tempkn, tempmm, tempnn;
    int ldak, ldam;

    double zone  = (double)1.0;
    double mzone = (double)-1.0;

    void * fakedep;
    /* How many threads per panel? Probably needs to be adjusted during factorization. */

    CORE_dgetrf_rectil_init();

    for (k = 0; k < min(A.mt, A.nt); k++)
    {
        tempk  = k * A.mb;
        tempm  = A.m - tempk;
        tempkm = k == A.mt-1 ? tempm      : A.mb;
        tempkn = k == A.nt-1 ? A.n-k*A.nb : A.nb;
        ldak = BLKLDD(A, k);

        double *dA = A(k, k);
        int *dB = IPIV(k);
        PLASMA_desc pDesc = plasma_desc_submatrix(A, tempk, k*A.nb, tempm, tempkn);
#pragma omp task depend(inout:dA[0:A.mb*A.nb]) depend(out:dB[0:pDesc.n])
        {
            int info[3];
            info[1] = 0;
            info[2] = 1;

            CORE_dgetrf_rectil( pDesc, dB, info );
        }

        /*
         * Update the trailing submatrix
         */
        fakedep = (void *)(intptr_t)(k+1);
        for (n = k+1; n < A.nt; n++)
        {
            /*
             * Apply row interchange after the panel (work on the panel)
             */
            tempnn = n == A.nt-1 ? A.n-n*A.nb : A.nb;
            PLASMA_desc descA = plasma_desc_submatrix(A, tempk, n*A.nb, tempm, tempnn);
            double *dA = A(k, n);
            double *dB = A(k, k);
            int *dipiv = IPIV(k);
#pragma omp task depend(inout:dA[0:1]) depend(in:dB[0:ldak], dipiv[0:tempkm])
            CORE_dswptr_ontile(descA, 1, tempkm, dipiv, 1, dB, ldak);

            m = k+1;
            if ( m < A.mt ) {
                tempmm = m == A.mt-1 ? A.m-m*A.mb : A.mb;
                ldam = BLKLDD(A, m);

                double *dA = A(m , k);
                double *dB = A(k , n);
                double *dC = A(m , n);
#pragma omp task depend(in:dA[0:A.mb*A.mb], dB[0:A.mb*A.mb]) depend(inout:dC[0:A.mb*A.mb])
                cblas_dgemm(CblasColMajor, (CBLAS_TRANSPOSE)PlasmaNoTrans, (CBLAS_TRANSPOSE)PlasmaNoTrans,
                        tempmm, tempnn, A.nb,
                        mzone, dA, ldam,
                        dB, ldak,
                        zone, dC, ldam);

                for (m = k+2; m < A.mt; m++)
                {
                    tempmm = m == A.mt-1 ? A.m-m*A.mb : A.mb;
                    ldam = BLKLDD(A, m);

                    double *dA = A(m , k);
                    double *dB = A(k , n);
                    double *dC = A(m , n);
                    double *fake1 = A(k+1, n);
                    double *fake2 = (double *)fakedep;
#if defined(KLANG_VERSION) && defined(KASTOR_USE_CW)
#warning "KLANG EXTENSION USED"
#pragma omp task depend(in:dA[0:A.mb*A.mb], dB[0:A.mb*A.mb], fake2[0:1]) depend(inout:dC[0:A.mb*A.mb]), depend(cw:fake1[0:A.mb*A.nb])
                        cblas_dgemm(CblasColMajor, (CBLAS_TRANSPOSE)PlasmaNoTrans, (CBLAS_TRANSPOSE)PlasmaNoTrans,
                                tempmm, tempnn, A.nb,
                                mzone, dA, ldam,
                                dB, ldak,
                                zone, dC, ldam);
#else
#pragma omp task depend(in:dA[0:A.mb*A.mb], dB[0:A.mb*A.mb], fake2[0:1]) depend(inout:dC[0:A.mb*A.mb], fake1[0:A.mb*A.nb])
                        cblas_dgemm(CblasColMajor, (CBLAS_TRANSPOSE)PlasmaNoTrans, (CBLAS_TRANSPOSE)PlasmaNoTrans,
                                tempmm, tempnn, A.nb,
                                mzone, dA, ldam,
                                dB, ldak,
                                zone, dC, ldam);
#endif
                }
            }
        }
    }

    for (k = 0; k < min(A.mt, A.nt); k++)
    {
        int mintmp;
        tempk  = k * A.mb;
        tempm  = A.m - tempk;
        tempkm = k == A.mt-1 ? tempm : A.mb;
        tempkn = k == A.nt-1 ? A.n - k * A.nb : A.nb;
        mintmp = min(tempkm, tempkn);
        ldak = BLKLDD(A, k);

        /*
         * Apply row interchange behind the panel (work on the panel)
         */
        fakedep = (void*)(intptr_t)k;
        for (n = 0; n < k; n++)
        {
            tempnn = n == A.nt-1 ? A.n-n*A.nb : A.nb;
            double *Aij = A(k, n);
            double *prevSwap = A(k-1, n);
            int *dipiv = IPIV(k);
            PLASMA_desc descA = plasma_desc_submatrix(A, tempk, n*A.nb, tempm, tempnn);
#if defined(KLANG_VERSION) && defined(KASTOR_USE_CW)
#warning "KLANG EXTENSION USED"
#pragma omp task depend(inout:Aij[0:1]) depend(cw:fakedep) depend(in:dipiv[0:mintmp], prevSwap[0:A.lm*A.nb])
            CORE_dlaswp_ontile(descA, 1, mintmp, dipiv, 1);
#else
#pragma omp task depend(inout:Aij[0:1],fakedep) depend(in:dipiv[0:mintmp], prevSwap[0:A.lm*A.nb])
            CORE_dlaswp_ontile(descA, 1, mintmp, dipiv, 1);
#endif
        }
    }
}
