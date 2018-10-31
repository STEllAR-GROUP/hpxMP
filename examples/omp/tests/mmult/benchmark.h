/*
 * Rectangular matrix multiplication, started from MIT Cilk matmul.cilk example
 *
 */

#include "mm_funcs.h"
#include "strass.h"

#define REAL double

struct entry
{
    char *name;
    void (*matrix_mult)(REAL*, REAL*, REAL*, int m, int n, int p, int block);
};
    
struct bench
{
    struct entry handle;
    REAL *data;
    double time;
    int collect_papi;
};
#ifdef USING_PAPI
struct papi_data
{
    int num_events;
    int event_set;
    int native_event_set;
    PAPI_event_info_t *native_info;
};
#else
struct papi_data
{
	int num_events;
};
#endif

void init_arrays(REAL *A, REAL *B, struct bench **entries, int n, int length);
void run(struct bench **entries, REAL *A, REAL *B, int n, int length, struct papi_data info);
void print_results(struct bench **entries, REAL *standard, int n, int num_threads, int length);
void free_data(struct bench **entries, REAL *A, REAL *B, int length);

