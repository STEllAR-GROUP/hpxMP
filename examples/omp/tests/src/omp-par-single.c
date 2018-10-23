#include <stdio.h>
#include <time.h>


void func2(int val1, int val2){
    printf("val 1 = %d, val 2 = %d\n", val1, val2);
}

void func1( int x, int y, int z) {
#pragma omp parallel
#pragma omp single
#pragma omp task untied     
    func2(x,y);
}

int main() {
    int x=1, y=2, z=3;
    func1(x,y,z);

    return 0;
}
