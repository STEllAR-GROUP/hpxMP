#include <stdio.h>

int main() {
    int i,j;

#pragma omp parallel for
    for(i = 0; i < 11; i++) 
    {
        printf("Hello World %d\n", i);
    }
    
    printf("loop 2: separate parallel and for pragmas\n");
#pragma omp parallel 
    {
#pragma omp for 
        for(i = 0; i < 11; i++) 
        {
            printf("Hello World %d\n", i);
        }
    }
    printf("loop 3: stride of 2, 0-9\n");
#pragma omp parallel for 
    for(i = 0; i < 10; i += 2) 
    {
        printf("Hello world %d\n",i);
    }
    printf("loop 4: stride of 2, 0-10\n");
#pragma omp parallel for 
    for(i = 0; i <= 10; i += 2) 
    {
        printf("Hello world %d\n",i);
    }
    printf("loop 5: stride of 1, -5-4\n");
#pragma omp parallel for 
    for(i = -5; i < 5; i++) 
    {
        printf("Hello world %d\n",i);
    }
    printf("loop 6: stride of 2, -5-4\n");
#pragma omp parallel for 
    for(i = -5; i < 5; i+=2) 
    {
        printf("Hello world %d\n",i);
    }
    printf("\nloop 7: nested par for loops\n");
#pragma omp parallel for
    for(i = 0; i < 5; i++) {
#pragma omp parallel for firstprivate(i)
        for(j = 0; j < 5; j++) {
            printf("Hello World %d, %d\n",i,j);
        }
    }

    //stride larger than range
    //range less than num_threads
    //
    return 0;
}
