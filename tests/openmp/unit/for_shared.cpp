//  Copyright (c) 2018 Tianyi Zhang
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <stdio.h>

int main()
{
    int x = 42;
    int i;
#pragma omp parallel for shared(x)
    for (i = 0; i < 100; i++)
    {
#pragma omp atomic
        x++;
    }
    printf("x = %d\n", x);
    if (x != 142)
        return 1;
    return 0;
}
