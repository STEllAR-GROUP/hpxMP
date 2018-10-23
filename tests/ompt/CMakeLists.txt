# Copyright (c) 2018 Tianyi Zhang
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

if(HPXMP_WITH_OMPT)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
    set(tests
            ompt_par_for
            ompt_parallel
            ompt_parallel_nested
            ompt_task
            ompt_task_dep
            ompt_task_fp
            ompt_task_implicit_simple
            ompt_task_simple
            ompt_wait_barrier
            ompt_task_wait
            ompt_task_group
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
                TIMEOUT 30
                )
    endmacro(do_test)

    foreach(test ${tests})
        set(sources ${test}.cpp)
        add_executable(${test} ${sources})
        do_test(${test})
    endforeach()
endif()
