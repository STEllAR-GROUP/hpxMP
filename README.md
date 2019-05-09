<!--   Distributed under the Boost Software License, Version 1.0. (See accompanying -->
<!--   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        -->

# hpxMP: An OpenMP runtime implemented using [HPX](https://github.com/STEllAR-GROUP/hpx)

hpxMP is a portable, scalable and flexible application programming interface using OpenMP specification 
that supports multi-platform shared memory multiprocessing programming in C/ C++. hpxMP is originally developed by our collaborator, Jeremy Kemp, hpxMP maps OpenMP calls to their equivalent HPX functions. OpenMP runtime shared
library such as libomp.so, libgomp.so can be replaced with this library when you are running an OpenMP
application. 

A recorded introduction video of hpxMP can be found
 [here](https://www.youtube.com/watch?v=ajDGWPDrcxU&index=12&list=PL7vEgTL3FalbVFwzkXLHpBRKlcJNULW1g).

The [CircleCI](https://circleci.com/gh/STEllAR-GROUP/hpxMP) contiguous
integration service tracks the current build status for the master branch:
[![CircleCI](https://circleci.com/gh/STEllAR-GROUP/hpxMP.svg?style=svg)](https://circleci.com/gh/STEllAR-GROUP/hpxMP).

# Motivation

OpenMP and HPX "fight against" each other if they are used in the same application
as they are both controlling concurrency, doing thread scheduling, which causes performance disaster.
The idea to solve this is to replace OpenMP runtime with hpxMP runtime, thus HPX will control concurrency itself. In this way, we prevent the OpenMP and HPX runtime systems from competing for resources when they are used in the same application. 

Currently, STE||AR group is developing [Phylanx](https://github.com/STEllAR-GROUP/phylanx), 
An Asynchronous Distributed C++ Array Processing Toolkit. This ability is useful in the context of Phylanx as our dependencies rely on libraries such as OpenBLAS which use OpenMP to manage their threading. 

For long term goals, a bug free hpxMP runtime updated with 
most recent OpenMP specification will be implemented,
and can be used in general purpose such as scientific parallel computing.

# Code summary

The intel and gcc openMP runtime calls are implemented in intel_hpxMP.cpp/ gcc_hpxMP.cpp

The bulk of the work is done in hpx_runtime.cpp.

The OMPT support is implemented in ompt_hpx_general.cpp

The tests are under folder tests/, which are performing automatic tests for this program. 
Some of the tests are adapted from examples under folder examples/omp/tests/src which were written by Jeremy Kemp.

This is a different hpx_runtime than the one defined in the hpx implementation, and will eventually
need to be replaced.

# Installation

Please refer to [Install Instruction](doc/install.md) for detailed instruction on how to install hpxMP.

# Usage Examples

Please refer to [Usage Examples](doc/usecases.md) for simple use examples.

# DONEs and TODOs

Please refer to [dones and todos](doc/done-todo.md) for information about
what has been implemented in hpxMP and what needs to be done.

# Credit

Please cite as
Jeremy Kemp, Tianyi Zhang, Bryce Adelstein, Shahrzad Shirzad, Hartmut Kaiser, Parsa Amini, & Bibek Wagle. (2018, November 1). hpxMP (Version 0.1.0). Zenodo. http://doi.org/10.5281/zenodo.2662481
