#  Copyright (c) 2018 Tianyi Zhang
#
#  Distributed under the Boost Software License, Version 1.0. (See accompanying
#  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

if(HPXMP_WITH_OMPT)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
    add_executable(hello_world hello_world.cpp)
    add_executable(task_ex task_ex.cpp)
endif()
