//  Copyright (c) 2007-2017 Hartmut Kaiser, Richard D Guidry Jr.
//  Copyright (c) 2011 Vinay C Amatya
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  Parts of this nqueen_client.cpp has been taken from the accumulator example
//  by Hartmut Kaiser.


//#include <boost/lexical_cast.hpp>

#include <cstddef>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>


#include "nqueen.hpp"


using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;

int task_create( nqueen::board sub_board, int size, int col)
{
    //return sub_board.solve_board( sub_board.access_board(), size, 0, i);

    int *sub_count = new int[size];
    nqueen::board b1(sub_board.access_board(), size, 0);
    b1.update_board(0, col);

    if(b1.check_board(b1.access_board(), 0)) {
        int level = 1;

        nqueen::board b2(b1.access_board(), size, level);
        for(int i=0; i < size; i++) {
            b2.update_board(level, i);
            if (b2.check_board(b2.access_board(), level)) {
#pragma omp task 
                {
                    sub_count[i] = b2.solve_board(b2.access_board(), size, level+1, col);
                }
            } else {
                sub_count[i] = 0;
            }
        }
    }
#pragma omp taskwait
    int soln_count_total = 0;
    for(int i=0; i < size; i++) {
        soln_count_total += sub_count[i];
    }

    delete[] sub_count;

    return soln_count_total;
}

int main(int argc, char* argv[]) 
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


    std::cout << "board size: " << sz << std::endl;

#pragma omp parallel
    {
#pragma omp single
        {
            nqueen::board *sub_boards = new nqueen::board[sz];
            int *sub_count = new int[sz];
            auto t1 = high_resolution_clock::now();
            for(int i=0; i < sz; i++) {
                sub_boards[i] = nqueen::board();
                sub_boards[i].init_board(sz);
                if(task_level == 0) {
#pragma omp task 
                    {
                        sub_count[i] = sub_boards[i].solve_board(sub_boards[i].access_board(), sz, 0, i);
                    }
                } else {
#pragma omp task 
                    {
                        sub_count[i] = task_create( sub_boards[i], sz, i);
                    }
                }
            }
#pragma omp taskwait
            for(int i=0; i < sz; i++) {
                soln_count_total += sub_count[i];
            }
            auto t2 = high_resolution_clock::now();

            auto total = duration_cast<nanoseconds> (t2-t1).count();
            std::cout << "time: " << total << " ns" << std::endl;
            std::cout << "soln_count:" << soln_count_total << std::endl;
            delete[] sub_boards;
            delete[] sub_count;

        }}//end parallel
    return 0;
}

