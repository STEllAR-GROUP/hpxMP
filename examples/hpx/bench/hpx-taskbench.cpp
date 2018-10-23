#include <hpx/hpx_init.hpp>
#include <hpx/include/lcos.hpp>
//#include <hpx/include/async.hpp>
#include <hpx/runtime/threads/topology.hpp>
#include <hpx/include/util.hpp>
#include <hpx/util/unwrapped.hpp>

#include <hpx/lcos/local/barrier.hpp>

#include <hpx/include/performance_counters.hpp>


#include <boost/assign/std/vector.hpp>
#include <boost/cstdint.hpp>
#include <boost/format.hpp>

#include <atomic>

using hpx::lcos::local::barrier;
using hpx::lcos::shared_future;
using hpx::lcos::future;

using std::vector;
using std::cout;
using std::endl;
using std::atomic;

const int DEPTH = 6;
int delay_ns = 50000;

atomic<int> task_counter{0};

//void delay(int delaylength) {
//    float a = 0.;
//    for(int i = 0; i < delaylength; i++)
//        a += i;
//    if(a < 0)
//        printf("%f \n", a);
//    //task_counter++;
//}

void delay(int nanosec_delay) {
    uint64_t start = hpx::util::high_resolution_clock::now();
    uint64_t end = start;
    while(end-start < nanosec_delay) {
        end = hpx::util::high_resolution_clock::now();
    }
}

//PARALLEL TASK 1 (nowait)
future<void> spawn_tasks(int inner_reps) {
    vector<future<void>> tasks(inner_reps);
    for(int i = 0; i < inner_reps; i++) {
        tasks[i] = hpx::async(delay, delay_ns);
    }
    return hpx::when_all(tasks);
}


uint64_t testParallelTaskGeneration(int num_threads, int inner_reps) {
    vector<future<void>> threads(num_threads);
    uint64_t start = hpx::util::high_resolution_clock::now();
    for(int i = 0; i < num_threads; i++) {
        threads[i]  = hpx::async(spawn_tasks, inner_reps);
    }
    hpx::wait_all(threads);
    return hpx::util::high_resolution_clock::now() - start;
}

//PARALLEL TASK 2 (wait)
void spawn_tasks_wait(int inner_reps) {
    vector<future<void>> tasks(inner_reps);
    for(int i = 0; i < inner_reps; i++) {
        tasks[i] = hpx::async(delay, delay_ns);
    }
    hpx::wait_all(tasks);
}

uint64_t testParallelTaskGeneration_wait(int num_threads, int inner_reps) {
    vector<future<void>> threads(num_threads);
    uint64_t start = hpx::util::high_resolution_clock::now();
    for(int i = 0; i < num_threads; i++) {
        threads[i]  = hpx::async(spawn_tasks_wait, inner_reps);
    }
    hpx::wait_all(threads);
    return hpx::util::high_resolution_clock::now() - start;
}

//MASTER TASK
uint64_t testMasterTaskGeneration(int num_threads, int inner_reps) {
    vector<future<void>> threads(num_threads * inner_reps);
    uint64_t start = hpx::util::high_resolution_clock::now();
    for(int i = 0; i < num_threads * inner_reps; i++) {
        threads[i] = hpx::async(delay, delay_ns);
    }
    hpx::wait_all(threads);
    return hpx::util::high_resolution_clock::now() - start;
}

//MASTER TASK BUSY SLAVES
future<void> master_busy_thread(int thread_id, int inner_reps) {
    if(thread_id == 0) {
        vector<future<void>> tasks(inner_reps);
        for(int i = 0; i < inner_reps; i++) {
            tasks[i] = hpx::async(delay, delay_ns);
        }
        return hpx::when_all(tasks);
    } else {
        vector<future<void>> tasks;
        for(int i = 0; i < inner_reps; i++) {
            delay( delay_ns );
        }
        return hpx::when_all(tasks);
    }
}

uint64_t testMasterTaskGenerationWithBusySlaves(int num_threads, int inner_reps)  {
    vector<future<void>> threads(num_threads);
    uint64_t start = hpx::util::high_resolution_clock::now();
    for(int i = 0; i < num_threads; i++) {
        threads[i] = hpx::async(master_busy_thread, i, inner_reps);
    }
    hpx::wait_all(threads);
    return hpx::util::high_resolution_clock::now() - start;
}

//TASK WAIT
void spawn_and_wait(int inner_reps) {
    for(int i = 0; i < inner_reps; i++) {
        auto task = hpx::async(delay, delay_ns);
        task.wait();
    }
}
// this is very similar to PARALLEL TASK, only with taskwaits in each thread
// this is probably going to be slower, though.
uint64_t testTaskWait(int num_threads, int inner_reps){
    vector<future<void>> threads(num_threads);
    uint64_t start = hpx::util::high_resolution_clock::now();
    for(int i = 0; i < num_threads; i++) {
        threads[i] = hpx::async(spawn_and_wait, inner_reps);
    }
    hpx::wait_all(threads);
    return hpx::util::high_resolution_clock::now() - start;
}

//TASK BARRIER
void barrier_thread_func(int inner_reps, int delay_ns, barrier *B) {
    for(int i=0; i < inner_reps; i++) {
        auto task = hpx::async(delay, delay_ns);
        task.wait();
        B->wait();
    }
}

boost::uint64_t barrier_test(int num_threads, int inner_reps) {
    vector<future<void>> threads(num_threads);
    barrier B(num_threads);
    boost::uint64_t start = hpx::util::high_resolution_clock::now();
    for(int i = 0; i < num_threads; i++) {
        threads[i] = hpx::async(barrier_thread_func, inner_reps, delay_ns, &B);
    }
    hpx::wait_all(threads);
    return hpx::util::high_resolution_clock::now() - start;
}

//NESTED TASK
//void spawn_tasks_wait(int inner_reps) {
//    vector<future<void>> tasks(inner_reps);
//    for(int i=0; i<inner_reps; i++) {
//        tasks[i] = hpx::async(delay, delay_ns);
//    }
//    hpx::wait_all(tasks);
//}

void spawn_nested_tasks_wait(int num_threads, int inner_reps) {
    vector<future<void>> tasks(inner_reps);
    for(int i = 0; i < inner_reps; i++) {
        tasks[i] = hpx::async(spawn_tasks_wait, num_threads );
    }
    hpx::wait_all(tasks);
}

uint64_t testNestedTaskGeneration(int num_threads, int inner_reps) {
    vector<future<void>> threads(num_threads);
    uint64_t start = hpx::util::high_resolution_clock::now();
    for(int i = 0; i < num_threads; i++) {
        threads[i] = hpx::async(spawn_nested_tasks_wait, num_threads, inner_reps/num_threads);
    }
    hpx::wait_all(threads);
    return hpx::util::high_resolution_clock::now() - start;
}

//NESTED MASTER TASK
uint64_t testNestedMasterTaskGeneration(int num_threads, int inner_reps) {
    vector<future<void>> threads(inner_reps);
    uint64_t start = hpx::util::high_resolution_clock::now();
    for(int i = 0; i < inner_reps; i++) {
        threads[i] = hpx::async(spawn_tasks_wait, num_threads );
    }
    hpx::wait_all(threads);
    return hpx::util::high_resolution_clock::now() - start;
}

//BRANCH TASK TREE 
//TODO: Maybe a version with executors?

future<void> branch2(int tree_level) {
    vector<future<void>> tasks(2);
    if(tree_level > 1 ) {
        tasks[0] = hpx::async( branch2, tree_level-1 );
        tasks[1] = hpx::async( branch2, tree_level-1 );
    } else {
        tasks[0] = hpx::make_ready_future();
        tasks[1] = hpx::make_ready_future();
    }
    delay(delay_ns);
    return hpx::when_all(tasks);
}
future<void> branch_thread_func(int inner_reps) {
    vector<future<void>> tasks(inner_reps>>DEPTH);
    for(int i = 0; i < (inner_reps >> DEPTH); i++) {
        tasks[i] = hpx::async(branch2, DEPTH);
    }
    return hpx::when_all(tasks);
}
uint64_t testBranchTaskGeneration(int num_threads, int inner_reps) {
    vector<future<void>> threads(num_threads);
    uint64_t start = hpx::util::high_resolution_clock::now();
    for(int i = 0; i < num_threads; i++) {
        threads[i] = hpx::async(branch_thread_func, inner_reps );
    }
    hpx::wait_all(threads);
    return hpx::util::high_resolution_clock::now() - start;
}

//LEAF TASK TREE
future<void> leaf_task_tree(int tree_level) {
    vector<future<void>> tasks(2);
    if( tree_level > 1 ) {
        tasks[0] = hpx::async(leaf_task_tree, tree_level-1);
        tasks[1] = hpx::async(leaf_task_tree, tree_level-1);
    } else {
        tasks[0] = hpx::async(delay, delay_ns);
        tasks[1] = hpx::async(delay, delay_ns);
    } 
    return hpx::when_all(tasks);
}
future<void> leaf_thread_func(int inner_reps) {
    vector<future<void>> tasks(inner_reps >> DEPTH);
    for(int i = 0; i < (inner_reps >> DEPTH); i++) {
       //tasks[i] = hpx::async(leaf_task_tree, DEPTH);
       tasks[i] = leaf_task_tree( DEPTH );
    }
    return hpx::when_all(tasks);
}
uint64_t testLeafTaskGeneration(int num_threads, int inner_reps) {
    vector<future<void>> threads(num_threads);
    uint64_t start = hpx::util::high_resolution_clock::now();
    for(int i = 0; i < num_threads; i++) {
        threads[i] = hpx::async(leaf_thread_func, inner_reps );
    }
    hpx::wait_all(threads);
    return hpx::util::high_resolution_clock::now() - start;
}

void print_time(std::vector<double> time, std::string name) {
    double total = 0, min = time[0], max = 0;
    for(int i = 0; i < time.size(); i++) {
        total += time[i];
        if(time[i] > max) {
            max = time[i];
        }
        if(time[i] < min) {
            min = time[i];
        }
    }
    cout << endl << name << ", (average, min, max) in ns:" << endl
         << (total / time.size()) << " - " << min << " - " << max << endl;
    
}

void print_delay_time(){
    uint64_t start = hpx::util::high_resolution_clock::now();
    for(int i = 0; i < 1000; i++) {
        delay(delay_ns);
    }
    uint64_t total = hpx::util::high_resolution_clock::now() - start;
    double average = (double)total / (double)1000.0;
    cout << "total delay time is: " << average << " nanoseconds)" << endl;
}

int hpx_main(boost::program_options::variables_map& vm) {
    int num_threads = hpx::get_os_thread_count();

    int reps = vm["reps"].as<int>();
    int inner_reps = vm["inner_reps"].as<int>();
    delay_ns= vm["delay_ns"].as<int>();
    vector<double> time(reps);

    for(int i = 0; i < reps; i++) {
        time[i] = ((double)testParallelTaskGeneration(num_threads, inner_reps) / (double)inner_reps);
    }
    print_time(time, "PARALLEL TASK");//20

    for(int i = 0; i < reps; i++) {
        time[i] = ((double)testParallelTaskGeneration_wait(num_threads, inner_reps) / (double)inner_reps);
    }
    print_time(time, "PARALLEL TASK v2 (wait)");//20

    for(int i = 0; i < reps; i++) {
        time[i] = ((double)testMasterTaskGeneration(num_threads, inner_reps) / (double)inner_reps);
    }
    print_time(time, "MASTER TASK");//20

    for(int i = 0; i < reps; i++) {
        time[i] = ((double)testMasterTaskGenerationWithBusySlaves(num_threads, inner_reps) / (double)inner_reps);
    }
    print_time(time, "MASTER TASK BUSY SLAVES");//1280 / 640 (hpxMP)

    for(int i = 0; i < reps; i++) {
        time[i] = ((double)testTaskWait(num_threads, inner_reps) / (double)inner_reps);
    }
    print_time(time, "TASK WAIT");//1280 / 80 (hpxMP)
    //barrier_thread_func
    for(int i = 0; i < reps; i++) {
        time[i] = ((double)barrier_test(num_threads, inner_reps) / (double)inner_reps);
    }
    print_time(time, "TASK BARRIER");

    for(int i = 0; i < reps; i++) {
        time[i] = ((double)testNestedTaskGeneration(num_threads, inner_reps) / (double)inner_reps);
    }
    print_time(time, "NESTED TASK");//2560 / 80 (hpxMP)

    for(int i = 0; i < reps; i++) {
        time[i] = ((double)testNestedMasterTaskGeneration(num_threads, inner_reps) / (double)inner_reps);
    }
    print_time(time, "NESTED MASTER TASK");//2560 / 160 (hpxMP)

    for(int i = 0; i < reps; i++) {
        time[i] = ((double)testBranchTaskGeneration(num_threads, inner_reps) / (double)inner_reps);
    }
    print_time(time, "BRANCH TASK TREE");//5120 / 160 (hpxMP)

    for(int i = 0; i < reps; i++) {
        time[i] = ((double)testLeafTaskGeneration(num_threads, inner_reps) / (double)inner_reps);
    }
    print_time(time, "LEAF TASK TREE");//5120 / 160 (hpxMP)


    return hpx::finalize(); // Handles HPX shutdown
}

int main(int argc, char ** argv) {

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
        ( "inner_reps", value<int>()->default_value(1024),
          "corresponds to the number of tasks spawned, default 1024")
        ( "delay_ns", value<int>()->default_value(50000),
          "number of nanoseconds in delay function (0-?, default: 50000)") ;

    return hpx::init(desc_commandline, argc, argv, cfg);
}

