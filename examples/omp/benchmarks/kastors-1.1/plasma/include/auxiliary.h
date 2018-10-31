/**
 *
 * @file control/auxiliary.h
 *
 *  PLASMA auxiliary routines
 *  PLASMA is a software package provided by Univ. of Tennessee,
 *  Univ. of California Berkeley and Univ. of Colorado Denver
 *
 * @version 2.6.0
 * @author Jakub Kurzak
 * @author Piotr Luszczek
 * @author Emmanuel Agullo
 * @date 2010-11-15
 *
 **/
#ifndef _PLASMA_AUXILIARY_H_
#define _PLASMA_AUXILIARY_H_

#ifndef max
#define max(a,b) ( ( (a) > (b) ) ? (a) : (b))
#endif
#ifndef min
#define min(a,b) ( ( (a) < (b) ) ? (a) : (b))
#endif

#include "common.h"
#include "dauxiliary.h"

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************//**
 *  Internal routines
 **/
void plasma_error(const char *func_name, char* msg_text);

#ifdef __cplusplus
}
#endif

#endif
