//  Copyright (c) 2018 Tianyi Zhang
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Demonstrating #9: terminating with uncaught exception

#include <stdio.h>
int main (int argc, char *argv[])
{
#pragma omp task
    printf("This task is not in parallel regin\n");
}
