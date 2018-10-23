
//  Copyright (c) 2011-2013 Thomas Heller
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "jacobi.hpp"
#include <boost/program_options.hpp>
#include <iostream>
#include <chrono>

using boost::program_options::variables_map;
using boost::program_options::options_description;
using boost::program_options::value;
using boost::program_options::store;
using boost::program_options::parse_command_line;

using boost::shared_ptr;
using std::min;
using std::vector;


void jacobi_kernel_wrap(size_t y_begin, size_t y_end, size_t n, vector<double> & dst, vector<double> const & src) {
    for(size_t y = y_begin; y < y_end; ++y) {
        size_t offset = y * n;
        for(size_t x = offset + 1; x < offset + n-1; ++x) {
            dst[x] = (src[x-n] + src[x+n] + src[x] + src[x-1] + src[x+1]) * 0.2;
        }
    }
}

void jacobi( size_t n , size_t iterations, size_t block_size, std::string output_filename) {
    shared_ptr< vector<double> > grid_new(new vector<double>(n * n, 1));
    shared_ptr< vector<double> > grid_old(new vector<double>(n * n, 1));

    size_t n_block = static_cast<size_t>(std::ceil(double(n)/block_size));

#pragma omp parallel 
{
#pragma omp single
{
    auto start = std::chrono::high_resolution_clock::now();

    for(size_t i = 0; i < iterations; ++i) {
        for(size_t y = 1, j = 0; y < n - 1; y += block_size, ++j) {
            size_t y_end = min(y + block_size, n - 1);

            double *dest = (*grid_new).data();
            double *src = (*grid_old).data();

#pragma omp task firstprivate(y, y_end, grid_new, grid_old) depend(inout: dest[y*n], src[y*n])
        {
            jacobi_kernel_wrap(y, y_end, n, boost::ref(*grid_new), boost::cref(*grid_old));
        }
            std::swap(grid_new, grid_old);
        }
    }
#pragma omp taskwait
    auto end = std::chrono::high_resolution_clock::now();
    double elapsed = std::chrono::duration_cast< std::chrono::duration<double> >(end-start).count();
    jacobi_smp::report_timing(n, iterations, elapsed);
    jacobi_smp::output_grid(output_filename, *grid_old, n);
}}

}


int main(int argc, char **argv)
{
    options_description
        desc_cmd("usage: jacobi_omp [options]");

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

    variables_map vm;
    store(parse_command_line( argc, argv, desc_cmd), vm);
    boost::program_options::notify(vm);

    std::size_t n           = vm["n"].as<std::size_t>();
    std::size_t iterations  = vm["iterations"].as<std::size_t>();
    std::size_t block_size  = vm["block-size"].as<std::size_t>();

    std::string output_filename;
    if(vm.count("output-filename"))
    {
        output_filename = vm["output-filename"].as<std::string>();
    }

    jacobi(n, iterations, block_size, output_filename);

    return 0;
}
