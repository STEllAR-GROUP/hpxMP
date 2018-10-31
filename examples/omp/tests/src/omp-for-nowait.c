#include <stdio.h>

int main() {
    int i,j;

#pragma omp parallel 
    {
        printf("Hello From thread %d\n", omp_get_thread_num());
#pragma omp for nowait
        for(i = 0; i < 11; i++) 
        {
            printf("Hello World %d\n", i);
        }
#pragma omp for nowait
        for(i = 0; i < 12; i += 2) 
        {
            printf("Hello Again %d\n", i);
        }
#pragma omp for
        for(i = 0; i < 13; i += 3) 
        {
            printf("Second Hello %d\n", i);
        }
#pragma omp for
        for(i = 0; i < 14; i += 4)
        {
            printf("Final Hello %d\n", i);
        }
    } 
    return 0;
}
