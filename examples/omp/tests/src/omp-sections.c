#include <stdio.h>
#include <unistd.h>
#include <omp.h>

int main(int argc, char **argv) {
    int x = 0;
#pragma omp parallel
    {
        printf("entered the parallel region\n");
#pragma omp sections
        {
        printf("entered the sections region\n");
#pragma omp section
            {
                sleep(1);
                printf("section 1, by thread %d\n", omp_get_thread_num());
            }
#pragma omp section
            {
                sleep(2);
                printf("section 2, by thread %d\n", omp_get_thread_num());
            }
#pragma omp section
            {
                sleep(3);
                printf("section 3, by thread %d\n", omp_get_thread_num());
            }
#pragma omp section
            {
                sleep(4);
                printf("section 4, by thread %d\n", omp_get_thread_num());
            }
#pragma omp section
            {
                sleep(5);
                printf("section 5, by thread %d\n", omp_get_thread_num());
            }
        }
    }
    return 0;
}
