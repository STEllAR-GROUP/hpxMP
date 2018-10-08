//  Copyright (c) 2018 Tianyi Zhang
//  Adapted from kempj omp-single-nowait.c
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <stdio.h>
#include <omp.h>

int parTreeSearch(int depth, int numChildren) 
{
    if(depth > 5) {
        return depth;
    }
    return parTreeSearch(depth+1, numChildren);
}

/*
   Node n[numChildren], *nodePtr;
   int i, j;
   counter_t subtreesize = 1, partialCount[numChildren];

// Recurse on the children
for (i = 0; i < numChildren; i++) {
nodePtr = &n[i];

nodePtr->height = parent->height + 1;

// The following line is the work (one or more SHA-1 ops)
for (j = 0; j < computeGranularity; j++) {
rng_spawn(parent->state.state, nodePtr->state.state, i);
}

nodePtr->numChildren = uts_numChildren(nodePtr);

#pragma omp task firstprivate(i, nodePtr) shared(partialCount) untied if (depth < bots_cutoff_value)
partialCount[i] = parTreeSearch(depth+1, nodePtr, nodePtr->numChildren);
}

#pragma omp taskwait

for (i = 0; i < numChildren; i++) {
subtreesize += partialCount[i];
}
return subtreesize;
}
*/


int main() {
    int num_nodes;

#pragma omp parallel  
#pragma omp single nowait
#pragma omp task untied
    num_nodes = parTreeSearch( 0, 42 );

    printf("num nodes = %d\n", num_nodes);
    if(num_nodes != 6)
        return 1;

    return 0;
}
