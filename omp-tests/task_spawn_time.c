#include <omp.h>
#include <sys/time.h>
#include <stdio.h>

void worker_timed(int delay_ms)
{
    struct timeval start, now;
    gettimeofday(&start, NULL);
    while(1)
    {
        gettimeofday(&now, NULL);
        if(((now.tv_sec - start.tv_sec)*1000) + ((now.tv_usec - start.tv_usec)/1000) >= delay_ms)
            break;
    }
}
//TODO: get loadbalancing using with threadlocal
//use an initial parallel region so initial setup is not counted
int main( int argc, char** argv)
{
    int i = 0;
    int num_tasks=500000;
    int delay = 0;
    int total_time;
    struct timeval start, end;
#pragma omp parallel
    {
#pragma omp single
        {
            gettimeofday(&start, NULL);
            for(i = 0; i < num_tasks; i++)
            {
#pragma omp task untied
                worker_timed(delay);
            }
#pragma omp taskwait
            gettimeofday(&end, NULL);
        }
    }
    total_time = ((end.tv_sec - start.tv_sec)*1000) + ((end.tv_usec - start.tv_usec)/1000);
    printf("total time for %d tasks on %d cores, with a delay of %d, is %d ms\n",
            num_tasks, omp_get_num_procs(), delay, total_time);

}
