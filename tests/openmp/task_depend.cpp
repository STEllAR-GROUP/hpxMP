//  Copyright (c) 2018 Tianyi Zhang
//  Adapted from kempj omp-task-dep.c
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <stdio.h>

int foo() {
    return 42;
}

int bar(int in) {
    return in + 11;
}

int main(int argc, char **argv) {
    int x = 5, y = 1, z = 0;
    printf("&x = %p\n", &x);
#pragma omp parallel
    {
#pragma omp single
        {
#pragma omp task depend(out: x)
            x = foo();

#pragma omp task depend(in: x) depend(out : y)
            y = bar(x);

#pragma omp task depend(in: y)
            z = bar(y);
        }
    }
    printf("x = %d\n",x);
    printf("y = %d\n",y);
    printf("z = %d\n",z);
    if(x != 42 || y !=53 || z !=64)
        return 1;
    return 0;
}
