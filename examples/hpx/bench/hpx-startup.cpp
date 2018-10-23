#include <hpx/hpx_init.hpp>
#include <hpx/runtime/threads/topology.hpp>
//#include <hpx/include/util.hpp>
//#include <boost/assign/std/vector.hpp>
//#include <boost/cstdint.hpp>
#include <boost/format.hpp>

#include <chrono>

using hpx::lcos::shared_future;
using hpx::lcos::future;

using std::vector;
using std::cout;
using std::endl;

using std::chrono::high_resolution_clock;

using time_point = std::chrono::system_clock::time_point;
time_point hpx_time1;
time_point hpx_time2;

void print_time(time_point t1, time_point t2, std::string name) {
     auto time = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
     cout << name << ": " << time << " microseconds" << endl;
}

int hpx_main(boost::program_options::variables_map& vm) {
    hpx_time1 = high_resolution_clock::now();

    cout << "hpx started with " << hpx::get_os_thread_count() << " threads" << endl;

    hpx_time2 = high_resolution_clock::now();
    return hpx::finalize();
}

void time_startup(int argc, char** argv) {
    time_point t1 = high_resolution_clock::now();
    hpx::init(argc, argv);
    time_point t2 = high_resolution_clock::now();
    print_time(t1, hpx_time1,  "startup time");
    print_time(hpx_time2, t2, "shutdown time");
}

int main(int argc, char ** argv) {
    int arg_count = 3;
    char *new_args[3];

    if(argc > 1) {
        time_startup(argc, argv);
    }

    char opt[] = "-t";
    new_args[1] = opt;
    std::string num_threads = std::to_string(hpx::threads::hardware_concurrency());
    new_args[2] = &num_threads[0];

    time_startup(arg_count, new_args);

    num_threads = std::to_string(1);
    new_args[2] = &num_threads[0];
    time_startup(arg_count, new_args);

    return 0;
}
