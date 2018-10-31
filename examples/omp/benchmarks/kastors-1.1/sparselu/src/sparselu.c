/**********************************************************************************************/
/*  This program is part of the Barcelona OpenMP Tasks Suite                                  */
/*  Copyright (C) 2009 Barcelona Supercomputing Center - Centro Nacional de Supercomputacion  */
/*  Copyright (C) 2009 Universitat Politecnica de Catalunya                                   */
/*                                                                                            */
/*  This program is free software; you can redistribute it and/or modify                      */
/*  it under the terms of the GNU General Public License as published by                      */
/*  the Free Software Foundation; either version 2 of the License, or                         */
/*  (at your option) any later version.                                                       */
/*                                                                                            */
/*  This program is distributed in the hope that it will be useful,                           */
/*  but WITHOUT ANY WARRANTY; without even the implied warranty of                            */
/*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                             */
/*  GNU General Public License for more details.                                              */
/*                                                                                            */
/*  You should have received a copy of the GNU General Public License                         */
/*  along with this program; if not, write to the Free Software                               */
/*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA            */
/**********************************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <libgen.h>
#include "sparselu.h"
#include "timer.h"
#include "main.h"


/***********************************************************************
 * genmat:
 **********************************************************************/
static void genmat (float *M[], int matrix_size, int submatrix_size)
{
    int null_entry, init_val, i, j, ii, jj;
    float *p;

    init_val = 1325;

    /* generating the structure */
    for (ii=0; ii < matrix_size; ii++)
    {
        for (jj=0; jj < matrix_size; jj++)
        {
            /* computing null entries */
            null_entry=0;
            if ((ii<jj) && (ii%3 !=0)) null_entry = 1;
            if ((ii>jj) && (jj%3 !=0)) null_entry = 1;
            if (ii%2==1) null_entry = 1;
            if (jj%2==1) null_entry = 1;
            if (ii==jj) null_entry = 0;
            if (ii==jj-1) null_entry = 0;
            if (ii-1 == jj) null_entry = 0;
            /* allocating matrix */
            if (null_entry == 0){
                M[ii*matrix_size+jj] = (float *) malloc(submatrix_size*submatrix_size*sizeof(float));
                if (M[ii*matrix_size+jj] == NULL)
                    exit(101);
                /* initializing matrix */
                p = M[ii*matrix_size+jj];
                for (i = 0; i < submatrix_size; i++)
                {
                    for (j = 0; j < submatrix_size; j++)
                    {
                        init_val = (3125 * init_val) % 65536;
                        (*p) = (float)((init_val - 32768.0) / 16384.0);
                        p++;
                    }
                }
            }
            else
            {
                M[ii*matrix_size+jj] = NULL;
            }
        }
    }
}
/***********************************************************************
 * allocate_clean_block:
 **********************************************************************/
float * allocate_clean_block(int submatrix_size)
{
    int i,j;
    float *p, *q;

    p = (float *) malloc(submatrix_size*submatrix_size*sizeof(float));
    q=p;
    if (p!=NULL){
        for (i = 0; i < submatrix_size; i++)
            for (j = 0; j < submatrix_size; j++){(*p)=0.0; p++;}

    }
    else
        exit (101);
    return (q);
}

/***********************************************************************
 * lu0:
 **********************************************************************/
void lu0(float *diag, int submatrix_size)
{
    int i, j, k;

    for (k=0; k<submatrix_size; k++)
        for (i=k+1; i<submatrix_size; i++)
        {
            diag[i*submatrix_size+k] = diag[i*submatrix_size+k] / diag[k*submatrix_size+k];
            for (j=k+1; j<submatrix_size; j++)
                diag[i*submatrix_size+j] = diag[i*submatrix_size+j] - diag[i*submatrix_size+k] * diag[k*submatrix_size+j];
        }
}

/***********************************************************************
 * bdiv:
 **********************************************************************/
void bdiv(float *diag, float *row, int submatrix_size)
{
    int i, j, k;
    for (i=0; i<submatrix_size; i++)
        for (k=0; k<submatrix_size; k++)
        {
            row[i*submatrix_size+k] = row[i*submatrix_size+k] / diag[k*submatrix_size+k];
            for (j=k+1; j<submatrix_size; j++)
                row[i*submatrix_size+j] = row[i*submatrix_size+j] - row[i*submatrix_size+k]*diag[k*submatrix_size+j];
        }
}
/***********************************************************************
 * bmod:
 **********************************************************************/
void bmod(float *row, float *col, float *inner, int submatrix_size)
{
    int i, j, k;
    for (i=0; i<submatrix_size; i++)
        for (j=0; j<submatrix_size; j++)
            for (k=0; k<submatrix_size; k++)
                inner[i*submatrix_size+j] = inner[i*submatrix_size+j] - row[i*submatrix_size+k]*col[k*submatrix_size+j];
}
/***********************************************************************
 * fwd:
 **********************************************************************/
void fwd(float *diag, float *col, int submatrix_size)
{
    int i, j, k;
    for (j=0; j<submatrix_size; j++)
        for (k=0; k<submatrix_size; k++)
            for (i=k+1; i<submatrix_size; i++)
                col[i*submatrix_size+j] = col[i*submatrix_size+j] - diag[i*submatrix_size+k]*col[k*submatrix_size+j];
}


static void sparselu_init (float ***pBENCH, int matrix_size, int submatrix_size)
{
    *pBENCH = (float **) malloc(matrix_size*matrix_size*sizeof(float *));
    genmat(*pBENCH, matrix_size, submatrix_size);
}

#ifdef _OPENMP

/***********************************************************************
 * checkmat:
 **********************************************************************/
static int checkmat (float *M, float *N, int submatrix_size)
{
    int i, j;
    float r_err;

    for (i = 0; i < submatrix_size; i++)
    {
        for (j = 0; j < submatrix_size; j++)
        {
            r_err = M[i*submatrix_size+j] - N[i*submatrix_size+j];
            if ( r_err == 0.0 ) continue;

            if (r_err < 0.0 ) r_err = -r_err;

            if ( M[i*submatrix_size+j] == 0 )
                return 0;
            r_err = r_err / M[i*submatrix_size+j];
            if(r_err > EPSILON)
                return 0;
        }
    }
    return 1;
}

static int sparselu_check(float **BENCH_SEQ, float **BENCH, int matrix_size, int submatrix_size)
{
    int ii,jj,ok=1;

    for (ii=0; ((ii<matrix_size) && ok); ii++)
    {
        for (jj=0; ((jj<matrix_size) && ok); jj++)
        {
            if ((BENCH_SEQ[ii*matrix_size+jj] == NULL) && (BENCH[ii*matrix_size+jj] != NULL)) ok = 0;
            if ((BENCH_SEQ[ii*matrix_size+jj] != NULL) && (BENCH[ii*matrix_size+jj] == NULL)) ok = 0;
            if ((BENCH_SEQ[ii*matrix_size+jj] != NULL) && (BENCH[ii*matrix_size+jj] != NULL))
                ok = checkmat(BENCH_SEQ[ii*matrix_size+jj], BENCH[ii*matrix_size+jj], submatrix_size);
        }
    }
    return ok;
}
#endif

double run(struct user_parameters* params)
{
    float **BENCH;
    int matrix_size = params->matrix_size;
    if (matrix_size <= 0) {
        matrix_size = 64;
        params->matrix_size = matrix_size;
    }
    int submatrix_size = params->submatrix_size;
    if (submatrix_size <= 0) {
        submatrix_size = 64;
        params->submatrix_size = submatrix_size;
    }
    sparselu_init(&BENCH, matrix_size, submatrix_size);

    /// KERNEL INTENSIVE COMPUTATION
    START_TIMER;
#ifndef _OPENMP
    sparselu_seq_call(BENCH, matrix_size, submatrix_size);
#else
    sparselu_par_call(BENCH, matrix_size, submatrix_size);
#endif
    END_TIMER;

#ifdef _OPENMP
    if(params->check) {
        float **BENCH_SEQ;
        sparselu_init(&BENCH_SEQ, matrix_size, submatrix_size);
        sparselu_seq_call(BENCH_SEQ, matrix_size, submatrix_size);
        params->succeed = sparselu_check(BENCH_SEQ, BENCH, matrix_size, submatrix_size);
    }
#else
    params->succeed = 1;
#endif
    return TIMER;
}
