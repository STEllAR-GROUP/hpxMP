#define _GNU_SOURCE             /* See feature_test_macros(7) */
#include <pthread.h>

#include <sys/timeb.h>
#include <stdlib.h>
#include <stdio.h>
#include <sched.h>

/* This really sucks: just do some arith to introduce a delay */
void delay(double * some_value) {
	static int i = 0;
	*some_value = 3.1415926 * i * (*some_value);
	i++;
}

/* read timer in second */
double read_timer()
{
	struct timeb tm;
	ftime(&tm);
	return (double)tm.time + (double)tm.millitm/1000.0;
}

/* read timer in ms */
double read_timer_ms()
{
	struct timeb tm;
	ftime(&tm);
	return (double)tm.time * 1000.0 + (double)tm.millitm;
}

void thread_bind(int id) {
    int s, j;
    cpu_set_t cpuset;
    cpu_set_t cpuset2;
    pthread_t thread;

    thread = pthread_self();

    /** TODO: the following code are not correct, only shows how to use pthread_setaffinity_np with cpuset */
    CPU_ZERO(&cpuset);
    CPU_SET(id, &cpuset);

    s = pthread_setaffinity_np(thread, sizeof(cpu_set_t), &cpuset);
    if (s != 0) fprintf(stderr, "pthread_setaffinity_np error: %d\n", s);

    /* Check the actual affinity mask assigned to the thread */
    s = pthread_getaffinity_np(thread, sizeof(cpu_set_t), &cpuset2);
    if (s != 0) fprintf(stderr, "pthread_getaffinity_np error: %d\n", s);

    if (!CPU_EQUAL(&cpuset, &cpuset2)) fprintf(stderr, "pthread_getaffinity_np and pthread_setaffinity_np does not match, binding may not be good!\n");
}


