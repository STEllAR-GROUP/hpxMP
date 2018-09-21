#include <stdio.h>

int main()
{
    int x = 42;
    int i;
#pragma omp parallel for shared(x)
        for(i = 0; i < 4;i++) {
                x++;
        }
    printf("x = %d\n", x);
    if(x!=46) return 1;
    return 0;
}
