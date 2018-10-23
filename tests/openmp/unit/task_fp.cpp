// Copyright (c) 2018 Tianyi Zhang
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <omp.h>

int main()
{
    int result_x[4];
    int result_j[4];
    int x = 10, i = 0;
#pragma omp parallel
    {
#pragma omp single
        {
#pragma omp task
            {
                x = x + 1;
                if (x != 11)
                    throw "not correct !";
            }
#pragma omp taskwait
            int j = 0;

            for (i = 0; i < 4; i++)
            {
#pragma omp task firstprivate(i, j)
                {
                    j += i;
                    result_x[i] = x + i;
                    result_j[i] = j;
                }
            }
#pragma omp taskwait
            if (j != 0)
                throw "not correct";
        }
    }

    if (x != 11)
        return 1;
    if (result_x[0] != 11 || result_x[1] != 12 || result_x[2] != 13 ||
        result_x[3] != 14)
        return 1;
    if (result_j[0] != 0 || result_j[1] != 1 || result_j[2] != 2 ||
        result_j[3] != 3)
        return 1;
    return 0;
}
