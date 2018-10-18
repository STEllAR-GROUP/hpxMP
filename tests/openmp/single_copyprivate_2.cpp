//  Copyright (c) 2018 Tianyi Zhang
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <stdio.h>
#include <omp.h>
int x = 0, y = 0, Global = 0;
#pragma omp threadprivate(x, y)
float get_int() {
    Global += 1;
    return Global;
}

void use_int(int f, int t) {
    printf("Value = %d, thread = %d\n", f, t);
}


int main() {

    printf("call CopyPrivate from a single thread\n");
#pragma omp single copyprivate(x, y)
    {
        x = get_int();
        y = get_int();
    }
    use_int(x, omp_get_thread_num());
    use_int(y, omp_get_thread_num());

    printf("call CopyPrivate from a parallel region\n");
#pragma omp parallel
    {
#pragma omp single copyprivate(x, y)
        {
            x = get_int();
            y = get_int();
        }
        use_int(x, omp_get_thread_num());
        use_int(y, omp_get_thread_num());
    }
}
