
=====
Code summary
=====

The intel openMP runtime calls are implemented in intel_hpxMP.cpp.
The bulk of the work is donein hpx_runtime.cpp.
All of the structs/classes of interest are defined in hpx_runtime.h.
This is a different hpx_runtime than the one defined in the hpx implementation, and will eventually
need to be replaced.

=====
Installation 
=====

requires HPX, which can be found at https://github.com/STEllAR-GROUP/hpx

In addition to the other cmake options, HPX must be built with the following option:
 `-DHPX_WITH_THREAD_LOCAL_STORAGE=ON` 

omp/tests contains simple openMP programs and the Makefile to build them.
currently, multiple runtimes and compilers have been added to the tests with the following targets:
tests-omp tests-omp-clang tests-omp-icc tests-omp-UH

to build the library for OpenUH, use

make libopenmp.so.1

and to build the library for clang/icc, use 

make libiomp5.so

Any applications that you want to run need only be compiled with OpenUH or icc/clang+OpenMP, with
the normal openmp flags. Then run the application with the corresponding hpxMP library: 

LD_PRELOAD=/path/to/lib/libiomp5.so myapplication

This library will read in most OpenMP environment variables, as well as pass hpx arguments using the
OMP_HPX_ARGS environment variable. Any HPX arguments passed to the openmp application will not be
passed to hpx.



To build with OpenUH build on Hermoine, add /home/jkemp/openUH/bin to your path, or use your own installation of openUH.
I also have "/home/jkemp/openUH/lib/gcc-lib/x86_64-open64-linux/5.0/" appended to my LD_LIBRARY_PATH, though I forget why.

OpenUH can be found here:

http://svn.open64.net/svnroot/open64/branches/OpenUH

Directives not implemented:
threadprivate, copyprivate, and copyin 

