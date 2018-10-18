//  Copyright (c) 2018 Tianyi Zhang
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <stdio.h>

int main() {
    int x=0, y=0;
#pragma omp parallel num_threads(2)
    {
#pragma omp critical
        {
            for (int i = 0; i<1000000 ; i++)
            {x++; y+=2;}
        }

    }
    printf("x = %d, y = %d\n", x,y);
    if(x != 2000000 || y != 4000000) return 1;
    return 0;
}
