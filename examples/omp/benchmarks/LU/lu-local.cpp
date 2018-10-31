
#include "lu-utils.h"
#include <stdio.h>

extern std::vector<double> A;

using std::vector;

//void getBlockList( vector<vector<block>> &blockList, int numBlocks, int size)
void getBlockList( block ***blockList, int numBlocks, int size)
{
    int blockSize, start, height;
    for(int i=0; i < numBlocks; i++) {
        //blockList.push_back(vector<block>());
        blockList[0][i] = new block[numBlocks];
        blockList[1][i] = new block[numBlocks];
    }

    height = size/numBlocks;
    if(size%numBlocks > 0) {
        height += 1;
    }
    for(int i=0; i < numBlocks; i++) {
        if(i < size % numBlocks) {
            blockSize = size/numBlocks+1;
            start = (size/numBlocks+1)*i;
        } else {
            blockSize = size/numBlocks;
            start = (size/numBlocks+1)*(size%numBlocks) + (size/numBlocks)*(i-size%numBlocks);
        }
        //blockList[0].push_back( block( blockSize, start, height));
        blockList[0][0][i] =  block( blockSize, start, height);
    }
    for(int i = 1; i < numBlocks; i++) {
        //height = blockList[0][i].size;
        height = blockList[0][0][i].size;
        for(int j = 0; j < numBlocks; j++) {
            //blockSize = blockList[0][j].size;
            //start = blockList[i-1][j].start + blockList[i-1][0].height * size;
            //blockList[i].push_back( block( blockSize, start, height));
            blockSize = blockList[0][0][j].size;
            start = blockList[0][i-1][j].start + blockList[0][i-1][0].height * size;
            blockList[0][i][j] = block( blockSize, start, height);
        }
    }
}

block diag_op( int size,  block B) {
    for(int i = 0; i < B.size; i++) {
        for(int j = i+1; j < B.size; j++){
            A[B.start+j*size+i] /= A[B.start+i*size+i];
            for(int k = i+1; k < B.size; k++) {
                A[B.start+j*size+k] -= A[B.start+j*size+i] * A[B.start+i*size+k];
            }
        }
    }
    return  B;
}

block col_op( int size, block B1, block B2) {
    for(int i=0; i < B2.size; i++) {
        for(int j=0; j < B1.height; j++) {
            A[B1.start+j*size+i] /= A[B2.start+i*size+i];
            for(int k = i+1; k < B2.size; k++) {
                A[B1.start+j*size+k] += -A[B1.start+j*size+i] * A[B2.start+i*size+k];
            }
        }
    }
    return B1;
}

block row_op( int size, block B1, block B2) {
    for(int i=0; i < B2.size; i++)
        for(int j=i+1; j < B2.size; j++)
            for(int k=0; k < B1.size; k++)
                A[B1.start+j*size+k] += -A[B2.start+j*size+i] * A[B1.start+i*size+k];
    return B1;
}

block inner_op( int size, block B1, block B2, block B3) {
    for(int i=0; i < B3.size; i++)
        for(int j=0; j < B1.height; j++)
            for(int k=0; k < B2.size; k++)
                A[B1.start+j*size+k] += -A[B3.start+j*size+i] * A[B2.start+i*size+k];
    return B1;
}

