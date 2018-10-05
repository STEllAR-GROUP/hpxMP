#include <stdio.h>
//without taskwait will print A is fun to watch race car
//with taskwait will print A race car is fun to watch
int main(int argc, char *argv[]) {
#pragma omp parallel
{
#pragma omp single
    {
        printf("A ");
        #pragma omp task
            {printf("race ");}
        #pragma omp task
            {printf("car ");}
        #pragma omp taskwait

        printf("is fun to watch ");
    }
} // End of parallel region

    printf("\n");
    return(0);
}
