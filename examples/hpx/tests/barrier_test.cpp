#include <hpx/hpx_init.hpp>
#include <hpx/include/lcos.hpp>
#include <hpx/include/async.hpp>
#include <hpx/lcos/local/barrier.hpp>
#include <hpx/runtime/threads/topology.hpp>
#include <atomic>


using hpx::lcos::local::barrier;

std::atomic<int> count{0};

void wait_and_return(barrier *B) {
    std::cout << "count decremented from " << count-- << std::endl;
    B->wait();
}

void spawn_and_wait(barrier *B, int NT) {
    std::vector<hpx::future<void>> threads;
    for(int i = 0; i < NT; i++) {
        threads.push_back( hpx::async( &wait_and_return, B ) );
    }
    std::cout << "waiting on threads" << std::endl;
    hpx::wait_all(threads);
    std::cout << "done waiting on threads" << std::endl;
}

int hpx_main() {
    int NT = hpx::get_os_thread_count();
    barrier B(NT);

    count = NT;
    spawn_and_wait(&B, NT);
    std::cout << "count = " << count << std::endl;
    
    count = NT;
    spawn_and_wait(&B, NT);
    std::cout << "second count = " << count << std::endl;

    return hpx::finalize();
}

int main(int argc, char *argv[]) {
    using namespace boost::assign;
    std::vector<std::string> cfg;
    cfg += "hpx.os_threads=" +        
        boost::lexical_cast<std::string>(hpx::threads::hardware_concurrency());

    hpx::init(argc, argv, cfg);
    return 0;
}

