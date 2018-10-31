#include <hpx/hpx_init.hpp>

#include <hpx/include/async.hpp>

using std::cout;
using std::endl;

int arr_add(int size) {
    int n[size];
    int i;
    for( i = 0; i < size; i++) {
        n[i] = 2;
    }
    int sum = 0;
    for( i = 0; i < size; i++) {
        sum += n[i];
    }
    return sum;
}



int hpx_main(boost::program_options::variables_map& vm)
{
    hpx::future<int> sum = hpx::async(arr_add, 2000);
    
    cout << "sum = " << sum.get() << endl;

    return hpx::finalize(); // Handles HPX shutdown
}

int main(int argc, char **argv) {

    return hpx::init( argc, argv);
}
