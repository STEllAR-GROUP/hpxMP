#include <hpx/hpx_init.hpp>
//#include <hpx/hpx_main.hpp>
//#include <hpx/hpx_fwd.hpp>
//#include <hpx/hpx_start.hpp>
//#include <hpx/runtime/threads/topology.hpp>
//#include <hpx/lcos/local/barrier.hpp>
//#include <hpx/util/static.hpp>
//#include <hpx/include/lcos.hpp>
//#include <hpx/include/thread_executors.hpp>

#include <iostream>

using hpx::async;
using std::vector;
using hpx::lcos::future;
using std::cout;
using std::endl;


int hpx_main(int argc, char **argv){
    cout << "os_thread_count() = " << hpx::get_os_thread_count() << endl;
    return hpx::finalize();
}

int main(int argc, char **argv) {

    return hpx::init(argc, argv);
}
