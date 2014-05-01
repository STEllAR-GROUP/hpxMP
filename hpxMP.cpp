//  Copyright (c) 2013 Jeremy Kemp
//  Copyright (c) 2013 Bryce Adelstein-Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "hpx_runtime.h"
#include "hpxMP.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>

using namespace std;
boost::shared_ptr<hpx_runtime> hpx_backend;

bool started = false;
//boost::atomic<bool> running(false);
int single_counter = 0;
int current_single_thread = -1;
int single_mtx_id = -1;
int crit_mtx_id = -1;
int lock_mtx_id = -1;
int print_mtx_id = -1;

omp_micro fork_func = 0;

void mtx_setup() {
    print_mtx_id = hpx_backend->new_mtx();
    single_mtx_id = hpx_backend->new_mtx();
    crit_mtx_id = hpx_backend->new_mtx();
    lock_mtx_id = hpx_backend->new_mtx();
}

//This function allows a thread to be handled the same way a task is.
void omp_thread_func(void *firstprivates, void *fp) {
    mtx_setup();
    int tid = hpx_backend->get_thread_num();
    fork_func(tid, fp);
}

//overwrites global in openmp
int __ompc_init_rtl(int num_threads) {
    return 0;
}

void __ompc_fork(int nthreads, omp_micro micro_task, frame_pointer_t fp) {
    assert(nthreads >= 0);
    if(!hpx_backend) {
        hpx_backend.reset(new hpx_runtime());
    }
    fork_func = micro_task;
    assert(!started);//Nested parallelism is disabled
    started = true;
    hpx_backend->fork(nthreads, omp_thread_func, fp);
    started = false;
}

int __ompc_can_fork() {
    return !started;
}

//ignoring chunk size input, assuming it is one
void __ompc_static_init_4( int global_tid, omp_sched_t schedtype,
                           int *p_lower, int *p_upper, 
                           int *p_stride, int incr, 
                           int chunk) {
    //copied very directly from the openUH OpenMP runtime:
    int block_size, stride, my_lower, my_upper;
    int team_size = omp_get_num_threads();
    if (schedtype == OMP_SCHED_STATIC_EVEN) {
        int trip_count = (*p_upper - *p_lower) / incr + 1;
        int adjustment = ((trip_count % team_size) == 0) ? -1 : 0;
        stride = (trip_count / team_size + adjustment + 1) * incr;
        block_size = (trip_count / team_size + adjustment) * incr;
        my_lower = *p_lower + global_tid * stride;
        my_upper = my_lower + block_size;
    } else { /* OMP_SCHED_STATIC*/
        block_size = (chunk - 1) * incr;
        stride = chunk * incr;
        my_lower = *p_lower + global_tid * stride;
        my_upper = my_lower + block_size;
        *p_stride = stride * team_size;
    }
    *p_lower = my_lower;
    *p_upper = my_upper;
}

void __ompc_static_init_8( omp_int32 global_tid, omp_sched_t schedtype,
                      omp_int64 *p_lower, omp_int64 *p_upper, omp_int64 *p_stride,
                      omp_int64 incr, omp_int64 chunk ){
    omp_int64 block_size, stride, my_lower, my_upper;
    int team_size = omp_get_num_threads();
    if (schedtype == OMP_SCHED_STATIC_EVEN) {
        omp_int64 trip_count = (*p_upper - *p_lower) / incr + 1;
        omp_int64 adjustment = ((trip_count % team_size) == 0) ? -1 : 0;
        stride = (trip_count / team_size + adjustment + 1) * incr;
        block_size = (trip_count / team_size + adjustment) * incr;
        my_lower = *p_lower + global_tid * stride;
        my_upper = my_lower + block_size;
    } else { /* OMP_SCHED_STATIC*/
        block_size = (chunk - 1) * incr;
        stride = chunk * incr;
        my_lower = *p_lower + global_tid * stride;
        my_upper = my_lower + block_size;
        *p_stride = stride * team_size;
    }
    *p_lower = my_lower;
    *p_upper = my_upper;
}

//These functions essentially store the paramaters of an array,
// the chunk size, stride, and schedule type.
// to be used later when calculating the bounds and stride
// in __ompc_schedule_next_4/8
// storing them in the thread pointer struct will probably work
void __ompc_scheduler_init_4( omp_int32 global_tid,
                              omp_sched_t schedtype,
                              omp_int32 lower, omp_int32 upper,
                              omp_int32 stride, omp_int32 chunk){
    cout << "Not implemented: __ompc_scheduler_init_4" << endl;
}

void __ompc_scheduler_init_8( omp_int32 global_tid,
                              omp_sched_t schedtype,
                              omp_int64 lower, omp_int64 upper,
                              omp_int64 stride, omp_int64 chunk){
    cout << "Not implemented: __ompc_scheduler_init_8" << endl;
}

omp_int32 __ompc_schedule_next_4( omp_int32 global_tid,
                                  omp_int32 *plower, omp_int32 *pupper,
                                  omp_int32 *pstride){
    cout << "Not implemented: __ompc_schedule_next_4" << endl;
    //switch (schedule_type) {
    //    case OMP_SCHED_STATIC_EVEN:
    //    case OMP_SCHED_STATIC:
    //    case OMP_SCHED_GUIDED:
    //    case OMP_SCHED_DYNAMIC:
    //    case OMP_SCHED_ORDERED_STATIC_EVEN:
    //    case OMP_SCHED_ORDERED_STATIC:
    //    case OMP_SCHED_ORDERED_DYNAMIC:
    //    case OMP_SCHED_ORDERED_GUIDED:
    return 0;
}

omp_int32 __ompc_schedule_next_8( omp_int32 global_tid,
                                  omp_int64 *plower, omp_int64 *pupper,
                                  omp_int64 *pstride){
    cout << "Not implemented: __ompc_schedule_next_8" << endl;
    return 0;
}

void __ompc_reduction(omp_int32 gtid, omp_int32 **lck){
    __ompc_critical(gtid, lck);
}

void __ompc_end_reduction(omp_int32 gtid, omp_int32 **lck){
    __ompc_end_critical(gtid, lck);
}

void __ompc_barrier() {
    //TODO: double check that this behaves the same as an explicit barrier
    // specifically do all explicit tasks need to finish
    __ompc_ebarrier();
}

void __ompc_ebarrier() {
    //This is added because a barrier is supposed to wait for all current 
    // tasks to finish. In the case where tasks were spawned, but taskwait 
    // was not called, this is needed.
    //TODO: needs to be reworked for executor to wait on all child tasks
    hpx_backend->task_wait();
    hpx_backend->barrier_wait();
}

int __ompc_get_num_threads(){
    return hpx_backend->get_num_threads();
}

int __ompc_master(int global_tid){
    if(__ompc_get_local_thread_num() == 0) 
        return 1;
    return 0;
}

void __ompc_end_master(int global_tid){
}

int __ompc_single(int tid){
    hpx_backend->lock(single_mtx_id);
    int num_threads = __ompc_get_num_threads();
    if(current_single_thread == -1 && single_counter == 0) {
        current_single_thread = tid;
        single_counter = 1 - num_threads;
    } else {
        single_counter++;
    }
    hpx_backend->unlock(single_mtx_id);
    if(current_single_thread == tid) {
        return 1;
    }
    return 0;
}

void __ompc_end_single(int tid){
    hpx_backend->lock(single_mtx_id);
    if(single_counter == 0) {
        current_single_thread = -1;
    }
    hpx_backend->unlock(single_mtx_id);
}

int __ompc_task_will_defer(int may_delay){
    //in the OpenUH runtime, this also checks if a task limit has been reached
    //leaving that to hpx to decide
    //Not sure if this is correct
    return may_delay;
}
void __ompc_task_firstprivates_alloc(void **firstprivates, int size){
    *firstprivates = malloc(size);
}

void __ompc_task_firstprivates_free(void *firstprivates){
    free(firstprivates);
}

void __ompc_task_create( omp_task_func task_func, void *frame_pointer,
                         void *firstprivates, int may_delay,
                         int is_tied, int blocks_parent) {
    // blocks_parent keeps parent tasks from exiting when they have shared 
    // variables in nested tasks. Since the current hpxMP implementation
    // calls a taskwait at the end of each task, the blocks_parent variable
    // is not used.

    // TODO: Optimization, store is_tied in the thread/task, and whenever 
    // waiting on it, check it, or possibly have a separate vector to store
    // untied tasks
    if(may_delay == 0) {
       task_func(firstprivates, frame_pointer);
    } else {
        hpx_backend->create_task( task_func, frame_pointer, firstprivates,
                                  is_tied);
    }
}

void __ompc_task_wait(){
    hpx_backend->task_wait();
}

void __ompc_task_exit(){
}

void __ompc_serialized_parallel(int global_tid) {
    //It appears this function does nothing
}
void __ompc_end_serialized_parallel(int global_tid) {
    //It appears this function does nothing
}

void __ompc_critical(int gtid, int **lck) {
    if(*lck == NULL || **lck < 0) {
        hpx_backend->lock(crit_mtx_id);
        if(*lck == NULL || **lck < 0){
            *lck = new int;
            hpx_backend->lock(lock_mtx_id);
            **lck = hpx_backend->new_mtx();
            hpx_backend->unlock(lock_mtx_id);
        }
        hpx_backend->unlock(crit_mtx_id);
    }
    hpx_backend->lock(**lck);
}

void __ompc_end_critical(omp_int32 gtid, omp_int32 **lck) {
    hpx_backend->unlock(**lck);
}

omp_int32 __ompc_get_thdprv( void *** thdprv_p, omp_int64 size, 
                             void *datap, omp_int32 global_tid) {
    cout << "unimplemented function called: __ompc_get_thdprv" << endl;
    return 1;
}
omp_int32 __ompc_copyin_thdprv(int num,...) {
    cout << "unimplemented function called: __ompc_copyin_thdprv" << endl;
    return 0;
}

omp_int32 __ompc_copyprivate( omp_int32 mpsp_status,
                              void *cppriv, 
                              void(*cp)(void* src, void* dst) ) {
    cout << "unimplemented function called: __ompc_copyprivate" << endl;
    return 0;
}

int __ompc_get_local_thread_num() {
    if(hpx_backend && started) {
        return hpx_backend->get_thread_num();
    }
    return 0;
}
//OpenMP 3.1 spec, section 3.2.1
void omp_set_num_threads(int nthreads){
    hpx_backend->set_num_threads(nthreads);
}

//OpenMP 3.1 spec, section 3.2.2
//can be called from outside a parallel region
int omp_get_num_threads() {
    if(hpx_backend && started)
        return hpx_backend->get_num_threads();
    return 1;
}

//OpenMP 3.1 spec, section 3.2.3
int omp_get_max_threads() {
    if(!hpx_backend) {
        hpx_backend.reset(new hpx_runtime());
    }                      
    return hpx_backend->get_num_threads();
}

//OpenMP 3.1 spec, section 3.2.4
int omp_get_thread_num() {
    return __ompc_get_local_thread_num();
}

//OpenMP 3.1 spec, section 3.2.5
int omp_get_num_procs() {
    if(!hpx_runtime) {
        hpx_backend.reset(new hpx_runtime());       
    }
    return hpx_runtime->get_num_procs();
}

//OpenMP 3.1 spec, section 3.2.6
int omp_in_parallel(){
    return started;
}

//OpenMP 3.1 spec, section 3.2.7
void omp_set_dynamic(int dynamic_threads){
    //The omp_set_dynamic routine enables or disables dynamic adjustment of the
    //number of threads available for the execution of subsequent parallel regions by
    //setting the value of the dyn-var ICV.
}
//OpenMP 3.1 spec, section 3.2.8
//int omp_get_dynamic(void);
//OpenMP 3.1 spec, section 3.2.9
void omp_set_nested(int nested){
}
//OpenMP 3.1 spec, section 3.2.10
//int omp_get_nested(void);
//OpenMP 3.1 spec, section 3.2.11
//void omp_set_schedule(omp_sched_t kind, int modifier);
//OpenMP 3.1 spec, section 3.2.12
//void omp_get_schedule(omp_sched_t * kind, int * modifier );
//OpenMP 3.1 spec, section 3.2.13
//int omp_get_thread_limit(void);
//OpenMP 3.1 spec, section 3.2.14
//void omp_set_max_active_levels (int max_levels);
//OpenMP 3.1 spec, section 3.2.15
//int omp_get_max_active_levels(void);
//OpenMP 3.1 spec, section 3.2.16
//int omp_get_level (void);
//OpenMP 3.1 spec, section 3.2.17
//int omp_get_ancestor_thread_num (int level);
//OpenMP 3.1 spec, section 3.2.18
//int omp_get_team_size (int level);
//OpenMP 3.1 spec, section 3.2.19
//int omp_get_active_level (void);
//OpenMP 3.1 spec, section 3.2.20
//int omp_in_final(void);

//OpenMP 3.1 spec, section 3.3.1
void omp_init_lock(volatile omp_lock_t *lock) {
    hpx_backend->lock(lock_mtx_id);
    int new_id = hpx_backend->new_mtx();
    hpx_backend->unlock(lock_mtx_id);

    *lock = reinterpret_cast<omp_lock_t>(new_id);
}

void omp_init_nest_lock(volatile omp_nest_lock_t *lock) {
    //unimplmented
}


//OpenMP 3.1 spec, section 3.3.2
void omp_destroy_lock(volatile omp_lock_t *lock) {
}

void omp_destroy_nest_lock(volatile omp_nest_lock_t *lock) {
    //unimplmented
}

//OpenMP 3.1 spec, section 3.3.3
void omp_set_lock(volatile omp_lock_t *lock) {
    int lock_id = *((int*)lock);
    hpx_backend->lock(lock_id);
}

void omp_set_nest_lock(volatile omp_nest_lock_t *lock) {
    //unimplmented
}

//OpenMP 3.1 spec, section 3.3.4
void omp_unset_lock(volatile omp_lock_t *lock) {
    int lock_id = *((int*)lock);
    hpx_backend->unlock(lock_id);
}

void omp_unset_nest_lock(volatile omp_nest_lock_t *lock) {
    //unimplmented
}

//OpenMP 3.1 spec, section 3.3.5
int omp_test_lock(volatile omp_lock_t *lock) {
    if(hpx_backend->trylock(*((int*)lock)))
        return 1;
    return 0;
}

int omp_test_nest_lock(volatile omp_nest_lock_t *lock) {
    //unimplmented
    return 1;
}

//OpenMP 3.1 spec, section 3.4.1
double omp_get_wtime() {
    return hpx_backend->get_time();
}

//OpenMP 3.1 spec, section 3.4.2
double omp_get_wtick() {
    //high resolution elapsed_min
    return .000000001;
}

