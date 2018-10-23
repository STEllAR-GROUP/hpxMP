/**
 *
 * @file control/descriptor.c
 *
 *  PLASMA auxiliary routines
 *  PLASMA is a software package provided by Univ. of Tennessee,
 *  Univ. of California Berkeley and Univ. of Colorado Denver
 *
 * @version 2.6.0
 * @author Jakub Kurzak
 * @date 2010-11-15
 *
 **/
#include <stdlib.h>
#include <assert.h>
#include "descriptor.h"
#include "auxiliary.h"

/***************************************************************************//**
 *
 **/
int plasma_desc_mat_alloc(PLASMA_desc *desc)
{
    size_t size;

    size = (size_t)desc->lm * (size_t)desc->ln * (size_t)plasma_element_size(desc->dtyp);
    if ((desc->mat = malloc(size)) == NULL) {
        plasma_error("plasma_desc_mat_alloc", "malloc() failed");
        return PLASMA_ERR_OUT_OF_RESOURCES;
    }

    return PLASMA_SUCCESS;
}

/***************************************************************************//**
 *
 * @ingroup Auxiliary
 *
 *  PLASMA_Desc_Create - Create matrix descriptor.
 *
 *******************************************************************************
 *
 * @param[out] desc
 *          On exit, descriptor of the matrix.
 *
 * @param[in] mat
 *          Memory location of the matrix.
 *
 * @param[in] dtyp
 *          Data type of the matrix:
 *          @arg PlasmaRealFloat:     single precision real (S),
 *          @arg PlasmaRealDouble:    double precision real (D),
 *          @arg PlasmaComplexFloat:  single precision complex (C),
 *          @arg PlasmaComplexDouble: double precision complex (Z).
 *
 * @param[in] mb
 *          Number of rows in a tile.
 *
 * @param[in] nb
 *          Number of columns in a tile.
 *
 * @param[in] bsiz
 *          Size in elements (mb*nb).
 *
 * @param[in] lm
 *          Number of rows of the entire matrix.
 *
 * @param[in] ln
 *          Number of columns of the entire matrix.
 *
 * @param[in] i
 *          Row index to the beginning of the submatrix.
 *
 * @param[in] j
 *          Column index to the beginning of the submatrix.
 *
 * @param[in] m
 *          Number of rows of the submatrix.
 *
 * @param[in] n
 *          Number of columns of the submatrix.
 *
 *******************************************************************************
 *
 * @return
 *          \retval PLASMA_SUCCESS successful exit
 *
 ******************************************************************************/
int PLASMA_Desc_Create(PLASMA_desc **desc, void *mat, PLASMA_enum dtyp, int mb, int nb, int bsiz,
                       int lm, int ln, int i, int j, int m, int n)
{
    /* Allocate memory and initialize the descriptor */
    *desc = (PLASMA_desc*)malloc(sizeof(PLASMA_desc));
    **desc = plasma_desc_init(dtyp, mb, nb, bsiz, lm, ln, i, j, m, n);
    (**desc).mat = mat;
    return PLASMA_SUCCESS;
}

/***************************************************************************//**
 *
 * @ingroup Auxiliary
 *
 *  PLASMA_Desc_Destroy - Destroys matrix descriptor.
 *
 *******************************************************************************
 *
 * @param[in] desc
 *          Matrix descriptor.
 *
 *******************************************************************************
 *
 * @return
 *          \retval PLASMA_SUCCESS successful exit
 *
 ******************************************************************************/
int PLASMA_Desc_Destroy(PLASMA_desc **desc)
{
    free(*desc);
    *desc = NULL;
    return PLASMA_SUCCESS;
}


/***************************************************************************//**
 *  Internal static descriptor initializer
 **/
PLASMA_desc plasma_desc_init(PLASMA_enum dtyp, int mb, int nb, int bsiz,
                             int lm, int ln, int i, int j, int m, int n)
{
    PLASMA_desc desc;
    size_t A21 = (size_t)(lm - lm%mb) * (size_t)(ln - ln%nb);
    size_t A12 = (size_t)(     lm%mb) * (size_t)(ln - ln%nb);
    size_t A22 = (size_t)(lm - lm%mb) * (size_t)(     ln%nb);

    // Matrix address
    desc.mat = NULL;
    desc.A21 = A21;
    desc.A12 = A12 + desc.A21;
    desc.A22 = A22 + desc.A12;
    // Matrix properties
    desc.dtyp = dtyp;
    desc.mb = mb;
    desc.nb = nb;
    desc.bsiz = bsiz;
    // Large matrix parameters
    desc.lm = lm;
    desc.ln = ln;
    // Large matrix derived parameters
    desc.lm1 = (lm/mb);
    desc.ln1 = (ln/nb);
    desc.lmt = (lm%mb==0) ? (lm/mb) : (lm/mb+1);
    desc.lnt = (ln%nb==0) ? (ln/nb) : (ln/nb+1);
    // Submatrix parameters
    desc.i = i;
    desc.j = j;
    desc.m = m;
    desc.n = n;
    // Submatrix derived parameters
    desc.mt = (m == 0) ? 0 : (i+m-1)/mb - i/mb + 1;
    desc.nt = (n == 0) ? 0 : (j+n-1)/nb - j/nb + 1;

    return desc;
}

/***************************************************************************//**
 *  Internal static descriptor initializer for submatrices
 **/
PLASMA_desc plasma_desc_submatrix(PLASMA_desc descA, int i, int j, int m, int n)
{
    PLASMA_desc descB;
    int mb, nb;

    if ( (descA.i + i + m) > descA.lm ) {
        coreblas_error(2, "plasma_desc_submatrix: The number of rows (i+m) of the submatrix doesn't fit in the parent matrix");
        assert((descA.i + i + m) > descA.lm);
    }
    if ( (descA.j + j + n) > descA.ln ) {
        coreblas_error(3, "plasma_desc_submatrix: The number of rows (j+n) of the submatrix doesn't fit in the parent matrix");
        assert((descA.j + j + n) > descA.ln);
    }

    descB = descA;
    mb = descA.mb;
    nb = descA.nb;
    // Submatrix parameters
    descB.i = descA.i + i;
    descB.j = descA.j + j;
    descB.m = m;
    descB.n = n;
    // Submatrix derived parameters
    descB.mt = (m == 0) ? 0 : (descB.i+m-1)/mb - descB.i/mb + 1;
    descB.nt = (n == 0) ? 0 : (descB.j+n-1)/nb - descB.j/nb + 1;
    return descB;
}
