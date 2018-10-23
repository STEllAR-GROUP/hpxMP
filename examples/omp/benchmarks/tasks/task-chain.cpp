#include <chrono>
#include <cstdlib>
#include <iostream>
#include <vector>

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

int main(int argc, char ** argv) {

    int length = 20;
    if(argc > 1)
        length = atoi(argv[1]);
    int val = 0;
#pragma omp parallel
#pragma omp single
{
    auto t1 = high_resolution_clock::now();

    func_time.reserve(length);

    for(int i = 0; i < length; i++) {
#pragma omp task depend(inout: val) shared(val)
       val = chain_add(val); 
    }
#pragma omp taskwait
    auto t2 = high_resolution_clock::now();
    cout << "val = " << val << endl;
    
    auto total = duration_cast<nanoseconds> (t2-t1).count();
    cout << "total time = " << total << endl;

    cout << " time 0 = " << duration_cast<nanoseconds> (func_time[0]-t1).count() << endl;
    for(int i = 1; i < length; i++) {
        cout << " time " << i << " = " << duration_cast<nanoseconds> (func_time[i]-func_time[i-1]).count() << endl;
    }
    cout << " last time = " << duration_cast<nanoseconds> (t2-func_time[length-1]).count() << endl;

}
    return 0;
}

