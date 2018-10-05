#include <stdio.h>

int main() {
#pragma omp parallel for schedule(dynamic)
    for(int i = 0; i < 10; i++)
    {
        printf("Hello World #%d\n", i );
    }
    return 0;
}
