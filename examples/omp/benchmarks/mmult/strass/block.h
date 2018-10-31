
struct block {
    int size;
    int start;
    int height;
    block(int size, int startAddress, int H) : size(size), start(startAddress), height(H){}
    block() : size(0), start(0), height(0){}
};

block** getBlockList( int size, int blocksize);
