#include <stdio.h>
#include <time.h>

int main() {
    struct timespec requestStart, requestEnd;
    clock_gettime(CLOCK_REALTIME, &requestStart);
#pragma omp parallel
    {
        printf("hello world\n");
    }
    clock_gettime(CLOCK_REALTIME, &requestEnd);
    printf("Parallel region took %d second, and %d nanoseconds\n", requestEnd.tv_sec - requestStart.tv_sec, 
                                                                   requestEnd.tv_nsec - requestStart.tv_nsec);
#pragma omp parallel
    {
    }
    clock_gettime(CLOCK_REALTIME, &requestEnd);
    printf("Total of both parallel regions took %d second, and %d nanoseconds\n", requestEnd.tv_sec - requestStart.tv_sec, 
                                                                   requestEnd.tv_nsec - requestStart.tv_nsec);
    return 0;
}
