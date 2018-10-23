/**
 *
 * @file core_dpamm.c
 *
 *  PLASMA core_blas kernel
 *  PLASMA is a software package provided by Univ. of Tennessee,
 *  Univ. of California Berkeley and Univ. of Colorado Denver
 *
 * @version 2.6.0
 * @author Dulceneia Becker
 * @date 2011-06-14
 * @generated d Tue Jan  7 11:44:49 2014
 *
 **/
#ifdef USE_MKL
#include <mkl_cblas.h>
#include <mkl_lapacke.h>
#else
#include <cblas.h>
#include <lapacke.h>
#endif
#include "common.h"

static inline int CORE_dpamm_a2(PLASMA_enum side, PLASMA_enum trans, PLASMA_enum uplo,
                                int M, int N, int K, int L,
                                int vi2, int vi3,
                                      double *A2, int LDA2,
                                const double *V,  int LDV,
                                      double *W,  int LDW);

static inline int CORE_dpamm_w(PLASMA_enum side, PLASMA_enum trans, PLASMA_enum uplo,
                               int M, int N, int K, int L,
                               int vi2, int vi3,
                               const double *A1, int LDA1,
                                     double *A2, int LDA2,
                               const double *V,  int LDV,
                                     double *W,  int LDW);

/***************************************************************************//**
 *
 * @ingroup CORE_double
 *
 *  ZPAMM  performs one of the matrix-matrix operations
 *
 *                    LEFT                      RIGHT
 *     OP PlasmaW  :  W  = A1 + op(V) * A2  or  W  = A1 + A2 * op(V)
 *     OP PlasmaA2 :  A2 = A2 - op(V) * W   or  A2 = A2 - W * op(V)
 *
 *  where  op( V ) is one of
 *
 *     op( V ) = V   or   op( V ) = V**T   or   op( V ) = V**T,
 *
 *  A1, A2 and W are general matrices, and V is:
 *
 *        l = k: rectangle + triangle
 *        l < k: rectangle + trapezoid
 *        l = 0: rectangle
 *
 *  Size of V, both rowwise and columnwise, is:
 *
 *         ----------------------
 *          side   trans    size
 *         ----------------------
 *          left     N     M x K
 *                   T     K x M
 *          right    N     K x N
 *                   T     N x K
 *         ----------------------
 *
 *  LEFT (columnwise and rowwise):
 *
 *              |    K    |                 |         M         |
 *           _  __________   _              _______________        _
 *              |    |    |                 |             | \
 *     V:       |    |    |            V':  |_____________|___\    K
 *              |    |    | M-L             |                  |
 *           M  |    |    |                 |__________________|   _
 *              |____|    |  _
 *              \    |    |                 |    M - L    | L  |
 *                \  |    |  L
 *           _      \|____|  _
 *
 *
 *  RIGHT (columnwise and rowwise):
 *
 *          |         K         |                   |    N    |
 *          _______________        _             _  __________   _
 *          |             | \                       |    |    |
 *     V':  |_____________|___\    N        V:      |    |    |
 *          |                  |                    |    |    | K-L
 *          |__________________|   _             K  |    |    |
 *                                                  |____|    |  _
 *          |    K - L    | L  |                    \    |    |
 *                                                    \  |    |  L
 *                                               _      \|____|  _
 *
 *  Arguments
 *  ==========
 *
 * @param[in] op
 *
 *         OP specifies which operation to perform:
 *
 *         @arg PlasmaW  : W  = A1 + op(V) * A2  or  W  = A1 + A2 * op(V)
 *         @arg PlasmaA2 : A2 = A2 - op(V) * W   or  A2 = A2 - W * op(V)
 *
 * @param[in] side
 *
 *         SIDE specifies whether  op( V ) multiplies A2
 *         or W from the left or right as follows:
 *
 *         @arg PlasmaLeft  : multiply op( V ) from the left
 *                            OP PlasmaW  :  W  = A1 + op(V) * A2
 *                            OP PlasmaA2 :  A2 = A2 - op(V) * W
 *
 *         @arg PlasmaRight : multiply op( V ) from the right
 *                            OP PlasmaW  :  W  = A1 + A2 * op(V)
 *                            OP PlasmaA2 :  A2 = A2 - W * op(V)
 *
 * @param[in] storev
 *
 *         Indicates how the vectors which define the elementary
 *         reflectors are stored in V:
 *
 *         @arg PlasmaColumnwise
 *         @arg PlasmaRowwise
 *
 * @param[in] M
 *         The number of rows of the A1, A2 and W
 *         If SIDE is PlasmaLeft, the number of rows of op( V )
 *
 * @param[in] N
 *         The number of columns of the A1, A2 and W
 *         If SIDE is PlasmaRight, the number of columns of op( V )
 *
 * @param[in] K
 *         If SIDE is PlasmaLeft, the number of columns of op( V )
 *         If SIDE is PlasmaRight, the number of rows of op( V )
 *
 * @param[in] L
 *         The size of the triangular part of V
 *
 * @param[in] A1
 *         On entry, the M-by-N tile A1.
 *
 * @param[in] LDA1
 *         The leading dimension of the array A1. LDA1 >= max(1,M).
 *
 * @param[in,out] A2
 *         On entry, the M-by-N tile A2.
 *         On exit, if OP is PlasmaA2 A2 is overwritten
 *
 * @param[in] LDA2
 *         The leading dimension of the tile A2. LDA2 >= max(1,M).
 *
 * @param[in] V
 *         The matrix V as described above.
 *         If SIDE is PlasmaLeft : op( V ) is M-by-K
 *         If SIDE is PlasmaRight: op( V ) is K-by-N
 *
 * @param[in] LDV
 *         The leading dimension of the array V.
 *
 * @param[in,out] W
 *         On entry, the M-by-N matrix W.
 *         On exit, W is overwritten either if OP is PlasmaA2 or PlasmaW.
 *         If OP is PlasmaA2, W is an input and is used as a workspace.
 *
 * @param[in] LDW
 *         The leading dimension of array WORK.
 *
 *******************************************************************************
 *
 * @return
 *          \retval PLASMA_SUCCESS successful exit
 *          \retval <0 if -i, the i-th argument had an illegal value
 *
 ******************************************************************************/
int
CORE_dpamm(int op, PLASMA_enum side, PLASMA_enum storev,
           int M, int N, int K, int L,
           const double *A1, int LDA1,
                 double *A2, int LDA2,
           const double *V, int LDV,
                 double *W, int LDW)
{


    int vi2, vi3, uplo, trans, info;

    /* Check input arguments */
    if ((op != PlasmaW) && (op != PlasmaA2)) {
        coreblas_error(1, "Illegal value of op");
        return -1;
    }
    if ((side != PlasmaLeft) && (side != PlasmaRight)) {
        coreblas_error(2, "Illegal value of side");
        return -2;
    }
    if ((storev != PlasmaColumnwise) && (storev != PlasmaRowwise)) {
        coreblas_error(3, "Illegal value of storev");
        return -3;
    }
    if (M < 0) {
        coreblas_error(4, "Illegal value of M");
        return -4;
    }
    if (N < 0) {
        coreblas_error(5, "Illegal value of N");
        return -5;
    }
    if (K < 0) {
        coreblas_error(6, "Illegal value of K");
        return -6;
    }
    if (L < 0) {
        coreblas_error(7, "Illegal value of L");
        return -7;
    }
    if (LDA1 < 0) {
        coreblas_error(9, "Illegal value of LDA1");
        return -9;
    }
    if (LDA2 < 0) {
        coreblas_error(11, "Illegal value of LDA2");
        return -11;
    }
    if (LDV < 0) {
        coreblas_error(13, "Illegal value of LDV");
        return -13;
    }
    if (LDW < 0) {
        coreblas_error(15, "Illegal value of LDW");
        return -15;
    }

    /* Quick return */
    if ((M == 0) || (N == 0) || (K == 0))
        return PLASMA_SUCCESS;

    /*
     * TRANS is set as:
     *
     *        -------------------------------------
     *         side   direct     PlasmaW  PlasmaA2
     *        -------------------------------------
     *         left   colwise       T        N
     *                rowwise       N        T
     *         right  colwise       N        T
     *                rowwise       T        N
     *        -------------------------------------
     */

    /* Columnwise*/
    if (storev == PlasmaColumnwise) {
        uplo = CblasUpper;
        if (side == PlasmaLeft) {
            trans = op == PlasmaA2 ? PlasmaNoTrans : PlasmaTrans;
            vi2 = trans == PlasmaNoTrans ? M - L : K - L;
        }
        else {
            trans = op == PlasmaW ? PlasmaNoTrans : PlasmaTrans;
            vi2 = trans == PlasmaNoTrans ? K - L : N - L;
        }
        vi3 = LDV * L;
    }

    /* Rowwise */
    else {
        uplo = CblasLower;
        if (side == PlasmaLeft) {
            trans = op == PlasmaW ? PlasmaNoTrans : PlasmaTrans;
            vi2 = trans == PlasmaNoTrans ? K - L : M - L;
        }
        else {
            trans = op == PlasmaA2 ? PlasmaNoTrans : PlasmaTrans;
            vi2 = trans == PlasmaNoTrans ? N - L : K - L;
        }
        vi2 *= LDV;
        vi3  = L;
    }

    /**/
    if (op==PlasmaW) {
        info = CORE_dpamm_w(
                side, trans, uplo, M, N, K, L, vi2, vi3,
                A1, LDA1, A2, LDA2, V, LDV, W, LDW);
        if (info != 0)
            return info;
    } else if (op==PlasmaA2) {
        info = CORE_dpamm_a2(
                side, trans, uplo, M, N, K, L, vi2, vi3,
                A2, LDA2, V, LDV, W, LDW);
        if (info != 0)
            return info;
    }

    return PLASMA_SUCCESS;
}

/***************************************************************************/
static inline int
CORE_dpamm_w(PLASMA_enum side, PLASMA_enum trans, PLASMA_enum uplo,
             int M, int N, int K, int L,
             int vi2, int vi3,
             const double *A1, int LDA1,
                   double *A2, int LDA2,
             const double *V, int LDV,
                   double *W, int LDW)
{

   /*
    * W = A1 + op(V) * A2  or  W = A1 + A2 * op(V)
    */

    int j;
    static double zone  =  1.0;
    static double zzero =  0.0;

    if (side == PlasmaLeft) {

        if (((trans == PlasmaTrans) && (uplo == CblasUpper)) ||
            ((trans == PlasmaNoTrans) && (uplo == CblasLower))) {

            /*
             * W = A1 + V' * A2
             */

            /* W = A2_2 */
            LAPACKE_dlacpy_work(LAPACK_COL_MAJOR,
                lapack_const(PlasmaUpperLower),
                L, N,
                &A2[K-L], LDA2, W, LDW);

            /* W = V_2' * W + V_1' * A2_1 (ge+tr, top L rows of V') */
            if (L > 0) {
                /* W = V_2' * W */
                cblas_dtrmm(
                    CblasColMajor, CblasLeft, (CBLAS_UPLO)uplo,
                    (CBLAS_TRANSPOSE)trans, CblasNonUnit, L, N,
                    (zone), &V[vi2], LDV,
                    W, LDW);

                /* W = W + V_1' * A2_1 */
                if (K > L) {
                    cblas_dgemm(
                        CblasColMajor, (CBLAS_TRANSPOSE)trans, CblasNoTrans,
                        L, N, K-L,
                        (zone), V, LDV,
                        A2, LDA2,
                        (zone), W, LDW);
                }
            }

            /* W_2 = V_3' * A2: (ge, bottom M-L rows of V') */
            if (M > L) {
                cblas_dgemm(
                    CblasColMajor, (CBLAS_TRANSPOSE)trans, CblasNoTrans,
                    (M-L), N, K,
                    (zone), &V[vi3], LDV,
                    A2, LDA2,
                    (zzero), &W[L], LDW);
            }

            /* W = A1 + W */
            for(j = 0; j < N; j++) {
                cblas_daxpy(
                        M, (zone),
                        &A1[LDA1*j], 1,
                        &W[LDW*j], 1);
            }
        }
        else {
            printf("Left Upper/NoTrans & Lower/ConjTrans not implemented yet\n");
            return PLASMA_ERR_NOT_SUPPORTED;

        }
    }
    else { //side right

        if (((trans == PlasmaTrans) && (uplo == CblasUpper)) ||
            ((trans == PlasmaNoTrans) && (uplo == CblasLower))) {
            printf("Right Upper/ConjTrans & Lower/NoTrans not implemented yet\n");
            return PLASMA_ERR_NOT_SUPPORTED;

        }
        else {

            /*
             * W = A1 + A2 * V
             */

            if (L > 0) {

                /* W = A2_2 */
                LAPACKE_dlacpy_work(LAPACK_COL_MAJOR,
                    lapack_const(PlasmaUpperLower),
                    M, L,
                    &A2[LDA2*(K-L)], LDA2, W, LDW);

                /* W = W * V_2 --> W = A2_2 * V_2 */
                cblas_dtrmm(
                    CblasColMajor, CblasRight, (CBLAS_UPLO)uplo,
                    (CBLAS_TRANSPOSE)trans, CblasNonUnit, M, L,
                    (zone), &V[vi2], LDV,
                    W, LDW);

                /* W = W + A2_1 * V_1 */
                if (K > L) {
                    cblas_dgemm(
                        CblasColMajor, CblasNoTrans, (CBLAS_TRANSPOSE)trans,
                        M, L, K-L,
                        (zone), A2, LDA2,
                        V, LDV,
                        (zone), W, LDW);
                }

            }

            /* W = W + A2 * V_3 */
            if (N > L) {
                cblas_dgemm(
                    CblasColMajor, CblasNoTrans, (CBLAS_TRANSPOSE)trans,
                    M, N-L, K,
                    (zone), A2, LDA2,
                    &V[vi3], LDV,
                    (zzero), &W[LDW*L], LDW);
            }

            /* W = A1 + W */
            for (j = 0; j < N; j++) {
                cblas_daxpy(
                        M, (zone),
                        &A1[LDA1*j], 1,
                        &W[LDW*j], 1);
            }
        }
    }

    return PLASMA_SUCCESS;
}

/***************************************************************************/
static inline int
CORE_dpamm_a2(PLASMA_enum side, PLASMA_enum trans, PLASMA_enum uplo,
              int M, int N, int K, int L,
              int vi2, int vi3,
                    double *A2, int LDA2,
              const double *V, int LDV,
                    double *W, int LDW)
{

   /*
    *  A2 = A2 + op(V) * W  or  A2 = A2 + W * op(V)
    */

    int j;
    static double zone  =  1.0;
    static double mzone  =  -1.0;

    if (side == PlasmaLeft) {

        if (((trans == PlasmaTrans) && (uplo == CblasUpper)) ||
            ((trans == PlasmaNoTrans) && (uplo == CblasLower))) {

            printf("Left Upper/ConjTrans & Lower/NoTrans not implemented yet\n");
            return PLASMA_ERR_NOT_SUPPORTED;

        }
        else {  //trans

            /*
             * A2 = A2 - V * W
             */

            /* A2_1 = A2_1 - V_1  * W_1 */
            if (M > L) {
                cblas_dgemm(
                    CblasColMajor, (CBLAS_TRANSPOSE)trans, CblasNoTrans,
                    M-L, N, L,
                    (mzone), V, LDV,
                    W, LDW,
                    (zone), A2, LDA2);
            }

            /* W_1 = V_2 * W_1 */
            cblas_dtrmm(
                CblasColMajor, CblasLeft, (CBLAS_UPLO)uplo,
                (CBLAS_TRANSPOSE)trans, CblasNonUnit, L, N,
                (zone), &V[vi2], LDV,
                W, LDW);

            /* A2_2 = A2_2 - W_1 */
            for(j = 0; j < N; j++) {
                cblas_daxpy(
                    L, (mzone),
                    &W[LDW*j], 1,
                    &A2[LDA2*j+(M-L)], 1);
            }

            /* A2 = A2 - V_3  * W_2 */
            if (K > L) {
                cblas_dgemm(
                    CblasColMajor, (CBLAS_TRANSPOSE)trans, CblasNoTrans,
                    M, N, (K-L),
                    (mzone), &V[vi3], LDV,
                    &W[L], LDW,
                    (zone), A2, LDA2);
            }

        }
    }
    else { //side right

        if (((trans == PlasmaTrans) && (uplo == CblasUpper)) ||
            ((trans == PlasmaNoTrans) && (uplo == CblasLower))) {

            /*
             * A2 = A2 - W * V'
             */

            /* A2 = A2 - W_2 * V_3' */
            if (K > L) {
                cblas_dgemm(
                    CblasColMajor, CblasNoTrans, (CBLAS_TRANSPOSE)trans,
                    M, N, K-L,
                    (mzone), &W[LDW*L], LDW,
                    &V[vi3], LDV,
                    (zone), A2, LDA2);
            }

            /* A2_1 = A2_1 - W_1 * V_1' */
            if (N > L) {
                cblas_dgemm(
                    CblasColMajor, CblasNoTrans, (CBLAS_TRANSPOSE)trans,
                    M, N-L, L,
                    (mzone), W, LDW,
                    V, LDV,
                    (zone), A2, LDA2);
            }

            /* A2_2 =  A2_2 -  W_1 * V_2' */
            if (L > 0) {
                cblas_dtrmm(
                    CblasColMajor, CblasRight, (CBLAS_UPLO)uplo,
                    (CBLAS_TRANSPOSE)trans, CblasNonUnit, M, L,
                    (mzone), &V[vi2], LDV,
                    W, LDW);

                for (j = 0; j < L; j++) {
                    cblas_daxpy(
                        M, (zone),
                        &W[LDW*j], 1,
                        &A2[LDA2*(N-L+j)], 1);
                }
            }

        }
        else {
            printf("Right Upper/NoTrans & Lower/ConjTrans not implemented yet\n");
            return PLASMA_ERR_NOT_SUPPORTED;
        }
    }

    return PLASMA_SUCCESS;
}
