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
        omp_set_get_nested
        par_for
        par_nested
        par_single
        sections
        sections_2
        #single_copyprivate #failure sometime
        #single_copyprivate_2   #failure sometime
        #single_copyprivate_1var    #failure sometime
        single_nowait
        taskgroup
        task_fp
        task_tree
        taskwait
        taskwait_2
        #threadprivate  #failure sometime
        )
if(HPXMP_WITH_OMP_50_ENABLED)
    set(tests_omp50
            task_in_reduction
            )
endif()
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
    set(sources ${test}.cpp)
    add_executable(tests.omp.unit.${test} ${sources})
    do_test(tests.omp.unit.${test})
endforeach()

if(HPXMP_WITH_OMP_50_ENABLED)
    foreach(test ${tests_omp50})
        set(sources ${test}.cpp)
        add_executable(tests.omp.unit.${test} ${sources})
        do_test(tests.omp.unit.${test})
    endforeach()
endif()
