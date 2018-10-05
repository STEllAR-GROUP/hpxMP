# Copyright (c) 2018 Tianyi Zhang
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fopenmp")
set(examples
        omp-barrier
        omp-for
        omp-for-decrement
        omp-for-dynamic
        omp-for-nested
        omp-for-nowait
        omp-for-private
        omp-for-simple
        omp-lu-orig
        omp-master
        omp-nested-par
        omp-not-thrdprvt
        omp-num-thread
        omp-par-for
        omp-par-single
        omp-sections
        omp-simple-task
        omp-single
        omp-task.simple
        omp-task-fp
        omp-thrdprvt
        omp-threadprivate
        #task_spawn_time
        )

foreach(example ${examples})
    set(sources ${example}.c)
    add_executable(${example} ${sources})
endforeach()
