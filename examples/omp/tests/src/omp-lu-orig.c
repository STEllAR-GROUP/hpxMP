/*
 * Copyright (C) 2010 Computer Architecture and Parallel Systems Laboratory (CAPSL)
 *
 * Original author: Elkin E. Garcia
 * E-Mail: egarcia@capsl.udel.edu
 *
 * License
 * Redistribution of this code is allowed only after an explicit permission is
 * given by the original author or CAPSL and this license should be included in
 * all files, either existing or new ones. Modifying the code is allowed, but
 * the original author and/or CAPSL must be notified about these modifications.
 * The original author and/or CAPSL is also allowed to use these modifications
 * and publicly report results that include them. Appropriate acknowledgments
 * to everyone who made the modifications will be added in this case.
 *
 * Warranty
 *
 * THIS CODE IS PROVIDED ON AN "AS IS" 
 * THIS CODE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTY OF ANY KIND,
 * EITHER EXPRESSED OR IMPLIED, INCLUDING, WITHOUT LIMITATION, WARRANTIES THAT
 * THE COVERED CODE IS FREE OF DEFECTS, MERCHANTABLE, FIT FOR A PARTICULAR
 * PURPOSE OR NON-INFRINGING. THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE
 * OF THE COVERED CODE IS WITH YOU. SHOULD ANY COVERED CODE PROVE DEFECTIVE IN
 * ANY RESPECT, YOU (NOT THE INITIAL DEVELOPER OR ANY OTHER CONTRIBUTOR) ASSUME
 * THE COST OF ANY NECESSARY SERVICING, REPAIR OR CORRECTION. THIS DISCLAIMER
 * OF WARRANTY CONSTITUTES AN ESSENTIAL PART OF THIS LICENSE. NO USE OF ANY
 * COVERED CODE IS AUTHORIZED HEREUNDER EXCEPT UNDER THIS DISCLAIMER.
 */

/*
 Static blocked LU Decomposition

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <omp.h>
#include <math.h>
#include <sys/time.h>


//#define DEBUG 1
//#define CHECK 1
#define MEASURE 1

void Print_Matrix (double *v, int M, int N);
void InitMatrix(double *A, int N);
void ProcessDiagonalBlock(double *A, int L1, int N);
void ProcessBlockOnRow(double *A, double *D, int L1, int L3, int N);
void ProcessBlockOnColumn(double *A, double *D, int L1, int L2, int N);

void ProcessInnerBlock(double *A, double *R, double *C, int L1, int L2, int L3, int N);
void stepLU(double *A, int Block, int offset,  int N );
void InitMatrix2(double *A, int N);
void InitMatrix3(double *A, int N);

void stage1(double *A, int offset, int *sizedim, int *start, int N, int M);
void stage2(double *A, int offset, int *sizedim, int *start, int N, int M);
void stage3(double *A, int offset, int *sizedim, int *start, int N, int M);

void lu2 (double *A, int N);

unsigned long GetTickCount()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);

    return (tv.tv_sec * 1000000) + (tv.tv_usec);
}

int N = 100;
int Block = 1;
int M=1; //number of blocks per dimension

int main (int argc, char *argv[])
{
  double *A,*A2,*L,*U, temp2;
  int i,j,k;
  int temp=0;
  int offset = 0;
  double t1,t2;

  if( argc > 1 )
    N = atoi(argv[1]);

  if( argc > 2 )
    //Block = atoi(argv[2]);
    M = atoi(argv[2]);

  A = (double *)malloc (N*N*sizeof(double));
  A2 = (double *)malloc (N*N*sizeof(double));
  L = (double *)malloc (N*N*sizeof(double));
  U = (double *)malloc (N*N*sizeof(double));
  if( A==NULL || A2==NULL || L==NULL || U==NULL) {
    printf("Can't allocate memory\n");
    exit(1);
  }

  /* INITIALIZATION */
  //InitMatrix(A,N);
  InitMatrix3(A,N);
  for(i=0; i<N*N; i++) {
    A2[i] = A[i]; // Copy of A for verification of correctness
    L[i] = 0;
    U[i] = 0;
  }

/*   /\* LU DECOMPOSITION *\/ */
/*   for (k=0;k<N-1;k++){ */
/*     for (i=k+1;i<N;i++){ */
/*       A[i*N+k] = A[i*N+k]/A[k*N+k]; */
/*    /\*  for (i=k+1;i<N;i++) *\/ */
/*       for (j=k+1;j<N;j++) */
/*         A[i*N+j] = A[i*N+j] - A[i*N+k]*A[k*N+j]; */
/*     } */
/*   } */
  
  int *sizedim;
  int *start;
  int R; //Remain
  int itr = 0;

  sizedim = (int*)malloc(M*sizeof(int));
  start = (int*)malloc(M*sizeof(int));
  R = N;

  t1 = GetTickCount();
#pragma omp parallel
  {
  //printf("The number of thread: %d\n", omp_get_num_threads());
#pragma omp master
      {
          while (N-offset>M){
            //  printf(" Iteration: %d\n", itr++);
              for (i=0;i<M;i++){
                  if (i<R%M){
                      sizedim[i]=R/M+1;
                      start[i]=(R/M+1)*i;
                  }
                  else{
                      sizedim[i]=R/M;
                      start[i]=(R/M+1)*(R%M)+(R/M)*(i-R%M);
                  }
                  //printf("%i,%i \n",sizedim[i],start[i]);
              }

              //Print_Matrix(sizedim,1,M);

              stage1(A, offset, sizedim, start, N, M);
              //Print_Matrix(A,N,N);
              stage2(A, offset, sizedim, start, N, M);
              //Print_Matrix(A,N,N);
              stage3(A, offset, sizedim, start, N, M);

              offset+=sizedim[0];
              R=R-sizedim[0];
              //Print_Matrix(A,N,N);
          } //while
      } //master
  } //omp parallel
  ProcessDiagonalBlock(&A[offset*N+offset], N-offset, N);

  t2 = GetTickCount();

  printf("Time for LU-decomposition in secs: %f \n", (t2-t1)/1000000);
  //Print_Matrix(A,N,N);


/*   while (N-offset>Block){ */
/*     stepLU(A,Block,offset,N); */
/*     offset+=Block; */
/*   } */
/*   ProcessDiagonalBlock(&A[offset*N+offset], N-offset, N); */

  //Print_Matrix(A,N,N);
#ifdef CHECK
  /* PROOF OF CORRECTNESS */
 
  for (i=0;i<N;i++)
    for (j=0;j<N;j++)
      if (i>j)
	L[i*N+j] = A[i*N+j];
      else
	U[i*N+j] = A[i*N+j];
  for (i=0;i<N;i++)
    L[i*N+i] = 1;

  //printf("L=\n");
  //Print_Matrix(L,N,N);
  //printf("U=\n");
  //Print_Matrix(U,N,N);

  for (i=0;i<N;i++)
    for (j=0;j<N;j++){
      temp2=0;
      for (k=0;k<N;k++)
	temp2+=L[i*N+k]*U[k*N+j];
      if ((A2[i*N+j]-temp2)/A2[i*N+j] >0.1 || (A2[i*N+j]-temp2)/A2[i*N+j] <-0.1)
	temp++;
    }
  printf("Errors = %d \n", temp);
#endif
  return 0;

}

void stage1(double *A, int offset, int *sizedim, int *start, int N, int M)
{
  // always start[0] is 0, so it is not used;
  ProcessDiagonalBlock(&A[offset*N+offset], sizedim[0], N);
}
void stage2(double *A, int offset, int *sizedim, int *start, int N, int M)
{
  int x=offset, y=offset;
  int B = sizedim[0]; 
  int i;
  int L1 = sizedim[0];
  int L2, L3;
  /* Processing only one big block in column and row */
  //ProcessBlockOnRow(&A[x*N+(B+y)], &A[x*N+y], B, N-(B+x), N);
  //ProcessBlockOnColumn(&A[(B+x)*N+y], &A[x*N+y], B, N-(B+y), N);
  for (i=1;i<M;i++){
    L2 = sizedim[i];
    L3 = sizedim[i];
    #pragma omp task firstprivate(i, L1, L2,x, y, N)
    ProcessBlockOnColumn(&A[(x+start[i])*N+y], &A[x*N+y], L1, L2, N);
    #pragma omp task firstprivate(i, L1, L2,x, y, N)
    ProcessBlockOnRow(&A[x*N+(y+start[i])], &A[x*N+y], L1, L3, N);
  }
  #pragma omp taskwait
}

void stage3(double *A, int offset, int *sizedim, int *start, int N, int M)
{
  int x=offset, y=offset;
  int B = sizedim[0];
  int i,j;
  int L1 = sizedim[0];
  int L2, L3;
  //ProcessInnerBlock(&A[(B+x)*N+(B+y)],  &A[x*N+(B+y)], &A[(B+x)*N+y], B, N-(B+y), N-(B+x), N);
  for (i=1;i<M;i++)
    for (j=1;j<M;j++){
      L2 = sizedim[i];
      L3 = sizedim[j];
      #pragma omp task firstprivate(i,j,M,N,x,y,L1,L2,L3)
      ProcessInnerBlock(&A[(x+start[i])*N+(y+start[j])],  &A[x*N+(y+start[j])], &A[(x+start[i])*N+y], L1, L2, L3, N);
    }
#pragma omp taskwait

}

void ProcessDiagonalBlock(double *A, int L1, int N)
/* *A is a pointer to the block processed */
/* The size of the diagonal block is L1xL1 */
/* N is the size of the matrix in one dimension */
{
  int i,j,k;
  for (i=0;i<L1;i++)
    for (j=i+1;j<L1;j++){
      A[j*N+i]/=A[i*N+i];
/*       DAXPY(&A[j*N+(i+1)],&A[i*N+(i+1)] ,-A[j*N+i],L1-(i+1),1); */
      for (k=i+1;k<L1;k++)
        A[j*N+k] = A[j*N+k] - A[j*N+i]*A[i*N+k];
    }
}

void ProcessBlockOnColumn(double *A, double *D, int L1, int L2, int N)
/* The size of the column block is L2xL1 */
{
/* *A is a pointer to the column block processed */
/* *D is a pointer to the diagonal block required */
/* The size of the column block is L2xL1 */
/* The size of the diagonal block is L1xL1 */
  int i,j,k;
    for (i=0;i<L1;i++)
    for (j=0;j<L2;j++){
      A[j*N+i]/=D[i*N+i];
/*       DAXPY(&A[j*N+(i+1)],&D[i*N+(i+1)],-A[j*N+i],L1-(i+1),1); */
      for (k=i+1;k<L1;k++)
	A[j*N+k]+=-A[j*N+i]*D[i*N+k];
    }
}

void ProcessBlockOnRow(double *A, double *D, int L1, int L3, int N)
/* The size of the row block is L2xL1 */
{
/* *A is a pointer to the row block processed */
/* *D is a pointer to the diagonal block required */
/* The size of the row block is L1xL3 */
/* The size of the diagonal block is L1xL1 */
  int i,j,k;
  for (i=0;i<L1;i++)
    for (j=i+1;j<L1;j++)
/*       DAXPY(&A[N*j],&A[N*i],-D[j*N+i],L3,1); */
      for (k=0;k<L3;k++)
	A[j*N+k]+=-D[j*N+i]*A[i*N+k];
}

void ProcessInnerBlock(double *A, double *R, double *C, int L1, int L2, int L3, int N)
{
/* *A is a pointer to the inner block processed */
/* *R is a pointer to the row block required */
/* *C is a pointer to the column block required */
/* The size of the row block is L1xL3 */
/* The size of the column block is L2xL1 */
/* The size of the inner block is L2xL3 */
  int i,j,k;
  for (i=0;i<L1;i++)
    for (j=0;j<L2;j++)
/*       DAXPY(&A[N*j],&R[N*i],-C[j*N+i],L3,1); */
      for (k=0;k<L3;k++)
	A[j*N+k]+=-C[j*N+i]*R[i*N+k];
      
}

void Print_Matrix (double *v, int M, int N)
{

  int i,j;

  printf("\n");
  for (i=0;i<M;i++){
    for (j=0;j<N;j++)
      printf("%.2f,",v[i*N+j]);
    printf("\n");
  }
  printf("\n");

  return;
}

 /*void InitMatrix(double *A, int N)
{
  long long	i, j;
  struct timeval	InitTime;
  
  gettimeofday(&InitTime, NULL);
  
  srand(InitTime.tv_sec * 1000000 + InitTime.tv_usec);
  
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      A[i * N + j] = ( rand() - RAND_MAX/2) / (RAND_MAX/1000 );
      if (i == j) {
	A[i * N + i] *= 10;
      }
      //A[i*N+j]=i+j+1;
    }
  }
  } 
*/

void InitMatrix2(double *A, int N)
{
  long long	i, j,k;
  
  for (i=0;i<N*N;i++)
    A[i]=0;
  for (k=0;k<N;k++)
    for (i = k; i < N; i++)
      for (j = k; j < N; j++)
	A[i * N + j] +=1;
}

void InitMatrix3(double *A, int N)
{
  long long i,j,k;
  double *L, *U;
  L = (double*) malloc(N*N*sizeof(double));
  U = (double*) malloc(N*N*sizeof(double));
#pragma omp parallel 
{
#pragma omp for private(i,j)
  for (i=0;i<N;i++)
    for (j=0;j<N;j++){
      A[i*N+j]=0;
      if (i>=j)
	L[i*N+j] = i-j+1;
      else
	L[i*N+j] = 0;
      if (i<=j)
	U[i*N+j] = j-i+1;
      else
	U[i*N+j] = 0;
    }
#pragma omp for private(i,j,k)
  for (i=0;i<N;i++)
    for (j=0;j<N;j++)
      for (k=0;k<N;k++)
	A[i*N+j]+=L[i*N+k]*U[k*N+j];
}
}
