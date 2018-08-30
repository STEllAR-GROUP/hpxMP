#include <unistd.h>
#include "callback.h"
// with taskwait, the current task waits only for its child tasks. With taskgroup,
// the current task waits not only for the child tasks generated in the taskgroup but also for all the descendants of those child tasks.
int main() {
#pragma omp parallel num_threads(2)
    {
#pragma omp single
        {
#pragma omp task
            {
#pragma omp task
                {
                    printf("task1\n");
#pragma omp task
                    sleep(2);
                    printf("task2\n");
// current task suspended until task 2 completed
#pragma omp taskwait
#pragma omp task
                    printf("task3, after task 2\n");
                }
            }
        }
    }
    if(do_generic_test())
        return 1;
    //check if taskwait task id matches
    for (auto it = count_taskwait_task_id.begin();
         it != count_taskwait_task_id.end();
         ++it)
    {
        if (it->second != 0)
            return 1;
    }

    //check if taskwait parallel id matches
    for (auto it = count_taskwait_parallel_id.begin();
         it != count_taskwait_parallel_id.end();
         ++it)
    {
        if (it->second != 0)
            return 1;
    }

    //check if taskwait parrallel id = parallel begin parallel id
    if (count_parallel_id.begin()->first !=
        count_taskwait_parallel_id.begin()->first)
        return 1;

    //check if taskwait task id = implicit task create task id
    for (auto it = count_implicit_task_id.begin();
         it != count_implicit_task_id.end();
         ++it)
    {
        if (it->first != (++count_taskwait_task_id.begin())->first &&
            it->first != count_taskwait_task_id.begin()++->first)
            return 1;
    }
    return 0;
}
