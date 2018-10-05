//  Copyright (c) 2018 Tianyi Zhang
//  Adapted from kempj omp-task-tree.c
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <stdio.h>
#include <stdlib.h>

int spawn_children(int depth, int num_children)
{
    int partial_sum[num_children];
    if (depth == 0)
    {
        return 1;
    }
    int i;
    for (i = 0; i < num_children; i++)
    {
#pragma omp task firstprivate(i) shared(partial_sum)
        partial_sum[i] = spawn_children(depth - 1, num_children);
    }
#pragma omp taskwait
    int sum = 0;
    for (i = 0; i < num_children; i++)
    {
        //printf("partial sum = %d\n", partial_sum[i]);
        sum += partial_sum[i];
    }
    return sum;
}

int main(int argc, char **argv)
{
    int depth = 6;
    int breadth = 4;
    int total = 0;
    if (argc > 1)
    {
        depth = atoi(argv[1]);
    }
    if (argc > 2)
    {
        breadth = atoi(argv[2]);
    }
#pragma omp parallel
#pragma omp single nowait
#pragma omp task
    total = spawn_children(depth, breadth);

    printf("depth   %d\n", depth);
    printf("breadth %d\n", breadth);
    printf("total   %d\n", total);
    if (total != 4096)
        return 1;
    return 0;
}
