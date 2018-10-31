#include "lu-utils.h"

//void getBlockList(std::vector<std::vector<block>> &, int , int );
void getBlockList(block***, int , int );

block diag_op( int size, block B);
block col_op( int size, block B1, block B2);
block row_op( int size, block B1, block B2);
block inner_op( int size, block B1, block B2, block B3);


