#include <stdio.h>

int main() {
    int var_i = 0, var_j = 1;
#pragma omp parallel
    {
#pragma omp task shared(var_i) firstprivate(var_j)
        {
            printf("hello tasks %d, %d\n", var_i, var_j);
        }
    }
    return 0;
}
