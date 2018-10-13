//  Copyright (c) 2018 Tianyi Zhang
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <stdio.h>

int main(int argc, char* argv[])
{
#pragma omp parallel
        {
                printf("Hello World ! \n");
        }
}
