//  Copyright (c) 2018 Tianyi Zhang
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <vector>

int main(int argc, char **argv)
{
    int sum = 0;
    std::vector<int> a(100,1);
#pragma omp parallel
#pragma omp single
    {
    #pragma omp taskgroup task_reduction(+:sum)
        {
        #pragma omp task in_reduction(+:sum)
            for (int i=0; i<50; i++) sum += a[i];
        #pragma omp task in_reduction(+:sum)
            for (int i=50; i<100; i++) sum += a[i];
        }
        std::cout<<sum<<std::endl;
    }
    if(sum!=100)
        return 1;
    return 0;
}
