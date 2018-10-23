/**
 *
 * @file tile.h
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
#ifndef _PLASMA_TILE_H_
#define _PLASMA_TILE_H_

#include <inttypes.h>

#define BLKADDR(A, type, m, n)  (type *)plasma_getaddr(A, m, n)
#define BLKLDD(A, k) ( ( (k) + (A).i/(A).mb) < (A).lm1 ? (A).mb : (A).lm%(A).mb )

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************//**
 *  Internal routines - dynamic scheduling
 **/
void plasma_pdtile_to_lapack_quark(PLASMA_desc, double*, int);

#ifdef __cplusplus
}
#endif

#endif
