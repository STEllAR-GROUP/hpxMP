#include "stdio.h"

int main()
{
#pragma omp parallel
    {
    printf("hello world 1\n");
#pragma omp barrier
    printf("hello world 2\n");
#pragma omp barrier
    printf("hello world 3\n");
#pragma omp barrier
    printf("hello world 4\n");
    }
    return 0;
}
