#include <stdio.h>

int main() {
    int i,j;
    j = -1;

#pragma omp parallel for private(j)
    for(i = 0; i < 11; i++) 
    {
        printf("Hello World %d\n", i);
        j = i;
        printf("j = %d\n", j);
    }
    printf("Outside the Parallel Region: j = %d\n", j);
    
    return 0;
}
