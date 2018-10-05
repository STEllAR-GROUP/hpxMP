// Copyright (c) 2018 Tianyi Zhang
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <omp.h>

int main()
{
    omp_set_nested(1);
    int num_threads;
    bool result[num_threads][num_threads];
#pragma omp parallel
    {
#pragma omp single
        int num_threads = omp_get_num_threads();
        int tid = omp_get_thread_num();
#pragma omp parallel
        {
            int ntid = omp_get_thread_num();
            result[tid][ntid] = true;
        }
    }

    for (int i = 0; i < num_threads; i++)
        for (int j = 0; j < num_threads; j++)
            if (result[i][j] != true)
                return 1;
    return 0;
}
