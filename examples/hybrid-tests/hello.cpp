#include <hpx/hpx_main.hpp>
#include <iostream>

int main() {
#pragma omp parallel for
    for(int i = 0; i < 10; ++i) {
        std::cout << i << std::endl;
    }
}
