//  Copyright (c) 2018 Tianyi Zhang
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "callback.h"

int main()
{
    int x = 10, i = 0;
#pragma omp parallel
    {
#pragma omp single
        {
#pragma omp task
            {
                x = x + 1;
                printf("x = %d\n", x);
            }
#pragma omp taskwait
            int j = 0;

            for (i = 0; i < 4; i++)
            {
#pragma omp task firstprivate(i, j)
                {
                    j += i;
                    printf("x (%d) = %d\n", i, x + i);
                    printf("j (%d) = %d\n", i, j);
                }
            }
#pragma omp taskwait
            printf(" j = %d\n", j);
        }
    }
    printf("final x = %d\n", x);

    //check number of task created and ended
    if (count_task_create != 6 && count_task_complete != 5)
    {
        return 1;
    }

    //check task type
    for (auto it = task_type.begin(); it != task_type.end(); ++it)
    {
        if (it->first != 1 && it->first != 4)
            return 1;
    }
    if (task_type[1] != 1 || task_type[4] != 5)
        return 1;

    //check return adress of task create (only check if the count is right)
    for (auto it = return_address.begin(); it != return_address.end(); ++it)
    {
        if (it->second != 1 && it->second != 4)
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
