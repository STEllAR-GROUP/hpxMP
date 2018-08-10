//  Copyright (c) 2018 Tianyi Zhang
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "callback.h"

int main()
{
    int var_i = 0, var_j = 0;
#pragma omp parallel num_threads(5)
    {
#pragma omp task shared(var_i) firstprivate(var_j)
        {
#pragma omp critical
            var_i++;
            var_j++;
            printf("hello tasks %d, %d\n", var_i, var_j);
        }
    }
    //check number of task created and ended
    if (count_task_create != 6 && count_task_complete != 6)
    {
        return 1;
    }

    //check task create task type
    for (auto it = task_type.begin(); it != task_type.end(); ++it)
    {
        if (it->first != 1 && it->first != 4)
            return 1;
    }
    //check task create num of task type
    if (task_type[1] != 1 || task_type[4] != 5)
        return 1;

    //check return adress of task create(only check if the count is right)
    for (auto it = return_address.begin(); it != return_address.end(); ++it)
    {
        if (it->second != 1 && it->second != 5)
            return 1;
    }

    //check if task id matches
    for (auto it = count_task_id.begin(); it != count_task_id.end(); ++it)
    {
        if (it->second != 0)
            return 1;
    }

    //check if task schedule id matches
    for (auto it = count_task_schedule_id.begin();
         it != count_task_schedule_id.end(); ++it)
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
