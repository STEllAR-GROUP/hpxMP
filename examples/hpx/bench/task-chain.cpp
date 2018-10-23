#include <chrono>

#include <hpx/hpx_init.hpp>
#include <hpx/runtime/threads/topology.hpp>
#include <hpx/include/util.hpp>
#include <hpx/include/lcos.hpp>
//#include <hpx/util/unwrapping.hpp>
//#include <hpx/lcos/local/dataflow.hpp>

#include <boost/assign/std/vector.hpp>
#include <boost/cstdint.hpp>
#include <boost/format.hpp>

using hpx::lcos::future;
//using hpx::lcos::local::dataflow;
using hpx::dataflow;
using hpx::util::unwrapping;

using std::vector;
using std::cout;
using std::endl;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;

vector<std::chrono::time_point<std::chrono::high_resolution_clock>> func_time;

int chain_add(int n) {
    func_time[n]= high_resolution_clock::now();
    return n+1;
}

int hpx_main(boost::program_options::variables_map& vm) {

    int length = vm["length"].as<int>();
    func_time.reserve(length);
    auto val = hpx::make_ready_future(0);

    auto t1 = high_resolution_clock::now();
    for(int i = 0; i < length; i++) {
       val = dataflow( unwrapping(&chain_add), val); 
    }
    val.wait();
    auto t2 = high_resolution_clock::now();
    cout << "val = " << val.get() << endl;
    
    auto total = duration_cast<nanoseconds> (t2-t1).count();
    cout << "total time = " << total << endl;

    cout << " time 0 = " << duration_cast<nanoseconds> (func_time[0]-t1).count() << endl;
    for(int i = 1; i < length; i++) {
        cout << " time " << i << " = " << duration_cast<nanoseconds> (func_time[i]-func_time[i-1]).count() << endl;
    }
    cout << " last time = " << duration_cast<nanoseconds> (t2-func_time[length-1]).count() << endl;

    return hpx::finalize();
}

int main(int argc, char ** argv) {


    boost::program_options::options_description
       desc_commandline("Usage: " HPX_APPLICATION_STRING " [options]");

    using boost::program_options::value;
    desc_commandline.add_options()
        ( "length", value<int>()->default_value(20),
          "length of the chain of task dependencies used") ;

    return hpx::init(desc_commandline, argc, argv);
}
