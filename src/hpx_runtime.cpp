//  Copyright (c) 2013 Jeremy Kemp
//  Copyright (c) 2013 Bryce Adelstein-Lelbach
//  Copyright (c) 2018 Tianyi Zhang
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#define  HPX_LIMIT 9
#include "hpx_runtime.h"
#include "ompt-internal.h"
#include "intel_hpxMP.h"
// We need to explicitly include the implementations for hpx::start if hpxMP is
// being compiled as part of HPX itself
#include <hpx/hpx_start_impl.hpp>
#include <hpx/runtime/threads/run_as_hpx_thread.hpp>
#include <hpx/lcos/local/barrier.hpp>

using std::cout;
using std::endl;

using hpx::dataflow;
using hpx::util::unwrapping;
using hpx::make_ready_future;
using hpx::threads::set_thread_data;
using hpx::threads::get_thread_data;
using hpx::threads::get_self_id;


extern boost::shared_ptr<hpx_runtime> hpx_backend;


void wait_for_startup(std::mutex& startup_mtx, std::condition_variable& cond, bool& running)
{
    {   // Let the main thread know that we're done.
        //std::scoped_lock lk(startup_mtx);
        std::lock_guard<std::mutex> lk(startup_mtx);
        running = true;
        cond.notify_all();
    }
#if defined DEBUG
    std::cerr << "HPX OpenMP runtime has started" << endl;
#endif
}

void fini_runtime()
{
#if defined DEBUG
    cout << "Stopping HPX OpenMP runtime" << endl;
#endif
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    //this should only be done if this runtime started hpx
    hpx::threads::run_as_hpx_thread([]() { hpx::finalize(); });
    hpx::stop();
#if defined DEBUG
    cout << "Stopped" << endl;
#endif
}

void start_hpx(int initial_num_threads)
{
#ifdef OMP_COMPLIANT
    int num_hard_coded_args = 2;
#else
    int num_hard_coded_args = 1;
#endif
    std::vector<std::string> cfg;
    int argc;
    char ** argv;
    using namespace boost::assign;
    cfg += "hpx.os_threads=" + boost::lexical_cast<std::string>(initial_num_threads);
    cfg += "hpx.stacks.use_guard_pages=0";
    cfg += "hpx.run_hpx_main!=0";
    //cfg += "hpx.stacks.huge_size=0x2000000";

    char const* hpx_args_raw = getenv("OMP_HPX_ARGS");

    std::vector<std::string> hpx_args;

    if (hpx_args_raw) {
        std::string tmp(hpx_args_raw);

        boost::algorithm::split(hpx_args, tmp,
            boost::algorithm::is_any_of(";"),
                boost::algorithm::token_compress_on);

        argc = hpx_args.size() + num_hard_coded_args;
        argv = new char*[argc];

        for (boost::uint64_t i = 0; i < hpx_args.size(); ++i) {
            argv[i + num_hard_coded_args] = const_cast<char*>(hpx_args[i].c_str());
        }
    } else {
        argc = num_hard_coded_args;
        argv = new char*[argc];
    }
    argv[0] = const_cast<char*>("hpxMP");
#ifdef OMP_COMPLIANT
    argv[1] = const_cast<char*>("--hpx:queuing=static");
#endif
    hpx::util::function_nonser<int(boost::program_options::variables_map& vm)> f;
    boost::program_options::options_description desc_cmdline;

    std::mutex startup_mtx;
    std::condition_variable cond;//TODO: replace this with something that can be checked later, once hpx is needed.
    bool running = false;

    hpx::start(f, desc_cmdline, argc, argv, cfg,
            std::bind(&wait_for_startup, boost::ref(startup_mtx), boost::ref(cond), boost::ref(running)));

    {
        //std::scoped_lock lk(startup_mtx);
        std::unique_lock<std::mutex> lk(startup_mtx);
        if (!running)
            cond.wait(lk);
    }

    atexit(fini_runtime);

    delete[] argv;
}

hpx_runtime::hpx_runtime()
{
    int initial_num_threads;
    num_procs = hpx::threads::hardware_concurrency();
    char const* omp_num_threads = getenv("OMP_NUM_THREADS");

    if(omp_num_threads != NULL){
        initial_num_threads = atoi(omp_num_threads);
    } else {
        initial_num_threads = num_procs;
    }

    external_hpx = hpx::get_runtime_ptr();
    if(external_hpx){
        //It doesn't make much sense to try and use openMP thread settings
        // when the application has already initialized it's own threads.
        num_procs = hpx::get_os_thread_count();
        initial_num_threads = num_procs;
    }

    implicit_region.reset(new parallel_region(1));
    initial_thread.reset(new omp_task_data(implicit_region.get(), &device_icv, initial_num_threads));
    walltime.reset(new high_resolution_timer);

    if(!external_hpx) {
        start_hpx(initial_num_threads);
    }
}

parallel_region* hpx_runtime::get_team()
{
    auto task_data = get_task_data();
    auto team = task_data->team;
    return team;
}

bool hpx_runtime::set_thread_data_check() {
    omp_task_data *data;
    if (hpx::threads::get_self_ptr()) {
        data = reinterpret_cast<omp_task_data *>(get_thread_data(get_self_id()));
        if (!data)
            return true;
    }
    return false;
}

omp_task_data* hpx_runtime::get_task_data()
{
    omp_task_data *data;
    if(hpx::threads::get_self_ptr()) {
        data = reinterpret_cast<omp_task_data*>(get_thread_data(get_self_id()));
        if(!data) {
            std::cerr<<"trying to get null hpx thread data\n";
            data = initial_thread.get();
        }
    } else {
        data = initial_thread.get();
    }
    return data;
}

double hpx_runtime::get_time() {
    return walltime->now();
}

int hpx_runtime::get_num_threads() {
    return get_team()->num_threads;
}

int hpx_runtime::get_num_procs() {
    return num_procs;
}

void hpx_runtime::set_num_threads(int nthreads) {
    if(nthreads > 0) {
        get_task_data()->icv.nthreads = nthreads;
        get_task_data()->threads_requested = nthreads;
    }
}

int hpx_runtime::get_thread_num() {
    return get_task_data()->local_thread_num;
}

// this should only be called from implicit tasks
void hpx_runtime::barrier_wait(){
    auto *team = get_team();
    task_wait();
#ifdef OMP_COMPLIANT
    while(team->exec->num_pending_closures() > 0 ) {
        //hpx::this_thread::sleep_for(std::chrono::milliseconds(100));
        hpx::this_thread::yield();
    }
#endif
    if(team->num_threads > 1) {
        team->globalBarrier.wait();
    }
}

//TODO: Does the spec say that outstanding tasks need to end before this begins?
bool hpx_runtime::start_taskgroup()
{
    auto *task = get_task_data();
    task->in_taskgroup = true;
#ifdef OMP_COMPLIANT
    //FIXME: why is this local_thread_num? shouldn't it be team->num_threads
    //task->tg_exec.reset(new local_priority_queue_executor(task->local_thread_num));
    task->tg_exec.reset(new local_priority_queue_executor(task->team->num_threads));
#else
    task->taskgroupLatch.reset(new latch(1));
#endif
    return true;
}

void hpx_runtime::end_taskgroup()
{
    auto *task = get_task_data();
#ifdef OMP_COMPLIANT
    task->tg_exec.reset();
#else
    task->taskgroupLatch->count_down_and_wait();
    task->taskgroupLatch.reset();
#endif
    task->in_taskgroup = false;
}

void hpx_runtime::task_wait()
{
    auto *task = get_task_data();
    task->taskBarrier.wait();
    task->taskBarrier.reset(1);
}

void task_setup( int gtid, kmp_task_t *task, omp_task_data* parent_task)
{
    auto task_func = task->routine;
    omp_task_data current_task(gtid, parent_task->team, parent_task->icv);
    //this makes tasks wait for the task it created, aka task created tasks
    current_task.taskBarrier.count_up();
    set_thread_data( get_self_id(), reinterpret_cast<size_t>(&current_task));
#if HPXMP_HAVE_OMPT
    ompt_data_t *my_task_data = &hpx_backend->get_task_data()->task_data;
    if (ompt_enabled.ompt_callback_task_create)
    {
        ompt_callbacks.ompt_callback(ompt_callback_task_create)(NULL, NULL,
            my_task_data, ompt_task_explicit, 0, __builtin_return_address(0));
    }
    ompt_task_status_t status = ompt_task_others;
    /* let OMPT know that we're about to run this task */
    ompt_data_t *prior_task_data =
        &hpx_backend->get_task_data()->team->parent_data;
    if (ompt_enabled.ompt_callback_task_schedule)
    {
        ompt_callbacks.ompt_callback(ompt_callback_task_schedule)(
            prior_task_data, status, my_task_data);
    }
#endif
    // actually running the taskfunctions
if(! task->gcc)
    task_func(gtid, task);
else
    ((void (*)(void *))(*(task->routine)))(task->shareds);
#ifndef OMP_COMPLIANT
    //count down number of tasks under team
    current_task.team->teamTaskLatch.count_down(1);
#endif
    if(task->part_id ==0)
        delete[] (char*)task;
#if HPXMP_HAVE_OMPT
    ompt_task_status_t status_fin = ompt_task_complete;
    /* let OMPT know that we're returning to the callee task */
    if (ompt_enabled.ompt_callback_task_schedule)
    {
        ompt_callbacks.ompt_callback(ompt_callback_task_schedule)(
            my_task_data, status_fin, prior_task_data);
    }
#endif
    //this makes tasks wait for the task it created, thus this thread data is not used anymore
    current_task.taskBarrier.wait();
    //make sure nothing is accessing this thread data after task_data got destroyed
    set_thread_data( get_self_id(), reinterpret_cast<size_t>(nullptr));
    //if task is in taskgroup, count down taskgroup latch as this task is done
    if(parent_task->in_taskgroup)
        parent_task->taskgroupLatch->count_down(1);
    //all child tasks has finished if reaching this point, tell parent me and my child tasks are done
    parent_task->taskBarrier.wait();
}

//task with depend with use this to setup tasks
void task_setup_df( int gtid, kmp_task_t *task, omp_task_data* parent_task)
{
    auto task_func = task->routine;
    omp_task_data current_task(gtid, parent_task->team, parent_task->icv);
    //this makes tasks wait for the task it created
    current_task.taskBarrier.count_up();
    current_task.taskLatch.count_up(1);
    set_thread_data( get_self_id(), reinterpret_cast<size_t>(&current_task));
#if HPXMP_HAVE_OMPT
    ompt_data_t *my_task_data = &hpx_backend->get_task_data()->task_data;
    if (ompt_enabled.ompt_callback_task_create)
    {
        ompt_callbacks.ompt_callback(ompt_callback_task_create)(NULL, NULL,
            my_task_data, ompt_task_explicit, 0, __builtin_return_address(0));
    }
    ompt_task_status_t status = ompt_task_others;
    /* let OMPT know that we're about to run this task */
    ompt_data_t *prior_task_data =
        &hpx_backend->get_task_data()->team->parent_data;
    if (ompt_enabled.ompt_callback_task_schedule)
    {
        ompt_callbacks.ompt_callback(ompt_callback_task_schedule)(
            prior_task_data, status, my_task_data);
    }
#endif

    if(! task->gcc)
        task_func(gtid, task);
    else
        ((void (*)(void *))(*(task->routine)))(task->shareds);

#ifndef OMP_COMPLIANT
    current_task.team->teamTaskLatch.count_down(1);
#endif
    if(task->part_id ==0)
        delete[] (char*)task;
#if HPXMP_HAVE_OMPT
    ompt_task_status_t status_fin = ompt_task_complete;
    /* let OMPT know that we're returning to the callee task */
    if (ompt_enabled.ompt_callback_task_schedule)
    {
        ompt_callbacks.ompt_callback(ompt_callback_task_schedule)(
            my_task_data, status_fin, prior_task_data);
    }
#endif
    //this two line makes tasks wait for the task it created, thus this thread data is not used anymore
    //the perpose is to keep this thread data allocated and not goes out of scope when its child are still using it
    current_task.taskBarrier.wait();
    current_task.taskLatch.count_down_and_wait();
    //make sure nothing is accessing this thread data after task_data got destroyed
    set_thread_data( get_self_id(), reinterpret_cast<size_t>(nullptr));
    if(parent_task->in_taskgroup)
        parent_task->taskgroupLatch->count_down(1);
    // no wait, return thus the when_all in task_create_df can continue
    parent_task->taskLatch.count_down(1);
}

#ifdef OMP_COMPLIANT
void tg_task_setup( int gtid, kmp_task_t *task, omp_icv icv,
                 shared_ptr<local_priority_queue_executor> tg_exec,
                 parallel_region *team)
{
    auto task_func = task->routine;
    omp_task_data task_data(gtid, team, icv);
    task_data.in_taskgroup = true;
    task_data.tg_exec = tg_exec;
    set_thread_data( get_self_id(), reinterpret_cast<size_t>(&task_data));

    task_func(gtid, task);

    delete[] (char*)task;
}
#endif

//shared_ptr is used for these counters, because the parent/calling task may terminate at any time,
//causing its omp_task_data to be deallocated.
void hpx_runtime::create_task( kmp_routine_entry_t task_func, int gtid, kmp_task_t *thunk)
{
    auto *current_task = get_task_data();

    if(current_task->team->num_threads > 0) {
#ifdef OMP_COMPLIANT
        if(current_task->in_taskgroup) {
            hpx::apply( *(current_task->tg_exec), tg_task_setup, gtid, thunk, current_task->icv,
                        current_task->tg_exec, current_task->team );
        } else {
            *(current_task->num_child_tasks) += 1;
            hpx::apply( *(current_task->team->exec), task_setup, gtid, thunk, current_task->icv,
                        current_task->num_child_tasks, current_task->team );
        }
#else
        //this is waited in thread_setup, wait for all task this thread created to be done
        // create_task function is not supposed to wait anything
        current_task->taskBarrier.count_up();
        //count up number of tasks in this team
        current_task->team->teamTaskLatch.count_up(1);
        //count up number of task in taskgroup if we are under taskgroup construct
        if(current_task->in_taskgroup)
            current_task->taskgroupLatch->count_up(1);
        //this fixes hpx::apply changes in hpx backend
        hpx::applier::register_thread_nullary(
            std::bind(&task_setup, gtid, thunk, current_task),
            "omp_explicit_task", hpx::threads::pending, true,
            hpx::threads::thread_priority_normal);
#endif
    }
//    else {
//        *(current_task->num_child_tasks) += 1;
//        task_setup(gtid, thunk, current_task->icv, current_task->num_child_tasks, current_task->team);
//    }
}

//deps will notify when_all function
void df_task_wrapper( int gtid, kmp_task_t *task, omp_task_data* parent_task, vector<shared_future<void>> deps)
{
    task_setup_df( gtid, task, parent_task);
}

#ifdef OMP_COMPLIANT
void df_tg_task_wrapper( int gtid, kmp_task_t *task, omp_icv icv,
                        shared_ptr<local_priority_queue_executor> tg_exec,
                        parallel_region *team,
                        vector<shared_future<void>> deps)
{
    tg_task_setup( gtid, task, icv, tg_exec, team);
}
#endif


// The input on the Intel call is a pair of pointers to arrays of dep structs,
// and the length of these arrays.
// The structs contain a pointer and a flag for in or out dep
void hpx_runtime::create_df_task( int gtid, kmp_task_t *thunk,
                           int ndeps, kmp_depend_info_t *dep_list,
                           int ndeps_noalias, kmp_depend_info_t *noalias_dep_list )
{
    auto current_task = get_task_data();
    auto team = current_task->team;
    vector<shared_future<void>> dep_futures;
    dep_futures.reserve( ndeps + ndeps_noalias);

    //Populating a vector of futures that the task depends on
    for(int i = 0; i < ndeps;i++) {
        if(current_task->df_map.count( dep_list[i].base_addr) > 0) {
            dep_futures.push_back(current_task->df_map[dep_list[i].base_addr]);
        }
    }
    for(int i = 0; i < ndeps_noalias;i++) {
        if(current_task->df_map.count( noalias_dep_list[i].base_addr) > 0) {
            dep_futures.push_back(current_task->df_map[noalias_dep_list[i].base_addr]);
        }
    }

    shared_future<void> new_task;

    if(current_task->in_taskgroup) {
        current_task->taskgroupLatch->count_up(1);
    } else {
        current_task->taskLatch.count_up(1);
    }
#ifndef OMP_COMPLIANT
    team->teamTaskLatch.count_up(1);
#endif
    if(dep_futures.size() == 0) {
#ifdef OMP_COMPLIANT
        if(task->in_taskgroup) {
            new_task = hpx::async( *(task->tg_exec), tg_task_setup, gtid, thunk, task->icv,
                                    task->tg_exec, team);
        } else {
            new_task = hpx::async( *(team->exec), task_setup, gtid, thunk, task->icv,
                                    task->num_child_tasks, team);
        }
#else
        new_task = hpx::async(task_setup_df, gtid, thunk, current_task);
#endif
    } else {


#ifdef OMP_COMPLIANT
        //shared_future<shared_ptr<local_priority_queue_executor>> tg_exec = hpx::make_ready_future(task->tg_exec);

        if(task->in_taskgroup) {
            new_task = dataflow( *(task->tg_exec),
                                 unwrapping(df_tg_task_wrapper), gtid, thunk, task->icv,
                                 task->tg_exec,
                                 team, hpx::when_all(dep_futures) );
        } else {
            new_task = dataflow( *(team->exec),
                                 unwrapping(df_task_wrapper), gtid, thunk, task->icv,
                                 task->num_child_tasks,
                                 team, hpx::when_all(dep_futures) );
        }
#else
        new_task = dataflow( unwrapping(df_task_wrapper), gtid, thunk, current_task, hpx::when_all(dep_futures));
#endif
    }
    for(int i = 0 ; i < ndeps; i++) {
        if(dep_list[i].flags.out) {
            current_task->df_map[dep_list[i].base_addr] = new_task;
        }
    }
    for(int i = 0 ; i < ndeps_noalias; i++) {
        if(noalias_dep_list[i].flags.out) {
            current_task->df_map[noalias_dep_list[i].base_addr] = new_task;
        }
    }
    //task->last_df_task = new_task;
}

#ifdef FUTURIZE_TASKS
//This is for the unfinished compiler work for adding futures to OpenMP
raw_data future_wrapper( int gtid, kmp_task_t *task, raw_data arg1)
{
    memcpy( (task->shareds), arg1.data, arg1.size);

    task->routine(gtid, task);

    delete[] (char*)task;

    return arg1;
}

//I don't have access to which variable is output, assuming it's the first one for now.
raw_data future_wrapper2( int gtid, kmp_task_t *task, raw_data arg1, raw_data arg2)
{
    memcpy((task->shareds)            , arg1.data, arg1.size);
    memcpy((task->shareds) + arg1.size, arg2.data, arg2.size);

    task->routine(gtid, task);

    delete[] (char*)task;

    memcpy(arg1.data, (task->shareds), arg1.size);
    return arg1;
}

raw_data future_wrapper3( int gtid, kmp_task_t *task, raw_data arg1, raw_data arg2, raw_data arg3)
{
    memcpy((task->shareds),
            arg1.data, arg1.size);
    memcpy((task->shareds) + arg1.size,
            arg2.data, arg2.size);
    memcpy((task->shareds) + arg1.size + arg3.size,
            arg3.data, arg3.size);

    task->routine(gtid, task);

    delete[] (char*)task;

    memcpy(arg1.data, (task->shareds), arg1.size);
    return arg1;
}

void hpx_runtime::create_future_task( int gtid, kmp_task_t *thunk,
                                      int ndeps, kmp_depend_info_t *dep_list)
{
    shared_future<raw_data> *output_future;
    vector<shared_future<raw_data>*> input_futures(ndeps);

    //if the variables are FP, then the data needs to be copied, if it's shared, then only
    //pointers need to be set. working with the assumption/requirement that data is FP.
    for(int i=0; i < ndeps; i++) {
        input_futures[i] = (**(shared_future<raw_data>***)(dep_list[i].base_addr));
        if(dep_list[i].flags.out ) {
            output_future = (**(shared_future<raw_data>***)(dep_list[i].base_addr));
        }
    }

    if(ndeps == 1) {
        *(output_future) = dataflow( unwrapping(future_wrapper),
                                                make_ready_future(gtid), make_ready_future(thunk),
                                                *(input_futures[0]) );
    } else if(ndeps == 2) {
        *(output_future) = dataflow( unwrapping(future_wrapper2),
                                                make_ready_future(gtid), make_ready_future(thunk),
                                                *(input_futures[0]), *(input_futures[1]) );
    } else if(ndeps == 3) {
        *(output_future) = dataflow( unwrapping(future_wrapper3),
                                                make_ready_future(gtid), make_ready_future(thunk),
                                                *(input_futures[0]), *(input_futures[1]),
                                                *(input_futures[2]) );
    } else {
        std::cerr << "too many dependencies for now" << endl;
    }
}
#endif

// --- start up for threads and parallel regions below --- //

void thread_setup( invoke_func kmp_invoke, microtask_t thread_func,
                   int argc, void **argv, int tid,
                   parallel_region *team, omp_task_data *parent,
                   barrier& threadBarrier)
{
    omp_task_data task_data(tid, team, parent);
    //count up taskBarrier before set to the thread data
    task_data.taskBarrier.count_up();

    set_thread_data( get_self_id(), reinterpret_cast<size_t>(&task_data));

    if(argc == 0) { //note: kmp_invoke segfaults iff argc == 0
        thread_func(&tid, &tid);
    } else {
#if HPXMP_HAVE_OMPT
        ompt_data_t *implicit_task_data =
            &hpx_backend->get_task_data()->task_data;
        // get parallel id from parent task data;
        ompt_data_t parallel_data = team->parallel_data;
        if (ompt_enabled.enabled)
        {
            if (ompt_enabled.ompt_callback_implicit_task)
            {
                ompt_callbacks.ompt_callback(ompt_callback_implicit_task)(
                    ompt_scope_begin, &parallel_data, implicit_task_data, 0, 0);
            }
        }
#endif
//#ifdef HPXMP_HAVE_GCC
//    ((void(*)(void*)) argv[0])(argv[1]);
//#else
    kmp_invoke(thread_func, tid, tid, argc, argv);
//#endif
#if HPXMP_HAVE_OMPT
    if (ompt_enabled.enabled) {
        if (ompt_enabled.ompt_callback_implicit_task) {
            ompt_callbacks.ompt_callback(ompt_callback_implicit_task)(
                    ompt_scope_end, NULL, implicit_task_data, 0,
                    0);
        }
    }
#endif
}
    // wait for the task this thread created to finish
    task_data.taskBarrier.wait();
    //This together keeps the task_data on this stack allocated
    team->teamTaskLatch.count_down(1);
    threadBarrier.wait();
}

// This is the only place where get_thread can't be called, since
// that data is not initialized for the new hpx threads yet.
void fork_worker( invoke_func kmp_invoke, microtask_t thread_func,
                  int argc, void **argv,
                  omp_task_data *parent)
{
    parallel_region team(parent->team, parent->threads_requested);

#if HPXMP_HAVE_OMPT
    //TODO:HOW TO FIND OUT INVOKER
    ompt_invoker_t a = ompt_invoker_runtime;
    if (ompt_enabled.enabled) {
        if (ompt_enabled.ompt_callback_parallel_begin) {
            int team_size = parent->threads_requested;
            ompt_callbacks.ompt_callback(ompt_callback_parallel_begin)(
                    NULL, NULL,&team.parallel_data, team_size,
                    a,__builtin_return_address(0));
        }
    }
#endif

#ifdef OMP_COMPLIANT
    team.exec.reset(new local_priority_queue_executor(parent->threads_requested));
#endif
    int running_threads = parent->threads_requested;
    barrier threadBarrier(running_threads+1);
    team.teamTaskLatch.count_up(running_threads+1);

    for( int i = 0; i < parent->threads_requested; i++ ) {
        hpx::applier::register_thread_nullary(
                std::bind( &thread_setup, kmp_invoke, thread_func, argc, argv, i, &team, parent,
                           boost::ref(threadBarrier)),
                "omp_implicit_task", hpx::threads::pending,
                true, hpx::threads::thread_priority_low, i );
                //true, hpx::threads::thread_priority_normal, i );
    }
    // wait for all the tasks in the team to finish
    team.teamTaskLatch.count_down_and_wait();
    threadBarrier.wait();

    //The executor containing the tasks will be destroyed as this call goes out
    //of scope, which will wait on all tasks contained in it. So, nothing needs
    //to be done here for it.


#if HPXMP_HAVE_OMPT
    if (ompt_enabled.ompt_callback_parallel_end) {
        ompt_callbacks.ompt_callback(ompt_callback_parallel_end)(
                &team.parallel_data,NULL,a,
                __builtin_return_address(0));
    }
#endif
}

//TODO: This can make main an HPX high priority thread
//TODO: according to the spec, the current thread should be thread 0 of the new team, and execute the new work.
void hpx_runtime::fork(invoke_func kmp_invoke, microtask_t thread_func, int argc, void** argv)
{
    omp_task_data *current_task = get_task_data();

    if( hpx::threads::get_self_ptr() ) {
        fork_worker(kmp_invoke, thread_func, argc, argv, current_task);
    } else {
        //this handles the sync for hox threads.
        hpx::threads::run_as_hpx_thread(&fork_worker,kmp_invoke, thread_func, argc, argv,
                                        current_task);
    }
    current_task->set_threads_requested(current_task->icv.nthreads );
}

