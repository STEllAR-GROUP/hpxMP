//  Copyright (c) 2018 Tianyi Zhang
//  Adapted from kempj omp-vla.c
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <stdio.h>

int arr_add(int size)
{
    int n[size];
    int i;
    for (i = 0; i < size; i++)
    {
        n[i] = 2;
    }
    int sum = 0;
    for (i = 0; i < size; i++)
    {
        sum += n[i];
    }
    return sum;
}

int main(int argc, char **argv)
{
    int arr_size = 2000;
    int sum;
#pragma omp parallel
#pragma omp single nowait
#pragma omp task untied
    sum = arr_add(arr_size);
    printf("sum = %d (should be %d)\n", sum, 2 * arr_size);
    if (sum != 4000)
        return 1;
    return 0;
}
