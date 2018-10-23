//  Copyright (c) 2018 Tianyi Zhang
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Demonstrating #32: Returns a unique thread identification number within the current team. In a sequential parts of the program, omp_get_thread_num always returns 0.

#include <stdio.h>
#include <omp.h>
#define PASS 10
int main (int argc, char *argv[])
{
    int test[10];
#pragma omp parallel num_threads(10)
    {
        int tid = omp_get_thread_num();
        printf("This is HPX_THREAD %d\n", tid);
        test[tid] = PASS;
    }
    for(int i=0; i<10; i++){
        if(test[i] != PASS)
            return 1;
    }
    return 0;
}
