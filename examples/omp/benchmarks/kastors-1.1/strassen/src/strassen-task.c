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


/*****************************************************************************
 **
 ** OptimizedStrassenMultiply
 **
 ** For large matrices A, B, and C of size MatrixSize * MatrixSize this
 ** function performs the operation C = A x B efficiently.
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
static void OptimizedStrassenMultiply_par(double *C, double *A, double *B,
    unsigned MatrixSize, unsigned RowWidthC, unsigned RowWidthA,
    unsigned RowWidthB, unsigned int Depth, unsigned int cutoff_depth,
    unsigned cutoff_size)
{
  unsigned QuadrantSize = MatrixSize >> 1; /* MatixSize / 2 */
  unsigned QuadrantSizeInBytes = sizeof(double) * QuadrantSize * QuadrantSize;
  unsigned Column, Row;

  /************************************************************************
   ** For each matrix A, B, and C, we'll want pointers to each quandrant
   ** in the matrix. These quandrants will be addressed as follows:
   **  --        --
   **  | A    A12 |
   **  |          |
   **  | A21  A22 |
   **  --        --
   ************************************************************************/
  double /* *A, *B, *C, */ *A12, *B12, *C12,
         *A21, *B21, *C21, *A22, *B22, *C22;

  double *S1,*S2,*S3,*S4,*S5,*S6,*S7,*S8,*M2,*M5,*T1sMULT;
#define T2sMULT C22
#define NumberOfVariables 11

  char *Heap;
  void *StartHeap;

  if (MatrixSize <= cutoff_size) {
    MultiplyByDivideAndConquer(C, A, B, MatrixSize, RowWidthC, RowWidthA, RowWidthB, 0);
    return;
  }

  /* Initialize quandrant matrices */
  A12 = A + QuadrantSize;
  B12 = B + QuadrantSize;
  C12 = C + QuadrantSize;
  A21 = A + (RowWidthA * QuadrantSize);
  B21 = B + (RowWidthB * QuadrantSize);
  C21 = C + (RowWidthC * QuadrantSize);
  A22 = A21 + QuadrantSize;
  B22 = B21 + QuadrantSize;
  C22 = C21 + QuadrantSize;

  /* Allocate Heap Space Here */
  Heap = (char*)malloc(QuadrantSizeInBytes * NumberOfVariables);
  StartHeap = Heap;

  /* Distribute the heap space over the variables */
  S1 = (double*) Heap; Heap += QuadrantSizeInBytes;
  S2 = (double*) Heap; Heap += QuadrantSizeInBytes;
  S3 = (double*) Heap; Heap += QuadrantSizeInBytes;
  S4 = (double*) Heap; Heap += QuadrantSizeInBytes;
  S5 = (double*) Heap; Heap += QuadrantSizeInBytes;
  S6 = (double*) Heap; Heap += QuadrantSizeInBytes;
  S7 = (double*) Heap; Heap += QuadrantSizeInBytes;
  S8 = (double*) Heap; Heap += QuadrantSizeInBytes;
  M2 = (double*) Heap; Heap += QuadrantSizeInBytes;
  M5 = (double*) Heap; Heap += QuadrantSizeInBytes;
  T1sMULT = (double*) Heap; Heap += QuadrantSizeInBytes;

  if (Depth < cutoff_depth)
  {

#pragma omp task private(Row, Column)
  for (Row = 0; Row < QuadrantSize; Row++)
    for (Column = 0; Column < QuadrantSize; Column++)
      S1[Row * QuadrantSize + Column] = A21[RowWidthA * Row + Column] + A22[RowWidthA * Row + Column];

#pragma omp taskwait

#pragma omp task private(Row, Column)
  for (Row = 0; Row < QuadrantSize; Row++)
    for (Column = 0; Column < QuadrantSize; Column++)
      S2[Row * QuadrantSize + Column] = S1[Row * QuadrantSize + Column] - A[RowWidthA * Row + Column];

#pragma omp taskwait

#pragma omp task private(Row, Column)
  for (Row = 0; Row < QuadrantSize; Row++)
    for (Column = 0; Column < QuadrantSize; Column++)
      S4[Row * QuadrantSize + Column] = A12[Row * RowWidthA + Column] - S2[QuadrantSize * Row + Column];

#pragma omp task private(Row, Column)
  for (Row = 0; Row < QuadrantSize; Row++)
    for (Column = 0; Column < QuadrantSize; Column++)
      S5[Row * QuadrantSize + Column] = B12[Row * RowWidthB + Column] - B[Row * RowWidthB + Column];

#pragma omp taskwait

#pragma omp task private(Row, Column)
  for (Row = 0; Row < QuadrantSize; Row++)
    for (Column = 0; Column < QuadrantSize; Column++)
      S6[Row * QuadrantSize + Column] = B22[Row * RowWidthB + Column] - S5[Row * QuadrantSize + Column];

#pragma omp taskwait

#pragma omp task private(Row, Column)
  for (Row = 0; Row < QuadrantSize; Row++)
    for (Column = 0; Column < QuadrantSize; Column++)
      S8[Row * QuadrantSize + Column] = S6[Row * QuadrantSize + Column] - B21[Row * RowWidthB + Column];

#pragma omp task private(Row, Column)
  for (Row = 0; Row < QuadrantSize; Row++)
    for (Column = 0; Column < QuadrantSize; Column++)
      S3[Row * QuadrantSize + Column] = A[RowWidthA * Row + Column] - A21[RowWidthA * Row + Column];

#pragma omp task private(Row, Column)
  for (Row = 0; Row < QuadrantSize; Row++)
    for (Column = 0; Column < QuadrantSize; Column++)
      S7[Row * QuadrantSize + Column] = B22[Row * RowWidthB + Column] - B12[Row * RowWidthB + Column];

#pragma omp taskwait

    /* M2 = A x B */
#pragma omp task untied
    OptimizedStrassenMultiply_par(M2, A, B, QuadrantSize, QuadrantSize, RowWidthA, RowWidthB, Depth+1, cutoff_depth, cutoff_size);

    /* M5 = S1 * S5 */
#pragma omp task untied
    OptimizedStrassenMultiply_par(M5, S1, S5, QuadrantSize, QuadrantSize, QuadrantSize, QuadrantSize, Depth+1, cutoff_depth, cutoff_size);

    /* Step 1 of T1 = S2 x S6 + M2 */
#pragma omp task untied
    OptimizedStrassenMultiply_par(T1sMULT, S2, S6,  QuadrantSize, QuadrantSize, QuadrantSize, QuadrantSize, Depth+1, cutoff_depth, cutoff_size);

    /* Step 1 of T2 = T1 + S3 x S7 */
#pragma omp task untied
    OptimizedStrassenMultiply_par(C22, S3, S7, QuadrantSize, RowWidthC /*FIXME*/, QuadrantSize, QuadrantSize, Depth+1, cutoff_depth, cutoff_size);

    /* Step 1 of C = M2 + A12 * B21 */
#pragma omp task untied
    OptimizedStrassenMultiply_par(C, A12, B21, QuadrantSize, RowWidthC, RowWidthA, RowWidthB, Depth+1, cutoff_depth, cutoff_size);

    /* Step 1 of C12 = S4 x B22 + T1 + M5 */
#pragma omp task untied
    OptimizedStrassenMultiply_par(C12, S4, B22, QuadrantSize, RowWidthC, QuadrantSize, RowWidthB, Depth+1, cutoff_depth, cutoff_size);

    /* Step 1 of C21 = T2 - A22 * S8 */
#pragma omp task untied
    OptimizedStrassenMultiply_par(C21, A22, S8, QuadrantSize, RowWidthC, RowWidthA, QuadrantSize, Depth+1, cutoff_depth, cutoff_size);

#pragma omp taskwait

#pragma omp task private(Row, Column)
  for (Row = 0; Row < QuadrantSize; Row++)
    for (Column = 0; Column < QuadrantSize; Column += 1)
      C[RowWidthC * Row + Column] += M2[Row * QuadrantSize + Column];

#pragma omp task private(Row, Column)
  for (Row = 0; Row < QuadrantSize; Row++)
    for (Column = 0; Column < QuadrantSize; Column += 1)
      C12[RowWidthC * Row + Column] += M5[Row * QuadrantSize + Column] + T1sMULT[Row * QuadrantSize + Column] + M2[Row * QuadrantSize + Column];

#pragma omp task private(Row, Column)
  for (Row = 0; Row < QuadrantSize; Row++)
    for (Column = 0; Column < QuadrantSize; Column += 1)
      C21[RowWidthC * Row + Column] = -C21[RowWidthC * Row + Column] + C22[RowWidthC * Row + Column] + T1sMULT[Row * QuadrantSize + Column] + M2[Row * QuadrantSize + Column];

#pragma omp taskwait

#pragma omp task private(Row, Column)
  for (Row = 0; Row < QuadrantSize; Row++)
    for (Column = 0; Column < QuadrantSize; Column += 1)
      C22[RowWidthC * Row + Column] += M5[Row * QuadrantSize + Column] + T1sMULT[Row * QuadrantSize + Column] + M2[Row * QuadrantSize + Column];

#pragma omp taskwait
  }
  else
  {
    for (Row = 0; Row < QuadrantSize; Row++)
      for (Column = 0; Column < QuadrantSize; Column++) {
        S1[Row * QuadrantSize + Column] = A21[RowWidthA * Row + Column] + A22[RowWidthA * Row + Column];
        S2[Row * QuadrantSize + Column] = S1[Row * QuadrantSize + Column] - A[RowWidthA * Row + Column];
        S4[Row * QuadrantSize + Column] = A12[Row * RowWidthA + Column] - S2[QuadrantSize * Row + Column];
        S5[Row * QuadrantSize + Column] = B12[Row * RowWidthB + Column] - B[Row * RowWidthB + Column];
        S6[Row * QuadrantSize + Column] = B22[Row * RowWidthB + Column] - S5[Row * QuadrantSize + Column];
        S8[Row * QuadrantSize + Column] = S6[Row * QuadrantSize + Column] - B21[Row * RowWidthB + Column];
        S3[Row * QuadrantSize + Column] = A[RowWidthA * Row + Column] - A21[RowWidthA * Row + Column];
        S7[Row * QuadrantSize + Column] = B22[Row * RowWidthB + Column] - B12[Row * RowWidthB + Column];
      }
    /* M2 = A x B */
    OptimizedStrassenMultiply_par(M2, A, B, QuadrantSize, QuadrantSize, RowWidthA, RowWidthB, Depth+1, cutoff_depth, cutoff_size);
    /* M5 = S1 * S5 */
    OptimizedStrassenMultiply_par(M5, S1, S5, QuadrantSize, QuadrantSize, QuadrantSize, QuadrantSize, Depth+1, cutoff_depth, cutoff_size);
    /* Step 1 of T1 = S2 x S6 + M2 */
    OptimizedStrassenMultiply_par(T1sMULT, S2, S6,  QuadrantSize, QuadrantSize, QuadrantSize, QuadrantSize, Depth+1, cutoff_depth, cutoff_size);
    /* Step 1 of T2 = T1 + S3 x S7 */
    OptimizedStrassenMultiply_par(C22, S3, S7, QuadrantSize, RowWidthC /*FIXME*/, QuadrantSize, QuadrantSize, Depth+1, cutoff_depth, cutoff_size);
    /* Step 1 of C = M2 + A12 * B21 */
    OptimizedStrassenMultiply_par(C, A12, B21, QuadrantSize, RowWidthC, RowWidthA, RowWidthB, Depth+1, cutoff_depth, cutoff_size);
    /* Step 1 of C12 = S4 x B22 + T1 + M5 */
    OptimizedStrassenMultiply_par(C12, S4, B22, QuadrantSize, RowWidthC, QuadrantSize, RowWidthB, Depth+1, cutoff_depth, cutoff_size);
    /* Step 1 of C21 = T2 - A22 * S8 */
    OptimizedStrassenMultiply_par(C21, A22, S8, QuadrantSize, RowWidthC, RowWidthA, QuadrantSize, Depth+1, cutoff_depth, cutoff_size);

    for (Row = 0; Row < QuadrantSize; Row++) {
      for (Column = 0; Column < QuadrantSize; Column += 1) {
        C[RowWidthC * Row + Column] += M2[Row * QuadrantSize + Column];
        C12[RowWidthC * Row + Column] += M5[Row * QuadrantSize + Column] + T1sMULT[Row * QuadrantSize + Column] + M2[Row * QuadrantSize + Column];
        C21[RowWidthC * Row + Column] = -C21[RowWidthC * Row + Column] + C22[RowWidthC * Row + Column] + T1sMULT[Row * QuadrantSize + Column] + M2[Row * QuadrantSize + Column];
        C22[RowWidthC * Row + Column] += M5[Row * QuadrantSize + Column] + T1sMULT[Row * QuadrantSize + Column] + M2[Row * QuadrantSize + Column];
      }
    }
  }
  free(StartHeap);
}

void strassen_main_par(double *A, double *B, double *C, int n, unsigned int cutoff_size, unsigned int cutoff_depth)
{
#pragma omp parallel
#pragma omp master
  OptimizedStrassenMultiply_par(C, A, B, n, n, n, n, 1, cutoff_depth, cutoff_size);
}
