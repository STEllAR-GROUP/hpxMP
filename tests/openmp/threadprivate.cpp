// Copyright (c) 2018 Tianyi Zhang
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <omp.h>

int thread_num, val;
#pragma omp threadprivate(thread_num, val)

int main()
{
#pragma omp parallel
    {
        thread_num = omp_get_thread_num();
    }

#pragma omp parallel
    {
        if (omp_get_thread_num() != thread_num)
            throw "not correct !";
    }
    return 0;
}
