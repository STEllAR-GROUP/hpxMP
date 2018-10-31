#include <vector>

struct block {
    int size;
    int start;
    int height;
    block(int size, int startAddress, int H) : size(size), start(startAddress), height(H){}
    block() : size(0), start(0), height(0){}
};

unsigned long GetTickCount();
void InitMatrix3(int size);
void fastInitMatrix(int size);

void Print_Matrix( std::vector<double> &v, int size);
void checkResult( std::vector<double> &originalA, int size );

