
#define HPX_LIMIT 10

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <omp.h>
#include <math.h>
#include <sys/time.h>

#include <hpx/hpx_main.hpp>
#include <hpx/hpx_fwd.hpp>
#include <hpx/async.hpp>
#include <hpx/include/future.hpp>
#include <hpx/lcos/future_wait.hpp>


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
int M=1;

int main (int argc, char *argv[])
{
    double *A,*A2,*L,*U, temp2;
    int i,j,k;
    int temp=0;
    int offset = 0;
    double t1,t2;
    int do_check = 1;

    if( argc > 1 )
        N = atoi(argv[1]);

    if( argc > 2 )
        M = atoi(argv[2]);

    A = (double *)malloc (N*N*sizeof(double));
    A2 = (double *)malloc (N*N*sizeof(double));
    L = (double *)malloc (N*N*sizeof(double));
    U = (double *)malloc (N*N*sizeof(double));
    if( A==NULL || A2==NULL || L==NULL || U==NULL) {
        printf("Can't allocate memory\n");
        exit(1);
    }

    InitMatrix3(A,N);
    for(i=0; i<N*N; i++) {
        A2[i] = A[i]; // Copy of A for verification of correctness
        L[i] = 0;
        U[i] = 0;
    }

    int *sizedim;
    int *start;
    int R; //Remain
    int itr = 0;

    sizedim = (int*)malloc(M*sizeof(int));
    start = (int*)malloc(M*sizeof(int));
    R = N;

    t1 = GetTickCount();
    while (N-offset>M){
        for (i=0;i<M;i++){
            if (i<R%M){
                sizedim[i]=R/M+1;
                start[i]=(R/M+1)*i;
            }
            else{
                sizedim[i]=R/M;
                start[i]=(R/M+1)*(R%M)+(R/M)*(i-R%M);
            }
        }
        stage1(A, offset, sizedim, start, N, M);
        stage2(A, offset, sizedim, start, N, M);
        stage3(A, offset, sizedim, start, N, M);

        offset+=sizedim[0];
        R=R-sizedim[0];
    }
    ProcessDiagonalBlock(&A[offset*N+offset], N-offset, N);

    t2 = GetTickCount();

    printf("Time for LU-decomposition in secs: %f \n", (t2-t1)/1000000);

    if(do_check) {
        for (i=0;i<N;i++)
            for (j=0;j<N;j++)
                if (i>j)
                    L[i*N+j] = A[i*N+j];
                else
                    U[i*N+j] = A[i*N+j];
        for (i=0;i<N;i++)
            L[i*N+i] = 1;

        for (i=0;i<N;i++)
            for (j=0;j<N;j++){
                temp2=0;
                for (k=0;k<N;k++)
                    temp2+=L[i*N+k]*U[k*N+j];
                if ((A2[i*N+j]-temp2)/A2[i*N+j] >0.1 || (A2[i*N+j]-temp2)/A2[i*N+j] <-0.1)
                    temp++;
            }
        printf("Errors = %d \n", temp);
    }
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
    std::vector<hpx::unique_future<void> > futures;
    futures.reserve((M-1)*2);
    for (i=1;i<M;i++){
        L2 = sizedim[i];
        L3 = sizedim[i];
        futures.push_back(hpx::async(&ProcessBlockOnColumn, &A[(x+start[i])*N+y], &A[x*N+y], L1, L2, N));
        futures.push_back(hpx::async(&ProcessBlockOnRow, &A[x*N+(y+start[i])], &A[x*N+y], L1, L3, N));
    }
    hpx::wait_all(futures);
}

void stage3(double *A, int offset, int *sizedim, int *start, int N, int M)
{
    int x=offset, y=offset;
    int B = sizedim[0];
    int i,j;
    int L1 = sizedim[0];
    int L2, L3;
    //ProcessInnerBlock(&A[(B+x)*N+(B+y)],  &A[x*N+(B+y)], &A[(B+x)*N+y], B, N-(B+y), N-(B+x), N);
    std::vector<hpx::unique_future<void> > futures;
    futures.reserve((M-1)*(M-1));
    for (i=1;i<M;i++)
        for (j=1;j<M;j++){
            L2 = sizedim[i];
            L3 = sizedim[j];
            futures.push_back(hpx::async(ProcessInnerBlock, &A[(x+start[i])*N+(y+start[j])],  &A[x*N+(y+start[j])], &A[(x+start[i])*N+y], L1, L2, L3, N));
        }
    hpx::wait_all(futures);
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
    //#pragma omp parallel 
    {
        //#pragma omp for private(i,j)
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
        //#pragma omp for private(i,j,k)
        for (i=0;i<N;i++)
            for (j=0;j<N;j++)
                for (k=0;k<N;k++)
                    A[i*N+j]+=L[i*N+k]*U[k*N+j];
    }
}
