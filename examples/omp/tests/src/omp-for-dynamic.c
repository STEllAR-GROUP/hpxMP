#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int i,j;


#pragma omp parallel for schedule(static)
    for(i = 0; i < 11; i++) 
    {
        printf("Static Hello World %d\n", i);
    }

#pragma omp parallel for schedule(static, 1)
    for(i = 0; i < 11; i++) 
    {
        printf("Static1 Hello World %d\n", i);
    }

#pragma omp parallel for schedule(static, 2)
    for(i = 0; i < 11; i++) 
    {
        printf("Static2 Hello World %d\n", i);
    }

    printf("\nDynamic loop\n");
#pragma omp parallel for schedule(dynamic)
    for(i = 0; i < 9; i++) 
    {
        printf("Thread %d: Dynamic Hello World %d\n", omp_get_thread_num(), i);
    }

    printf("\nStatic Ordered loop\n");
#pragma omp parallel for schedule(static) ordered
    for(i = 0; i < 10; i++) 
    {
#pragma omp ordered
        printf("Thread %d: Static Ordered Hello World %d\n", omp_get_thread_num(), i);
    }

    printf("\nDynamic Ordered loop\n");
#pragma omp parallel for schedule(dynamic) ordered
    for(i = 0; i < 16; i++) 
    {
#pragma omp ordered
        printf("Thread %d: Dynamic Ordered Hello World %d\n", omp_get_thread_num(), i);
    }
    

    return 0;
}
