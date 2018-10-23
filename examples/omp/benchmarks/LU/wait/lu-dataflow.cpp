// Static blocked LU Decomposition
#include <stdio.h>
#include <cstdlib>
#include "lu-local.h"

using std::vector;

vector<double> A;


//void init_df(vector<vector<vector<block>>> &block_list, int numBlocks, int size) {
    //getBlockList(block_list[0], numBlocks, size);
    //block_list[1].resize(numBlocks);
void init_df(block ***block_list, int numBlocks, int size) {
    
    block_list[0] = new block*[numBlocks];
    block_list[1] = new block*[numBlocks];
    getBlockList(block_list, numBlocks, size);

    //for(int i = 0; i < numBlocks; i++){
    //    block_list[1][i].resize( numBlocks );
    //}

#pragma omp task depend(inout: block_list[0][0][0])
    block_list[0][0][0] = diag_op( size, block_list[0][0][0] );
    for(int i = 1; i < numBlocks; i++) {
#pragma omp task depend(  in : block_list[0][0][0]) \
                 depend(inout: block_list[0][0][i])
        block_list[0][0][i] = row_op( size, block_list[0][0][i], 
                                            block_list[0][0][0] );
    }
    for(int i = 1; i < numBlocks; i++) {
#pragma omp task depend(  in : block_list[0][0][0]) \
                 depend(inout: block_list[0][i][0])
        block_list[0][i][0] = col_op( size, block_list[0][i][0], 
                                            block_list[0][0][0] );
        for(int j = 1; j < numBlocks; j++) {
#pragma omp task depend(  in : block_list[0][0][j], block_list[0][i][0]) \
                 depend(inout: block_list[0][i][j] )
            block_list[0][i][j] = inner_op( size, block_list[0][i][j],
                                                  block_list[0][0][j],
                                                  block_list[0][i][0] );
        }
    }
#pragma omp taskwait
}

void LU( int size, int numBlocks)
{
    //vector<vector<vector<block>>> block_list(2);
    block ***block_list = new block**[2];


#pragma omp parallel
{
#pragma omp master
{
    //init_df(block_list, numBlocks, size);
    init_df(block_list, numBlocks, size);

    for(int i = 1; i < numBlocks; i++) {
#pragma omp task depend( in: block_list[(i-1)%2][i][i]) \
                 depend(out: block_list[i%2][i][i])
        block_list[i%2][i][i] = diag_op( size, block_list[(i-1)%2][i][i] );
        for(int j = i + 1; j < numBlocks; j++){
#pragma omp task depend( in: block_list[(i-1)%2][i][j], block_list[i%2][i][i]) \
                 depend(out: block_list[i%2][i][j])
            block_list[i%2][i][j] = row_op( size, block_list[(i-1)%2][i][j],
                                                  block_list[ i   %2][i][i] );
        }
        for(int j = i + 1; j < numBlocks; j++){
#pragma omp task depend( in: block_list[(i-1)%2][j][i], block_list[i%2][i][i]) \
                 depend(out: block_list[i%2][j][i])
            block_list[i%2][j][i] = col_op( size, block_list[(i-1)%2][j][i], 
                                                  block_list[ i   %2][i][i] );
            for(int k = i + 1; k < numBlocks; k++) {
#pragma omp task depend( in: block_list[(i-1)%2][j][k], \
                             block_list[i%2][i][k], block_list[i%2][j][i]) \
                 depend(out: block_list[i%2][j][k])
                block_list[i%2][j][k] = inner_op( size, block_list[(i-1)%2][j][k], 
                                                        block_list[ i   %2][i][k],
                                                        block_list[ i   %2][j][i] );
            }
        }
#pragma omp taskwait
    }
}
}
}

int main(int argc, char *argv[])
{
    vector<double> originalA;
    int size = 1000;
    int numBlocks = 10;
    unsigned long t1, t2;
    bool runCheck = false;

    if( argc > 1 )
        size = atoi(argv[1]);
    if( argc > 2 )
        numBlocks = atoi(argv[2]);
    if( argc > 3 )
        runCheck = true;
    printf("size = %d, numBlocks = %d\n", size, numBlocks);

    A.resize(size*size, 0);
    if(runCheck) {
        printf("Error checking enabled\n");
        printf("initializing\n");
        InitMatrix3( size );
        printf("initialization complete\n");
        originalA.reserve(size*size);
        for(int i = 0; i < size * size; i++) {
            originalA[i] = A[i];
        }
    } else {
        printf("fast initialization\n");
        fastInitMatrix(size);
        printf("initialization complete\n");
    }

    if(numBlocks == 1) {
        t1 = GetTickCount();
        printf("starting serial LU\n");
        diag_op( size, block(size, 0, size));
        t2 = GetTickCount();
    } else if( numBlocks > 1) {
        printf("starting LU\n");
        t1 = GetTickCount();
        LU( size, numBlocks);
        t2 = GetTickCount();
    } else { 
        printf("Error: numBlocks must be greater than 0.\n");
        return 0;
    }
    printf("Time for LU-decomposition in secs: %f \n", (t2-t1)/1000000.0);
    
    if(runCheck) {
        checkResult( originalA,  size );
    }
    return 0;
}
