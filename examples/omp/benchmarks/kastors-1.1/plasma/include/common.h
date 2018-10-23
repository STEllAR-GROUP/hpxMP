/**
 *
 * @file common.h
 *
 *  PLASMA auxiliary routines
 *  PLASMA is a software package provided by Univ. of Tennessee,
 *  Univ. of California Berkeley and Univ. of Colorado Denver
 *
 * @version 2.6.0
 * @author Jakub Kurzak
 * @author Mathieu Faverge
 * @date 2010-11-15
 *
 **/

/***************************************************************************//**
 *  PLASMA facilities of interest to both PLASMA core developer
 *  and also of interest to PLASMA community contributor.
 **/
#ifndef _PLASMA_COMMON_H_
#define _PLASMA_COMMON_H_

#include "core_blas.h"
#include "auxiliary.h"
#include "tile.h"

# include <unistd.h>


/** ****************************************************************************
 *  Determine if weak symbols are allowed
 */
#if defined(linux) || defined(__linux) || defined(__linux__)
#if defined(__GNUC_EXCL__) || defined(__GNUC__)
#define PLASMA_HAVE_WEAK 1
#endif
#endif

/***************************************************************************//**
 *  Global utilities
 **/
#ifndef max
#define max(a, b) ((a) > (b) ? (a) : (b))
#endif
#ifndef min
#define min(a, b) ((a) < (b) ? (a) : (b))
#endif
#ifndef roundup
#define roundup(a, b) (b <= 0) ? (a) : (((a) + (b)-1) & ~((b)-1))
#endif

/***************************************************************************//**
 *  Additional Internal routines to handle descriptors not available in coreblas
 *  library
 **/
int plasma_desc_mat_alloc(PLASMA_desc *desc);

/***************************************************************************//**
 *  Global array of LAPACK constants
 **/
extern char *plasma_lapack_constants[];

#ifdef __cplusplus
extern "C" {
#endif

#include "compute_d.h"

#ifdef __cplusplus
}
#endif

#endif
