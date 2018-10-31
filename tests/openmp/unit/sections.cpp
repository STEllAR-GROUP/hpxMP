// Copyright (c) 2018 Tianyi Zhang
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <omp.h>
#include <vector>

bool inRange(int low, int high, int x)
{
    return (low <= x && x <= high);
}

int main(int argc, char **argv)
{
    int result[5];
    int threads = omp_get_max_threads();
#pragma omp parallel sections
    {
#pragma omp section
        {
            result[0] = omp_get_thread_num();
        }
#pragma omp section
        {
            result[1] = omp_get_thread_num();
        }
#pragma omp section
        {
            result[2] = omp_get_thread_num();
        }
#pragma omp section
        {
            result[3] = omp_get_thread_num();
        }
#pragma omp section
        {
            result[4] = omp_get_thread_num();
        }
    }
    printf("array result: \n");
    for (int i = 0; i < 5; i++)
    {
        printf("%d", result[i]);
    }
    for (int i = 0; i < 5; i++) {
            for (int i = 0; i < 5; i++)
                if (!inRange(0, threads, omp_get_thread_num()))
                    return 1;
        }

    int count = 0;
    if(threads !=1){
        for(int i = 0; i <5; i++){
            if(result[i] == 0)
                count++;
        }
    }
    if (count == 5)
        return 1;
    return 0;
}
