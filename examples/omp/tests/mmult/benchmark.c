/*
 * Rectangular matrix multiplication, started from MIT Cilk matmul.cilk example
 */

#include "benchmark.h"

#define REAL double

long long int cache[48][4];
int global_eventSet[1];

int main(int argc, char *argv[])
{
    int i, n, length, num_threads;
    REAL *A, *B, *C_seq;
    struct papi_data info;
    struct bench **bench_list;
    struct entry entries[] = {
/*
                        {"Sequential", iter_matmul},
                        {"Seq Tiling", sequential_tiling}, 
                        {"Rec Tile", matmul_recursive_tile_caller}, 
*/
                        {"OMP For", omp_matmul}, 
                        {"OMP Task", matmul_omp_task_caller}, 
//                        {"OMP Dtile", omp_dtile}, 
//                        {"OMP DRTile", omp_tile_rec},
                        {"Hybrid Tiling", omp_tile_rec},
                        {"Strassen", matmul_matmul_caller},
//                        {"MKL", mkl_call}
    };

    info.num_events = 0;
    if (argc != 2) {
        fprintf(stderr, "Usage: matmul <n>\n");
        exit(1);
    }
    n = atoi(argv[1]);

    length = sizeof(entries) / sizeof(struct entry);
    bench_list =  calloc(length, sizeof(struct bench*));
    for(i = 0; i < length; i++)
    {
        bench_list[i] = calloc(1, sizeof(struct bench));
        bench_list[i]->handle = entries[i];
    }
#ifdef USING_PAPI
#ifndef NO_NATIVE
    info.native_event_set = PAPI_NULL;
#endif
    info.event_set = PAPI_NULL; 
    unsigned int testEvents[] = {PAPI_L2_TCA, PAPI_L2_TCM, PAPI_L3_TCA, PAPI_L3_TCM};
    info.num_events = 4;
    info.native_info = (PAPI_event_info_t*) startPAPI(&info.event_set, &info.native_event_set, testEvents, info.num_events);
    global_eventSet[0] = info.event_set;
#endif
    srand48(1<<12);

    A = calloc(n * n, sizeof(REAL));
    B = calloc(n * n, sizeof(REAL));
    init_arrays(A, B, bench_list, n, length);
    C_seq = bench_list[0]->data;

    run(bench_list, A, B, n, length, info);
    return 0;
}

void init_arrays(REAL *A, REAL *B, struct bench **list, int n, int length)
{
    int i;
    init(A,n);
    init(B,n);

    for( i = 0; i < length; i++)
    {
        //printf("%s\n",list[i]->handle.name);
        list[i]->data = calloc(n * n, sizeof(REAL));
    }
}
/*
void run(struct bench **list, REAL *A, REAL *B, int n, int length, struct papi_data info)
{
    int i, num_native=0, num_threads = omp_get_max_threads();
    double nnn = 2.0 * n * n *n;
    char header[512];

    printf("========================================================================|\n");
    sprintf(header,"\t\tmatmul(%dx%d) example on %d threads(cores)", n, n, num_threads);
    printf("%-58s|",header);
    printf("Performance:  Runtime(s)        Error");

    for(i = 0; i < length; i++)
    {
        printf("%-11s:  ", list[i]->handle.name);
        get_pwr();
        list[i]->time = omp_get_wtime();

        list[i]->handle.matrix_mult(A,B, list[i]->data, n, n, n, 32);

        list[i]->time = omp_get_wtime() - list[i]->time;

        printf("%-12f %-13g\n", list[i]->time, maxerror(list[0]->data, list[i]->data, n));
        get_pwr();
    }
}
*/
void run(struct bench **list, REAL *A, REAL *B, int n, int length, struct papi_data info)
{
    int i, num_native=0, num_threads = omp_get_max_threads();
    double nnn = 2.0 * n * n *n;
    char header[512];
//    long long int cache_data[48,4];

#ifdef USING_PAPI
    long long int *nativeE, *events;
#ifndef NO_NATIVE
    for(i = 0;i < 3; i++)
        if( info.native_info[i].event_code > 0)
        {
            //printf("%s\n",info.native_info[i].symbol);
            num_native++;
        }
    nativeE = calloc(num_native, sizeof(long long int));
#endif
    events = calloc(info.num_events, sizeof(long long int));
    long long int *init_power = calloc(num_native, sizeof(long long int));
    double unit_joules = 1;//.0000152588;
#endif

    printf("========================================================================|\n");
    sprintf(header,"\t\tmatmul(%dx%d) example on %d threads(cores)", n, n, num_threads);
    printf("%-58s|",header);
    if(info.num_events > 0) printf("%22s","Power (uJ)");
    printf("\n------------------------------------------------------------------------|\n");
    printf("Performance:  Runtime (s)  MFLOPS        Error");
#ifdef USING_PAPI
    printf("        L2 Hit    L3 Hit  | Package      DRAM");
    if(num_native > 2)
        printf("        single core");
#endif
    printf("\n------------------------------------------------------------------------|\n");

    for(i = 0; i < length; i++)
    {
#ifdef USING_PAPI
        PAPI_read(info.native_event_set, init_power);
        PAPI_read(info.event_set, events);
        PAPI_reset(info.event_set);
#endif
        printf("%-11s:  ", list[i]->handle.name);
        list[i]->time = omp_get_wtime();

        list[i]->handle.matrix_mult(A,B, list[i]->data, n, n, n, 32);

        list[i]->time = omp_get_wtime() - list[i]->time;
#ifdef USING_PAPI
#ifndef NO_NATIVE
        PAPI_read(info.native_event_set, nativeE);
#endif
        PAPI_read(info.event_set, events);

#endif

        printf("%-12f %-14f%-13g", list[i]->time, nnn/(1.0e6*(list[i]->time)), maxerror(list[0]->data, list[i]->data, n));
#ifdef USING_PAPI
        printf("%-8g %-8g ", 100 * (double)(events[0] - events[1]) /((double) events[0]), 
                                          100 * (double)(events[2] - events[3]) /((double) events[2]));
#ifndef NO_NATIVE
        printf("| %-12g %-12g",(double)(nativeE[0] - init_power[0]) * unit_joules / 1000,
                               (double)(nativeE[1] - init_power[1]) * unit_joules / 1000);
        if(num_native > 2)
            printf("%-12g", (double)(nativeE[3] - init_power[3]) * unit_joules/ 1000);
#endif
#endif
        printf("\n");
    }
}

void free_data(struct bench **list, REAL *A, REAL *B, int length)
{

    int i;
    for( i = 0; i < length; i++)
        free(list[i]->data);
    free(B);
    free(A);
}
