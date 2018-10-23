#include <stdlib.h>
#include <vector>
#include <iostream>
using std::cout;
using std::endl;
using std::vector;

struct block {
    double *ptr;
    int stride{0};
    int row{0};
    int col{0};
    int width{0};
    int height{0};
    vector<double> data;

    block(const block& other) : ptr(other.ptr), stride(other.stride), 
                                row(other.row), col(other.col),
                                width(other.width), height(other.height) 
                                //data(other.stride * other.stride)
    { }

    block(double *matrix, int size) {
        ptr = matrix;
        stride = size;
        height = size;
        width = size;
    }

    block(int size) : data(size*size)
    {
        stride = size;
        width = size;
        height = size;
        ptr = data.data();

        const int RM = 100;
        double rv1 = (rand() % RM) / ((double)RM);
        double rv2 = (rand() % RM) / ((double)RM);
        for (int i = 0; i < size*size; i++) {
            data[i] = ((i+1) * rv1) / ((i+1) * rv2);
        }
    }

    void add_scratch() {
        data.resize(width * height);
        ptr = data.data();
        row = 0;
        col = 0;
        stride = width;
    }
    double* operator[](int idx) const {
        return &(ptr[(row+idx)*stride + col]);
    }
    block block11(){
        block tmp(ptr, stride);
        tmp.row = row;
        tmp.col = col;
        tmp.width = width/2;
        tmp.height = height/2;
        return tmp;
    }
    block block12(){
        block tmp(ptr, stride);
        tmp.row = row;
        tmp.col = col + width/2;
        tmp.width = width - (width/2);
        tmp.height = height/2;
        return tmp;
    }
    block block21(){
        block tmp(ptr, stride);
        tmp.row = row + height/2;
        tmp.col = col;
        tmp.width = width/2;
        tmp.height = height - (height/2);
        return tmp;
    }
    block block22(){
        block tmp(ptr, stride);
        tmp.row = row + height/2;
        tmp.col = col + width/2;
        tmp.width = width - (width/2);
        tmp.height = height - (height/2);
        return tmp;
    }
};
