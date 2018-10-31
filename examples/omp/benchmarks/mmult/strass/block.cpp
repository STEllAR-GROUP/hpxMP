#include "block.h"


//using std::vector;

//void getBlockList( vector<vector<block>> &blockList, int numBlocks, int size)
block** getBlockList( int size, int blockSize)
{
    int numBlocks = size/blockSize;
    int start;
    block **blockList = new block*[numBlocks];

    for(int i=0; i < numBlocks; i++) {
        blockList[i] = new block[numBlocks];
    }

    int height = size/numBlocks;
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
        blockList[0][i] =  block( blockSize, start, height);
    }
    for(int i = 1; i < numBlocks; i++) {
        height = blockList[0][i].size;
        for(int j = 0; j < numBlocks; j++) {
            blockSize = blockList[0][j].size;
            start = blockList[i-1][j].start + blockList[i-1][0].height * size;
            blockList[i][j] = block( blockSize, start, height);
        }
    }
    return blockList;
}
