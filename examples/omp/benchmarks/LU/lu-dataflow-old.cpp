// Static blocked LU Decomposition

#include <stdio.h>

#include "lu-local.h"

using std::vector;

vector<double> A;
auto diag_op  = unwrapped( &ProcessDiagonalBlock );
auto row_op   = unwrapped( &ProcessBlockOnRow );
auto col_op   = unwrapped( &ProcessBlockOnColumn );
auto inner_op = unwrapped( &ProcessInnerBlock );


void init_df(vector<vector<vector<shared_future<block>>>> &dfArray, int numBlocks, int size) {
    vector<vector<block>> blockList;
    getBlockList(blockList, numBlocks, size);
    
    dfArray[0].resize(numBlocks);
    dfArray[1].resize(numBlocks);

    for(int i = 0; i < numBlocks; i++){
        dfArray[0][i].resize( numBlocks );
        dfArray[1][i].resize( numBlocks );
    }

    shared_future<int> fsize = make_ready_future(size);

    dfArray[0][0][0] = async( ProcessDiagonalBlock, size, blockList[0][0] );
    
    for(int i = 1; i < numBlocks; i++) {
        dfArray[0][0][i] = dataflow( row_op, fsize, make_ready_future( blockList[0][i] ), dfArray[0][0][0]);
    }
    for(int i = 1; i < numBlocks; i++) {
        dfArray[0][i][0] = dataflow( col_op, fsize, make_ready_future( blockList[i][0] ), dfArray[0][0][0]);
        for(int j = 1; j < numBlocks; j++) {
            dfArray[0][i][j] = dataflow( inner_op, fsize, make_ready_future( blockList[i][j] ),
                                                   dfArray[0][0][j], dfArray[0][i][0] );
        }
    }
}

void LU( int size, int numBlocks)
{
    vector<vector<vector<shared_future<block>>>> dfArray(2);
    shared_future<int> fsize = make_ready_future(size);

    init_df(dfArray, numBlocks, size);

    for(int i = 1; i < numBlocks; i++) {
        dfArray[i%2][i][i] = dataflow( diag_op, fsize, dfArray[(i-1)%2][i][i]);
        for(int j = i + 1; j < numBlocks; j++){
            dfArray[i%2][i][j] = dataflow( row_op , fsize, 
                                           dfArray[(i-1)%2][i][j], 
                                           dfArray[ i   %2][i][i] );
        }
        for(int j = i + 1; j < numBlocks; j++){
            dfArray[i%2][j][i] = dataflow( col_op, fsize, 
                                           dfArray[(i-1)%2][j][i], 
                                           dfArray[ i   %2][i][i] );
            
            for(int k = i + 1; k < numBlocks; k++) {
                dfArray[i%2][j][k] = dataflow( inner_op, fsize, 
                                               dfArray[(i-1)%2][j][k], 
                                               dfArray[ i   %2][i][k],
                                               dfArray[ i   %2][j][i] );
            }
        }
    }
    wait_all(dfArray[(numBlocks-1)%2][numBlocks-1][numBlocks-1]);
}

int hpx_main(int argc, char *argv[])
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
    InitMatrix3( size );
    if(runCheck) {
        printf("Error checking enabled\n");
        originalA.reserve(size*size);
        for(int i = 0; i < size * size; i++) {
            originalA[i] = A[i];
        }
    }

    if(numBlocks == 1) {
        t1 = GetTickCount();
        ProcessDiagonalBlock( size, block(size, 0, size));
        t2 = GetTickCount();
    } else if( numBlocks > 1) {
        t1 = GetTickCount();
        LU( size, numBlocks);
        t2 = GetTickCount();
    } else { 
        printf("Error: numBlocks must be greater than 0.\n");
        return hpx::finalize();
    }
    printf("Time for LU-decomposition in secs: %f \n", (t2-t1)/1000000.0);
    
    if(runCheck) {
        checkResult( originalA,  size );
    }
    return hpx::finalize();
}

int main(int argc, char *argv[])
{
    using namespace boost::assign;
    std::vector<std::string> cfg;
    cfg += "hpx.os_threads=" +
        boost::lexical_cast<std::string>(hpx::threads::hardware_concurrency());

    return hpx::init(argc, argv, cfg);
}
