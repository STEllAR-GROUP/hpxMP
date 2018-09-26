# Copyright (c) 2018 Tianyi Zhang
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fopenmp")
set(tests
        old-fib
        omp-barrier
        omp-crit
        omp-fib
        omp-firstprivate
        omp-for
        omp-for-decrement
        omp-for-dynamic
        omp-for-nested
        omp-for-nowait
        omp-for-private
        omp-for-shared
        omp-for-simple
        omp-lu
        omp-lu-orig
        omp-master
        omp-nested-par
        omp-not-thrdprvt
        omp-num-thread
        omp-par-for
        omp-par-single
        omp-reduction
        omp-sections
        omp-simple-task
        omp-single
        omp-single-copyprivate
        omp-single-copyprivate-1var
        omp-single-nowait
        omp-task
        omp-task.simple
        omp-task-dep
        omp-task-fp
        omp-task-tree
        omp-thrdprvt
        omp-threadprivate
        omp-vla
        #task_spawn_time
        )

enable_testing()

macro(do_test name)
    add_test(${name} ${name})
    set_target_properties(${name} PROPERTIES
            CXX_STANDARD 11
            CXX_STANDARD_REQUIRED ON
            CXX_EXTENSIONS OFF
            )
    set_tests_properties(${name} PROPERTIES
            ENVIRONMENT "LD_PRELOAD=${PROJECT_BINARY_DIR}/libhpxmp.so;OMP_NUM_THREADS=2"
            TIMEOUT 50
            )
endmacro(do_test)

foreach(test ${tests})
    set(sources ${test}.c)
    add_executable(${test} ${sources})
    do_test(${test})
endforeach()
