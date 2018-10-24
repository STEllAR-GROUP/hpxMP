# Prerequisites
* C++ Compiler (C++14-compatible)
  * GCC 4.9 or newer.
  * Intel Compiler 2014 or newer.
  * Clang 3.4 or newer.
* [CMake](https://cmake.org/) 2.8.10 or newer.
* [Boost](http://www.boost.org/) 1.57.0 or newer.
* [HPX](https://github.com/STEllAR-GROUP/hpx)

# Downloading and building HPX
You can find more details in [HPX Build Recipes](https://stellar-group.github.io/hpx/docs/html/hpx/manual/build_system/building_hpx/build_recipes.html).

In addition to the other cmake options, HPX must be built with the following option:
 `-DHPX_WITH_THREAD_LOCAL_STORAGE=ON` 
 
If you want to build hpxMP within HPX, HPX should be built with the following option:
`-DHPX_WITH_THREAD_LOCAL_STORAGE=ON -DHPX_WITH_HPXMP=ON` It will pull hpxMP master when you build HPX.

**Note:** *TCMalloc or JEMalloc will speed up memory allocations *significantly* in HPX (thus in hpxMP). 

# Downloading hpxMP

hpxMP is open source, and available on Github at <https://github.com/STEllAR-GROUP/hpxMP>.

Other users may want to work with the most recent code available, in which case you can clone the git repo:

```bash
https://github.com/STEllAR-GROUP/hpxMP.git
cd hpxMP
```

# Installation Option 1: Configuring and building hpxMP with CMake directly (recommended for most users)

hpxMP is built with CMake. The process for building hpxMP is:

1) Get the code (as demonstrated above)

2) Enter the repo directory, make a build directory:

```bash
cd hpxMP
mkdir build
cd build
```

3) configure using CMake:
```bash
cmake -DCMAKE_BUILD_TYPE=Debug/Release
 -DCMAKE_ASM_COMPILER=clang/gcc
 -DCMAKE_CXX_COMPILER=clang++/g++ 
 -DCMAKE_C_COMPILER=clang 
 -DHPX_DIR=path_to_hpx_build_dir/lib/cmake/HPX 
 -DCMAKE_CXX_FLAGS=-stdlib=libc++ ..
```
4) build with make:
```bash
make
make test
```
5) compile your own application with the normal openmp flags.

```bash
clang -fopenmp my_application.c -o my_application
```

6) run the application with the corresponding hpxMP library
```bash
LD_PRELOAD=..path_to_hpxMP_build_dir/libhpxmp.so ./my_application
```

**Note:** Compiling your application with gcc may not work as expected for now.

This library will read in most OpenMP environment variables, as well as pass hpx arguments using the
OMP_HPX_ARGS environment variable. Any HPX arguments passed to the openmp application will not be
passed to hpx.

# Other CMake settings, depending on your needs/wants
There are several cmake settings that provide additional functionality in hpxMP. 
For the following options, the default values are in italics.
* **-DHPX_WITH_OMPT=**
TRUE or *FALSE*. Currently not fully functioning. OpenMP Tool Interfaces in hpxMP. 
It is a first party performance analysis tool as it is integrated as part of the hpxMP runtime system. 
Supporting construction of portable and efficient performance tools.
* **-DHPX_WITH_TRACE=**
TRUE or *FALSE*. Showing tracing information of hpxMP function calls.

# Installation Option 2: Building with Make

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

**Note:** This installation option is not maintained anymore.