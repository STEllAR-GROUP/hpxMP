//  Copyright (c) 2018 Tianyi Zhang
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "callback.h"
int main()
{
    int x = 10, i = 0;
#pragma omp parallel num_threads(2)
    {
        printf("x par = %d\n", x);
        printf("i par = %d\n", i);
    }
    printf("final x = %d\n", x);

    //check number of implicit tasks created
    if (count_implicit_task_create != 2)
    {
        return 1;
    }

    //check if implicit task id matches
    for (auto it = count_implicit_task_id.begin();
         it != count_implicit_task_id.end(); ++it)
    {
        if (it->second != 0)
            return 1;
    }

    if (do_generic_test())
        return 1;

    fprintf(stderr, "Passes!\n");
    fflush(stderr);
    printf("pass\n");

    return 0;
}
