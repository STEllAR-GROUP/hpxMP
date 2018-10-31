#include <chrono>
#include <atomic>
#include <mutex>
#include <condition_variable>


#include <hpx/hpx_init.hpp>
#include <hpx/runtime/threads/topology.hpp>
#include <hpx/include/util.hpp>
#include <hpx/include/lcos.hpp>
#include <hpx/apply.hpp>

#include <boost/assign/std/vector.hpp>
#include <boost/cstdint.hpp>
#include <boost/format.hpp>

#include <hpx/parallel/executors/thread_pool_executors.hpp>

using hpx::lcos::shared_future;
using hpx::dataflow;
using hpx::util::unwrapping;

using std::vector;
using std::cout;
using std::endl;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;
using std::atomic;

using hpx::threads::executors::local_priority_queue_executor;


typedef hpx::lcos::local::mutex mutex_type;

atomic<int64_t> task_counter;
mutex_type count_mutex;
hpx::lcos::local::condition_variable count_cond;



void delay_cond(int nanosec_delay) {
    auto t1 = high_resolution_clock::now();
    auto t2 = high_resolution_clock::now();
    while(true) {
        if( duration_cast<nanoseconds> (t2-t1).count() > nanosec_delay) {
            break;
        }
        t2 = high_resolution_clock::now();
    }
    int task_num = --task_counter;
    if(task_num == 0){
        std::unique_lock<mutex_type> lk(count_mutex);
                  count_cond.notify_all();
    }
}

int64_t cond_task_spawn(int num_tasks, int delay_time) {
    task_counter = 0;
    auto t1 = high_resolution_clock::now();
    {
        t1 = high_resolution_clock::now();
        for(int i = 0; i < num_tasks; i++) {
            task_counter++;
            hpx::apply(delay_cond, delay_time);
        }
    }
    {
        std::unique_lock<mutex_type> lk(count_mutex);
        while(task_counter > 0) {
            count_cond.wait(lk);
        }
    }
    auto t2 = high_resolution_clock::now();
    return duration_cast<nanoseconds> (t2-t1).count();
}


void delay_counter(int nanosec_delay) {
    auto t1 = high_resolution_clock::now();
    auto t2 = high_resolution_clock::now();
    while(true) {
        if( duration_cast<nanoseconds> (t2-t1).count() > nanosec_delay) {
            break;
        }
        t2 = high_resolution_clock::now();
    }
    task_counter--;
}

int64_t atomic_task_spawn(int num_tasks, int delay_time) {
    task_counter = 0;
    auto t1 = high_resolution_clock::now();
    {
        t1 = high_resolution_clock::now();
        for(int i = 0; i < num_tasks; i++) {
            task_counter++;
            hpx::apply(delay_counter, delay_time);
        }
    }
    hpx::threads::set_thread_state( hpx::threads::get_self_id(), 
                                    hpx::threads::pending, 
                                    hpx::threads::wait_signaled, 
                                    hpx::threads::thread_priority_low);
    while(task_counter > 0) {
        hpx::this_thread::yield();
    }
    auto t2 = high_resolution_clock::now();
    return duration_cast<nanoseconds> (t2-t1).count();
}

void delay(int nanosec_delay) {
    auto t1 = high_resolution_clock::now();
    auto t2 = high_resolution_clock::now();
    while(true) {
        if( duration_cast<nanoseconds> (t2-t1).count() > nanosec_delay) {
            break;
        }
        t2 = high_resolution_clock::now();
    }
}

int64_t exec_task_spawn(int64_t num_tasks, int64_t delay_time)
{
    auto t1 = high_resolution_clock::now();
    {
        local_priority_queue_executor exec;
        t1 = high_resolution_clock::now();
        for(int i = 0; i < num_tasks; i++) {
            hpx::async(exec, delay, delay_time);
        }
    }
    auto t2 = high_resolution_clock::now();
    return duration_cast<nanoseconds> (t2-t1).count();
}

int64_t future_task_spawn(int64_t num_tasks, int64_t delay_time)
{
    vector<shared_future<void> > tasks(num_tasks);
    auto t1 = high_resolution_clock::now();
    t1 = high_resolution_clock::now();
    for(int i = 0; i < num_tasks; i++) {
        tasks[i] = hpx::async(delay, delay_time);
    }
    hpx::wait_all(tasks);
    auto t2 = high_resolution_clock::now();
    return duration_cast<nanoseconds> (t2-t1).count();
}

int hpx_main(int argc, char ** argv) {

    int64_t num_tasks = 500000;
    int64_t delay_time = 50000;
    if(argc > 1)
        delay_time = atoi(argv[1]);
    if(argc > 2)
        num_tasks = atoi(argv[2]);

    cout << "spawning " << num_tasks << " tasks, with a delay of " << delay_time << endl;

    int64_t total_time = num_tasks * delay_time;
    int64_t num_threads = hpx::threads::hardware_concurrency();
    int64_t theory = total_time / num_threads; 
    cout << "theory time = " << theory    / 1000000.0 << " ms (" << total_time << " / " << num_threads << " threads)" << endl;

    int64_t exec_time = exec_task_spawn(num_tasks, delay_time);
    cout << "exec time  = " << exec_time / 1000000.0 << " ms : " << ( exec_time - theory) / 1000000.0 << " ms overhead " << endl;

    int64_t future_time = future_task_spawn(num_tasks, delay_time);
    cout << "future time  = " << future_time / 1000000.0 << " ms : " << ( future_time - theory) / 1000000.0 << " ms overhead " << endl;

    int64_t atomic_time = atomic_task_spawn(num_tasks, delay_time);
    cout << "atomic time  = " << atomic_time / 1000000.0 << " ms : " << ( atomic_time - theory) / 1000000.0 << " ms overhead " << endl;

    int64_t cond_time = cond_task_spawn(num_tasks, delay_time);
    cout << "cond time  = " << cond_time / 1000000.0 << " ms : " << ( cond_time - theory) / 1000000.0 << " ms overhead " << endl;

    return hpx::finalize();
}

int main(int argc, char ** argv) {

    return hpx::init(argc, argv);
}
