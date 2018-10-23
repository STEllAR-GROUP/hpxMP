/**
 *
 * @file control/auxiliary.c
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
#include "common.h"
#include "auxiliary.h"

#include <stdio.h>
#include <stdlib.h>

/***************************************************************************//**
 *
 *  Indicates a recoverable problem.
 *  User's erroneous action with potentially severe consequences.
 *  Problems occuring due to incorrect use of PLASMA.
 *  Context aware.
 *
 * @param[in] func_name
 *          Function location where warning occurred
 *
 * @param[in] msg_text
 *          Warning message to display.
 *
 ******************************************************************************/
void plasma_error(const char *func_name, char* msg_text)
{
    fprintf(stderr, "PLASMA ERROR: %s(): %s\n", func_name, msg_text);

}
