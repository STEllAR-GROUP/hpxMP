//  Copyright (c) 2018 Tianyi Zhang
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Demonstrating #23: double free or corruption (fasttop)

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
#pragma omp parallel num_threads(1)
    {
#pragma omp task untied
        {
#pragma omp task untied
            {
                printf("this is untiedtask 1\n");
            }
#pragma omp task untied
            {
                printf("this is untied task 2\n");
            }
        }
    }
    return 0;
}
