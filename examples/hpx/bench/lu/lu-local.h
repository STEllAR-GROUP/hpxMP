#include "lu-utils.h"

void getBlockList(std::vector<std::vector<block>> &, int , int );

block ProcessDiagonalBlock( int size, block B);
block ProcessBlockOnColumn( int size, block B1, block B2);
block ProcessBlockOnRow( int size, block B1, block B2);
block ProcessInnerBlock( int size, block B1, block B2, block B3);


