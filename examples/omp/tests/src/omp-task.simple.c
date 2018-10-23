#include <stdio.h>

int main() {
    int x = 10, i = 0;
#pragma omp parallel
    {
        printf("x par = %d\n", x);
        printf("i par = %d\n", i);
    }
    printf("final x = %d\n", x);
    return 0;
}
