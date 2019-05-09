#hpxMP V0.2.0, what's new: 

##Initial support for OpenMP 5.0 features:

*#pragma omp taskgroup task_reduction(+:sum)

*#pragma omp task in_reduction(+:sum)

##Performance optimization
HPX Latch introduced for optimized thread and task synchronization.

BOOST instrusive_pointer introduced for improving memory management

##Bug fixes
Properly trigger shutdown of HPX
Fixes #pragma omp task depend


##Detailed introduction please refer to [readme](../README.md).

Date: 05/09/2019