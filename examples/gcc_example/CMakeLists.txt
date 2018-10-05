# Copyright (c) 2018 Tianyi Zhang
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fopenmp")
set(tests
        hello_world_gcc
        task_gcc
        task_with_global
        task_wait_single_gcc
        private_shared_gcc
        omp-copyprivate
        omp-for-dynamic_gcc
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
            #                PASS_REGULAR_EXPRESSION "pass"
            ENVIRONMENT "LD_PRELOAD=${PROJECT_BINARY_DIR}/libhpxmp.so;OMP_NUM_THREADS=2"
            TIMEOUT 10
            )
endmacro(do_test)

foreach(test ${tests})
    set(sources ${test}.c)
    add_executable(${test} ${sources})
    do_test(${test})
endforeach()
