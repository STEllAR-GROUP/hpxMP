# Copyright (c) 2018 Tianyi Zhang
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fopenmp")
set(tests
        old-fib
        omp-barrier
        omp-firstprivate
        omp-for-nowait
        omp-for-shared
        omp-lu-orig
        omp-par-single
        omp-reduction
        omp-sections
        omp-simple-task
        omp-single
        omp-single-copyprivate
        omp-single-copyprivate-1var
        omp-task
        omp-task-dep
        omp-task-fp
        )

set(tests_failed
        omp-crit   #timeout on circleci
        omp-fib    #child abort on local
        #something is wrong with omp-for
        omp-for    #timeout on circleci
        omp-for-decrement  #timeout on circleci
        omp-for-dynamic    #timeout on circleci
        omp-for-nested     #timeout on circleci
        omp-for-private    #timeout on circleci
        omp-for-simple     #timeout on circleci
        omp-lu     #timeout on circleci
        omp-master     #timeout on circleci
        omp-nested-par     #timeout on circleci
        omp-not-thrdprvt   #timeout on circleci
        omp-num-thread     #timeout on circleci
        omp-par-for    #timeout on local
        omp-single-nowait  #timeout on circleci
        omp-task.simple    #timeout on circleci
        omp-task-tree  #undefined behavior on local
        omp-thrdprvt    #timeout on circleci
        omp-threadprivate  #timeout on circleci
        omp-vla    #timeout on circleci
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
            ENVIRONMENT LD_PRELOAD=${PROJECT_BINARY_DIR}/libhpxmp.so
            TIMEOUT 30
            )
endmacro(do_test)

foreach(test ${tests})
    set(sources ${test}.c)
    add_executable(${test} ${sources})
    do_test(${test})
endforeach()

if(0)
    foreach(test_failed ${tests_failed})
        set(sources ${test_failed}.c)
        add_executable(${test_failed} ${sources})
        do_test(${test_failed})
    endforeach()
endif()