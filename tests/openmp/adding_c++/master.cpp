// Copyright (c) 2018 Tianyi Zhang
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <vector>
#include <omp.h>

int main() {
#pragma omp parallel num_threads(3)
    {
//#pragma omp master
//        printf("this should be thread 0: %d\n", omp_get_thread_num());
        printf("all threads: %d\n", omp_get_thread_num());
    }
    return 0;
}
