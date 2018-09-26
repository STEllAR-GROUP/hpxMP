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

            for(i = 0; i < 4; i++) 
            {
#pragma omp task firstprivate(i)
                {
                    printf("x%d = %d\n", i, x + i );
                }
            }
#pragma omp taskwait
        }
    }
    printf("final x = %d\n", x);
    if(x != 11)
        return 1;
    return 0;
}
