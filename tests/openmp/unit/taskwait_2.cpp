//  Copyright (c) 2018 Tianyi Zhang
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <omp.h>
#include <stdio.h>
#include <vector>
//without taskwait will print A is fun to watch race car
//with taskwait will print A race car is fun to watch
int main(int argc, char *argv[]) {
    std::vector<int> result;
#pragma omp parallel
{
#pragma omp single
    {
        printf("A ");
        result.push_back(1);
        #pragma omp task
            {
                printf("race ");
                result.push_back(2);
            }
        #pragma omp task
            {
                printf("car ");
                result.push_back(2);
            }
        #pragma omp taskwait

        printf("is fun to watch ");
        result.push_back(3);
    }
} // End of parallel region
    printf("\n");
    for(int i = 0; i < result.size() -1; i++){
        if(result[i] > result[i+1])
            return 1;
    }
    return 0;
}
