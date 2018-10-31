/**
 *
 * @file dgetrs.c
 *
 *  PLASMA computational routines
 *  PLASMA is a software package provided by Univ. of Tennessee,
 *  Univ. of California Berkeley and Univ. of Colorado Denver
 *
 * @version 2.6.0
 * @author Jakub Kurzak
 * @author Mathieu Faverge
 * @date 2010-11-15
 * @generated d Tue Jan  7 11:45:07 2014
 *
 **/
#include "common.h"

/***************************************************************************//**
 *
 * @ingroup double_Tile
 *
 *  PLASMA_dgetrs_Tile- Solves a system of linear equations using previously
 *  computed LU factorization.
 *  Non-blocking equivalent of PLASMA_dgetrs_Tile().
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
 * @sa PLASMA_dgetrs
 * @sa PLASMA_dgetrs_Tile
 * @sa PLASMA_cgetrs_Tile
 * @sa PLASMA_dgetrs_Tile
 * @sa PLASMA_sgetrs_Tile
 * @sa PLASMA_dgetrf_Tile
 *
 ******************************************************************************/
int PLASMA_dgetrs_Tile(PLASMA_enum trans, PLASMA_desc *A, const int *IPIV, PLASMA_desc *B)
{
    PLASMA_desc descA;
    PLASMA_desc descB;

        descA = *A;
        descB = *B;

    if ( trans == PlasmaNoTrans )
    {

        /* swap */
        plasma_pdlaswp_quark(descB, IPIV, 1);

        plasma_pdtrsm_quark(PlasmaLeft, PlasmaLower, PlasmaNoTrans, PlasmaUnit,
                            1.0, descA, descB);

        plasma_pdtrsm_quark(PlasmaLeft, PlasmaUpper, PlasmaNoTrans, PlasmaNonUnit,
                            1.0, descA, descB);
    }
    else {
        abort();
    }
    return PLASMA_SUCCESS;
}
