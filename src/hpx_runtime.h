//  Copyright (c) 2013 Jeremy Kemp
//  Copyright (c) 2013 Bryce Adelstein-Lelbach
//  Copyright (c) 2018 Tianyi Zhang
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#pragma once

#include <limits>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>

#include <hpx/hpx.hpp>
#include <hpx/hpx_start.hpp>
#include <hpx/runtime/threads/topology.hpp>
#include <hpx/lcos/local/barrier.hpp>
#include <hpx/util/static.hpp>
#include <hpx/include/lcos.hpp>
#include <hpx/lcos/local/condition_variable.hpp>

#include <hpx/parallel/executors/thread_pool_executors.hpp>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/std/vector.hpp>
#include <boost/cstdint.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/lockfree/queue.hpp>
//#include <boost/thread/mutex.hpp>
//#include <boost/thread/condition.hpp>

#include <hpx/util/high_resolution_timer.hpp>
#include <map>

#include "icv-vars.h"
#include "ompt.h"


using std::atomic;
using boost::shared_ptr;
using hpx::threads::executors::local_priority_queue_executor;
using hpx::lcos::local::barrier;
using hpx::lcos::local::latch;
using hpx::lcos::shared_future;
using hpx::lcos::future;
using std::vector;
using hpx::util::high_resolution_timer;
using boost::intrusive_ptr;
using boost::lockfree::queue;


typedef void (*microtask_t)( int *gtid, int *npr, ... );
typedef int (*invoke_func)( microtask_t , int , int , int , void**);

typedef void *frame_pointer_t;
typedef int omp_tid;
typedef void (*omp_micro)(int , frame_pointer_t);

typedef void (*omp_task_func)(void *firstprivates, void *fp);

typedef hpx::lcos::local::spinlock mutex_type;
//typedef hpx::lcos::local::mutex  mutex_type;
typedef boost::shared_ptr<mutex_type> mtx_ptr;

typedef int (* kmp_routine_entry_t)( int, void * );

typedef std::map<int64_t, hpx::shared_future<void>> depends_map;

struct kmp_task_t {
    void *              shareds;
    kmp_routine_entry_t routine;
    int                 part_id;
    bool                gcc;
    atomic<int> pointer_counter;
#if OMP_40_ENABLED
    kmp_routine_entry_t destructors;
#endif
};

inline void intrusive_ptr_add_ref(kmp_task_t *x)
{
    ++x->pointer_counter;
}

inline void intrusive_ptr_release(kmp_task_t *x)
{
    if (x->pointer_counter == 0)
        delete x;
}


typedef struct kmp_depend_info {
    int64_t   base_addr;
    size_t    len;
    struct {
        bool  in:1;
        bool  out:1;
    } flags;
} kmp_depend_info_t;

#if HPXMP_HAVE_OMP_50_ENABLED
struct kmp_task_red_flags_t {
    unsigned lazy_priv : 1; // hint: (1) use lazy allocation (big objects)
    unsigned reserved31 : 31;
};

// internal structure for reduction data item related info
struct kmp_task_red_data_t {
    void *reduce_shar; // shared reduction item
    size_t reduce_size; // size of data item
    void *reduce_priv; // thread specific data
    void *reduce_pend; // end of private data for comparison op
    void *reduce_init; // data initialization routine
    void *reduce_fini; // data finalization routine
    void *reduce_comb; // data combiner routine
    kmp_task_red_flags_t flags; // flags for additional info from compiler
};

// structure sent us by compiler - one per reduction item
struct kmp_task_red_input_t {
    void *reduce_shar; // shared reduction item
    size_t reduce_size; // size of data item
    void *reduce_init; // data initialization routine
    void *reduce_fini; // data finalization routine
    void *reduce_comb; // data combiner routine
    kmp_task_red_flags_t flags; // flags for additional info from compiler
};

struct kmp_taskgroup_t {
    std::atomic<int> count; // number of allocated and incomplete tasks
    std::atomic<int>
            cancel_request; // request for cancellation of this taskgroup
     kmp_taskgroup_t* parent; // parent taskgroup
    // Block of data to perform task reduction
    shared_ptr<vector<kmp_task_red_data_t>> reduce_data; // reduction related info
    int reduce_num_data; // number of data items to reduce
};
#endif

class loop_data {
    public:
        loop_data(int NT, int L, int U, int S, int C, int sched)
            : lower(L), upper(U), stride(S), chunk(C), num_threads(NT),
              schedule(sched), total_iter(0),
              first_iter(NT,0), last_iter(NT,0), iter_count(NT,0)
        {
            if( stride == 0) {
                total_iter = (upper - lower) + 1;
            } else if( stride > 0) {
                total_iter = (upper - lower) / stride + 1;
            } else {
                total_iter = (lower - upper) / -stride + 1;
            }
        }
        loop_data(const loop_data &other)
            : loop_data( other.num_threads, other.lower, other.upper,
                         other.stride, other.chunk, other.schedule )
        { }

        loop_data operator=(const loop_data &other) {
            return loop_data(other);
        }

        void yield(){ hpx::this_thread::yield(); }
        int lower;
        int upper;
        int stride;
        int chunk;
        atomic<int> ordered_count{0};
        atomic<int> schedule_count{0};
        int num_threads;
        int schedule;
        int total_iter;
        std::vector<int> first_iter;
        std::vector<int> last_iter;
        std::vector<int> iter_count;
};

struct omp_task_data;
//struct thread_pool{
//    typedef void(*func_type)(int, intrusive_ptr<kmp_task_t>, intrusive_ptr<omp_task_data>);
//    std::atomic_bool done;
//    queue<void*,boost::lockfree::capacity<50>> work_queue;
//
//    template<typename T>
//    void submit(T function){
//        std::cerr<<typeid(T).name()<<std::endl;
//        void* func_ptr = new T(function);
//        T* real_ptr = reinterpret_cast<T*>(func_ptr);
//        T real_func = *real_ptr;
//        real_func();
//        //work_queue.push(func_ptr);
//    }
//
//    void worker_thread(){
//        while(!done){
//            void* task = nullptr;
//            if(work_queue.pop(task)){
//                reinterpret_cast<void(*)()>(task)();
//            }else{
//                hpx::this_thread::yield();
//            }
//        }
//    }
//    thread_pool(int num_threads):done(false){
//    }
//
//    void create_pool(int num_threads){
//        for( int i = 0; i < num_threads; i++ ) {
//            hpx::applier::register_thread_nullary(
//                    std::bind(&thread_pool::worker_thread,this),
//                    "omp_implicit_task", hpx::threads::pending,
//                    true, hpx::threads::thread_priority_low, i );
//        }
//    }
//    ~thread_pool(){
//        done = true;
//    }
//};
void task_setup( int, intrusive_ptr<kmp_task_t>, intrusive_ptr<omp_task_data>);

struct task_wrapper{
    task_wrapper(int gtid, intrusive_ptr<kmp_task_t> kmp_task_ptr, intrusive_ptr<omp_task_data> parent_task_ptr):pointer_counter(0){
        this->gtid = gtid;
        this->kmp_task_ptr = kmp_task_ptr;
        this->parent_task_ptr = parent_task_ptr;
    }
    int gtid;
    intrusive_ptr<kmp_task_t> kmp_task_ptr;
    intrusive_ptr<omp_task_data> parent_task_ptr;
    atomic<int> pointer_counter;
};
inline void intrusive_ptr_add_ref(task_wrapper *x)
{
    ++x->pointer_counter;
}

inline void intrusive_ptr_release(task_wrapper *x)
{
    if (x->pointer_counter == 0)
        delete x;
}
struct thread_pool{
    std::atomic_bool done;
    queue<task_wrapper*,boost::lockfree::capacity<50>> work_queue;
    latch pool_latch;
    bool is_created = false;

    void submit(intrusive_ptr<task_wrapper> data){
        intrusive_ptr_add_ref(data.get());
        work_queue.push(data.get());
    }

    void worker_thread(){
        while(!done){
            task_wrapper* task = nullptr;
            if(work_queue.pop(task)){
                task_setup(task->gtid, task->kmp_task_ptr,task->parent_task_ptr);
                intrusive_ptr_release(task);
            }else{
                hpx::this_thread::yield();
            }
        }
        pool_latch.count_down(1);
    }
    thread_pool(int num_threads):done(false),pool_latch(num_threads){
    }

    void create_pool(int num_threads){
        is_created = true;
        for( int i = 0; i < num_threads; i++ ) {
            hpx::applier::register_thread_nullary(
                    std::bind(&thread_pool::worker_thread,this),
                    "omp_implicit_task", hpx::threads::pending,
                    true, hpx::threads::thread_priority_low, i );
        }
    }
    ~thread_pool(){
        if(is_created) {
            done = true;
            pool_latch.wait();
        }else{
            pool_latch.reset(0);
        }
    }
};

//Does this need to keep track of the parallel region it is nested in,
// the omp_task_data of the parent thread, or both?
//template<typename scheduler>
struct parallel_region {

    parallel_region( int N ) : num_threads(N), globalBarrier(N),
                               depth(0), reduce_data(N), teamTaskLatch(0),pool(N)
    {};

    parallel_region( parallel_region *parent, int threads_requested ) : parallel_region(threads_requested)
    {
        depth = parent->depth + 1;
        //needed in task_schedule, actually should be called parent_task_data
#if (HPXMP_HAVE_OMPT)
        parent_data = parent->parent_data;
#endif
    }
    int num_threads;
    //hpx::lcos::local::condition_variable_any cond;
    barrier globalBarrier;
    mutex_type crit_mtx{};
    mutex_type thread_mtx{};
    mutex_type single_mtx{};
    int depth;
    atomic<int> single_counter{0};
    atomic<int> current_single_thread{-1};
    void *copyprivate_data;
    vector<void*> reduce_data;
    vector<loop_data> loop_list;
    mutex_type loop_mtx;
    latch teamTaskLatch;
    thread_pool pool;
#if (HPXMP_HAVE_OMPT)
    ompt_data_t parent_data = ompt_data_none;
    ompt_data_t parallel_data = ompt_data_none;
#endif
#ifdef OMP_COMPLIANT
    shared_ptr<local_priority_queue_executor> exec;
#endif
};


//What parts of a task could I move to a shared state to get a performance
// improvement, or some other, orgizational improvement?
// icvs?
class omp_task_data {
    public:
        //This constructor should only be used once for the implicit task
        omp_task_data( parallel_region *T, omp_device_icv *global, int init_num_threads)
            : team(T),taskLatch(0)
        {
            local_thread_num = 0;
            icv.device = global;
            icv.nthreads = init_num_threads;
            threads_requested = icv.nthreads;
        };

        //should be used for implicit tasks/threads
        omp_task_data(int tid, parallel_region *T, omp_task_data *P )
            : omp_task_data(tid, T, P->icv)
        {
            icv.levels++;
            if(team->num_threads > 1) {
                icv.active_levels++;
            }
        };

        //This is for explicit tasks
        omp_task_data(int tid, parallel_region *T, omp_icv icv_vars)
            : local_thread_num(tid), team(T), icv(icv_vars),taskLatch(0)
        {
            threads_requested = icv.nthreads;
            icv_vars.device = icv.device;
        };

        //assuming the number of threads that can be created is infinte (so I can avoid using ThreadsBusy)
        //See section 2.3 of the OpenMP 4.0 spec for details on ICVs.
        void set_threads_requested( int nthreads ){
            if( nthreads > 0) {
                threads_requested = nthreads;
            }
            int active_regions = icv.active_levels;
            if( icv.nest && active_regions > 1) {
                threads_requested = 1;
            }
            if(active_regions == icv.device->max_active_levels) {
                threads_requested = 1;
            }
        }

        int local_thread_num;
        //int global_thread_num;
        int threads_requested;
        parallel_region *team;
        //mutex_type thread_mutex;
        //hpx::lcos::local::condition_variable_any thread_cond;
        int single_counter{0};
        int loop_num{0};
        bool in_taskgroup{false};
        latch taskLatch;
        atomic<int> pointer_counter{0};
        //shared_future<void> last_df_task;
#if HPXMP_HAVE_OMPT
        ompt_data_t task_data = ompt_data_none;
#endif

#ifdef OMP_COMPLIANT
        shared_ptr<local_priority_queue_executor> tg_exec;
#else
        shared_ptr<latch> taskgroupLatch;
#endif

        omp_icv icv;
        depends_map df_map;
#if HPXMP_HAVE_OMP_50_ENABLED
        kmp_taskgroup_t* td_taskgroup;
#endif
};

inline void intrusive_ptr_add_ref(omp_task_data *x)
{
    ++x->pointer_counter;
}

inline void intrusive_ptr_release(omp_task_data *x)
{
    if (--x->pointer_counter == 0)
        delete x;
}

struct raw_data {
    void *data;
    size_t size;
};

class hpx_runtime {
    public:
        hpx_runtime();
        void fork(invoke_func kmp_invoke, microtask_t thread_func, int argc, void** argv);
        parallel_region* get_team();
        bool set_thread_data_check();
        intrusive_ptr<omp_task_data> get_task_data();
        int get_thread_num();
        int get_num_threads();
        int get_num_procs();
        void set_num_threads(int nthreads);
        void barrier_wait();
        void create_task( omp_task_func taskfunc, void *frame_pointer,
                          void *firstprivates, int is_tied, int blocks_parent);
        void create_task( kmp_routine_entry_t taskfunc, int gtid, intrusive_ptr<kmp_task_t> task);
        void create_df_task( int gtid, kmp_task_t *thunk,
                             int ndeps, kmp_depend_info_t *dep_list,
                             int ndeps_noalias, kmp_depend_info_t *noalias_dep_list );

#ifdef FUTURIZE_TASKS
        void create_future_task( int gtid, kmp_task_t *thunk,
                                 int ndeps, kmp_depend_info_t *dep_list);
#endif
        void task_exit();
        void task_wait();
        double get_time();
        void delete_hpx_objects();
        void env_init();
        bool nesting_enabled();
        void** get_threadprivate();
        bool start_taskgroup();
        void end_taskgroup();

    private:
        shared_ptr<parallel_region> implicit_region;
        intrusive_ptr<omp_task_data> initial_thread;
        int num_procs;
        shared_ptr<high_resolution_timer> walltime;
        bool external_hpx;
        omp_device_icv device_icv;

        //atomic<int> threads_running{0};//ThreadsBusy
};

