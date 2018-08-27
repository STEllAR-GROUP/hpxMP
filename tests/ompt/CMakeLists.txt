# Copyright (c) 2018 Tianyi Zhang
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

if(HPXMP_WITH_OMPT)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
    set(tests
            par_for
            parallel
            parallel_nested
            task
            task_dep
            task_fp
            task_implicit_simple
            task_simple
            wait_barrier
            task_wait
            task_group
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
                ENVIRONMENT LD_PRELOAD=${PROJECT_BINARY_DIR}/libhpxmp.so
                TIMEOUT 10
                )
    endmacro(do_test)

    foreach(test ${tests})
        set(sources ${test}.cpp)
        add_executable(${test} ${sources})
        do_test(${test})
    endforeach()
endif()
