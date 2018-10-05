// Copyright (c) 2018 Tianyi Zhang
// Adapted from kempj omp-for-dynamic.c
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <omp.h>
#include <vector>

int main()
{
    int i, j;
    int result_1[10];
    std::vector<int> result_2;

    printf("\nStatic loop chunk size 2\n");
#pragma omp parallel for schedule(dynamic)
    for (i = 0; i < 10; i++)
    {
        printf("%d, %d\n ", i, omp_get_thread_num());
        result_1[i] = i;
    }

    printf("\nStatic Ordered loop\n");
#pragma omp parallel for schedule(dynamic) ordered
    for (i = 0; i < 10; i++)
    {
#pragma omp ordered
        {
            printf("%d, %d\n ", i, omp_get_thread_num());
            result_2.push_back(i);
        }
    }

    for (i = 0; i < 10; i++)
    {
        if (result_1[i] != i)
            return 1;
    }

    for (i = 0; i < 10; i++)
    {
        if (result_2[i] != i)
            return 1;
    }
    return 0;
}
