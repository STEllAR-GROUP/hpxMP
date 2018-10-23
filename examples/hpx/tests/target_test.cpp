#include <iostream>
#include <hpx/hpx.hpp>
/*
void foo(int *in_vals, int size, int *out_vals)
{
    for(int i = 0; i < size; i++) {
        out_vals[i] = in_vals[i] + 1;
    }
}

HPX_PLAIN_ACTION(foo, foo_action);
*/
int add(int val1, int val2)
{
    return val1 + val2;
}
HPX_PLAIN_ACTION(add, add_action);


int hpx_main()
{
    /*
    const int size = 10;
    int in[size], out[size];
    for(int i = 0; i < size; i++) {
        in[i] = i;
    }


    foo(in, size, out);

    for(int i = 0; i < size; i++) {
        std::cout << out[i] << ", ";
    }
    std::cout << std::endl;
    */

    auto localities = hpx::find_all_localities();
    
    for( auto &node : localities ) {
        auto result = hpx::async(add_action(), node, 2, 3);
        std::cout << result.get() << std::endl;
    }

    return hpx::finalize();
}

int main(int argc, char** argv) 
{
    return hpx::init(argc, argv);
}
