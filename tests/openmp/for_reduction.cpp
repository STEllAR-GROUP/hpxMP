//  Copyright (c) 2018 Tianyi Zhang
//  Adapted from kempj omp-reduction.c
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <omp.h>
#include <stdio.h>
int main()
{
    int i, num_steps = 15, x, sum = 0, pi;

#pragma omp parallel for reduction(+ : sum)
    for (i = 1; i <= num_steps; i++)
    {
        sum += i;
        printf("i = %d, sum = %d, thread = %d\n", i, sum, omp_get_thread_num());
    }
    printf("sum = %d\n", sum);
    if (sum != 120)
        return 1;
    return 0;
}
