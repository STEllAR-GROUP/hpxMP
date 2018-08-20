//  Copyright (c) 2018 Tianyi Zhang
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "callback.h"

int main()
{
    omp_set_num_threads(2);
#pragma omp parallel
    {
        printf("hello world 1\n");
#pragma omp barrier
        printf("hello world 2\n");
#pragma omp barrier
        printf("hello world 3\n");
#pragma omp barrier
        printf("hello world 4\n");
    }
    return 0;
}
