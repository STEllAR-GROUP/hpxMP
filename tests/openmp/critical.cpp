//  Copyright (c) 2018 Tianyi Zhang
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <stdio.h>

int main()
{
    int x = 0, y = 0, z = 0;
#pragma omp parallel num_threads(2)
    {
#pragma omp critical
        {
            x++;
            y += 2;
            z += 3;
        }
    }
    printf("x = %d,y = %d, z=%d\n", x, y, z);
    if (x != 2 || y != 4 || z != 6)
        return 1;
    return 0;
}
