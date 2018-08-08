//  Copyright (c) 2018 Tianyi Zhang
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "callback.h"

int foo()
{
    return 42;
}

int bar(int in)
{
    return in + 11;
}

int main(int argc, char** argv)
{
    omp_set_num_threads(2);
    int x = 5, y = 1, z = 0;
    printf("&x = %p\n", &x);
#pragma omp parallel
    {
#pragma omp single
        {
#pragma omp task depend(out : x)
            x = foo();

#pragma omp task depend(in : x) depend(out : y)
            y = bar(x);

#pragma omp task depend(in : y)
            z = bar(y);
        }
    }
    printf("x = %d\n", x);
    printf("y = %d\n", y);
    printf("z = %d\n", z);

    //check number of task created and ended
    if (count_task_create != 4 && count_task_complete != 3)
    {
        return 1;
    }

    //check task type
    for (auto it = task_type.begin(); it != task_type.end(); ++it)
    {
        if (it->first != 1 && it->first != 4)
            return 1;
    }
    if (task_type[1] != 1 || task_type[4] != 3)
        return 1;

    //check return adress of task create (only check if the count is right)
    for (auto it = return_address.begin(); it != return_address.end(); ++it)
    {
        if (it->second != 1 && it->second != 2)
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
