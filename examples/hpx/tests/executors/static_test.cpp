
#include <hpx/hpx_init.hpp>
#include <hpx/hpx.hpp>
//#include <hpx/parallel/executors/thread_pool_executors.hpp>

#include <hpx/runtime/threads/policies/static_priority_queue_scheduler.hpp>
#include <hpx/runtime/threads/executors/thread_pool_executors.hpp>

//#include <hpx/runtime/threads/detail/set_thread_state.hpp>
#include <hpx/runtime/threads/detail/create_thread.hpp>

#include <hpx/util/bind.hpp>

#include <cstdlib>
#include <vector>

using std::cout;
using std::endl;
using hpx::threads::thread_init_data;

typedef hpx::threads::executors::static_priority_queue_executor static_executor;

struct implicit_task_executor : public static_executor
{
    implicit_task_executor(std::size_t max_punits, std::size_t min_punits = 1)
        : static_executor(max_punits, min_punits)
    {}
    
    hpx::threads::thread_state_enum thread_function_nullary( closure_type func)
    {
        func ();
        ++tasks_completed_;
        hpx::util::force_error_on_lock();
        return hpx::threads::terminated;
    }

     void add(closure_type && f, char const* desc,
             hpx::threads::thread_state_enum initial_state, bool run_now,
             hpx::threads::thread_stacksize stacksize, hpx::error_code& ec,
             std::size_t os_thread)
     {
         thread_init_data data(hpx::util::bind(
                                 hpx::util::one_shot( &thread_function_nullary),
                                             this, std::move(f)), desc);
                 data.stacksize = hpx::threads::get_stack_size(stacksize);
     }

};

void f1 () { 
    std::size_t tid = hpx::get_worker_thread_num();
    cout << "test function #" << tid << endl; 
} 

int hpx_main(int argc, char* argv[])
{
    std::size_t num_threads = hpx::get_os_thread_count();
    cout << "num_threads = " << num_threads << endl;

    {
        implicit_task_executor exec(num_threads, num_threads);
        hpx::error_code ec = hpx::throws;
        
        for( int i = 0; i < num_threads * 2; i++) {
            exec.add(std::bind(f1), "", hpx::threads::pending, true, 
                    hpx::threads::thread_stacksize_default, ec, i);
        }
    }

    return hpx::finalize();
}

int main(int argc, char* argv[])
{
    std::vector<std::string> cfg;
    cfg.push_back("hpx.os_threads=" +
        boost::lexical_cast<std::string>(hpx::threads::hardware_concurrency()));

    hpx::init(argc, argv, cfg);

    return 0;
}
