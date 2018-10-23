#include <iostream>
#include <hpx/hpx_fwd.hpp>
#include <hpx/hpx_init.hpp>
#include <hpx/runtime/threads/topology.hpp>
#include <hpx/lcos/local/barrier.hpp>
#include <hpx/util/static.hpp>
#include <hpx/include/lcos.hpp>
#include <hpx/include/thread_executors.hpp>

#include <boost/shared_ptr.hpp>

#include <boost/lexical_cast.hpp>


using hpx::async;
using std::vector;
using hpx::lcos::future;
using std::cout;
using std::endl;
using hpx::threads::executors::local_priority_queue_executor;

class mock_runtime {
    public:
        boost::shared_ptr<local_priority_queue_executor> exec;
};

boost::shared_ptr<mock_runtime> test_runtime;
/*
void print_ints(int i, int j) {
    cout << "* i = " << i << ", j = " << j << endl;
}

void thread_setup(int i) {
    vector<hpx::lcos::future<void>> tasks;
    for(int j = 0; j < 5; j++) {
        tasks.push_back(async(print_ints, i , j));
    }
}
*/
int hpx_main() {
    vector<hpx::lcos::future<void>> threads;
    
    test_runtime->exec.reset(new local_priority_queue_executor);
    
//    for(int i = 0; i < 8; i++) {
//        threads.push_back(async(thread_setup, i));
//    }
//    hpx::wait_all(threads);

    test_runtime->exec.reset();
    cout << "All done" << endl;
    return hpx::finalize();
}

int main(int argc, char *argv[]) {

    using namespace boost::assign;
    std::vector<std::string> cfg;
    cfg += "hpx.os_threads=" +        
        boost::lexical_cast<std::string>(hpx::threads::hardware_concurrency());

    test_runtime.reset(new mock_runtime);
    hpx::init(argc, argv, cfg);
    return 0;
}
