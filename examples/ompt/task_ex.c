//  Copyright (c) 2018 Tianyi Zhang
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../src/ompt.h"
#include "callback.h"
int main(int argc, char* argv[])
{
    int nthreads;
    printf("This task is not in parallel regin\n");
#pragma omp parallel num_threads(2)
    {
#pragma omp single
        {
            omp_wait_id_t tid;
            tid = omp_get_thread_num();
#pragma omp task
            {
                printf("This task is performed by thread [%lu]\n", tid);
            }
#pragma omp task
            {
                printf("This task2 is performed by thread [%lu]\n", tid);
            }
            /*won't work without this line*/
            nthreads = omp_get_num_threads();
        }
    }
    printf("This is not in parallel region\n");
}
