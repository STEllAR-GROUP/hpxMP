//  Copyright (c) 2018 Tianyi Zhang
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <stdio.h>

int main()
{
    int sum0 = 10;
    int correct = 1;

#pragma omp parallel firstprivate(sum0) shared(correct)
    {
        sum0 += 1;
        printf("%d\n", sum0);
        if (sum0 != 11)
            correct = 0;
    }
    printf("out side the parallel region sum0 = %d", sum0);

    if (sum0 != 10 || correct == 0)
        return 1;

    return 0;
}
