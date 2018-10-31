#include <chrono>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "omp.h"

using std::vector;
using std::cout;
using std::endl;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;


int **A;

void delay(int nanosec_delay) {
    auto t2 = high_resolution_clock::now();
    auto t1 = high_resolution_clock::now();
    while(true) {
        if( duration_cast<nanoseconds> (t2-t1).count() > nanosec_delay) {
            break;
        }
        t2 = high_resolution_clock::now();
    }
}

void spawn_tasks(int num_tasks, int delay_time){
    for(int i = 0; i < num_tasks; i++) {
#pragma omp task
        delay(delay_time);

    }
#pragma omp taskwait
}

void spawn_dep_tasks(int num_tasks1, int num_tasks2, int delay_time) {
    for(int i = 0; i < num_tasks2; i++) {
#pragma omp task depend(out: A[0][i])
        delay(delay_time);
    }
    for(int i = 1; i < num_tasks1; i++) {
        for(int j = 0; j < num_tasks2; j++) {
#pragma omp task depend(in: A[i-1][j]) depend(out: A[i][j])
            delay(delay_time);
        }
    }
#pragma omp taskwait
}

int main(int argc, char ** argv) {

    int num_tasks1 = 1000;
    int num_tasks2 = 500;
    int delay_time = 50000;
    if(argc > 1)
        delay_time = atoi(argv[1]);
    if(argc > 2)
        num_tasks1 = atoi(argv[2]);
    if(argc > 3)
        num_tasks2 = atoi(argv[3]);

    int num_tasks = num_tasks1 * num_tasks2;
    int num_threads;
#pragma omp parallel
{
#pragma omp single 
{
    num_threads = omp_get_num_threads();

    cout << "spawning " << num_tasks << " tasks, with a delay of " << delay_time << endl;

    A = new int*[num_tasks1];

    auto t1 = high_resolution_clock::now();
    spawn_tasks(num_tasks, delay_time);
    auto t2 = high_resolution_clock::now();
    
    auto total = duration_cast<nanoseconds> (t2-t1).count();

    t1 = high_resolution_clock::now();
    spawn_dep_tasks(num_tasks1, num_tasks2, delay_time);
    t2 = high_resolution_clock::now();
    
    auto dep_total = duration_cast<nanoseconds> (t2-t1).count();

    int64_t total_time = num_tasks * delay_time;
    int64_t theory = total_time / num_threads; 
    cout << "theory time = " << theory    / 1000000.0 << " ms (" << total_time << " / " << num_threads << " threads)" << endl;
    cout << "spawn time  = " << total     / 1000000.0 << " ms : " << (    total - theory) / 1000000.0 << " ms overhead " << endl;
    cout << "depend time = " << dep_total / 1000000.0 << " ms : " << (dep_total - theory) / 1000000.0 << " ms overhead " << endl;

    cout << "difference  = " << dep_total - total << endl;
}}

    return 0;
}

