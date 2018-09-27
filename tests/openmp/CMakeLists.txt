# Copyright (c) 2018 Tianyi Zhang
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fopenmp")
set(tests
        old-fib
        omp-crit
        omp-firstprivate
        omp-fib
        omp-for-shared
        omp-lu
        omp-reduction
        omp-single-copyprivate
        #omp-single-copyprivate-1var failed sometime
        omp-single-nowait
        omp-task
        omp-task-dep
        omp-task-tree
        omp-vla
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

add_subdirectory(issues)
add_subdirectory(adding_c++)
