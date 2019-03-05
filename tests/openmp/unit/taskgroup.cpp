//  Copyright (c) 2018 Tianyi Zhang
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <omp.h>
#include <iostream>
#include <vector>
#include <atomic>

//not checking correctness as taskgroup is not implemented properly
int main(int argc, char *argv[]) {
    int result[5];
    std::atomic<int> position(-1);
#pragma omp parallel
    {
#pragma omp single
        {
            printf("A ");
            position++;
            result[position] = 1;
#pragma omp taskgroup
            {
#pragma omp task
                {
                    printf("race ");
                    position++;
                    result[position] = 2;
                }
#pragma omp task
                {
                    printf("car ");
                    position++;
                    result[position] = 2;
#pragma omp task
                    {
                        printf("is");
                        position++;
                        result[position] = 2;
                    }
                }
            }
            printf(" fun to watch ");
            position++;
            result[position] = 3;
#pragma omp taskgroup
            {
#pragma omp task
                {
                    printf(", good ");
                    position++;
                    result[position] = 4;
                }
            }
            printf("job ! ");
            position++;
            result[position] = 5;
        }
    } // End of parallel region
    printf("\n");
    for(int i = 0; i < 5; i++){
        if(result[i] > result[i+1])
            return 1;
    }
    return 0;
}
