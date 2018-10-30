// Copyright (c) 2018 Tianyi Zhang
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//This should produce the same result with taskwait_2.cpp
#include <iostream>
#include <omp.h>
#include <atomic>

int main()
{
    std::atomic<int> position(-1);
    int result[4];

    position++;
    result[position] = 1;
    printf("The ");
#pragma omp parallel sections
    {
#pragma omp section
            {
                position++;
                result[position] = 2;
                printf("STE||AR ");
            }
#pragma omp section
            {
                position++;
                result[position] = 2;
                printf("group");
            }
    }
    position++;
    result[position] = 3;
    printf("is awesome\n ");

    printf("\n");
    for(int i = 0; i < 3; i++){
        if(result[i] > result[i+1])
            return 1;
    }
    return 0;
}
