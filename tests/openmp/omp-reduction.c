#include <stdio.h>
int main() {
    int i, num_steps=15, x, sum = 0, pi;

#pragma omp parallel for reduction (+:sum)
    for(i=1;i<=num_steps;i++)
    {   
        sum += i;
        printf("i = %d, sum = %d, thread = %d\n", i, sum, omp_get_thread_num());
    }
    printf("sum = %d\n", sum);
    if(sum != 120) return 1;
    return 0;
}
