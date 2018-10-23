#include <stdio.h>

int main() {
    int i,j;

    printf("loop 1: stride of -1, 10 - 0\n");
#pragma omp parallel for 
    for(i = 10; i > 0; i--) 
    {
        printf("Hello world %d\n",i);
    }

    printf("loop 2: stride of -1, 10 - -1\n");
#pragma omp parallel for 
    for(i = 10; i > -1; i--) 
    {
        printf("Hello world %d\n",i);
    }

    printf("loop 3: stride of -2, 10 - 0\n");
#pragma omp parallel for 
    for(i = 10; i > 0; i -= 2) 
    {
        printf("Hello world %d\n",i);
    }

    printf("loop 4: stride of -2, 10 - -1\n");
#pragma omp parallel for 
    for(i = 10; i > -1; i -= 2) 
    {
        printf("Hello world %d\n",i);
    }

    //stride larger than range
    //range less than num_threads
    //
    return 0;
}
