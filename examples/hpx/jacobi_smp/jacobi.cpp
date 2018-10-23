
//  Copyright (c) 2011-2013 Thomas Heller
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx_fwd.hpp>
#include <hpx/hpx_init.hpp>

#include <boost/program_options.hpp>
#include <boost/assign.hpp>

#include <iostream>

using boost::program_options::variables_map;
using boost::program_options::options_description;
using boost::program_options::value;
using boost::program_options::store;
using boost::program_options::parse_command_line;

#include "jacobi.hpp"

namespace jacobi_smp {

    void jacobi_kernel(
        double * dst
      , const double * src
      , std::size_t n
    )
    {
#ifdef HPX_INTEL_VERSION
#pragma vector always
#pragma unroll(4)
#endif
        for(std::size_t x = 1; x < n-1; ++x) {
            dst[x] = (src[x-n] + src[x+n] + src[x] + src[x-1] + src[x+1]) * 0.2;
        }
    }
}

int hpx_main(variables_map &vm)
{
    {
        std::size_t n           = vm["n"].as<std::size_t>();
        std::size_t iterations  = vm["iterations"].as<std::size_t>();
        std::size_t block_size  = vm["block-size"].as<std::size_t>();

        std::string output_filename;
        if(vm.count("output-filename"))
        {
            output_filename = vm["output-filename"].as<std::string>();
        }

        if(n > block_size) {
            jacobi_smp::jacobi(n, iterations, block_size, output_filename);
        } else {
            jacobi_smp::jacobi_serial(n, iterations, output_filename);
        }
    }

    return hpx::finalize();
}

int main(int argc, char **argv)
{
    options_description
        desc_cmd("usage: " HPX_APPLICATION_STRING " [options]");

    desc_cmd.add_options()
    (
        "n", value<std::size_t>()->default_value(16)
      , "Will run on grid with dimensions (n x n)"
    )
    (
        "iterations", value<std::size_t>()->default_value(1000)
      , "Number of iterations"
    )
    (
        "block-size", value<std::size_t>()->default_value(256)
      , "Block size of the different chunks to calculate in parallel"
    )
    (
        "output-filename", value<std::string>()
      , "Filename of the result (if empty no result is written)"
    );
    using namespace boost::assign;
    std::vector<std::string> cfg;
    cfg += "hpx.os_threads=" +
        boost::lexical_cast<std::string>(hpx::threads::hardware_concurrency());


    return hpx::init(desc_cmd, argc, argv, cfg);
}
