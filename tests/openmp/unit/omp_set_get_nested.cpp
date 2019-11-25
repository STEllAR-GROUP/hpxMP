// Copyright (c) 2018 Tianyi Zhang
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <stdio.h>
#include <omp.h>

using namespace std;

int main()
{
    int number;
    int i;
    omp_set_num_threads(4);
    omp_set_nested(1); // 1 - enables nested parallelism; 0 - disables nested parallelism.

#pragma omp parallel // parallel region begins
    {
        printf("outer parallel region Thread ID == %d\n", omp_get_thread_num());
        /*
            Code for work to be done by outer parallel region threads over here.
        */
#pragma omp parallel num_threads(2) // nested parallel region
        {
            /*
                Code for work to be done by inner parallel region threads over here.
            */
            printf("inner parallel region thread id %d\n", omp_get_thread_num());
        }
    }
    return 0;
}
