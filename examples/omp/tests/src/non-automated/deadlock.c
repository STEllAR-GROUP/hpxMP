#include <omp.h>
#include <stdio.h>

omp_lock_t A, B;


void T1() {
    printf("Task 1: before locking A\n");
    omp_set_lock(&A);
    printf("Task 1: after locking A\n");
    sleep(2);
    printf("Task 1: before locking B\n");
    omp_set_lock(&B);
    printf("Task 1: after locking B\n");
    printf("Task 1\n");
    omp_unset_lock(&B);
    omp_unset_lock(&A);
}

void T2() {
    printf("Task 2: before locking B\n");
    omp_set_lock(&B);
    printf("Task 2: after locking B\n");
    printf("Task 2: before locking A\n");
    omp_set_lock(&A);
    printf("Task 2: after locking A\n");
    printf("Task 2\n");
    omp_unset_lock(&A);
    omp_unset_lock(&B);
}

int main()
{

    omp_init_lock(&A);
    omp_init_lock(&B);

#pragma omp parallel
    {
#pragma omp single
        {
#pragma omp task
            T1();
#pragma omp task
            T2();
        }
    }
}
