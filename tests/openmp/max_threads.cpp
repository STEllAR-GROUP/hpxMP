// Copyright (c) 2018 Tianyi Zhang
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <omp.h>

int main()
{
    int max_threads_exp = 0;
    char const* omp_num_threads = getenv("OMP_NUM_THREADS");
    if (omp_num_threads != NULL)
    {
        max_threads_exp = atoi(omp_num_threads);
    }
    else
    {
        return 0;
    }

    int max_threads = omp_get_max_threads();
    int max_threads_par;

#pragma omp parallel
    {
#pragma omp single
        max_threads_par = omp_get_max_threads();
    }

    if (max_threads_par != max_threads_exp || max_threads != max_threads_exp)
        return 1;
    return 0;
}
