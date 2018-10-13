#include <stdio.h>

int main (void)
{
    int i = 10;
#pragma omp parallel private(i)
    {
        printf("i = %d\n", i);
        i++;
    }
    printf("i = %d\n", i);
#pragma omp parallel firstprivate(i)
    {
        printf("i = %d\n", i);
        i++;
    }
    printf("i = %d\n", i);
#pragma omp parallel
#pragma omp task firstprivate(i)
    {
        printf("i = %d\n", i);
        i++;
    }
    printf("i = %d\n", i);

#pragma omp parallel
#pragma omp task shared(i)
    {
        printf("i = %d\n", i);
        i++;
    }
    printf("i = %d\n", i);
    return 0;
}
