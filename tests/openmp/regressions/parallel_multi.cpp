//  Copyright (c) 2018 Tianyi Zhang
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Demonstrating #36: parallel region run into deadlock sometimes

#include <stdio.h>
#include <omp.h>
int main(){
    for(int i =1; i < 20; i++){
        omp_set_num_threads(i);
        for (int j = 0; j < 1000; j++) {
#pragma omp parallel
            {
                int t = 0;
            }
        }
    }
    return 0;
}
