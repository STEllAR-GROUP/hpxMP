#include <stdio.h>
#include <unistd.h>

int main() {
    int i,j;

#pragma omp parallel for
    for(i = 0; i < 5; i++) {
#pragma omp parallel for firstprivate(i)
        for(j = 0; j < 5; j++) {
            printf("Hello World %d, %d\n",i,j);
        }
    }



    return 0;
}
