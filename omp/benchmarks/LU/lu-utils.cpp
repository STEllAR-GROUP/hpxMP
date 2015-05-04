#include "lu-utils.h"
#include <sys/time.h>
#include <cstdlib>
#include <stdio.h>


using std::vector;

extern std::vector<double> A;

void initA( vector<double> &L, vector<double> &U, int in, int size, int range)
{
    //TODO: init A using logic in L and U in this loop. Make work on blocks
    for(int i = in; i < in + range; i++) {
        for(int j = 0; j < size; j++) {
            for(int k = 0; k < size; k++) {
                if( i >= k && k <= j)
                    A[i * size + j] += (i-k+1)*(j-k+1);
                //A[i * size + j] += L[i * size + k] * U[k*size + j];
            }
        }
    }
}

void initLU( vector<double> &L, vector<double> &U, int in, int size, int range)
{
    for(int i = in; i < in + range; i++) {
        for(int j = 0; j < i; j++) { //i > j
            L[i*size + j] = i-j+1;
            U[i*size + j] = 0; 
        }
        //i == j
        L[i*size + i] = 1;
        U[i*size + i] = 1;
        for(int j = i + 1; j < size; j++){//i < j
            L[i*size + j] = 0;
            U[i*size + j] = j-i+1;
        }
/*            if(i > j || i == j)
                L[i*size + j] = i-j+1;
            else // i < j
                L[i*size + j] = 0;
            if(i < j || i == j)
                U[i*size + j] = j-i+1;
            else // j > i
                U[i*size + j] = 0; 
	}*/
    }
}

void fastInitMatrix(int size)
{
    std::srand(0);
    for(int i=0; i < size*size;i++) {
        A[i] = std::rand();
    }
}


void InitMatrix3(int size)
{
    double *L = new double[size*size]{0};
    double *U = new double[size*size]{0};
#pragma omp parallel for
    for(int i=0;i<size;i++) {
        for(int j=0; j<=i; j++){
            L[i*size+j] = i-j+1;
        }
        for(int j=i;j<size;j++){
            U[i*size+j] = j-i+1;
        }
    }
#pragma omp parallel for
    for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
            for(int k=0;k<size;k++)
                A[i*size+j]+=L[i*size+k]*U[k*size+j];
    delete L;
    delete U;
}

void Print_Matrix(vector<double> &v, int size)
{
    printf( "\n" );
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++)
            printf( "%5.1f, ", v[i*size + j] );
        printf( "\n" );
    }
    printf( "\n" );
}

void checkResult( vector<double> &originalA, int size )
{
    int errors = 0;
    double temp2;
    vector<double> L(size*size, 0);
    vector<double> U(size*size, 0);
    for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
            if (i>j)
                L[i*size+j] = A[i*size+j];
            else
                U[i*size+j] = A[i*size+j];
    for(int i=0;i<size;i++)
        L[i*size+i] = 1;

    for(int i=0;i<size;i++)
        for(int j=0;j<size;j++){
            temp2=0;
            for(int k=0;k<size;k++)
                temp2+=L[i*size+k]*U[k*size+j];
            if( (originalA[i*size+j]-temp2) / originalA[i*size+j] > 0.1 || (originalA[i*size+j]-temp2) / originalA[i*size+j] < -0.1 ){
                printf("error:[%d][%d] ", i, j);
                errors++;
            }
        }
    if(errors > 0){
        printf("A:\n");
        Print_Matrix(A, size);
        printf("originalA:\n");
        Print_Matrix(originalA, size);
    }

    printf("Errors = %d \n", errors);
}

unsigned long GetTickCount()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000000) + (tv.tv_usec);
}
