// Copyright (c) 2018 Tianyi Zhang
// Adapted from kempj omp-for-nowait.c
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <algorithm>
#include <iostream>
#include <omp.h>
#include <vector>

int main()
{
    int i;
    std::vector<int> result;
#pragma omp parallel
    {
#pragma omp for nowait
        for (i = 0; i < 10; i++)
        {
#pragma omp critical
            result.push_back(i);
            printf("Hello World %d\n", i);
        }
#pragma omp for
        for (i = 10; i < 20; i++)
        {
#pragma omp critical
            result.push_back(i);
            printf("Hello Again %d\n", i);
        }
    }

    std::sort(result.begin(), result.end());
    for (int i = 0; i < 20; i++)
        if (result[i] != i)
            return 1;
    return 0;
}
