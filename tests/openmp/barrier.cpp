// Copyright (c) 2018 Tianyi Zhang
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <omp.h>
#include <sstream>
#include <string>
#include <vector>

int main()
{
    int num_threads;
    std::ostringstream result;
    std::vector<char> vec;
#pragma omp parallel
    {
#pragma omp single
        num_threads = omp_get_num_threads();
#pragma omp critical
        result << "0";
#pragma omp barrier
#pragma omp critical
        result << "1";
#pragma omp barrier
#pragma omp critical
        result << "2";
#pragma omp barrier
#pragma omp critical
        result << "3";
    }

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < num_threads; j++)
        {
            if (i == 0)
                vec.push_back('0');
            if (i == 1)
                vec.push_back('1');
            if (i == 2)
                vec.push_back('2');
            if (i == 3)
                vec.push_back('3');
        }
    std::string result_expected(vec.begin(), vec.end());
    if (result.str() != result_expected)
        return 1;
    return 0;
}
