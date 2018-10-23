#include <stdio.h>

int main() {
#pragma omp parallel
    {
#pragma omp master
        printf("this should be thread 0: %d\n", omp_get_thread_num());
        printf("all threads: %d\n", omp_get_thread_num());
    }
    return 0;
}
