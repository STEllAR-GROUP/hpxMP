#include "ompt-internal.h"
#include "intel_hpxMP.h"
#include <boost/shared_ptr.hpp>
#include <iostream>
#include <assert.h>

using std::cout;
using std::endl;

boost::shared_ptr<hpx_runtime> hpx_backend;


//This is called where the library calls can potentially be executed
// outside a parallel region. If the function is not able to be called from
// outside a parallel region, it makes this check and generates it's own 
// output, but does not start the runtime.
void start_backend(){
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"start_backend"<<std::endl;
    #endif
    if(!hpx_backend) {
        hpx_backend.reset(new hpx_runtime());
        #if defined DEBUG && defined HPXMP_HAVE_TRACE
                std::cout<<"new hpx runtime started"<<std::endl;
        #endif
    }
    else {
        #if defined DEBUG && defined HPXMP_HAVE_TRACE
                std::cout << "hpx runtime exists" << std::endl;
        #endif
    }
}

int __kmpc_ok_to_fork(ident_t *loc){
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"kmpc_ok_to_fork"<<std::endl;
    #endif
    start_backend();
    return 1;
}

void __kmpc_begin( ident_t *, kmp_int32 flags ) {
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"__kmpc_begin"<<std::endl;
    #endif
    start_backend();
}

void __kmpc_end(ident_t *loc) {
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"__kmpc_end"<<std::endl;
    #endif
    start_backend();
}

void
__kmpc_fork_call(ident_t *loc, kmp_int32 argc, kmpc_micro microtask, ...) {
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"__kmpc_fork_call"<<std::endl;
    #endif
#if HPXMP_HAVE_OMPT
    ompt_pre_init();
    ompt_post_init();
#endif
    start_backend();
    vector<void*> argv(argc);
    start_backend();

    va_list     ap;
    va_start(   ap, microtask );

    for( int i = 0; i < argc; i++ ){
        argv[i] = va_arg( ap, void * );
    }
    va_end( ap );
    void ** args = argv.data();

    hpx_backend->fork(__kmp_invoke_microtask, microtask, argc, args);
}

// ----- Tasks -----

//sizeof_kmp_task_t includes the private variables for the task
kmp_task_t*
__kmpc_omp_task_alloc( ident_t *loc_ref, kmp_int32 gtid, kmp_int32 flags,
                       size_t sizeof_kmp_task_t, size_t sizeof_shareds,
                       kmp_routine_entry_t task_entry ){

    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"__kmpc_omp_task_alloc"<<std::endl;
    #endif
    start_backend();
    //kmp_tasking_flags_t *input_flags = (kmp_tasking_flags_t *) & flags;
    //TODO: do I need to do something with these flags?
    int task_size = sizeof_kmp_task_t + (-sizeof_kmp_task_t%8);

    kmp_task_t *task = (kmp_task_t*)new char[task_size + sizeof_shareds]; 

    //This gets deleted at the end of task_setup
    task->routine = task_entry;
    if( sizeof_shareds == 0 ) {
        task->shareds = NULL;
    } else {
        task->shareds = &((char*) task)[task_size];
    }
    task->part_id = 0;

    return task;
}

int __kmpc_omp_task( ident_t *loc_ref, kmp_int32 gtid, kmp_task_t * new_task){
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"__kmpc_omp_task"<<std::endl;
    #endif
    start_backend();
    hpx_backend->create_task(new_task->routine, gtid, new_task);
    return 1;
}

// return 1 if suspended and queued the current task to be resumed later, 0 if not.
kmp_int32 
__kmpc_omp_task_with_deps( ident_t *loc_ref, kmp_int32 gtid, kmp_task_t * new_task,
                           kmp_int32 ndeps, kmp_depend_info_t *dep_list,
                           kmp_int32 ndeps_noalias, kmp_depend_info_t *noalias_dep_list ){
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"__kmpc_omp_task_with_deps"<<std::endl;
    #endif
    start_backend();

    if(ndeps == 0 && ndeps_noalias == 0) {
        //TODO:how to I handle immediate tasks, read them from flags?
        hpx_backend->create_task(new_task->routine, gtid, new_task);
    } else {
#ifdef FUTURIZE_TASKS
        hpx_backend->create_future_task( gtid, new_task, ndeps, dep_list);
#else
        hpx_backend->create_df_task( gtid, new_task, ndeps, dep_list,
                                     ndeps_noalias, noalias_dep_list);
#endif
    }

    return 1;
}

// __kmpc_omp_task_parts: Schedule a thread-switchable task for execution
// loc_ref: location of original task pragma (ignored)
// gtid: Global Thread ID of encountering thread
// new_task: task thunk allocated by __kmp_omp_task_alloc() for the ''new task''
// Returns:
//    TASK_CURRENT_NOT_QUEUED (0) if did not suspend and queue current task to be resumed later.
//    TASK_CURRENT_QUEUED (1) if suspended and queued the current task to be resumed later.
int __kmpc_omp_task_parts( ident_t *loc_ref, int gtid, kmp_task_t * new_task) {
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"__kmpc_omp_task_parts"<<std::endl;
    #endif
    start_backend();
    hpx_backend->create_task(new_task->routine, gtid, new_task);
    return 0;
}

kmp_int32 __kmpc_omp_taskwait( ident_t *loc_ref, kmp_int32 gtid ){
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"__kmpc_omp_taskwait"<<std::endl;
    #endif
    start_backend();
#if HPXMP_HAVE_OMPT
    ompt_data_t *my_task_data = &hpx_backend->get_task_data()->task_data;
    if (ompt_enabled.enabled)
    {
        if (ompt_enabled.ompt_callback_sync_region_wait)
        {
            ompt_callbacks.ompt_callback(ompt_callback_sync_region_wait)(
                ompt_sync_region_taskwait, ompt_scope_begin,
                __ompt_get_parallel_data_internal(), my_task_data,
                __builtin_return_address(0));
        }
    }
#endif

    hpx_backend->task_wait();

#if HPXMP_HAVE_OMPT
    if (ompt_enabled.enabled)
    {
        if (ompt_enabled.ompt_callback_sync_region_wait)
        {
            ompt_callbacks.ompt_callback(ompt_callback_sync_region_wait)(
                ompt_sync_region_taskwait, ompt_scope_end,
                __ompt_get_parallel_data_internal(), my_task_data,
                __builtin_return_address(0));
        }
    }
#endif
    return 0;
}

kmp_int32 __kmpc_omp_taskyield(ident_t *loc_ref, kmp_int32 gtid, int end_part ){
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"__kmpc_omp_taskyield"<<std::endl;
    #endif
    start_backend();
    hpx::this_thread::yield();
    return 0;
}

void __kmpc_taskgroup( ident_t* loc, int gtid ) {
    if( hpx_backend->start_taskgroup() ) {
        #if defined DEBUG && defined HPXMP_HAVE_TRACE
                std::cout<<"__kmpc_taskgroup"<<std::endl;
        #endif
        start_backend();
#if HPXMP_HAVE_OMPT
        ompt_data_t *my_task_data = &hpx_backend->get_task_data()->task_data;
        if (ompt_enabled.enabled)
        {
            if (ompt_enabled.ompt_callback_sync_region_wait)
            {
                ompt_callbacks.ompt_callback(ompt_callback_sync_region_wait)(
                    ompt_sync_region_taskgroup, ompt_scope_begin,
                    __ompt_get_parallel_data_internal(), my_task_data,
                    __builtin_return_address(0));
            }
        }
#endif
        cout << "Warning, taskgroup failed to start" << endl;
    }
    //hpx_backend->get_task_data()->num_taskgroup_tasks.reset(new atomic<int>{0});
}

//Wait until all tasks generated by the current task and its descendants are complete
void __kmpc_end_taskgroup( ident_t* loc, int gtid ) {
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"__kmpc_end_taskgroup"<<std::endl;
    #endif
    start_backend();
#if HPXMP_HAVE_OMPT
    ompt_data_t *my_task_data = &hpx_backend->get_task_data()->task_data;
    if (ompt_enabled.enabled)
    {
        if (ompt_enabled.ompt_callback_sync_region_wait)
        {
            ompt_callbacks.ompt_callback(ompt_callback_sync_region_wait)(
                    ompt_sync_region_taskgroup, ompt_scope_end,
                    __ompt_get_parallel_data_internal(), my_task_data,
                    __builtin_return_address(0));
        }
    }
#endif
    hpx_backend->end_taskgroup();
    /*
    while( *(hpx_backend->get_task_data()->num_taskgroup_tasks) > 0 ) {
        hpx::this_thread::yield();
    }
    hpx_backend->get_task_data()->num_taskgroup_tasks.reset();
    */
}

void
__kmpc_omp_wait_deps( ident_t *loc_ref, kmp_int32 gtid, kmp_int32 ndeps, 
                      kmp_depend_info_t *dep_list, kmp_int32 ndeps_noalias, 
                      kmp_depend_info_t *noalias_dep_list ){
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"__kmpc_omp_wait_deps"<<std::endl;
    #endif
    start_backend();
    //Not handling dependencies at the moment
    if(ndeps > 0 || ndeps_noalias > 0){
        cout <<"task has more than 0 dependencies. This runtime does not support task dependencies\n";
        assert(ndeps == 0);
        assert(ndeps_noalias == 0);
    }
}

void __kmpc_omp_task_begin_if0( ident_t *loc_ref, kmp_int32 gtid, kmp_task_t * task ){
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"__kmpc_omp_task_begin_if0"<<std::endl;
    #endif
    start_backend();
    task->routine(gtid, task);
    //FIXME: not sure if this is correct. These only seem to do internal 
    //tracking in the intel runtime
}
void
__kmpc_omp_task_complete_if0( ident_t *loc_ref, kmp_int32 gtid, kmp_task_t *task) {
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"__kmpc_omp_task_complete_if0"<<std::endl;
    #endif
    start_backend();
    //This pairs up with task_begin_if0, waiting for the task that if0 starts.
    //For now, I am just going to execute the thread in task begin, and do nothing here.
}

// ----- End Tasks -----

void 
__kmpc_push_num_threads( ident_t *loc, 
                         kmp_int32 global_tid, 
                         kmp_int32 num_threads ){
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"__kmpc_push_num_threads"<<std::endl;
    #endif
    start_backend();
    start_backend();
    omp_task_data *data = hpx_backend->get_task_data();
    data->set_threads_requested( num_threads );
}

void
__kmpc_barrier(ident_t *loc, kmp_int32 global_tid) {
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"__kmpc_barrier"<<std::endl;
    #endif
    start_backend();
#if HPXMP_HAVE_OMPT
    ompt_data_t *my_task_data = &hpx_backend->get_task_data()->task_data;
    if (ompt_enabled.enabled)
    {
        if (ompt_enabled.ompt_callback_sync_region_wait)
        {
            ompt_callbacks.ompt_callback(ompt_callback_sync_region_wait)(
                ompt_sync_region_barrier, ompt_scope_begin,
                __ompt_get_parallel_data_internal(), my_task_data,
                __builtin_return_address(0));
        }
    }
#endif
    hpx_backend->barrier_wait();

#if HPXMP_HAVE_OMPT
    if (ompt_enabled.enabled)
    {
        if (ompt_enabled.ompt_callback_sync_region_wait)
        {
            ompt_callbacks.ompt_callback(ompt_callback_sync_region_wait)(
                ompt_sync_region_barrier, ompt_scope_end,
                __ompt_get_parallel_data_internal(), my_task_data,
                __builtin_return_address(0));
        }
    }
#endif
}

int  __kmpc_cancel_barrier(ident_t* loc_ref, kmp_int32 gtid){
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"__kmpc_cancel_barrier"<<std::endl;
    #endif
    start_backend();
    hpx_backend->barrier_wait();
    return 0;
}

int __kmpc_global_thread_num(ident_t *loc){
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"__kmpc_global_thread_num"<<std::endl;
    #endif
#if HPXMP_HAVE_OMPT
    ompt_pre_init();
    ompt_post_init();
#endif
    start_backend();
    if(hpx_backend)
        return hpx_backend->get_thread_num();
    return 0;
}

int __kmpc_single(ident_t *loc, int tid){
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"__kmpc_single"<<std::endl;
    #endif
    start_backend();
    //TODO: does this make sense in the context of a hybrid application?
    if(!hpx_backend || !hpx::threads::get_self_ptr() ) {
        return 1;
    }
    auto *task = hpx_backend->get_task_data();
    auto *team = task->team;
    int do_work = 0;

    team->single_mtx.lock();
    if(team->single_counter == task->single_counter) {
        team->single_counter++;
        do_work = 1;
    }
    team->single_mtx.unlock();

    task->single_counter++;
    return do_work;
}

//in the intel runtime, only the single thread calls this
void __kmpc_end_single(ident_t *loc, int tid){
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"__kmpc_end_single"<<std::endl;
    #endif
    start_backend();
}

int __kmpc_master(ident_t *loc, int global_tid){
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"__kmpc_master"<<std::endl;
    #endif
    start_backend();
    if(hpx_backend->get_thread_num() == 0) {
        return 1;
    }
    return 0;
}

void __kmpc_end_master(ident_t *loc, int global_tid){
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"__kmpc_end_master"<<std::endl;
    #endif
    start_backend();
}

void
__kmpc_critical( ident_t * loc, kmp_int32 global_tid, kmp_critical_name * crit ) {
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"__kmpc_critical"<<std::endl;
    #endif
    start_backend();
    parallel_region *team = hpx_backend->get_team();
    team->crit_mtx.lock();
}

void
__kmpc_end_critical(ident_t *loc, kmp_int32 global_tid, kmp_critical_name *crit) {
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"__kmpc_end_critical"<<std::endl;
    #endif
    start_backend();
    parallel_region *team = hpx_backend->get_team();
    team->crit_mtx.unlock();
}

void __kmpc_flush(ident_t *loc, ...){
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"kmpc_ok_to_fork"<<std::endl;
    #endif
    start_backend();
    __sync_synchronize();
}

void * __kmpc_future_cached(ident_t *  loc, kmp_int32  global_tid, void *data, size_t size, void ***cache) {
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"__kmpc_future_cache"<<std::endl;
    #endif
    start_backend();
    //cout << "__kmpc_future_cached called, data = " << data << ", cache = " << cache << endl;
    void *retval;
    shared_future<raw_data> *future_ptr;
    if(!(*cache)) {
        raw_data data; //TODO: When is this freed?
        data.data = (void*)new char[size]{0};
        data.size = size;
        future_ptr = new shared_future<raw_data>(hpx::make_ready_future(data));
        *cache = (void**) future_ptr;
    } else {
        future_ptr = (shared_future<raw_data>*) *cache;
    }

    retval = future_ptr->get().data;
    return retval;
}

//I think I need to pair up *data to with the memory allocated to represend the threadlocal version
void* __kmpc_threadprivate_cached( ident_t *loc, kmp_int32 tid, void *data, size_t size, void ***cache){
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"__kmpc_threadprivate_cached"<<std::endl;
    #endif
    start_backend();
    parallel_region *team = hpx_backend->get_team();
    int num_threads = hpx_backend->get_num_threads();

    if(!(*cache)){
        team->thread_mtx.lock();
        if(!(*cache)){
            *cache = (void**)calloc( 8, num_threads);//FIXME: this is never deallocated.
        }
        team->thread_mtx.unlock();
    }
    if( !((*cache)[tid]) ) {
        (*cache)[tid] = new char[size];
        std::memcpy((*cache)[tid], data, size);
    }
    return (*cache)[tid];
}

//Only one of the threads (called the single thread) should have the didit variable set to 1
//This function copies the copyprivate variable of the task that got ran the single
// into the other implicit tasks, at the end of the single region
// it also needs to cause other implicit tasks to wait until the single task is complete
void
__kmpc_copyprivate( ident_t *loc, kmp_int32 gtid, size_t cpy_size, void *cpy_data, void(*cpy_func)(void*,void*), kmp_int32 didit )
{
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"__kmpc_copyprivate"<<std::endl;
    #endif
    start_backend();
    void **data_ptr = &(hpx_backend->get_team()->copyprivate_data);
    if(didit) {
        *data_ptr = cpy_data;
    }
    hpx_backend->barrier_wait();
    cpy_func(cpy_data, *data_ptr);
    hpx_backend->barrier_wait();
}

int __kmpc_reduce_nowait( ident_t *loc, kmp_int32 gtid, kmp_int32 num_vars, size_t size,
                      void *data,  void (*reduce)(void *lhs, void *rhs), kmp_critical_name *lck ) {
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"__kmpc_reduce_nowait"<<std::endl;
    #endif
    start_backend();
    //This is 2 because the compiler generates a version where the runtime does the work(0/1 are
    //returned) and a version with calls to atomic operations that is used when 2 is returned.
    //return 2;
    return __kmpc_reduce(loc, gtid, num_vars, size, data, reduce, lck);
}

void __kmpc_end_reduce_nowait( ident_t *loc, kmp_int32 gtid, kmp_critical_name *lck ) {
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"__kmpc_end_reduce_nowait"<<std::endl;
    #endif
    start_backend();
    __kmpc_end_reduce( loc, gtid, lck );
}

/* A blocking reduce that includes an implicit barrier.
 *
 * num_vars number of items (variables) to be reduced
 * reduce_size size of data in bytes to be reduced
 * reduce_data pointer to data to be reduced
 * reduce_func callback function providing reduction operation on two operands and returning
 * result of reduction in lhs_data
 * param lck pointer to the unique lock data structure
 * @result 1 for the master thread, 0 for all other team threads, 2 for all team threads if atomic
 * reduction needed
 */
int 
__kmpc_reduce( ident_t *loc, kmp_int32 gtid, kmp_int32 num_vars, size_t size, 
               void *data, void (*func)(void *lhs, void *rhs), kmp_critical_name *lck ) {
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"__kmpc_reduce"<<std::endl;
    #endif
    start_backend();
    bool atomic_avail = (loc->flags & 0x10) == 0x10;
    if( atomic_avail ) {
        hpx_backend->barrier_wait();
        return 2;
    }
    cout << "warning: can't use atomics, runtime code untested" << endl;
    //the intel runtime uses a critical region here
    int is_master = __kmpc_single(loc, gtid);
    auto *team = hpx_backend->get_team();
    int num_threads = team->num_threads;

    team->reduce_data[gtid] = data;
    hpx_backend->barrier_wait();
    if(is_master) {
        for( int i = 0; i < num_threads; i++ ) {
            if(i != gtid) {
                func(data, team->reduce_data[i]);
            }
        }
        __kmpc_end_single(loc, gtid);
    }
    hpx_backend->barrier_wait();
    return is_master;
}

//this might be failing on parallel reduce because the data is no longer visible outside
//thread 0
void
__kmpc_end_reduce( ident_t *loc, kmp_int32 gtid, kmp_critical_name *lck ) {
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"__kmpc_end_reduce"<<std::endl;
    #endif
    start_backend();
    //note only master calls this if not using atomics
    bool atomic_avail = (loc->flags & 0x10) == 0x10;
    if( atomic_avail ) {
        hpx_backend->barrier_wait();
    } else {
        cout << "warning: can't use atomics, runtime code untested" << endl;
    }
}

void __kmpc_init_lock( ident_t *loc, kmp_int32 gtid,  void **lock ){
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"__kmpc_init_lock"<<std::endl;
    #endif
    start_backend();
    *lock = new omp_lock_t;
}

void __kmpc_destroy_lock( ident_t *loc, kmp_int32 gtid, void **lock ){
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"__kmpc_destroy_lock"<<std::endl;
    #endif
    start_backend();
    delete ((omp_lock_t*) *lock);
}

void __kmpc_set_lock( ident_t *loc, kmp_int32 gtid, void **lock ){
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"__kmpc_set_lock"<<std::endl;
    #endif
    start_backend();
    ((omp_lock_t*) *lock)->lock();
}

void __kmpc_unset_lock( ident_t *loc, kmp_int32 gtid, void **lock ){
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"__kmpc_unset_lock"<<std::endl;
    #endif
    start_backend();
    ((omp_lock_t*) *lock)->unlock();
}

int __kmpc_test_lock( ident_t *loc, kmp_int32 gtid, void **lock ){
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"__kmpc_test_lock"<<std::endl;
    #endif
    start_backend();
    return ((omp_lock_t*) *lock)->try_lock();
}


void __kmpc_init_nest_lock( ident_t *loc, kmp_int32 gtid, void **lock ){
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"__kmpc_init_nest_lock"<<std::endl;
    #endif
    start_backend();
    __kmpc_init_lock(loc, gtid, lock);
}

void __kmpc_destroy_nest_lock( ident_t *loc, kmp_int32 gtid, void **lock ){
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"__kmpc_destroy_nest_lock"<<std::endl;
    #endif
    start_backend();
    __kmpc_destroy_lock(loc, gtid, lock);
}

void __kmpc_set_nest_lock( ident_t *loc, kmp_int32 gtid, void **lock ){
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"__kmpc_set_nest_lock"<<std::endl;
    #endif
    start_backend();
    __kmpc_set_lock(loc, gtid, lock);
}

void __kmpc_unset_nest_lock( ident_t *loc, kmp_int32 gtid, void **lock ){
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"__kmpc_unset_nest_lock"<<std::endl;
    #endif
    start_backend();
    __kmpc_unset_lock(loc, gtid, lock);
}

int __kmpc_test_nest_lock( ident_t *loc, kmp_int32 gtid, void **lock ){
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"__kmpc_test_nest_lock"<<std::endl;
    #endif
    start_backend();
    return __kmpc_test_lock(loc, gtid, lock);
}

void __kmpc_serialized_parallel( ident_t *, kmp_int32 global_tid ){
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"__kmpc_serialized_parallel"<<std::endl;
    #endif
    start_backend();
    //Not sure if this needs to do anything. It is not used in clang, 
    //only in icc generated code
}

void __kmpc_end_serialized_parallel ( ident_t *, kmp_int32 global_tid ) {
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"__kmpc_end_serialized_parallel"<<std::endl;
    #endif
    start_backend();
}


//Library functions:--------------------------------------------------
int omp_get_thread_num(){
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"omp_get_thread_num"<<std::endl;
    #endif
    start_backend();
    if(hpx_backend)
        return hpx_backend->get_thread_num();
    else
        return 1;
}

//"returns the number of threads in the current team"
int omp_get_num_threads(){
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"omp_get_num_threads"<<std::endl;
    #endif
    start_backend();
    return hpx_backend->get_num_threads();
}

void omp_get_num_threads(int num_threads){
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"omp_get_num_threads"<<std::endl;
    #endif
    start_backend();
    hpx_backend->set_num_threads(num_threads);
}

int omp_get_max_threads() {
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"omp_get_max_threads"<<std::endl;
    #endif
    start_backend();
    return hpx_backend->get_task_data()->icv.nthreads;
}

int omp_get_num_procs(){
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"omp_get_num_procs"<<std::endl;
    #endif
    start_backend();
    return hpx_backend->get_num_procs();
}

void omp_set_num_threads(int num_threads) {
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"omp_set_num_threads"<<std::endl;
    #endif
    start_backend();
    hpx_backend->get_task_data()->set_threads_requested(num_threads);
}

double omp_get_wtime(){
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"omp_get_wtime"<<std::endl;
    #endif
    start_backend();
    return hpx_backend->get_time();
}

double omp_get_wtick(){
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"omp_get_wtick"<<std::endl;
    #endif
    start_backend();
    return .000000001;
}

int omp_in_parallel(){
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"omp_in_parallel"<<std::endl;
    #endif
    start_backend();
    int active_levels = hpx_backend->get_task_data()->icv.active_levels;
    return (active_levels > 0);
}


void omp_set_dynamic(int dynamic_threads){
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"omp_set_dynamic"<<std::endl;
    #endif
    start_backend();
    hpx_backend->get_task_data()->icv.dyn = (dynamic_threads != 0);
}

int omp_get_dynamic(){
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"omp_get_dynamic"<<std::endl;
    #endif
    start_backend();
    return hpx_backend->get_task_data()->icv.dyn;
}

void omp_init_lock(omp_lock_t **lock){
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"omp_init_lock"<<std::endl;
    #endif
    start_backend();
    *lock = new omp_lock_t;
}

void omp_init_nest_lock(omp_lock_t **lock){
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"omp_init_nest_lock"<<std::endl;
    #endif
    start_backend();
    *lock = new omp_lock_t;
}

void omp_destroy_lock(omp_lock_t **lock) {
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"omp_destroy_lock"<<std::endl;
    #endif
    start_backend();
    delete *lock;
}
void omp_destroy_nest_lock(omp_lock_t **lock) {
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"omp_destroy_nest_lock"<<std::endl;
    #endif
    start_backend();
    delete *lock;
}

int omp_test_lock(omp_lock_t **lock) {
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"omp_test_lock"<<std::endl;
    #endif
    start_backend();
    if((*lock)->try_lock())
        return 1;
    return 0;
}
int omp_test_nest_lock(omp_lock_t **lock) {
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"omp_test_nest_lock"<<std::endl;
    #endif
    start_backend();
    if((*lock)->try_lock())
        return 1;
    return 0;
}

void omp_set_lock(omp_lock_t **lock) {
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"omp_set_lock"<<std::endl;
    #endif
    start_backend();
    (*lock)->lock();
}
void omp_set_nest_lock(omp_lock_t **lock) {
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"__omp_set_nest_lockl"<<std::endl;
    #endif
    start_backend();
    (*lock)->lock();
}

void omp_unset_lock(omp_lock_t **lock) {
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"__omp_unset_lock"<<std::endl;
    #endif
    start_backend();
    (*lock)->unlock();
}

void omp_unset_nest_lock(omp_lock_t **lock) {
    #if defined DEBUG && defined HPXMP_HAVE_TRACE
        std::cout<<"omp_unset_nest_lock"<<std::endl;
    #endif
    start_backend();
    (*lock)->unlock();
}


