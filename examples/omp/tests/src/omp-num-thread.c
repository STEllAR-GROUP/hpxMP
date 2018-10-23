
#include <stdio.h>
#include <omp.h>

int main() 
{
   
    printf("from main, MNT = %d\n", omp_get_max_threads());
    
#pragma omp parallel
    {
        printf("NT = %d\n", omp_get_max_threads());
    }
    return 0;
}
