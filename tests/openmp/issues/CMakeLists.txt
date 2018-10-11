# Copyright (c) 2018 Tianyi Zhang
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fopenmp")
set(tests
        task_no_parallel
        task_tree_simple
        task_untied
        get_thread_num
        parallel_multi
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
