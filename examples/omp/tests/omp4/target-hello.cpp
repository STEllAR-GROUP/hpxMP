#include <stdlib.h>
#include <stdio.h>


void hello() {

#pragma omp declare target

#pragma omp target
#pragma omp parallel
    printf("hello world\n");
}

int main(int argc, char **argv) {
    hello();
    return 0;
}
