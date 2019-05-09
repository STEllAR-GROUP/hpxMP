/*
 * fibonnaci test
 * select tasking or sequential implementation on command line
 *
 * Author: Deepak
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

long fib1(int k);
long fib2(int k);

//int num_tasks = 0;
int cutoff = 15;

int main(int argc, char* argv[])
{
    for(int i=2; i<=20; i++) {
        omp_set_num_threads(i/2);
        struct timeval t1;
        struct timeval t2;

        int input;
        long s, u;
        long f;
        double m;

        if (argc != 2 && argc != 3) {
            //fprintf(stderr, "Usage: ./fib <input> <cutoff>\n");
            input = 24;
            //return 1;
        } else {
            input = atoi(argv[1]);
            if (argc == 3) {
                cutoff = atoi(argv[2]);
            }
        }

        gettimeofday(&t1, NULL);

#pragma omp parallel
        {
#pragma omp master
            {
#pragma omp task shared(f)
                {
                    f = fib1(input);
                }
            }
        }

        gettimeofday(&t2, NULL);
        printf("fib(%d) = %d\n", input, f);

        s = t2.tv_sec - t1.tv_sec;
        u = t2.tv_usec - t1.tv_usec;
        m = (s * 1000 + u / 1000.0) + 0.5;
        printf("cutoff = %d\n", cutoff);
        printf("time = %.2lfms\n", m);
        if (f != 46368)
            return 1;
    }
    return 0;
}

long fib1(int k)
{
    long p2, p1;

    if (k == 2)
        return 1;
    if (k < 2)
    {
        return k;
    }
    if (k < cutoff)
    {
        return fib1(k - 1) + fib1(k - 2);
    }

#pragma omp task shared(p2)
    {
        p2 = fib1(k - 2);
    }

#pragma omp task shared(p1)
    {
        p1 = fib1(k - 1);
    }
    /*
#pragma omp atomic
num_tasks += 2;
*/
#pragma omp taskwait
    return (p2 + p1);
}

long fib2(int k)
{
    int i;
    long p2, p1, p0;

    if (k == 2)
        return 1;
    if (k < 2)
        return k;

    printf("0 1 1 ");

    p2 = 1;
    p1 = 2;
    p0 = p1;
    for (i = 3; i < k; i++)
    {
        p0 = p2 + p1;
        p2 = p1;
        p1 = p0;
        printf("%d ", p0);
    }

    printf("\n");

    return p0;
}
