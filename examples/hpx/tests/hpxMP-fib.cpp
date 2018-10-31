#include <sys/time.h>
#include <stdio.h>
#include "hpxMP.h"


struct task_args_fib {
    int k;
};

int cutoff = 26;

long fib1(int k);
static void fib1_1(void *taskargs, void *fake_fp);
static void fib1_2(void *taskargs, void *fake_fp);
static void parallel_region_func(int gtid_a,void *fake_fp);
static void task_func(void *unused_taskargs, void *fake_fp);

struct long_int_struct {
    long result;
    int input;
};

int main(int argc, char ** argv)
{
    struct timeval t1;
    struct timeval t2;
    int input;
    long s, u;
    double m;
    long_int_struct fake_fp;

    if (argc != 2 && argc != 3) {
        fprintf(stderr, "Usage: ./fib <input> <cutoff>\n");
        return 1;
    }

    input = atoi(argv[1]);
    fake_fp.input = input;
    if(argc == 3)
        cutoff= atoi(argv[2]);

    gettimeofday(&t1, NULL);

    __ompc_fork(0, &parallel_region_func, &fake_fp);

    gettimeofday(&t2, (struct timezone *) 0ULL);
    printf("fib(%d)= %ld\n", input, fake_fp.result);
    s = (t2).tv_sec - (t1).tv_sec;
    u = (t2).tv_usec - (t1).tv_usec;
    m = ((double)((s * 1000LL)) + ((double)(u) / 1.0e+03)) + 5.0e-01;
    printf("cutoff = %d\n", cutoff);
    printf("time = %.2lfms\n", m);
    return 0;
} 

static void parallel_region_func(int gtid_a, void *fake_fp)
{
    int _w2c_mp_is_master;

    _w2c_mp_is_master = __ompc_master(gtid_a);
    if(_w2c_mp_is_master == 1)
        __ompc_task_create(&task_func, fake_fp, 0ULL, 1, 0, 1);
    __ompc_end_master(gtid_a);
    __ompc_task_exit();
    return;
} 

static void task_func(void  *unused_taskargs, void *fake_fp)
{
    long_int_struct *fp = (long_int_struct *)fake_fp;
    fp->result = fib1(fp->input);
    __ompc_task_exit();
    return;
} 

long fib1(int k)
{
    long p2, p1;
    struct task_args_fib * taskarg1;
    struct task_args_fib * taskarg2;
    int is_deferred1, is_deferred2;
    struct long_int_struct fake_fp1, fake_fp2;

    if (k == 2){ return 1; }
    if (k < 2) { return k; }

    is_deferred1 = __ompc_task_will_defer(k > cutoff);
    __ompc_task_firstprivates_alloc((void**)&taskarg1, 4);
    (taskarg1) -> k = k;

    __ompc_task_create(&fib1_1,(void*) &fake_fp1, taskarg1, is_deferred1, 0, 0);

    is_deferred2 = __ompc_task_will_defer(k > cutoff);
    __ompc_task_firstprivates_alloc((void**)&taskarg2, 4);
    (taskarg2) -> k = k;
    __ompc_task_create(&fib1_2, (void*)&fake_fp2, taskarg2, is_deferred2, 0, 0);
    __ompc_task_wait();
    p1 = fake_fp1.result;
    p2 = fake_fp2.result;
    return p2 + p1;
} 

static void fib1_1(void *taskargs, void *fake_fp)
{
    long_int_struct *fp = (long_int_struct *)fake_fp;
    int local_k;
//    long local_r;

    assert(taskargs);

//    local_k = ((task_args_fib*)taskargs)->k;
//    next_k = (local_k - 2);

//    local_r = fib1(next_k);
//    fp->result = local_r;

    local_k = ((task_args_fib*)taskargs)->k;
    fp->result = fib1(local_k - 2);
    __ompc_task_exit();
    __ompc_task_firstprivates_free(taskargs);
    return;
}

static void fib1_2(void *taskargs, void *fake_fp)
{
    long_int_struct *fp = (long_int_struct *)fake_fp;
    int local_k;

    assert(taskargs);

    local_k = ((task_args_fib*)taskargs)->k;
    fp->result = fib1(local_k - 1);
    __ompc_task_exit();
    __ompc_task_firstprivates_free(taskargs);
    return;
}

