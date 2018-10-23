/**
 *
 * @file dpotrs.c
 *
 *  PLASMA computational routines
 *  PLASMA is a software package provided by Univ. of Tennessee,
 *  Univ. of California Berkeley and Univ. of Colorado Denver
 *
 * @version 2.6.0
 * @author Jakub Kurzak
 * @date 2010-11-15
 * @generated d Tue Jan  7 11:45:07 2014
 *
 **/
#include "common.h"

/***************************************************************************//**
 *
 * @ingroup double_Tile
 *
 *  PLASMA_dpotrs_Tile- Solves a system of linear equations using previously
 *  computed Cholesky factorization.
 *  Non-blocking equivalent of PLASMA_dpotrs_Tile().
 *  May return before the computation is finished.
 *  Allows for pipelining of operations at runtime.
 *
 *******************************************************************************
 *
 * @param[in] sequence
 *          Identifies the sequence of function calls that this call belongs to
 *          (for completion checks and exception handling purposes).
 *
 * @param[out] request
 *          Identifies this function call (for exception handling purposes).
 *
 *******************************************************************************
 *
 * @sa PLASMA_dpotrs
 * @sa PLASMA_dpotrs_Tile
 *
 ******************************************************************************/
int PLASMA_dpotrs_Tile(PLASMA_enum uplo, PLASMA_desc *A, PLASMA_desc *B)
{
    PLASMA_desc descA = *A;
    PLASMA_desc descB = *B;

    plasma_pdtrsm_quark(PlasmaLeft, uplo, uplo == PlasmaUpper ? PlasmaTrans : PlasmaNoTrans,
                        PlasmaNonUnit, 1.0, descA, descB);

    plasma_pdtrsm_quark(PlasmaLeft, uplo, uplo == PlasmaUpper ? PlasmaNoTrans : PlasmaTrans,
                        PlasmaNonUnit, 1.0, descA, descB);

    return PLASMA_SUCCESS;
}
