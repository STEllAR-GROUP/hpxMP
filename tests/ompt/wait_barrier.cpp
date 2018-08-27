//  Copyright (c) 2018 Tianyi Zhang
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "callback.h"
int main()
{
    int x = 10;
    omp_set_num_threads(2);
#pragma omp parallel
    {
        printf("hello world 1%d\n", x);
#pragma omp barrier
        printf("hello world 2\n");
#pragma omp barrier
        printf("hello world 3\n");
#pragma omp barrier
        printf("hello world 4\n");
    }

    if(do_generic_test())
        return 1;
    
    //check if barrier task id matches
    for (auto it = count_barrier_task_id.begin();
         it != count_barrier_task_id.end();
         ++it)
    {
        if (it->second != 0)
            return 1;
    }

    //    //openmp has 1 more call to barrier
    //    if(count_barrier_begin !=4 || count_barrier_end != 4)
    //        return 1;

    //check if barrier parallel id matches
    for (auto it = count_barrier_parallel_id.begin();
         it != count_barrier_parallel_id.end();
         ++it)
    {
        if (it->second != 0)
            return 1;
    }

    //check if barrier parrallel id = parallel begin parallel id
    if (count_parallel_id.begin()->first !=
        count_barrier_parallel_id.begin()->first)
        return 1;

    //check if barrier task id = implicit task create task id
    for (auto it = count_implicit_task_id.begin();
         it != count_implicit_task_id.end();
         ++it)
    {
        if (it->first != (++count_barrier_task_id.begin())->first &&
            it->first != count_barrier_task_id.begin()++->first)
            return 1;
    }

    return 0;
}
