//  Copyright (c) 2007-2017 Hartmut Kaiser, Richard D Guidry Jr.
//  Copyright (c) 2011 Vinay C Amatya
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  Parts of this nqueen_client.cpp has been taken from the accumulator example
//  by Hartmut Kaiser.

#include <hpx/hpx.hpp>
#include <hpx/hpx_init.hpp>
#include <hpx/include/lcos.hpp>

#include <hpx/runtime.hpp>
#include <hpx/include/client.hpp>

#include <boost/lexical_cast.hpp>

#include <cstddef>
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <chrono>
#include <numeric>

#include "nqueen.hpp"


using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;


int sum_count_futures(std::vector<hpx::shared_future<int> > counts)
{
    int sum = 0;
    for(int i=0; i<counts.size(); i++) {
        sum += counts[i].get();
    }
    return sum;
}
/*
hpx::shared_future<int> task_create( nqueen::board sub_board, int size, int col)
{
    nqueen::board b1(sub_board.access_board(), size, 0);
    b1.update_board(0, col);
    if(b1.check_board(b1.access_board(), 0)) {
        int level = 1;
        std::vector<hpx::shared_future<int> > sub_count(size);

        nqueen::board b2(b1.access_board(), size, level);
        for(int i=0; i<size; i++) {
            b2.update_board(level, i);
            if (b2.check_board(b2.access_board(), level)) {
                sub_count[i] = hpx::async(&nqueen::board::solve_board, b2, b2.access_board(), size, level+1, col);
            } else {
                sub_count[i] = hpx::make_ready_future(0);
            }
        }
        return hpx::dataflow( hpx::util::unwrapping(sum_count_futures), hpx::when_all(sub_count));
    }
    return hpx::make_ready_future(0);

}
*/
int task_create( nqueen::board sub_board, int size, int col)
{
    nqueen::board b1(sub_board.access_board(), size, 0);
    b1.update_board(0, col);
    int sum = 0;
    if(b1.check_board(b1.access_board(), 0)) {
        int level = 1;
        std::vector<hpx::shared_future<int> > sub_count(size);

        nqueen::board b2(b1.access_board(), size, level);
        for(int i=0; i<size; i++) {
            b2.update_board(level, i);
            if (b2.check_board(b2.access_board(), level)) {
                sub_count[i] = hpx::async(&nqueen::board::solve_board, b2, b2.access_board(), size, level+1, col);
            } else {
                sub_count[i] = hpx::make_ready_future(0);
            }
        }
        hpx::wait_all(sub_count);
        sum = sum_count_futures(sub_count);
    }
    return sum;
}


int hpx_main(int argc, char* argv[])
{
    int soln_count_total = 0;
    int sz = 8;
    int task_level = 1;
    if(argc > 1) {
        sz = atoi(argv[1]);
    } 
    if(argc > 2) {
        task_level = atoi(argv[2]);
    }

    std::cout << "board size: " << sz;
    std::cout << ", nesting level " << task_level << std::endl;

    std::vector<nqueen::board> sub_boards;
    std::vector<hpx::shared_future<int> > sub_count(sz);

    auto t1 = high_resolution_clock::now();
    for(int i=0; i < sz; i++) {
        sub_boards.push_back(nqueen::board());
        sub_boards[i].init_board(sz);
        if(task_level == 0) {
            sub_count[i] = hpx::async(&nqueen::board::solve_board, sub_boards[i], sub_boards[i].access_board(), sz, 0, i);
        } else {
            //sub_count[i] = task_create( sub_boards[i], sz, i);
            sub_count[i] = hpx::async(task_create, sub_boards[i], sz, i);
        }
    }
    soln_count_total = sum_count_futures(sub_count);

    auto t2 = high_resolution_clock::now();

    auto total = duration_cast<nanoseconds> (t2-t1).count();
    std::cout << "time: " << total << " ns" << std::endl;
    std::cout << "soln_count: " << soln_count_total << std::endl;

    return hpx::finalize();
}

int main(int argc, char* argv[])
{
    return hpx::init(argc, argv);
}
