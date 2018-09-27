// Copyright (c) 2018 Tianyi Zhang
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <vector>
#include <omp.h>

int main()
{
    std::vector<int> test;
    int num_threads;
#pragma omp parallel
    {
#pragma omp single
        num_threads = omp_get_num_threads();
#pragma omp critical
        test.push_back(0);
#pragma omp barrier
#pragma omp critical
        test.push_back(1);
#pragma omp barrier
#pragma omp critical
        test.push_back(2);
#pragma omp barrier
#pragma omp critical
        test.push_back(3);
    }
    for(int i = 0; i != test.size(); i++){
        std::cout<<test[i];
        if(i/num_threads != test[i])
            return 1;
    }
    std::cout<<std::endl;
    return 0;
}
