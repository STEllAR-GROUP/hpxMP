//  Copyright (c) 2018 Tianyi Zhang
//  Adapted from kempj omp-single-copyprivate.c
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#include <stdio.h>

const int LOOPCOUNT = 4;

int var2;
#pragma omp threadprivate(var2)

int j;
#pragma omp threadprivate(j)

int test_omp_single_copyprivate()
{
    int result = 0;
    int nr_iterations = 0;
#pragma omp parallel
    {
        int i;
        for (i = 0; i < LOOPCOUNT; i++)
        {
#pragma omp single copyprivate(j)
            {
                nr_iterations++;
                j = i;
                var2 = j;
            }
#pragma omp critical
            {
                result = result + j - i;
            }
#pragma omp barrier
        }
    }
    if (!((result == 0) && (nr_iterations == LOOPCOUNT)))
    {
        printf("result = %d, nr_iterations = %d\n", result, nr_iterations);
    }
    return ((result == 0) && (nr_iterations == LOOPCOUNT));
}
int main()
{
    if (test_omp_single_copyprivate())
        return 0;
    return 1;
}
