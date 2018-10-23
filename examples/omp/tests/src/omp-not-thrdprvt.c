#include <stdio.h>

int x, y;

int main() {

#pragma omp parallel
    {
        x = omp_get_thread_num();
    }

#pragma omp parallel
    {
        if(x % 2 == 0)
            y = x + 1;
        else
            y = 0;
    }
#pragma omp parallel
    {
        printf("%d, %d %d\n", x, y, omp_get_thread_num());
    }
#pragma omp parallel
    {
        printf("%d, %d %d\n", x, y, omp_get_thread_num());
    }
}
