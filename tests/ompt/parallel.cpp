#include "callback.h"

const int requested_team_size = 2;

int main (int argc, char *argv[]) {

#pragma omp parallel num_threads(requested_team_size)
    printf("hello\n");

#pragma omp parallel num_threads(requested_team_size)
    printf("hello\n");

    //test begins here
    //num of parallel begin = num of parallel end = 1
    if(count_parallel_begin!=2 || count_parallel_end !=2){
        return 1;
    }
    //check registered parallel id will be unregistered
    for(auto it = count_parallel_id.begin(); it != count_parallel_id.end();++it){
        if(it->second != 0) return 1;
    }
    //check team size are correct
    for(auto it = team_size.begin(); it != team_size.end();++it){
        if(it->second != 2 ) return 1;
    }

    if(do_generic_test()) return 1;

    fprintf(stderr,"Passes!\n"); fflush(stderr);
    printf("pass\n");
    return 0;
}



