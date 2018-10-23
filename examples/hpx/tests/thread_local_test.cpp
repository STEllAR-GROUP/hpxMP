#include <iostream>
#include <hpx/hpx_main.hpp>
#include <hpx/hpx_fwd.hpp>
#include <hpx/hpx_start.hpp>
#include <hpx/runtime/threads/topology.hpp>
#include <hpx/lcos/local/barrier.hpp>
#include <hpx/util/static.hpp>
#include <hpx/include/lcos.hpp>

struct thread_data {
    int thread_num;
};

int get_thread_num() {
    auto thread_id = hpx::threads::get_self_id();
    auto *data = reinterpret_cast<thread_data*>(
            hpx::threads::get_thread_data(thread_id) );
    int tid = data->thread_num;
    return tid;
}

void omp_thread_func() {
    int tid = get_thread_num();
    std::cout << "hello from thread " << tid << std::endl;
}

int main() {
    thread_data *data_struct = new thread_data();
    data_struct->thread_num = 42;
    auto thread_id = hpx::threads::get_self_id();
    hpx::threads::set_thread_data( thread_id, reinterpret_cast<size_t>(data_struct));
    omp_thread_func();
    return 0;
}
