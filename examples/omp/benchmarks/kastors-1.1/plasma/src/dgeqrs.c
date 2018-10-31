/**
 *
 * @file dgeqrs.c
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
 *  PLASMA_dgeqrs_Tile- Computes a minimum-norm solution using the tile
 *  QR factorization.
 *  Non-blocking equivalent of PLASMA_dgeqrs_Tile().
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
 * @sa PLASMA_dgeqrs
 * @sa PLASMA_dgeqrs_Tile
 *
 ******************************************************************************/
int PLASMA_dgeqrs_Tile(PLASMA_desc *A, PLASMA_desc *T, PLASMA_desc *B, int ib)
{
    PLASMA_desc descA;
    PLASMA_desc descT;
    PLASMA_desc descB;
    descA = *A;
    descT = *T;
    descB = *B;

    plasma_pdormqr_quark(PlasmaLeft, PlasmaTrans, descA, descB, descT, ib);

    plasma_pdtrsm_quark(PlasmaLeft, PlasmaUpper, PlasmaNoTrans, PlasmaNonUnit,
                        1.0,
                        plasma_desc_submatrix(descA, 0, 0, descA.n, descA.n),
                        plasma_desc_submatrix(descB, 0, 0, descA.n, descB.n));

    return PLASMA_SUCCESS;
}
