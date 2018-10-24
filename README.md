
=====
Code summary
=====

The intel openMP runtime calls are implemented in intel_hpxMP.cpp.
The OMPT support is implemented in ompt_hpx_general.cpp
The gcc support is implemented in gcc_hpxMP.cpp
The bulk of the work is donein hpx_runtime.cpp.
All of the structs/classes of interest are defined in hpx_runtime.h.
This is a different hpx_runtime than the one defined in the hpx implementation, and will eventually
need to be replaced.

=====
Installation with CMake
=====

requires HPX, which can be found at https://github.com/STEllAR-GROUP/hpx

In addition to the other cmake options, HPX must be built with the following option:
 `-DHPX_WITH_THREAD_LOCAL_STORAGE=ON` 
If you want to build hpxMP within HPX, HPX should be built with the following option:
`-DHPX_WITH_HPXMP=ON`

You can build stand-along hpxMP with the following cmake option:
`-DCMAKE_BUILD_TYPE=Debug/Release
 -DCMAKE_ASM_COMPILER=clang/gcc
 -DCMAKE_CXX_COMPILER=clang++/g++ 
 -DCMAKE_C_COMPILER=clang 
 -DHPX_DIR=.../lib/cmake/HPX 
 -DCMAKE_CXX_FLAGS=-stdlib=libc++ `
 
Please note that building with gcc works for the current tests but not fully functioning for now.

Any applications that you want to run need only be compiled with clang/gcc+OpenMP, with
the normal openmp flags. Then run the application with the corresponding hpxMP library: 

LD_PRELOAD=..path_to_build_dir/libhpxmp.so ./myapplication

This library will read in most OpenMP environment variables, as well as pass hpx arguments using the
OMP_HPX_ARGS environment variable. Any HPX arguments passed to the openmp application will not be
passed to hpx.

Tests are under folder tests/, which are performing automatic tests fot this program. 
Some of the tests are adapted from examples under folder examples/omp/tests/src which were written by Jeremy Kemp.

=====
Installation with Make
=====

If you do not want to build with cmake, make files are also provided by Jeremy Kemp, instructions are as follows:
Folder examples/hpx, examples/hybrid-tests and examples/omp were written by Jeremy Kemp, examples/omp/tests contains simple openMP programs originally written by Jeremy Kemp, and provided with the Makefile to build them.
currently, multiple runtimes and compilers have been added to the tests with the following targets:
tests-omp tests-omp-clang tests-omp-icc tests-omp-UH

to build the library for OpenUH, use

make libopenmp.so.1

and to build the library for clang/icc, use 

make libiomp5.so

To build with OpenUH build on Hermoine, add /home/jkemp/openUH/bin to your path, or use your own installation of openUH.
I also have "/home/jkemp/openUH/lib/gcc-lib/x86_64-open64-linux/5.0/" appended to my LD_LIBRARY_PATH, though I forget why.

OpenUH can be found here:

http://svn.open64.net/svnroot/open64/branches/OpenUH

=====
TODO
=====
GCC support not implemented:
sections, taskgroup, cancellation

OMPT optional events.

Directives not implemented:
threadprivate, copyprivate, and copyin 

