//  Copyright (c) 2018 Tianyi Zhang
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <stdio.h>

int main() {
    int x=0;
#pragma omp parallel for
    for (int i = 0; i<10000000; i++)
    {
        #pragma omp atomic
        x++;
    }
    printf("x = %d\n", x);
    if(x != 10000000) return 1;
    return 0;
}
