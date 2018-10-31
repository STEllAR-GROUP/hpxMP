//  Copyright (c) 2018 Tianyi Zhang
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Demonstrating #23: HPXMP hangs when creating more than one tasks under parent task

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
#pragma omp parallel num_threads(1)
    {
#pragma omp task
        {
#pragma omp task
            {
                printf("this is task 1\n");
            }
#pragma omp task
            {
                printf("this is task 2\n");
            }
        }
    }
    return 0;
}
