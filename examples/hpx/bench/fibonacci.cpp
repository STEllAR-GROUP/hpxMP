////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

// Naive SMP version implemented with futures.

#include <hpx/hpx.hpp>
#include <hpx/hpx_init.hpp>
//#include <hpx/include/actions.hpp>
#include <hpx/include/util.hpp>
#include <iostream>
#include <boost/cstdint.hpp>
#include <boost/format.hpp>

boost::uint64_t threshold = 2;


boost::uint64_t fibonacci(boost::uint64_t n) {
    if (n < 2)
        return n;
    if (n < threshold)
        return fibonacci(n-1) + fibonacci(n-2);
    hpx::future<boost::uint64_t> n1 = hpx::async(fibonacci, n - 1);
    hpx::future<boost::uint64_t> n2 = hpx::async(fibonacci, n - 2);

    return n1.get() + n2.get();
}

int hpx_main(boost::program_options::variables_map& vm)
{
    boost::uint64_t n = vm["n-value"].as<boost::uint64_t>();
    threshold = vm["threshold"].as<unsigned int>();  
    {
        hpx::util::high_resolution_timer t;
        boost::uint64_t r = fibonacci(n);
        char const* fmt = "fibonacci(%1%) == %2%\nelapsed time: %3% [s]\n";
        std::cout << (boost::format(fmt) % n % r % t.elapsed());
    }
    return hpx::finalize(); // Handles HPX shutdown
}

int main(int argc, char* argv[])
{
    boost::program_options::options_description
       desc_commandline("Usage: " HPX_APPLICATION_STRING " [options]");

    using boost::program_options::value;
    desc_commandline.add_options()
        ( "n-value",
          value<boost::uint64_t>()->default_value(10),
          "n value for the Fibonacci function")
        ( "threshold", value<unsigned int>()->default_value(2),
          "threshold for switching to serial code");

    return hpx::init(desc_commandline, argc, argv);
}
