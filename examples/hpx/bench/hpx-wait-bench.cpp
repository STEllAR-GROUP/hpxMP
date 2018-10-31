
#include <hpx/hpx_init.hpp>
#include <hpx/include/lcos.hpp>
#include <hpx/runtime/threads/topology.hpp>
#include <hpx/include/util.hpp>
#include <hpx/util/unwrapped.hpp>


#include <boost/assign/std/vector.hpp>
#include <boost/cstdint.hpp>
#include <boost/format.hpp>

#include <atomic>

using hpx::lcos::shared_future;
using hpx::lcos::future;

using std::atomic;
using std::vector;
using std::cout;
using std::endl;

int delay_length;
atomic<int> task_counter{0};

void placeholder_task() {
    float a = 0.;
    for(int i = 0; i < delay_length; i++)
        a += i;
    if(a < 0)
        printf("%f \n", a);
}
void wrapper_task() {
    placeholder_task();
    task_counter--;
}

void print_task_time() {
    auto start = hpx::util::high_resolution_clock::now();
    for(int i = 0; i < 1000; i++) {
        placeholder_task();
    }
    auto total_time = hpx::util::high_resolution_clock::now() - start;
    cout << "task time for delay = " << delay_length << " = " << (total_time)/1000 << " nanoseconds" << endl;
}

uint64_t task_spawn_wait(int total_tasks) {
    uint64_t start = hpx::util::high_resolution_clock::now();
    vector<future<void>> tasks;
    tasks.reserve(total_tasks);
    for(int i = 0; i < total_tasks; i++) {
        tasks.push_back(hpx::async(placeholder_task));
    }
    hpx::wait_all(tasks);
    return hpx::util::high_resolution_clock::now() - start;
}

uint64_t task_spawn_count(int total_tasks) {
    uint64_t start = hpx::util::high_resolution_clock::now();
    task_counter = 0;
    for(int i = 0; i < total_tasks; i++) {
        task_counter++;
        hpx::async(wrapper_task);
    }
    while(task_counter > 0) {
        hpx::this_thread::yield();
    }
    return hpx::util::high_resolution_clock::now() - start;
}

uint64_t task_apply_count(int total_tasks) {
    uint64_t start = hpx::util::high_resolution_clock::now();
    task_counter = 0;
    for(int i = 0; i < total_tasks; i++) {
        task_counter++;
        hpx::apply(wrapper_task);
    }
    while(task_counter > 0) {
        hpx::this_thread::yield();
    }
    return hpx::util::high_resolution_clock::now() - start;
}

// Nested tasking: 

void nested_wait_spawner(int num_tasks) {
    vector<future<void>> tasks;
    tasks.reserve(num_tasks);
    for(int i = 0; i < num_tasks; i++) {
        tasks.push_back(hpx::async(placeholder_task));
    }
    hpx::wait_all(tasks);
}

uint64_t nested_task_wait(int level1, int level2) {
    uint64_t start = hpx::util::high_resolution_clock::now();
    vector<future<void>> tasks;
    tasks.reserve(level1);
    for(int i = 0; i < level1; i++) {
        tasks.push_back(hpx::async(nested_wait_spawner, level2));
    }
    hpx::wait_all(tasks);
    return hpx::util::high_resolution_clock::now() - start;
}

// These functions are used for the nested_task_apply_count test
void counting_task(atomic<int> &local_counter) {
    placeholder_task();
    local_counter--;
}
void nested_spawner(int num_tasks, atomic<int> &local_counter) {
    for(int i = 0; i < num_tasks; i++) {
        local_counter++;
        hpx::apply(counting_task, boost::ref(local_counter));
    }
    local_counter--;
}
uint64_t nested_task_apply_count(int level1, int level2) {
    uint64_t start = hpx::util::high_resolution_clock::now();
    atomic<int> local_task_counter{0};
    for(int i = 0; i < level1; i++) {
        local_task_counter++;
        hpx::apply(nested_spawner, level2, boost::ref(local_task_counter));
    }
    while(local_task_counter > 0) {
        hpx::this_thread::yield();
    }
    return hpx::util::high_resolution_clock::now() - start;
}
//-----------------------------------------------------------------------------

int hpx_main(boost::program_options::variables_map& vm) {
    delay_length = vm["delay_length"].as<int>();
    int num_threads = hpx::get_os_thread_count();
    int total_tasks = vm["task_count"].as<int>();
    int nesting1 = num_threads;
    int nesting2 = total_tasks;
    total_tasks *= num_threads;

    print_task_time();

    cout << "wait  time ( " << total_tasks << " ) = " << task_spawn_wait(total_tasks) << endl;
    
    cout << "apply time ( " << total_tasks << " ) = " << task_apply_count(total_tasks) << endl;

    cout << "nested-wait(" << nesting1 << "," << nesting2  << ") = " 
        << nested_task_wait(nesting1, nesting2) << endl;
    cout << "nested-wait(" << nesting2 << "," << nesting1  << ") = " 
        << nested_task_wait(nesting2, nesting1) << endl;

    cout << "nested     (" << nesting1 << "," << nesting2  << ") = " 
         << nested_task_apply_count(nesting1, nesting2) << endl;
    cout << "nested     (" << nesting2 << "," << nesting1  << ") = " 
         << nested_task_apply_count(nesting2, nesting1) << endl;

    return hpx::finalize();
}

int main(int argc, char **argv) {
    using namespace boost::assign;
    std::vector<std::string> cfg;
    cfg += "hpx.os_threads=" +        
        boost::lexical_cast<std::string>(hpx::threads::hardware_concurrency());

    boost::program_options::options_description
       desc_commandline("Usage: " HPX_APPLICATION_STRING " [options]");

    using boost::program_options::value;
    desc_commandline.add_options()
        ( "reps", value<int>()->default_value(20),
          "number of times to repeat the benchmark")
        ( "task_count", value<int>()->default_value(1024),
          "number of tasks to spawn (default 1024*num_threads")
        ( "delay_length", value<int>()->default_value(10000),
          "size of work to be done in the task") ;

    return hpx::init(desc_commandline, argc, argv, cfg);
}

