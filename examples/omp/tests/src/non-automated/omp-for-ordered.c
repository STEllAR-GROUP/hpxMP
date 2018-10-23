#include <stdio.h>
#include <omp.h>

int main() {
#pragma omp parallel
    {
        int i;

#pragma omp single
        printf("\nloop0, static, chunk 1, no ordered\n");
#pragma omp for schedule(static, 1)
        for(i = 0; i < 10 ; i++) {
                printf("Thread %d, i = %d\n",omp_get_thread_num(), i);
        }

#pragma omp single
        printf("loop1, no schedule\n");
#pragma omp for ordered
        for(i = 0; i < 10 ; i++) {
#pragma omp ordered
            {
                printf("Thread %d, i = %d\n",omp_get_thread_num(), i);
            }
        }

#pragma omp single
        printf("\nloop2, static\n");
#pragma omp for schedule(static) ordered
        for(i = 0; i < 10 ; i++) {
#pragma omp ordered
            {
                printf("Thread %d, i = %d\n",omp_get_thread_num(), i);
            }
        }
    
#pragma omp single
        printf("\nloop3, static, chunk 1\n");
#pragma omp for schedule(static, 1) ordered
        for(i = 0; i < 10 ; i++) {
#pragma omp ordered
            {
                printf("Thread %d, i = %d\n",omp_get_thread_num(), i);
            }
        }
    
#pragma omp single
        printf("\nloop4, static, chunk 2\n");
#pragma omp for schedule(static, 2) ordered
        for(i = 0; i < 10 ; i++) {
#pragma omp ordered
            {
                printf("Thread %d, i = %d\n",omp_get_thread_num(), i);
            }
        }
    
    
    }

    return 0;
}

