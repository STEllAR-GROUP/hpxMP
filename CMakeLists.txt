# Copyright (c) 2018 Bibek Wagle
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

PROJECT(HPXMP CXX ASM)

cmake_minimum_required(VERSION 2.8)

SET(CMAKE_ASM_FLAGS "${CFLAGS} -x assembler-with-cpp")

# Find and include HPX settings
if(NOT HPX_DIR)
    message(FATAL "HPX_DIR not set, unable to find HPX!")
endif()

message(STATUS "HPX_DIR=${HPX_DIR}")

# This adds the HPX cmake configuration directory to the search path.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
        ${HPX_DIR}/share/cmake-${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}/Modules)

# Instruct cmake to find the HPX settings
find_package(HPX REQUIRED)

include_directories(${HPX_INCLUDE_DIR})
link_directories(${HPX_LIBRARY_DIR})

set(HPX_RPATH  "${HPX_RPATH}:${CMAKE_INSTALL_PREFIX}/lib/hpx:${CMAKE_BINARY_DIR}/lib/hpx")

add_hpx_library(hpxmp SOURCES src/asm_functions.s src/intel_hpxMP.cpp src/hpx_runtime.cpp src/kmp_atomic.cpp src/loop_schedule.cpp  HEADERS src/intel_hpxMP.h src/hpx_runtime.h src/kmp_atomic.h src/loop_schedule.h)
