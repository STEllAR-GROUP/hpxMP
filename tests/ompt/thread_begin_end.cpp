#include "callback.h"

//not correctly worked for now
void print_hello(){
#pragma omp parallel num_threads(2)
    printf("hello\n");
}

int main (int argc, char *argv[]) {
    print_hello();
    printf("%d\n", count_registrations);
    printf("%d\n", count_deregistrations);
    if(count_deregistrations==count_registrations){
        return 0;
    }
    return 1;
}



