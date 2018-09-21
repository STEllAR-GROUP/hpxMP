#include <stdio.h>

int fib(int n) {
    int f1, f2, f;
    if(n < 2) {
        return n;
    }
#pragma omp task shared(f1)
    f1 = fib(n-1);
#pragma omp task shared(f2)
    f2 = fib(n-2);

#pragma omp taskwait
    f = f1 + f2;

    return f;
}

int main() {
    int f=0;
#pragma omp parallel
    {
#pragma omp single
        {
            f = fib(8);
        }
    }
    printf("fib = %d\n", f);
    if(f != 21) return 1;
    return 0;
}
