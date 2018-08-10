#  Copyright (c) 2018 Tianyi Zhang
#
#  Distributed under the Boost Software License, Version 1.0. (See accompanying
#  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

if(HPXMP_WITH_OMPT)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -fopenmp")
    add_executable(hello_world hello_world.c)
    add_executable(task_ex task_ex.c)
endif()
