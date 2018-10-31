#include <stdio.h>

int main() {
#pragma omp parallel
    {
#pragma omp single 
        printf("one thread\n");
        printf("all threads\n");
    }
    return 0;
}
