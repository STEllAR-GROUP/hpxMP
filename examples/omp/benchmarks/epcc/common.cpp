/****************************************************************************
 *                                                                           *
 *             OpenMP MicroBenchmark Suite - Version 3.0                     *
 *                                                                           *
 *                            produced by                                    *
 *                                                                           *
 *             Mark Bull, Fiona Reid and Nix Mc Donnell                      *
 *                                                                           *
 *                                at                                         *
 *                                                                           *
 *                Edinburgh Parallel Computing Centre                        *
 *                                                                           *
 *         email: markb@epcc.ed.ac.uk or fiona@epcc.ed.ac.uk                 *
 *                                                                           *
 *                                                                           *
 *      This version copyright (c) The University of Edinburgh, 2011.        *
 *                                                                           *
 *                                                                           *
 *  Licensed under the Apache License, Version 2.0 (the "License");          *
 *  you may not use this file except in compliance with the License.         *
 *  You may obtain a copy of the License at                                  *
 *                                                                           *
 *      http://www.apache.org/licenses/LICENSE-2.0                           *
 *                                                                           *
 *  Unless required by applicable law or agreed to in writing, software      *
 *  distributed under the License is distributed on an "AS IS" BASIS,        *
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. *
 *  See the License for the specific language governing permissions and      *
 *  limitations under the License.                                           *
 *                                                                           *
 ****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <chrono>
#include <omp.h>

#include "common.h"

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;
        

#define CONF95 1.96
using std::vector;

void print_results(vector<double> &times) {
    int reps = times.size();//outer_reps
    double mintime = 1.0e10;
    double maxtime = 0.;
    double totaltime = 0.;

    for(int i = 0; i < reps; i++) {
        mintime = (mintime < times[i]) ? mintime : times[i];
        maxtime = (maxtime > times[i]) ? maxtime : times[i];
        totaltime += times[i];
    }
    double meantime = totaltime / reps;
    double sumsq = 0;

    for(int i = 1; i <= reps; i++) {
        sumsq += (times[i] - meantime) * (times[i] - meantime);
    }
    double sd = sqrt(sumsq / (reps - 1));

    double cutoff = 3.0 * sd;
    int num_outliers = 0;
    for(int i = 1; i <= reps; i++) {
        if (fabs(times[i] - meantime) > cutoff) {
            num_outliers++;
        }
    }

    printf("\nSample_size       Average     Min         Max          S.D.          Outliers\n");
    printf(" %d                %f   %f   %f    %f      %d\n\n",
            reps, meantime, mintime, maxtime, sd, num_outliers);
    printf("time     = %f microseconds +/- %f\n", meantime, CONF95*sd);
    printf("--------------------------------------------------------\n");
}

void benchmark(char name[], bench_func test, int delay_reps, int inner_reps, int outer_reps) {
    vector<double> times(outer_reps);

    printf("Computing %s time using %d reps\n", name, inner_reps);

    for(int k = 0; k < outer_reps; k++) {
        double start = omp_get_wtime();
        test(inner_reps, delay_reps);
        times[k] = (omp_get_wtime() - start) * 1.0e6 / (double) inner_reps;
    }
    print_results(times);
}

void delay(int nanosec_delay) {
    auto t1 = high_resolution_clock::now();
    auto t2 = high_resolution_clock::now();
    while( duration_cast<nanoseconds> (t2-t1).count() < nanosec_delay) 
    {
        t2 = high_resolution_clock::now();
    }
}

