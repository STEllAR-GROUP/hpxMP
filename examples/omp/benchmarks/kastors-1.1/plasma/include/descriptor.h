/**
 *
 * @file descriptor.h
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
#ifndef _PLASMA_DESCRIPTOR_H_
#define _PLASMA_DESCRIPTOR_H_

#include <stdio.h>
#include "plasma.h"

#ifdef __cplusplus
extern "C" {
#endif


/***************************************************************************//**
 *  Internal routines used by coreblas library
 **/
PLASMA_desc plasma_desc_init(PLASMA_enum dtyp, int mb, int nb, int bsiz,
                             int lm, int ln, int i, int j, int m, int n);
PLASMA_desc plasma_desc_submatrix(PLASMA_desc descA, int i, int j, int m, int n);


static inline int plasma_element_size(int type)
{
    switch(type) {
    case PlasmaByte:          return          1;
    case PlasmaInteger:       return   sizeof(int);
    case PlasmaRealFloat:     return   sizeof(float);
    case PlasmaRealDouble:    return   sizeof(double);
    case PlasmaComplexFloat:  return 2*sizeof(float);
    case PlasmaComplexDouble: return 2*sizeof(double);
    default:
        fprintf(stderr, "plasma_element_size: invalide type parameter\n");
        return -1;
    }
}

/***************************************************************************//**
 *  Internal function to return adress of block (m,n)
 **/
inline static void *plasma_getaddr(PLASMA_desc A, int m, int n)
{
    size_t mm = m+A.i/A.mb;
    size_t nn = n+A.j/A.nb;
    size_t eltsize = plasma_element_size(A.dtyp);
    size_t offset = 0;

    if (mm < (size_t)(A.lm1)) {
        if (nn < (size_t)(A.ln1))
            offset = A.bsiz*(mm + (size_t)A.lm1 * nn);
        else
            offset = A.A12 + ((size_t)A.mb * (A.ln%A.nb) * mm);
    }
    else {
        if (nn < (size_t)(A.ln1))
            offset = A.A21 + ((size_t)A.nb * (A.lm%A.mb) * nn);
        else
            offset = A.A22;
    }

    return (void*)((char*)A.mat + (offset*eltsize) );
}

#ifdef __cplusplus
}
#endif

#endif
