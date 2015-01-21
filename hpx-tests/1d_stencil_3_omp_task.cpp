//  Copyright (c) 2014 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// This is the third in a series of examples demonstrating the development of a
// fully distributed solver for a simple 1D heat distribution problem.
//
// This example takes the code from example one and introduces a partitioning
// of the 1D grid into groups of grid partitions which are handled at the same time.
// The purpose is to be able to control the amount of work performed. The
// example is still fully serial, no parallelization is performed.
//
// The only difference to 1d_stencil_3 is that this example uses OpenMP for
// parallelizing the inner loop.

#include <boost/cstdint.hpp>
#include <boost/program_options.hpp>
#include <boost/chrono.hpp>

#include <vector>
#include <cstdlib>

#include <omp.h>

#include "print_time_results.hpp"
///////////////////////////////////////////////////////////////////////////////
// Timer with nanosecond resolution
inline boost::uint64_t now()
{
    boost::chrono::nanoseconds ns =
        boost::chrono::steady_clock::now().time_since_epoch();
    return static_cast<boost::uint64_t>(ns.count());
}

///////////////////////////////////////////////////////////////////////////////
bool header = true; // print csv heading
double k = 0.5;     // heat transfer coefficient
double dt = 1.;     // time step
double dx = 1.;     // grid spacing

inline std::size_t idx(std::size_t i, std::size_t size)
{
    return (boost::int64_t(i) < 0) ? (i + size) % size : i % size;
}

///////////////////////////////////////////////////////////////////////////////
// Our partition_data data type
struct partition_data
{
    partition_data(std::size_t size = 0)
      : data_(size)
    {}

    partition_data(std::size_t size, double initial_value)
      : data_(size)
    {
        double base_value = double(initial_value * size);
        for (std::size_t i = 0; i != size; ++i)
            data_[i] = base_value + double(i);
    }

    double& operator[](std::size_t idx) { return data_[idx]; }
    double operator[](std::size_t idx) const { return data_[idx]; }

    std::size_t size() const { return data_.size(); }

private:
    std::vector<double> data_;
};

std::ostream& operator<<(std::ostream& os, partition_data const& c)
{
    os << "{";
    for (std::size_t i = 0; i != c.size(); ++i)
    {
        if (i != 0)
            os << ", ";
        os << c[i];
    }
    os << "}";
    return os;
}

///////////////////////////////////////////////////////////////////////////////
struct stepper
{
    // Our data for one time step
    typedef partition_data partition;
    //typedef std::vector<partition> space;
    typedef partition* space;

    // Our operator
    static double heat(double left, double middle, double right)
    {
        return middle + (k*dt/dx*dx) * (left - 2*middle + right);
    }

    // The partitioned operator, it invokes the heat operator above on all
    // elements of a partition.
    static partition_data heat_part(partition_data const& left,
        partition_data const& middle, partition_data const& right)
    {
        std::size_t size = middle.size();
        partition_data next(size);

        next[0] = heat(left[size-1], middle[0], middle[1]);

        for (std::size_t i = 1; i != size-1; ++i)
            next[i] = heat(middle[i-1], middle[i], middle[i+1]);

        next[size-1] = heat(middle[size-2], middle[size-1], right[0]);

        return next;
    }

    // do all the work on 'np' partitions, 'nx' data points each, for 'nt'
    // time steps
    space do_work(std::size_t np, std::size_t nx, std::size_t nt)
    {
        // U[t][i] is the state of position i at time t.
        partition* U[2];
        U[0] = new partition[np];
        U[1] = new partition[np];
        //It seems that the OpenMP 4.0 spec prevents elements in a vector from being used as
        //dependencies.

        // Initial conditions: f(0, i) = i
        # pragma omp parallel
        {
        #pragma omp master
        {
        //# pragma omp for schedule(static)
        for (boost::int64_t i = 0; i < (boost::int64_t)np; ++i)
            U[0][i] = partition_data(nx, double(i));

        // Actual time step loop
        for (std::size_t t = 0; t != nt; ++t)
        {
            space const& current = U[t % 2];
            space& next = U[(t + 1) % 2];

            for (size_t i = 0; i < np; ++i) 
            {
#pragma omp task untied depend( in: current[idx(i-1, np)], current[i], current[idx(i+1, np)] ) depend( out: U[(t+1)%2][i] )
                {
                    U[(t+1) % 2][i] = heat_part(current[idx(i-1, np)], current[i], current[idx(i+1, np)]);
                }
            }
        }

        }}
        delete U[(nt + 1) % 2];
        // Return the solution at time-step 'nt'.
        return U[nt % 2];
    }
};

///////////////////////////////////////////////////////////////////////////////
int hpx_main(boost::program_options::variables_map& vm)
{
    boost::uint64_t np = vm["np"].as<boost::uint64_t>();   // Number of partitions.
    boost::uint64_t nx = vm["nx"].as<boost::uint64_t>();   // Number of grid points.
    boost::uint64_t nt = vm["nt"].as<boost::uint64_t>();   // Number of steps.
    
    if (vm.count("no-header"))
        header = false;


    // Create the stepper object
    stepper step;

    // Measure execution time.
    boost::uint64_t t = now();

    // Execute nt time steps on nx grid points and print the final solution.
    stepper::space solution = step.do_work(np, nx, nt);

    boost::uint64_t elapsed = now() - t;

    // Print the final solution
    if (vm.count("results"))
    {
        for (std::size_t i = 0; i != np; ++i)
            std::cout << "U[" << i << "] = " << solution[i] << std::endl;
    }
//  boost::uint64_t const os_thread_count = omp_get_num_threads();
    # pragma omp parallel
    # pragma omp master
    print_time_results(omp_get_num_threads(), elapsed, nx, np, nt, header);


    return 0;
}

int main(int argc, char* argv[])
{
    namespace po = boost::program_options;

    po::options_description desc_commandline;
    desc_commandline.add_options()
        ("results", "print generated results (default: false)")
        ("nx", po::value<boost::uint64_t>()->default_value(10),
         "Local x dimension (of each partition)")
        ("nt", po::value<boost::uint64_t>()->default_value(45),
         "Number of time steps")
        ("np", po::value<boost::uint64_t>()->default_value(10),
         "Number of partitions")
        ("k", po::value<double>(&k)->default_value(0.5),
         "Heat transfer coefficient (default: 0.5)")
        ("dt", po::value<double>(&dt)->default_value(1.0),
         "Timestep unit (default: 1.0[s])")
        ("dx", po::value<double>(&dx)->default_value(1.0),
         "Local x dimension")
        ( "no-header", "do not print out the csv header row")
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc_commandline), vm);
    po::notify(vm);

    return hpx_main(vm);
}
