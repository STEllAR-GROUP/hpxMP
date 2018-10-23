//  Copyright (c) 2007-2010 Hartmut Kaiser
//  Copyright (c)      2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx.hpp>
#include <hpx/hpx_init.hpp>
#include <hpx/runtime/actions/plain_action.hpp>
#include <hpx/util/high_resolution_timer.hpp>
#include <hpx/include/async.hpp>

#include <algorithm>
#include <boost/atomic.hpp>

using boost::program_options::variables_map;
using boost::program_options::options_description;
using boost::program_options::value;

using hpx::async;
using hpx::lcos::shared_future;

using hpx::util::high_resolution_timer;

///////////////////////////////////////////////////////////////////////////////
template <typename T>
inline std::size_t partition(T* data, std::size_t begin, std::size_t end)
{
    T* first = data + begin;
    T* last = first + (end - begin);

    T* middle = std::partition(
        first, last, std::bind2nd(std::less<T>(), *first));

    return middle - data;
}

template <typename T>
void quicksort_serial(T* data, std::size_t begin, std::size_t end)
{
    if (begin != end) {
        std::size_t middle_idx = partition(data, begin, end);

        if (2 * middle_idx < end - begin) {
            quicksort_serial(data, (std::max)(begin + 1, middle_idx), end);
            quicksort_serial(data, begin, middle_idx);
        } else {
            quicksort_serial(data, begin, middle_idx);
            quicksort_serial(data, (std::max)(begin + 1, middle_idx), end);
        }
    }
}

template <typename T>
void quicksort_parallel(T *data, std::size_t begin, std::size_t end)
{
    if (begin != end) {
        std::size_t middle_idx = partition(data, begin, end);
        shared_future<void> n;

        if (2 * middle_idx < end - begin) {
            n = async(quicksort_parallel<T>, data, (std::max)(begin + 1, middle_idx), end);

            quicksort_parallel(data, begin, middle_idx);
        } else {
            n = async(quicksort_parallel<T>, data, begin, middle_idx);
            quicksort_parallel(data, (std::max)(begin + 1, middle_idx), end);
        }
        hpx::wait_all(n);
    }
}

int hpx_main(variables_map& vm)
{
    std::size_t elements = 0;

    if (vm.count("elements"))
        elements = vm["elements"].as<std::size_t>();

    int *data = new int[elements];
    std::generate(data, data + elements, std::rand);

    std::cout << "serial quicksort on " << elements << " elements."  << std::endl;

    high_resolution_timer t;
    quicksort_serial<int>(data, 0, elements);
    double elapsed = t.elapsed();

    std::cout << "  elapsed=" << elapsed << "\n";

    std::generate(data, data + elements, std::rand);

    std::cout << "parallel quicksort on " << elements << " elements." << std::endl;

    t.restart();
    shared_future<void> n = async(quicksort_parallel<int>, data, 0, elements);
    hpx::wait_all(n);
    elapsed = t.elapsed();

    std::cout << "  elapsed=" << elapsed << "\n";

    return hpx::finalize();
}

int main(int argc, char* argv[])
{
    // Configure application-specific options
    options_description
        desc_commandline("Usage: " HPX_APPLICATION_STRING " [options]");

    desc_commandline.add_options()
        ("elements", value<std::size_t>()->default_value(1024),
            "the number of elements to generate and sort")
        ;

    return hpx::init(desc_commandline, argc, argv);
}

