// Copyright (c) 2018 Tianyi Zhang
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <omp.h>
#include <vector>

int main()
{
    int master_thread_num;
#pragma omp parallel
    {
#pragma omp master
        {
            printf("this should be thread 0: %d\n", omp_get_thread_num());
            master_thread_num = omp_get_thread_num();
        }
    }
    if (master_thread_num != 0)
        return 1;
    return 0;
}
