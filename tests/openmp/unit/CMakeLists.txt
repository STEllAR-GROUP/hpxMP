# Copyright (c) 2018 Tianyi Zhang
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
set(tests
        app_lu
        app_old_fib
        app_vla
        atomic
        barrier
        critical
        critical_2
        firstprivate
        for_decrement
        for_dynamic
        for_increment
        for_nowait
        for_reduction
        for_shared
        for_static
        master
        max_threads
        par_for
        par_nested
        par_single
        sections
        sections_2
        #single_copyprivate #failure sometime
        #single_copyprivate_2   #failure sometime
        #single_copyprivate_1var    #failure sometime
        single_nowait
        taskgroup #to be implemented, not checking correctness
        task_in_reduction
        task_fp
        task_tree
        taskwait
        taskwait_2
        #threadprivate  #failure sometime
        )

set(tests_enhanced
        app_omp_fib
        task_depend
    )

enable_testing()

macro(do_test name)
    add_test(${name} ${name})
    set_target_properties(${name} PROPERTIES
            CXX_STANDARD 11
            CXX_STANDARD_REQUIRED ON
            CXX_EXTENSIONS OFF
            )
        #maybe make the omp_num_threads configurable later
    set_tests_properties(${name} PROPERTIES
            ENVIRONMENT "LD_PRELOAD=${PROJECT_BINARY_DIR}/libhpxmp.so;OMP_NUM_THREADS=2"
            TIMEOUT 50
            )
endmacro(do_test)

macro(do_test_enhanced name)
    add_test(${name} ${name})
    set_target_properties(${name} PROPERTIES
            CXX_STANDARD 11
            CXX_STANDARD_REQUIRED ON
            CXX_EXTENSIONS OFF
            )
    #maybe make the omp_num_threads configurable later
    set_tests_properties(${name} PROPERTIES
            ENVIRONMENT "LD_PRELOAD=${PROJECT_BINARY_DIR}/libhpxmp.so;OMP_NUM_THREADS=2"
            TIMEOUT 60
            )
endmacro(do_test_enhanced)



foreach(test ${tests})
    set(sources ${test}.cpp)
    add_executable(${test} ${sources})
    do_test(${test})
endforeach()

foreach(test ${tests_enhanced})
    set(sources ${test}.cpp)
    add_executable(${test} ${sources})
    do_test_enhanced(${test})
endforeach()
