#include <stdio.h>

int main() {
    int x = 10, i = 8;
    printf("%d\n", x);
#pragma omp parallel
    {
#pragma omp task
        {
            i = 9;
            x = 5;
            printf("x = %d,%d\n", x, i);
        }
    }
    return 0;
}
