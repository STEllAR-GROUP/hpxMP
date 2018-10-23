#include <unistd.h>
#include "callback.h"
//TODO:taskgroup was not correctly implemented by hpxMP
int main()
{
#pragma omp parallel num_threads(2)
#pragma omp single
    {
#pragma omp taskgroup
        {
#pragma omp task
            {
#pragma omp critical
                printf("Task 1\n");

#pragma omp task
                {
                    sleep(1);
#pragma omp critical
                    printf("Task 2\n");
                }
            }
        } /* end taskgroup */

#pragma omp task
        {
#pragma omp critical
            printf("Task 3\n");
        }
    }
    if(do_generic_test())
        return 1;
    
    return 0;
}