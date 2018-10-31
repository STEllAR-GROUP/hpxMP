#include <hpx/hpx_init.hpp>
#include <hpx/hpx.hpp>
#include <unistd.h>
#include <iostream>

using hpx::lcos::shared_future;

void delay1(int seconds) {
    std::cout << "\tdelay1" << std::endl;
    sleep(seconds);
    std::cout << "\tend delay1" << std::endl;
}
void delay2(int seconds) {
    std::cout << "\tdelay2" << std::endl;
    sleep(seconds);
    std::cout << "\tend delay2" << std::endl;
}

void wait_delay(int seconds, shared_future<void> f1){
    std::cout << "\t\twait and delay" << std::endl;
    sleep(seconds);
    hpx::async(delay2, 2);
    std::cout << "\t\twaiting" << std::endl;
    f1.wait();
    std::cout << "\t\tdone waiting" << std::endl;
    sleep(seconds);
    std::cout << "\t\tend wait and delay" << std::endl;
}

int hpx_main()
{

    std::cout << "beginning" << std::endl;
    shared_future<void> f1 = hpx::async(delay1, 2);
    shared_future<void> f2 = hpx::async(wait_delay, 1, f1);
    f2.wait();
    return hpx::finalize();
}

int main(int argc, char **argv)
{
    using namespace boost::assign;

    std::vector<std::string> cfg;
    cfg += "hpx.os_threads=2";// + 
    //    boost::lexical_cast<std::string>(hpx::threads::hardware_concurrency());

    std::cout << "before hpx_main" << std::endl;
    return hpx::init(argc, argv, cfg);

}
