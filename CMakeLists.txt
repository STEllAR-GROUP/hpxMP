# Copyright (c) 2018 Bibek Wagle
# Copyright (c) 2018 Tianyi Zhang
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

PROJECT(HPXMP CXX ASM)

cmake_minimum_required(VERSION 2.8)

set(hpxmp_sources
        src/asm_functions.s
        src/intel_hpxMP.cpp
        src/hpx_runtime.cpp
        src/kmp_atomic.cpp
        src/loop_schedule.cpp)

set(hpxmp_headers
        src/intel_hpxMP.h
        src/hpx_runtime.h
        src/kmp_atomic.h
        src/loop_schedule.h)

set(HPXMP_WITH_TRACE OFF CACHE BOOL "display traces in debug mode")
if(HPXMP_WITH_TRACE)
    add_definitions(-DHPXMP_HAVE_TRACE)
endif()

set(HPXMP_WITH_OMPT OFF CACHE BOOL "ompt support for hpxmp")
if(HPXMP_WITH_OMPT)
    add_definitions(-DHPXMP_HAVE_OMPT=1)
    set(hpxmp_sources
            ${hpxmp_sources}
            src/ompt_hpx-general.cpp)
    set(hpxmp_headers ${hpxmp_headers}
            src/ompt.h
            src/ompt-event-specific.h
            src/ompt-internal.h)
endif()

# Find and include HPX settings
if(NOT HPX_WITH_HPXMP)

    if (NOT HPX_DIR)
        message(FATAL "HPX_DIR not set, unable to find HPX!")
    endif()
    message(STATUS "HPX_DIR=${HPX_DIR}")

    SET(CMAKE_ASM_FLAGS "${CFLAGS} -x assembler-with-cpp")

    # This adds the HPX cmake configuration directory to the search path.
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
        ${HPX_DIR}/share/cmake-${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}/Modules)

    # Instruct cmake to find the HPX settings
    find_package(HPX NO_CMAKE_PACKAGE_REGISTRY REQUIRED)
    set(HPX_RPATH  "${HPX_RPATH}:${CMAKE_INSTALL_PREFIX}/lib/hpx:${CMAKE_BINARY_DIR}/lib/hpx")

    include_directories(${HPX_INCLUDE_DIRS})
    link_directories(${HPX_LIBRARY_DIR})

    add_library(hpxmp SHARED ${hpxmp_sources} ${hpxmp_headers})

    foreach(dir ${HPX_LIBRARY_DIR})
        target_link_libraries(hpxmp PRIVATE -L${dir})
    endforeach()

    target_link_libraries(hpxmp PRIVATE ${HPX_LIBRARIES})

else()

    foreach(__source ${hpxmp_sources})
        add_hpx_library_sources_noglob(hpx_external
            SOURCES "${__source}" APPEND)
    endforeach()
    foreach(__header ${hpxmp_headers})
        add_hpx_library_headers_noglob(hpx_external
            HEADERS "${PROJECT_SOURCE_DIR}/${__header}" APPEND)
    endforeach()

endif()

add_subdirectory(examples/ompt)
#add_subdirectory(tests/omp/tests/src)
add_subdirectory(tests/ompt)
add_subdirectory(tests/openmp)
enable_testing()
