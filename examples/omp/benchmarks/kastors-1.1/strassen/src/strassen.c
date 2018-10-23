/**********************************************************************************************/
/*  This program is part of the Barcelona OpenMP Tasks Suite                                  */
/*  Copyright (C) 2009 Barcelona Supercomputing Center - Centro Nacional de Supercomputacion  */
/*  Copyright (C) 2009 Universitat Politecnica de Catalunya                                   */
/*                                                                                            */
/**********************************************************************************************/

/*
 * Copyright (c) 1996 Massachusetts Institute of Technology
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to use, copy, modify, and distribute the Software without
 * restriction, provided the Software, including any modified copies made
 * under this license, is not distributed for a fee, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE MASSACHUSETTS INSTITUTE OF TECHNOLOGY BE LIABLE
 * FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * /WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of the Massachusetts
 * Institute of Technology shall not be used in advertising or otherwise
 * to promote the sale, use or other dealings in this Software without
 * prior written authorization from the Massachusetts Institute of
 * Technology.
 *
 */

#include <stdlib.h>
#include "strassen.h"
#include "main.h"
#include "timer.h"

/*****************************************************************************
**
** FastNaiveMatrixMultiply
**
** For small to medium sized matrices A, B, and C of size
** MatrixSize * MatrixSize this function performs the operation
** C = A x B efficiently.
**
** Note MatrixSize must be divisible by 8.
**
** INPUT:
**    C = (*C WRITE) Address of top left element of matrix C.
**    A = (*A IS READ ONLY) Address of top left element of matrix A.
**    B = (*B IS READ ONLY) Address of top left element of matrix B.
**    MatrixSize = Size of matrices (for n*n matrix, MatrixSize = n)
**    RowWidthA = Number of elements in memory between A[x,y] and A[x,y+1]
**    RowWidthB = Number of elements in memory between B[x,y] and B[x,y+1]
**    RowWidthC = Number of elements in memory between C[x,y] and C[x,y+1]
**
** OUTPUT:
**    C = (*C WRITE) Matrix C contains A x B. (Initial value of *C undefined.)
**
*****************************************************************************/
static void FastNaiveMatrixMultiply(REAL *C, REAL *A, REAL *B, unsigned MatrixSize,
     unsigned RowWidthC, unsigned RowWidthA, unsigned RowWidthB)
{
  /* Assumes size of real is 8 bytes */
  PTR RowWidthBInBytes = RowWidthB  << 3;
  PTR RowWidthAInBytes = RowWidthA << 3;
  PTR MatrixWidthInBytes = MatrixSize << 3;
  PTR RowIncrementC = ( RowWidthC - MatrixSize) << 3;
  unsigned Horizontal, Vertical;

  REAL *ARowStart = A;
  for (Vertical = 0; Vertical < MatrixSize; Vertical++) {
    for (Horizontal = 0; Horizontal < MatrixSize; Horizontal += 8) {
      REAL *BColumnStart = B + Horizontal;
      REAL FirstARowValue = *ARowStart++;

      REAL Sum0 = FirstARowValue * (*BColumnStart);
      REAL Sum1 = FirstARowValue * (*(BColumnStart+1));
      REAL Sum2 = FirstARowValue * (*(BColumnStart+2));
      REAL Sum3 = FirstARowValue * (*(BColumnStart+3));
      REAL Sum4 = FirstARowValue * (*(BColumnStart+4));
      REAL Sum5 = FirstARowValue * (*(BColumnStart+5));
      REAL Sum6 = FirstARowValue * (*(BColumnStart+6));
      REAL Sum7 = FirstARowValue * (*(BColumnStart+7));

      unsigned Products;
      for (Products = 1; Products < MatrixSize; Products++) {
	REAL ARowValue = *ARowStart++;
	BColumnStart = (REAL*) (((PTR) BColumnStart) + RowWidthBInBytes);
	Sum0 += ARowValue * (*BColumnStart);
	Sum1 += ARowValue * (*(BColumnStart+1));
	Sum2 += ARowValue * (*(BColumnStart+2));
	Sum3 += ARowValue * (*(BColumnStart+3));
	Sum4 += ARowValue * (*(BColumnStart+4));
	Sum5 += ARowValue * (*(BColumnStart+5));
	Sum6 += ARowValue * (*(BColumnStart+6));
	Sum7 += ARowValue * (*(BColumnStart+7));
      }
      ARowStart = (REAL*) ( ((PTR) ARowStart) - MatrixWidthInBytes);

      *(C) = Sum0;
      *(C+1) = Sum1;
      *(C+2) = Sum2;
      *(C+3) = Sum3;
      *(C+4) = Sum4;
      *(C+5) = Sum5;
      *(C+6) = Sum6;
      *(C+7) = Sum7;
      C+=8;
    }
    ARowStart = (REAL*) ( ((PTR) ARowStart) + RowWidthAInBytes );
    C = (REAL*) ( ((PTR) C) + RowIncrementC );
  }
}
/*****************************************************************************
**
** FastAdditiveNaiveMatrixMultiply
**
** For small to medium sized matrices A, B, and C of size
** MatrixSize * MatrixSize this function performs the operation
** C += A x B efficiently.
**
** Note MatrixSize must be divisible by 8.
**
** INPUT:
**    C = (*C READ/WRITE) Address of top left element of matrix C.
**    A = (*A IS READ ONLY) Address of top left element of matrix A.
**    B = (*B IS READ ONLY) Address of top left element of matrix B.
**    MatrixSize = Size of matrices (for n*n matrix, MatrixSize = n)
**    RowWidthA = Number of elements in memory between A[x,y] and A[x,y+1]
**    RowWidthB = Number of elements in memory between B[x,y] and B[x,y+1]
**    RowWidthC = Number of elements in memory between C[x,y] and C[x,y+1]
**
** OUTPUT:
**    C = (*C READ/WRITE) Matrix C contains C + A x B.
**
*****************************************************************************/
static void FastAdditiveNaiveMatrixMultiply(REAL *C, REAL *A, REAL *B, unsigned MatrixSize,
     unsigned RowWidthC, unsigned RowWidthA, unsigned RowWidthB)
{
  /* Assumes size of real is 8 bytes */
  PTR RowWidthBInBytes = RowWidthB  << 3;
  PTR RowWidthAInBytes = RowWidthA << 3;
  PTR MatrixWidthInBytes = MatrixSize << 3;
  PTR RowIncrementC = ( RowWidthC - MatrixSize) << 3;
  unsigned Horizontal, Vertical;

  REAL *ARowStart = A;
  for (Vertical = 0; Vertical < MatrixSize; Vertical++) {
    for (Horizontal = 0; Horizontal < MatrixSize; Horizontal += 8) {
      REAL *BColumnStart = B + Horizontal;

      REAL Sum0 = *C;
      REAL Sum1 = *(C+1);
      REAL Sum2 = *(C+2);
      REAL Sum3 = *(C+3);
      REAL Sum4 = *(C+4);
      REAL Sum5 = *(C+5);
      REAL Sum6 = *(C+6);
      REAL Sum7 = *(C+7);

      unsigned Products;
      for (Products = 0; Products < MatrixSize; Products++) {
	REAL ARowValue = *ARowStart++;

	Sum0 += ARowValue * (*BColumnStart);
	Sum1 += ARowValue * (*(BColumnStart+1));
	Sum2 += ARowValue * (*(BColumnStart+2));
	Sum3 += ARowValue * (*(BColumnStart+3));
	Sum4 += ARowValue * (*(BColumnStart+4));
	Sum5 += ARowValue * (*(BColumnStart+5));
	Sum6 += ARowValue * (*(BColumnStart+6));
	Sum7 += ARowValue * (*(BColumnStart+7));

	BColumnStart = (REAL*) (((PTR) BColumnStart) + RowWidthBInBytes);

      }
      ARowStart = (REAL*) ( ((PTR) ARowStart) - MatrixWidthInBytes);

      *(C) = Sum0;
      *(C+1) = Sum1;
      *(C+2) = Sum2;
      *(C+3) = Sum3;
      *(C+4) = Sum4;
      *(C+5) = Sum5;
      *(C+6) = Sum6;
      *(C+7) = Sum7;
      C+=8;
    }

    ARowStart = (REAL*) ( ((PTR) ARowStart) + RowWidthAInBytes );
    C = (REAL*) ( ((PTR) C) + RowIncrementC );
  }
}
/*****************************************************************************
**
** MultiplyByDivideAndConquer
**
** For medium to medium-large (would you like fries with that) sized
** matrices A, B, and C of size MatrixSize * MatrixSize this function
** efficiently performs the operation
**    C  = A x B (if AdditiveMode == 0)
**    C += A x B (if AdditiveMode != 0)
**
** Note MatrixSize must be divisible by 16.
**
** INPUT:
**    C = (*C READ/WRITE) Address of top left element of matrix C.
**    A = (*A IS READ ONLY) Address of top left element of matrix A.
**    B = (*B IS READ ONLY) Address of top left element of matrix B.
**    MatrixSize = Size of matrices (for n*n matrix, MatrixSize = n)
**    RowWidthA = Number of elements in memory between A[x,y] and A[x,y+1]
**    RowWidthB = Number of elements in memory between B[x,y] and B[x,y+1]
**    RowWidthC = Number of elements in memory between C[x,y] and C[x,y+1]
**    AdditiveMode = 0 if we want C = A x B, otherwise we'll do C += A x B
**
** OUTPUT:
**    C (+)= A x B. (+ if AdditiveMode != 0)
**
*****************************************************************************/
void MultiplyByDivideAndConquer(REAL *C, REAL *A, REAL *B,
				     unsigned MatrixSize,
				     unsigned RowWidthC,
				     unsigned RowWidthA,
				     unsigned RowWidthB,
				     int AdditiveMode
				    )
{
  REAL  *A01, *A10, *A11, *B01, *B10, *B11, *C01, *C10, *C11;
  unsigned QuadrantSize = MatrixSize >> 1;

  /* partition the matrix */
  A01 = A + QuadrantSize;
  A10 = A + RowWidthA * QuadrantSize;
  A11 = A10 + QuadrantSize;

  B01 = B + QuadrantSize;
  B10 = B + RowWidthB * QuadrantSize;
  B11 = B10 + QuadrantSize;

  C01 = C + QuadrantSize;
  C10 = C + RowWidthC * QuadrantSize;
  C11 = C10 + QuadrantSize;

  if (QuadrantSize > SizeAtWhichNaiveAlgorithmIsMoreEfficient) {

    MultiplyByDivideAndConquer(C, A, B, QuadrantSize,
				     RowWidthC, RowWidthA, RowWidthB,
				     AdditiveMode);

    MultiplyByDivideAndConquer(C01, A, B01, QuadrantSize,
				     RowWidthC, RowWidthA, RowWidthB,
				     AdditiveMode);

    MultiplyByDivideAndConquer(C11, A10, B01, QuadrantSize,
				     RowWidthC, RowWidthA, RowWidthB,
				     AdditiveMode);

    MultiplyByDivideAndConquer(C10, A10, B, QuadrantSize,
				     RowWidthC, RowWidthA, RowWidthB,
				     AdditiveMode);

    MultiplyByDivideAndConquer(C, A01, B10, QuadrantSize,
				     RowWidthC, RowWidthA, RowWidthB,
				     1);

    MultiplyByDivideAndConquer(C01, A01, B11, QuadrantSize,
				     RowWidthC, RowWidthA, RowWidthB,
				     1);

    MultiplyByDivideAndConquer(C11, A11, B11, QuadrantSize,
				     RowWidthC, RowWidthA, RowWidthB,
				     1);

    MultiplyByDivideAndConquer(C10, A11, B10, QuadrantSize,
				     RowWidthC, RowWidthA, RowWidthB,
				     1);

  } else {

    if (AdditiveMode) {
      FastAdditiveNaiveMatrixMultiply(C, A, B, QuadrantSize,
			      RowWidthC, RowWidthA, RowWidthB);

      FastAdditiveNaiveMatrixMultiply(C01, A, B01, QuadrantSize,
			      RowWidthC, RowWidthA, RowWidthB);

      FastAdditiveNaiveMatrixMultiply(C11, A10, B01, QuadrantSize,
			      RowWidthC, RowWidthA, RowWidthB);

      FastAdditiveNaiveMatrixMultiply(C10, A10, B, QuadrantSize,
			      RowWidthC, RowWidthA, RowWidthB);

    } else {

      FastNaiveMatrixMultiply(C, A, B, QuadrantSize,
			      RowWidthC, RowWidthA, RowWidthB);

      FastNaiveMatrixMultiply(C01, A, B01, QuadrantSize,
			      RowWidthC, RowWidthA, RowWidthB);

      FastNaiveMatrixMultiply(C11, A10, B01, QuadrantSize,
			      RowWidthC, RowWidthA, RowWidthB);

      FastNaiveMatrixMultiply(C10, A10, B, QuadrantSize,
			      RowWidthC, RowWidthA, RowWidthB);
    }

    FastAdditiveNaiveMatrixMultiply(C, A01, B10, QuadrantSize,
				    RowWidthC, RowWidthA, RowWidthB);

    FastAdditiveNaiveMatrixMultiply(C01, A01, B11, QuadrantSize,
				    RowWidthC, RowWidthA, RowWidthB);

    FastAdditiveNaiveMatrixMultiply(C11, A11, B11, QuadrantSize,
				    RowWidthC, RowWidthA, RowWidthB);

    FastAdditiveNaiveMatrixMultiply(C10, A11, B10, QuadrantSize,
				    RowWidthC, RowWidthA, RowWidthB);
  }
  return;
}

/*
 * Set an n by n matrix A to random values.  The distance between
 * rows is an
 */
static void init_matrix(int n, REAL *A, int an, unsigned int bs)
{
     int i, j;

#pragma omp parallel
#pragma omp master
     for (i = 0; i < n; i+=bs)
        for (j = 0; j < n; j+=bs)
        {
#pragma omp task firstprivate(i,j,bs,an)
          {
            unsigned int seed = rand();
            int ii, jj;
            for (ii = i; ii < i+bs; ++ii)
                 for (jj = 0; jj < j+bs; ++jj)
                      ELEM(A, an, ii, jj) = ((double) rand_r(&seed) / RAND_MAX);
          }
        }
}

/*
 * Compare two matrices.  Print an error message if they differ by
 * more than EPSILON.
 */
static int compare_matrix(int n, REAL *A, int an, REAL *B, int bn)
{
    int i, j;
    REAL c;

    for (i = 0; i < n; ++i)
        for (j = 0; j < n; ++j) {
            /* compute the relative error c */
            c = ELEM(A, an, i, j) - ELEM(B, bn, i, j);
            if (c < 0.0)
                c = -c;
            c = c / ELEM(A, an, i, j);
//	    printf("C: %f   A: %f   B: %f\n", c, ELEM(A, an, i, j), ELEM(B, bn, i, j));
            if (c > EPSILON)
                return 0;
        }

    return 1;
}

void matrix_multiply(double* A, double* B, double* C, int matrix_size)
{
int i, j, k;
for(i=0; i<matrix_size; i++)
    for(j=0; j<matrix_size; j++)
    {
	double res = 0;
        for(k=0; k<matrix_size; k++)
	    res += A[i * matrix_size + k] * B[k * matrix_size + j];
        C[i * matrix_size + j] = res;
    }
}

double run(struct user_parameters* params)
{
    double *A, *B, *C;
    int matrix_size = params->matrix_size;
    int cutoff_size = params->cutoff_size;
    int cutoff_depth = params->cutoff_depth;
    if (matrix_size <= 0) {
        matrix_size = 256;
        params->matrix_size = matrix_size;
    }
    if (cutoff_size <= 0) {
        cutoff_size = 64;
        params->cutoff_size = cutoff_size;
    }
    if (cutoff_depth <= 0) {
        cutoff_depth = 4;
        params->cutoff_depth = cutoff_depth;
    }

    A = (double *) malloc (matrix_size * matrix_size * sizeof(double));
    B = (double *) malloc (matrix_size * matrix_size * sizeof(double));
    C = (double *) malloc (matrix_size * matrix_size * sizeof(double));

    init_matrix(matrix_size,A,matrix_size, matrix_size/8);
    init_matrix(matrix_size,B,matrix_size, matrix_size/8);

    /// KERNEL INTENSIVE COMPUTATION
    START_TIMER;
#ifndef _OPENMP
    strassen_main_seq(C, A, B, matrix_size, cutoff_size);
#else
    strassen_main_par(C, A, B, matrix_size, cutoff_size, cutoff_depth);
#endif
    END_TIMER;

    if(params->check) {
        double *D = (double *) malloc (matrix_size * matrix_size * sizeof(double));
        matrix_multiply(A, B, D, matrix_size);
        params->succeed = compare_matrix(matrix_size, C, matrix_size, D, matrix_size);
        free(D);
    }
    free(A);
    free(B);
    free(C);
    return TIMER;
}
