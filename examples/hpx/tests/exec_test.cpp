#include <iostream>
#include <hpx/hpx.hpp>
#include <hpx/hpx_fwd.hpp>
#include <hpx/hpx_start.hpp>
#include <hpx/runtime/threads/topology.hpp>
#include <hpx/lcos/local/barrier.hpp>
#include <hpx/util/static.hpp>
#include <hpx/include/lcos.hpp>
#include <hpx/include/thread_executors.hpp>

using hpx::async;
using std::vector;
using hpx::lcos::future;
using std::cout;
using std::endl;
using hpx::threads::executors::local_priority_queue_executor;
using hpx::threads::executors::local_queue_executor;


void thread_setup(int i) {
    hpx::threads::thread_id_type id = hpx::threads::get_self_id();
    cout << "i = " << i << endl;
    cout << "executor: " << hpx::threads::get_executor(id) << endl;
}

void exec_spawn(int input){
    hpx::threads::thread_id_type id = hpx::threads::get_self_id();
    cout << "in spawn #" << input << ", executor: " << hpx::threads::get_executor(id) << endl;

    {
        local_priority_queue_executor exec1(1);
        auto f = async(exec1, thread_setup, input);
        f.wait();
    }
}

int hpx_main() {
    vector<hpx::lcos::future<void>> threads;
    //threads.push_back(async(thread_setup, 42));

    {
        //local_priority_queue_executor exec;
        for(int i = 0; i < 8; i++) {
            //threads.push_back(async(exec, thread_setup, i));
            threads.push_back(async(exec_spawn, i));
        }
        hpx::wait_all(threads);
        cout << "All done" << endl;
    }
    return hpx::finalize();
}

int main(int argc, char **argv) {
    return hpx::init(argc, argv);
}
