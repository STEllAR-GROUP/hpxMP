#include <stdio.h>

int main() {
    int i,j;

#pragma omp parallel for
    for(i = 0; i < 11; i++) 
    {
        printf("Hello World %d\n", i);
    }
    
    return 0;
}
