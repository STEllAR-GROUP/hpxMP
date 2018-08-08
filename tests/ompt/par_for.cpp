//  Copyright (c) 2018 Tianyi Zhang
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "callback.h"

int main()
{
    int i = 0;
    omp_set_num_threads(2);
#pragma omp parallel for
    for (i = 0; i < 10; i++)
    {
        printf("Hello World #%d\n", i);
    }

    //test begins here
    //num of parallel begin = num of parallel end = 1
    if (count_parallel_begin != 1 || count_parallel_end != 1)
    {
        return 1;
    }
    //check registered parallel id will be unregistered
    for (auto it = count_parallel_id.begin(); it != count_parallel_id.end();
         ++it)
    {
        if (it->second != 0)
            return 1;
    }
    //check team size are correct(can not tell 2 or 3 now
    for (auto it = team_size.begin(); it != team_size.end(); ++it)
    {
        if (it->second != 2)
            return 1;
    }

    if (do_generic_test())
        return 1;

    fprintf(stderr, "Passes!\n");
    fflush(stderr);
    printf("pass\n");
    return 0;
}
