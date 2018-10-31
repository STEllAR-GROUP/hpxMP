#include <stdio.h>

int main() {
#pragma omp parallel
    {
        printf("Hello World\n");
#pragma omp parallel
        {
            printf("nested parallel region\n");
        }
    }
    return 0;
}
