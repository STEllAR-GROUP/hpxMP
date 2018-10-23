/**
 *
 * @file workspace.h
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
#ifndef _PLASMA_WORKSPACE_H_
#define _PLASMA_WORKSPACE_H_

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************//**
 *  Internal routines
 **/
int plasma_alloc_ibnb(int M, int N, PLASMA_enum func, int type, void **memptr);
int plasma_alloc_ibnb_tile(int M, int N, int type, PLASMA_desc **desc, int IB, int NB);
int plasma_alloc_ipiv(int M, int N, PLASMA_enum func, void **memptr);

#ifdef __cplusplus
}
#endif

#endif
