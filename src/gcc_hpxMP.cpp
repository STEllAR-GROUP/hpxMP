#include "ompt-internal.h"
#include "kmp_atomic.h"
#include "intel_hpxMP.h"
#include "gcc_hpxMP.h"
#include <boost/shared_ptr.hpp>
#include <iostream>
#include <assert.h>

using std::cout;
using std::endl;

extern boost::shared_ptr<hpx_runtime> hpx_backend;

void
__kmp_GOMP_fork_call(void(*unwrapped_task)(void *), microtask_t wrapper, int argc, ...) {
    va_list ap;
    va_start(ap, argc);
    vector<void*> argv(argc);

    for( int i = 0; i < argc; i++ ){
        argv[i] = va_arg( ap, void * );
    }
    va_end( ap );
    void ** args = argv.data();

    hpx_backend->fork(__kmp_invoke_microtask, (microtask_t) wrapper, argc, args);

}

void
__kmp_GOMP_microtask_wrapper(int *gtid, int *npr, void (*task)(void *),
                             void *data) {
    task(data);
}

void
xexpand(KMP_API_NAME_GOMP_PARALLEL)(void (*task)(void *), void *data, unsigned num_threads, unsigned int flags) {
    printf("GOMP_PARALLEL\n");
#if HPXMP_HAVE_OMPT
    ompt_pre_init();
    ompt_post_init();
#endif
    start_backend();
    //__kmpc_push_num_threads
    omp_task_data * my_data = hpx_backend->get_task_data();
    my_data->set_threads_requested(num_threads);

    __kmp_GOMP_fork_call(task,(microtask_t )__kmp_GOMP_microtask_wrapper, 2, task, data);
}

void
xexpand(KMP_API_NAME_GOMP_TASK)(void (*func)(void *), void *data, void (*copy_func)(void *, void *),
                                long arg_size, long arg_align, bool if_cond, unsigned gomp_flags){
//    printf("GOMP_TASK\n");
    int gtid = hpx_backend->get_thread_num();

    kmp_task_t *task = __kmpc_omp_task_alloc(nullptr, gtid, 0,
                                        sizeof(kmp_task_t), arg_size ? arg_size + arg_align - 1 : 0,
                                        (kmp_routine_entry_t)func);

    if (arg_size > 0) {
        if (arg_align > 0) {
            task->shareds = (void *)((((size_t)task->shareds)
                                      + arg_align - 1) / arg_align * arg_align);
        }
        if (copy_func) {
            (*copy_func)(task->shareds, data);
        }
        else {
            memcpy(task->shareds, data, arg_size);
        }
    }
    if (if_cond) {
        __kmpc_omp_task(nullptr, gtid, task);
    }
    else {
        __kmpc_omp_task_begin_if0(nullptr, gtid, task);
        func(data);
        __kmpc_omp_task_complete_if0(nullptr, gtid, task);
    }
}

void
xexpand(KMP_API_NAME_GOMP_TASKWAIT)(void)
{
//    printf("GOMP_TASKWAIT\n");
    __kmpc_omp_taskwait(nullptr, 0);
}

int
xexpand(KMP_API_NAME_GOMP_SINGLE_START)(void)
{
//    printf("SINGLE_START\n");
    return __kmpc_single(nullptr, 0);
}

//TODO: omp-copyprivate not printing correct result yet,
//TODO: problem with compiling with clang as well use num_threads = 5

void *xexpand(KMP_API_NAME_GOMP_SINGLE_COPY_START)(void)
{
    printf("KMP_API_NAME_GOMP_SINGLE_COPY_START\n");
    void *retval;
    //
    // If this is the first thread to enter, return NULL.  The generated
    // code will then call GOMP_single_copy_end() for this thread only,
    // with the copyprivate data pointer as an argument.
    //
    if (__kmpc_single(nullptr, 0))
        return NULL;

    //
    // Wait for the first thread to set the copyprivate data pointer,
    // and for all other threads to reach this point.
    //
    hpx_backend->barrier_wait();

    //
    // Retrieve the value of the copyprivate data point, and wait for all
    // threads to do likewise, then return.
    //
    retval = hpx_backend->get_team()->copyprivate_data;
    hpx_backend->barrier_wait();
    return retval;
}

void xexpand(KMP_API_NAME_GOMP_SINGLE_COPY_END)(void *data)
{
    printf("KMP_API_NAME_GOMP_SINGLE_COPY_END\n");
    //
    // Set the copyprivate data pointer fo the team, then hit the barrier
    // so that the other threads will continue on and read it.  Hit another
    // barrier before continuing, so that the know that the copyprivate
    // data pointer has been propagated to all threads before trying to
    // reuse the t_copypriv_data field.
    //
    hpx_backend->get_team()->copyprivate_data = data;
    hpx_backend->barrier_wait();
    hpx_backend->barrier_wait();
}

void
xexpand(KMP_API_NAME_GOMP_BARRIER)(void)
{
//    printf("GOMP_BARRIER\n");
    __kmpc_barrier(nullptr, 0);
}

void
xexpand(KMP_API_NAME_GOMP_CRITICAL_START)(void)
{
//    printf("GOMP_CRITICAL_START\n");
    __kmpc_critical(nullptr, 0, nullptr);
}


void
xexpand(KMP_API_NAME_GOMP_CRITICAL_END)(void)
{
//    printf("GOMP_CRITICAL_END\n");
    __kmpc_end_critical(nullptr, 0, nullptr);
}

void
xexpand(KMP_API_NAME_GOMP_CRITICAL_NAME_START)(void **pptr)
{
//    printf("GOMP_CRITICAL_NAME_START\n");
    __kmpc_critical(nullptr, 0, nullptr);
}


void
xexpand(KMP_API_NAME_GOMP_CRITICAL_NAME_END)(void **pptr)
{
//    printf("GOMP_CRITICAL_NAME_END\n");
    __kmpc_end_critical(nullptr, 0, nullptr);
}

// not being called by gcc here and in openmp
void
xexpand(KMP_API_NAME_GOMP_ATOMIC_START)(void)
{
    printf("KMP_API_NAME_GOMP_ATOMIC_START\n");
    __kmp_acquire_atomic_lock(&__kmp_atomic_lock, 0);
}

//not being called by gcc here and in openmp
void
xexpand(KMP_API_NAME_GOMP_ATOMIC_END)(void)
{
    printf("KMP_API_NAME_GOMP_ATOMIC_END\n");
    __kmp_release_atomic_lock(&__kmp_atomic_lock, 0);
}

// GOMP_1.0 aliases
xaliasify(KMP_API_NAME_GOMP_ATOMIC_END, 10);
xaliasify(KMP_API_NAME_GOMP_ATOMIC_START, 10);
xaliasify(KMP_API_NAME_GOMP_BARRIER, 10);
xaliasify(KMP_API_NAME_GOMP_CRITICAL_END, 10);
xaliasify(KMP_API_NAME_GOMP_CRITICAL_NAME_END, 10);
xaliasify(KMP_API_NAME_GOMP_CRITICAL_NAME_START, 10);
xaliasify(KMP_API_NAME_GOMP_CRITICAL_START, 10);
xaliasify(KMP_API_NAME_GOMP_LOOP_DYNAMIC_NEXT, 10);
xaliasify(KMP_API_NAME_GOMP_LOOP_DYNAMIC_START, 10);
xaliasify(KMP_API_NAME_GOMP_LOOP_END, 10);
xaliasify(KMP_API_NAME_GOMP_LOOP_END_NOWAIT, 10);
xaliasify(KMP_API_NAME_GOMP_LOOP_GUIDED_NEXT, 10);
xaliasify(KMP_API_NAME_GOMP_LOOP_GUIDED_START, 10);
xaliasify(KMP_API_NAME_GOMP_LOOP_ORDERED_DYNAMIC_NEXT, 10);
xaliasify(KMP_API_NAME_GOMP_LOOP_ORDERED_DYNAMIC_START, 10);
xaliasify(KMP_API_NAME_GOMP_LOOP_ORDERED_GUIDED_NEXT, 10);
xaliasify(KMP_API_NAME_GOMP_LOOP_ORDERED_GUIDED_START, 10);
xaliasify(KMP_API_NAME_GOMP_LOOP_ORDERED_RUNTIME_NEXT, 10);
xaliasify(KMP_API_NAME_GOMP_LOOP_ORDERED_RUNTIME_START, 10);
xaliasify(KMP_API_NAME_GOMP_LOOP_ORDERED_STATIC_NEXT, 10);
xaliasify(KMP_API_NAME_GOMP_LOOP_ORDERED_STATIC_START, 10);
xaliasify(KMP_API_NAME_GOMP_LOOP_RUNTIME_NEXT, 10);
xaliasify(KMP_API_NAME_GOMP_LOOP_RUNTIME_START, 10);
xaliasify(KMP_API_NAME_GOMP_LOOP_STATIC_NEXT, 10);
xaliasify(KMP_API_NAME_GOMP_LOOP_STATIC_START, 10);
xaliasify(KMP_API_NAME_GOMP_ORDERED_END, 10);
xaliasify(KMP_API_NAME_GOMP_ORDERED_START, 10);
xaliasify(KMP_API_NAME_GOMP_PARALLEL_END, 10);
xaliasify(KMP_API_NAME_GOMP_PARALLEL_LOOP_DYNAMIC_START, 10);
xaliasify(KMP_API_NAME_GOMP_PARALLEL_LOOP_GUIDED_START, 10);
xaliasify(KMP_API_NAME_GOMP_PARALLEL_LOOP_RUNTIME_START, 10);
xaliasify(KMP_API_NAME_GOMP_PARALLEL_LOOP_STATIC_START, 10);
xaliasify(KMP_API_NAME_GOMP_PARALLEL_SECTIONS_START, 10);
xaliasify(KMP_API_NAME_GOMP_PARALLEL_START, 10);
xaliasify(KMP_API_NAME_GOMP_SECTIONS_END, 10);
xaliasify(KMP_API_NAME_GOMP_SECTIONS_END_NOWAIT, 10);
xaliasify(KMP_API_NAME_GOMP_SECTIONS_NEXT, 10);
xaliasify(KMP_API_NAME_GOMP_SECTIONS_START, 10);
xaliasify(KMP_API_NAME_GOMP_SINGLE_COPY_END, 10);
xaliasify(KMP_API_NAME_GOMP_SINGLE_COPY_START, 10);
xaliasify(KMP_API_NAME_GOMP_SINGLE_START, 10);

// GOMP_2.0 aliases
xaliasify(KMP_API_NAME_GOMP_TASK, 20);
xaliasify(KMP_API_NAME_GOMP_TASKWAIT, 20);
xaliasify(KMP_API_NAME_GOMP_LOOP_ULL_DYNAMIC_NEXT, 20);
xaliasify(KMP_API_NAME_GOMP_LOOP_ULL_DYNAMIC_START, 20);
xaliasify(KMP_API_NAME_GOMP_LOOP_ULL_GUIDED_NEXT, 20);
xaliasify(KMP_API_NAME_GOMP_LOOP_ULL_GUIDED_START, 20);
xaliasify(KMP_API_NAME_GOMP_LOOP_ULL_ORDERED_DYNAMIC_NEXT, 20);
xaliasify(KMP_API_NAME_GOMP_LOOP_ULL_ORDERED_DYNAMIC_START, 20);
xaliasify(KMP_API_NAME_GOMP_LOOP_ULL_ORDERED_GUIDED_NEXT, 20);
xaliasify(KMP_API_NAME_GOMP_LOOP_ULL_ORDERED_GUIDED_START, 20);
xaliasify(KMP_API_NAME_GOMP_LOOP_ULL_ORDERED_RUNTIME_NEXT, 20);
xaliasify(KMP_API_NAME_GOMP_LOOP_ULL_ORDERED_RUNTIME_START, 20);
xaliasify(KMP_API_NAME_GOMP_LOOP_ULL_ORDERED_STATIC_NEXT, 20);
xaliasify(KMP_API_NAME_GOMP_LOOP_ULL_ORDERED_STATIC_START, 20);
xaliasify(KMP_API_NAME_GOMP_LOOP_ULL_RUNTIME_NEXT, 20);
xaliasify(KMP_API_NAME_GOMP_LOOP_ULL_RUNTIME_START, 20);
xaliasify(KMP_API_NAME_GOMP_LOOP_ULL_STATIC_NEXT, 20);
xaliasify(KMP_API_NAME_GOMP_LOOP_ULL_STATIC_START, 20);

// GOMP_3.0 aliases
xaliasify(KMP_API_NAME_GOMP_TASKYIELD, 30);

// GOMP_4.0 aliases
// The GOMP_parallel* entry points below aren't OpenMP 4.0 related.
xaliasify(KMP_API_NAME_GOMP_PARALLEL, 40);
xaliasify(KMP_API_NAME_GOMP_PARALLEL_SECTIONS, 40);
xaliasify(KMP_API_NAME_GOMP_PARALLEL_LOOP_DYNAMIC, 40);
xaliasify(KMP_API_NAME_GOMP_PARALLEL_LOOP_GUIDED, 40);
xaliasify(KMP_API_NAME_GOMP_PARALLEL_LOOP_RUNTIME, 40);
xaliasify(KMP_API_NAME_GOMP_PARALLEL_LOOP_STATIC, 40);
xaliasify(KMP_API_NAME_GOMP_TASKGROUP_START, 40);
xaliasify(KMP_API_NAME_GOMP_TASKGROUP_END, 40);
xaliasify(KMP_API_NAME_GOMP_BARRIER_CANCEL, 40);
xaliasify(KMP_API_NAME_GOMP_CANCEL, 40);
xaliasify(KMP_API_NAME_GOMP_CANCELLATION_POINT, 40);
xaliasify(KMP_API_NAME_GOMP_LOOP_END_CANCEL, 40);
xaliasify(KMP_API_NAME_GOMP_SECTIONS_END_CANCEL, 40);
xaliasify(KMP_API_NAME_GOMP_TARGET, 40);
xaliasify(KMP_API_NAME_GOMP_TARGET_DATA, 40);
xaliasify(KMP_API_NAME_GOMP_TARGET_END_DATA, 40);
xaliasify(KMP_API_NAME_GOMP_TARGET_UPDATE, 40);
xaliasify(KMP_API_NAME_GOMP_TEAMS, 40);


// GOMP_1.0 versioned symbols
xversionify(KMP_API_NAME_GOMP_ATOMIC_END, 10, "GOMP_1.0");
xversionify(KMP_API_NAME_GOMP_ATOMIC_START, 10, "GOMP_1.0");
xversionify(KMP_API_NAME_GOMP_BARRIER, 10, "GOMP_1.0");
xversionify(KMP_API_NAME_GOMP_CRITICAL_END, 10, "GOMP_1.0");
xversionify(KMP_API_NAME_GOMP_CRITICAL_NAME_END, 10, "GOMP_1.0");
xversionify(KMP_API_NAME_GOMP_CRITICAL_NAME_START, 10, "GOMP_1.0");
xversionify(KMP_API_NAME_GOMP_CRITICAL_START, 10, "GOMP_1.0");
xversionify(KMP_API_NAME_GOMP_LOOP_DYNAMIC_NEXT, 10, "GOMP_1.0");
xversionify(KMP_API_NAME_GOMP_LOOP_DYNAMIC_START, 10, "GOMP_1.0");
xversionify(KMP_API_NAME_GOMP_LOOP_END, 10, "GOMP_1.0");
xversionify(KMP_API_NAME_GOMP_LOOP_END_NOWAIT, 10, "GOMP_1.0");
xversionify(KMP_API_NAME_GOMP_LOOP_GUIDED_NEXT, 10, "GOMP_1.0");
xversionify(KMP_API_NAME_GOMP_LOOP_GUIDED_START, 10, "GOMP_1.0");
xversionify(KMP_API_NAME_GOMP_LOOP_ORDERED_DYNAMIC_NEXT, 10, "GOMP_1.0");
xversionify(KMP_API_NAME_GOMP_LOOP_ORDERED_DYNAMIC_START, 10, "GOMP_1.0");
xversionify(KMP_API_NAME_GOMP_LOOP_ORDERED_GUIDED_NEXT, 10, "GOMP_1.0");
xversionify(KMP_API_NAME_GOMP_LOOP_ORDERED_GUIDED_START, 10, "GOMP_1.0");
xversionify(KMP_API_NAME_GOMP_LOOP_ORDERED_RUNTIME_NEXT, 10, "GOMP_1.0");
xversionify(KMP_API_NAME_GOMP_LOOP_ORDERED_RUNTIME_START, 10, "GOMP_1.0");
xversionify(KMP_API_NAME_GOMP_LOOP_ORDERED_STATIC_NEXT, 10, "GOMP_1.0");
xversionify(KMP_API_NAME_GOMP_LOOP_ORDERED_STATIC_START, 10, "GOMP_1.0");
xversionify(KMP_API_NAME_GOMP_LOOP_RUNTIME_NEXT, 10, "GOMP_1.0");
xversionify(KMP_API_NAME_GOMP_LOOP_RUNTIME_START, 10, "GOMP_1.0");
xversionify(KMP_API_NAME_GOMP_LOOP_STATIC_NEXT, 10, "GOMP_1.0");
xversionify(KMP_API_NAME_GOMP_LOOP_STATIC_START, 10, "GOMP_1.0");
xversionify(KMP_API_NAME_GOMP_ORDERED_END, 10, "GOMP_1.0");
xversionify(KMP_API_NAME_GOMP_ORDERED_START, 10, "GOMP_1.0");
xversionify(KMP_API_NAME_GOMP_PARALLEL_END, 10, "GOMP_1.0");
xversionify(KMP_API_NAME_GOMP_PARALLEL_LOOP_DYNAMIC_START, 10, "GOMP_1.0");
xversionify(KMP_API_NAME_GOMP_PARALLEL_LOOP_GUIDED_START, 10, "GOMP_1.0");
xversionify(KMP_API_NAME_GOMP_PARALLEL_LOOP_RUNTIME_START, 10, "GOMP_1.0");
xversionify(KMP_API_NAME_GOMP_PARALLEL_LOOP_STATIC_START, 10, "GOMP_1.0");
xversionify(KMP_API_NAME_GOMP_PARALLEL_SECTIONS_START, 10, "GOMP_1.0");
xversionify(KMP_API_NAME_GOMP_PARALLEL_START, 10, "GOMP_1.0");
xversionify(KMP_API_NAME_GOMP_SECTIONS_END, 10, "GOMP_1.0");
xversionify(KMP_API_NAME_GOMP_SECTIONS_END_NOWAIT, 10, "GOMP_1.0");
xversionify(KMP_API_NAME_GOMP_SECTIONS_NEXT, 10, "GOMP_1.0");
xversionify(KMP_API_NAME_GOMP_SECTIONS_START, 10, "GOMP_1.0");
xversionify(KMP_API_NAME_GOMP_SINGLE_COPY_END, 10, "GOMP_1.0");
xversionify(KMP_API_NAME_GOMP_SINGLE_COPY_START, 10, "GOMP_1.0");
xversionify(KMP_API_NAME_GOMP_SINGLE_START, 10, "GOMP_1.0");

// GOMP_2.0 versioned symbols
xversionify(KMP_API_NAME_GOMP_TASK, 20, "GOMP_2.0");
xversionify(KMP_API_NAME_GOMP_TASKWAIT, 20, "GOMP_2.0");
xversionify(KMP_API_NAME_GOMP_LOOP_ULL_DYNAMIC_NEXT, 20, "GOMP_2.0");
xversionify(KMP_API_NAME_GOMP_LOOP_ULL_DYNAMIC_START, 20, "GOMP_2.0");
xversionify(KMP_API_NAME_GOMP_LOOP_ULL_GUIDED_NEXT, 20, "GOMP_2.0");
xversionify(KMP_API_NAME_GOMP_LOOP_ULL_GUIDED_START, 20, "GOMP_2.0");
xversionify(KMP_API_NAME_GOMP_LOOP_ULL_ORDERED_DYNAMIC_NEXT, 20, "GOMP_2.0");
xversionify(KMP_API_NAME_GOMP_LOOP_ULL_ORDERED_DYNAMIC_START, 20, "GOMP_2.0");
xversionify(KMP_API_NAME_GOMP_LOOP_ULL_ORDERED_GUIDED_NEXT, 20, "GOMP_2.0");
xversionify(KMP_API_NAME_GOMP_LOOP_ULL_ORDERED_GUIDED_START, 20, "GOMP_2.0");
xversionify(KMP_API_NAME_GOMP_LOOP_ULL_ORDERED_RUNTIME_NEXT, 20, "GOMP_2.0");
xversionify(KMP_API_NAME_GOMP_LOOP_ULL_ORDERED_RUNTIME_START, 20, "GOMP_2.0");
xversionify(KMP_API_NAME_GOMP_LOOP_ULL_ORDERED_STATIC_NEXT, 20, "GOMP_2.0");
xversionify(KMP_API_NAME_GOMP_LOOP_ULL_ORDERED_STATIC_START, 20, "GOMP_2.0");
xversionify(KMP_API_NAME_GOMP_LOOP_ULL_RUNTIME_NEXT, 20, "GOMP_2.0");
xversionify(KMP_API_NAME_GOMP_LOOP_ULL_RUNTIME_START, 20, "GOMP_2.0");
xversionify(KMP_API_NAME_GOMP_LOOP_ULL_STATIC_NEXT, 20, "GOMP_2.0");
xversionify(KMP_API_NAME_GOMP_LOOP_ULL_STATIC_START, 20, "GOMP_2.0");

xversionify(KMP_API_NAME_GOMP_TASKYIELD, 30, "GOMP_3.0");

xversionify(KMP_API_NAME_GOMP_PARALLEL, 40, "GOMP_4.0");
xversionify(KMP_API_NAME_GOMP_PARALLEL_SECTIONS, 40, "GOMP_4.0");
xversionify(KMP_API_NAME_GOMP_PARALLEL_LOOP_DYNAMIC, 40, "GOMP_4.0");
xversionify(KMP_API_NAME_GOMP_PARALLEL_LOOP_GUIDED, 40, "GOMP_4.0");
xversionify(KMP_API_NAME_GOMP_PARALLEL_LOOP_RUNTIME, 40, "GOMP_4.0");
xversionify(KMP_API_NAME_GOMP_PARALLEL_LOOP_STATIC, 40, "GOMP_4.0");
xversionify(KMP_API_NAME_GOMP_TASKGROUP_START, 40, "GOMP_4.0");
xversionify(KMP_API_NAME_GOMP_TASKGROUP_END, 40, "GOMP_4.0");
xversionify(KMP_API_NAME_GOMP_BARRIER_CANCEL, 40, "GOMP_4.0");
xversionify(KMP_API_NAME_GOMP_CANCEL, 40, "GOMP_4.0");
xversionify(KMP_API_NAME_GOMP_CANCELLATION_POINT, 40, "GOMP_4.0");
xversionify(KMP_API_NAME_GOMP_LOOP_END_CANCEL, 40, "GOMP_4.0");
xversionify(KMP_API_NAME_GOMP_SECTIONS_END_CANCEL, 40, "GOMP_4.0");
xversionify(KMP_API_NAME_GOMP_TARGET, 40, "GOMP_4.0");
xversionify(KMP_API_NAME_GOMP_TARGET_DATA, 40, "GOMP_4.0");
xversionify(KMP_API_NAME_GOMP_TARGET_END_DATA, 40, "GOMP_4.0");
xversionify(KMP_API_NAME_GOMP_TARGET_UPDATE, 40, "GOMP_4.0");
xversionify(KMP_API_NAME_GOMP_TEAMS, 40, "GOMP_4.0");