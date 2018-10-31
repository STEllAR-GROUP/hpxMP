#include <stdio.h>
#include <omp.h>

int var1, var2;
#pragma omp threadprivate(var1, var2)

int main() {
    var1 = -1;
    var2 = -2;
    printf("Initial, var1 = %d, at %p\n", var1, &var1);
    printf("Initial, var2 = %d, at %p\n", var2, &var2);
#pragma omp parallel
    {
        var1 = omp_get_thread_num();

        printf("Thread %d, var1 = %d, var2 = %d\n", omp_get_thread_num(), var1, var2);
    }
    printf("Final, var1 = %d, at %p\n", var1, &var1);
    printf("Final, var2 = %d, at %p\n", var2, &var2);
    return 0;
}
