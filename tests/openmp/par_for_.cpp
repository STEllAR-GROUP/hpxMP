// Copyright (c) 2018 Tianyi Zhang
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <omp.h>

int main() {
    int result[10];
#pragma omp parallel for
    for(int i = 0; i < 10; i++)
    {
        result[i] = i;
    }

    for(int i = 0; i < 10; i++)
    {
        if(result[i] != i)
            return 1;
    }
    return 0;
}
