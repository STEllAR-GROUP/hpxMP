//  Copyright (c) 2018 Tianyi Zhang
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <omp.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    int nthreads;
#pragma omp parallel
    printf("Hello World from thread = [%d]\n", omp_get_thread_num());

    printf("this is not in parallel region\n");
}
