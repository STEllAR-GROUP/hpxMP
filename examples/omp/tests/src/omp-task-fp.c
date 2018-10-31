#include <stdio.h>

int main() {
    int x = 10, i = 0;
#pragma omp parallel
    {
#pragma omp single
        {
#pragma omp task
            {
                x = x + 1;
                printf("x = %d\n", x);
            }
#pragma omp taskwait
            int j = 0;

            for(i = 0; i < 4; i++) 
            {
#pragma omp task firstprivate(i, j)
                {
                    j += i;
                    printf("x (%d) = %d\n", i, x + i );
                    printf("j (%d) = %d\n", i, j );
                }
            }
#pragma omp taskwait
            printf(" j = %d\n",j);
        }
    }
    printf("final x = %d\n", x);
    return 0;
}
