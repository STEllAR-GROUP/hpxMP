#include <stdio.h>

int main() {
    int i = 0;
#pragma omp parallel for
    for(i = 0; i < 10; i++)
    {
        printf("Hello World #%d\n", i );
    }
    return 0;
}
