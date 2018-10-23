/*
 * Rectangular matrix multiplication, started from MIT Cilk matmul.cilk example
 *
 */

#include "benchmark.h"
//#include "mkl.h"
#include "mkl_types.h"
#include "mkl_cblas.h"


void zero(REAL *A, int n)
{
    int i, j;
//#pragma omp for private (i, j)
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            A[i * n + j] = 0.0;
        }
    }
}

void init(REAL *A, int n)
{
    int i, j;

//#pragma omp for private (i, j)
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            A[i * n + j] = (double)drand48();
        }
    }
}

double maxerror(REAL *A, REAL *B, int n)
{
    int i, j;
    double error = 0.0;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            double diff = (A[i * n + j] - B[i * n + j]) / A[i * n + j];
            if (diff < 0)
                diff = -diff;
            if (diff > error)
                error = diff;
        }
    }
    return error;
}

#ifdef USING_PAPI
inline papi_wrap(int error, char name[])
{
    if(error != PAPI_OK)
    {
        printf("Error: %s\n", name);
        printf("       %s\n", PAPI_strerror(error));
        exit(1);
    }
}

inline papi_threaded_setup()
{
    int ii;
    int num_threads = omp_get_num_threads();
    int thread_id = omp_get_thread_num();
    PAPI_register_thread();
    extern int global_eventSet[1];
    extern long long int cache[48][4];
//    thread_bind(thread_id);

    for(ii = 0; ii < 4; ii++)
        cache[thread_id][ii] = 0;
    PAPI_reset(global_eventSet[0]);
    return thread_id; 
}

inline papi_threaded_teardown(int id)
{
    PAPI_read(global_eventSet[0], &cache[id][0]);
    PAPI_unregister_thread();
    printf("%-4d %-16lld %-16lld %-16lld %-16lld\n", id, 
                               cache[id][0] , cache[id][1],
                               cache[id][2] , cache[id][3]);

//    PAPI_read(global_eventSet[0], cache[thread_id]);
//    PAPI_unregister_thread();
//    printf("%-4d %-6d %-6d\n", thread_id,
//                               100 * (int)( ( cache[thread_id][0] - cache[thread_id][1]) / cache[thread_id][0]),
//                               100 * (int)( ( cache[thread_id][2] - cache[thread_id][3]) / cache[thread_id][2]));
//
}
#endif

void mkl_call(REAL *A, REAL *B, REAL *C, int m, int n, int p, int bw)
{
    double alpha = 1, beta = 1;
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasTrans, m, n, p, alpha, A, p, B, n, beta, C, n);
}
void iter_matmul(REAL *A, REAL *B, REAL *C, int m, int n, int p, int bw)
{
    int i, j, k;

    for (i = 0; i < n; i++)
        for (k = 0; k < n; k++) {
            REAL c = 0.0;
            for (j = 0; j < n; j++)
                c += A[i * n + j] * B[k * n + j];
            C[i * n + k] = c;
        }
}


void omp_matmul(REAL *A, REAL *B, REAL *C, int m, int n, int p, int bw)
{
#pragma omp parallel shared(A, B, C, n)
    {
        int i, j, k;
#pragma omp for private(i,j,k)
        for (i = 0; i < n; i++)
        {
            for (k = 0; k < n; k++) {
                REAL c = 0.0;
                for (j = 0; j < n; j++)
                    c += A[i * n + j] * B[k * n + j];
                C[i * n + k] = c;
            }
        }
    }
}

/*
 * A \in M(m, n)
 * B \in M(n, p)
 * C \in M(m, p)
 */
void matmul_omp_task(REAL *A, REAL *B, REAL *C, int m, int n, int p, int ld, int add)
{
    if ((m + n + p) <= 64) {
        int i, j, k;
        /* base case */
        if (add) {
            for (i = 0; i < m; i++)
                for (k = 0; k < p; k++) {
                    REAL c = 0.0;
                    for (j = 0; j < n; j++)
                        c += A[i * ld + j] * B[k * ld + j];
                    C[i * ld + k] += c;
                }
        } else {
            for (i = 0; i < m; i++)
                for (k = 0; k < p; k++) {
                    REAL c = 0.0;
                    for (j = 0; j < n; j++)
                        c += A[i * ld + j] * B[k * ld + j];
                    C[i * ld + k] = c;
                }
        }
    } else if (m >= n && n >= p) {
        int m1 = m >> 1;
#pragma omp task
        matmul_omp_task(A, B, C, m1, n, p, ld, add);
#pragma omp task
        matmul_omp_task(A + m1 * ld, B, C + m1 * ld, m - m1,
                n, p, ld, add);
    } else if (n >= m && n >= p) {
        int n1 = n >> 1;
#pragma omp task
        matmul_omp_task(A, B, C, m, n1, p, ld, add);
#pragma omp taskwait
#pragma omp task
        matmul_omp_task(A + n1, B + n1 , C, m, n - n1, p, ld, 1);
    } else {
        int p1 = p >> 1;
#pragma omp task
        matmul_omp_task(A, B, C, m, n, p1, ld, add);
#pragma omp task
        matmul_omp_task(A, B + p1 * ld, C + p1, m, n, p - p1, ld, add);
    }
#pragma omp taskwait
}

void matmul_omp_task_caller(REAL *A, REAL *B, REAL *C, int m, int n, int p, int bw)
{
#pragma omp parallel shared(A, B, C, n)
    {
#pragma omp single
        {
            matmul_omp_task(A, B, C, n, n, n, n, 0);
        }
    }
}

void matmul_recursive_tile(REAL *A, REAL *B, REAL *C, int m, int n, int p, int ld, 
        int add)
{
    if ((m + n + p) <= 64) {
        int i, j, k;
        /* base case */
        if (add) {
            for (i = 0; i < m; i++)
                for (k = 0; k < p; k++) {
                    REAL c = 0.0;
                    for (j = 0; j < n; j++)
                        c += A[i * ld + j] * B[k * ld + j]; 
                    C[i * ld + k] += c;
                }   
        } else {
            for (i = 0; i < m; i++)
                for (k = 0; k < p; k++) {
                    REAL c = 0.0;
                    for (j = 0; j < n; j++)
                        c += A[i * ld + j] * B[k * ld + j]; 
                    C[i * ld + k] = c;
                }   
        }   
    } else if (m >= n && n >= p) {
        int m1 = m >> 1;
        matmul_recursive_tile(A, B, C, m1, n, p, ld, add);
        matmul_recursive_tile(A + m1 * ld, B, C + m1 * ld, m - m1, 
                n, p, ld, add);
    } else if (n >= m && n >= p) {
        int n1 = n >> 1;
        matmul_recursive_tile(A, B, C, m, n1, p, ld, add);
        matmul_recursive_tile(A + n1, B + n1 , C, m, n - n1, p, ld, 1); 
    } else {
        int p1 = p >> 1;
        matmul_recursive_tile(A, B, C, m, n, p1, ld, add);
        matmul_recursive_tile(A, B + p1 * ld, C + p1, m, n, p - p1, ld, add);
    }   
}

void matmul_recursive_tile_caller(REAL *A, REAL *B, REAL *C, int m, int n, int p, int ld)
{
    matmul_recursive_tile(A,B,C, m, n, p, n, 0);
}

/*
Input: A(m,n), B(n, p), the matrix array. 
bwidth, the small block size(height=width).
output: C(m,p)
Main function: multiplication for small blocks
*/
void sequential_tiling_smallblockMul(REAL *A, REAL *B, REAL *C, int m, int n, int p, int bwidth)
{
    int i, j, k;
    //small block multiplication
    for (i = 0; i < bwidth; i++ ) 
        for (j = 0; j < bwidth; j++) 
            for (k = 0; k < bwidth; k ++) 
                *(C + i * p + j) = *(C + i * p + j) + (*(A + i * n + k)) * (*(B + j * n + k));
}


/*
Input: A(m,n), B(n, p), the matrix array. 
bwidth, the small block size(height=width).
output: C(m,p)
Main Function: split the huge matrix into small blocks.
*/
void sequential_tiling(REAL *A, REAL *B, REAL *C, int m, int n, int p, int bwidth)
{
    int i, j, k;
    for (i = 0; i < m; i += bwidth) 
    {
        for (j = 0; j < p; j += bwidth) 
        {
            for (k = 0; k < n; k += bwidth) 
            {
                //Get the current block start addr
                REAL* pStartA = A + i * n + k;
                REAL* pStartB = B + j * n + k;
                REAL* pStartC = C + i * p + j;
                sequential_tiling_smallblockMul(pStartA, pStartB, pStartC, m, n, p, bwidth);          
            }
        }
    }
}


void omp_dtile(REAL *A, REAL *B, REAL *C, int m, int n, int p, int bwidth)
{
#pragma omp parallel shared(A, B, C, n)
    {
        int num_shcache = 1;//8; /* 8 for crill, and 4 for Hopper (Cray XE6) */
        int num_cores_per_shcache = 6;
        int num_cores = num_shcache * num_cores_per_shcache;

        int global_id = omp_get_thread_num();
        int num_threads = omp_get_num_threads();
        //thread_bind(global_id); 
        int master_id = global_id / num_shcache;
        int local_id = global_id % num_shcache;

        int M_sub_size = n/num_threads;
        int M_remain = n % num_threads;

        /*
         * A is row-based evenly decomposed
         * if not evenly distributed, some core gets one more starting from 0 */
        int M_start = global_id * M_sub_size;
        if (global_id < M_remain) {
            M_start += global_id;
            M_sub_size ++;
        } else M_start += M_remain;

        /* the real work */
        int i, j, k;
        long long int cache[4] = {0,0,0,0};
        long long int first[4] = {0,0,0,0};
        //PAPI_register_thread();
        for (i=0; i<M_sub_size; i++)
            for (k=0; k<n; k++) {
                //REAL tmp = 0.0;
                int ii = M_start + i;
                REAL tmp = A[ii * n] * B[k*n];
                // PAPI_accum(EventSet,first);
                for (j=1; j<n; j++)
                    tmp += A[ii * n + j] * B[k*n + j];
                C[ii*n+k] = tmp;
            }
        //PAPI_accum(EventSet, cache);
        //printf("RT:thread %d, cache: %lld (%lld miss), L3: %lld (%lld miss)\n",global_id, cache[0],cache[1],cache[2],cache[3]);
    }
}

void omp_tile_rec(REAL *A, REAL *B, REAL *C, int m, int n, int p, int bwidth)
{
#pragma omp parallel shared(A, B, C, n)
    {   
        //long long int cache[4] = {0,0,0,0};
        //long long int first[4] = {0,0,0,0};
        //PAPI_register_thread();
        int num_shcache = 4; /* 8 for crill, and 4 for Hopper (Cray XE6) */
        int num_cores_per_shcache = 6;
        int num_cores = num_shcache * num_cores_per_shcache;

        int global_id = omp_get_thread_num();
        int num_threads = omp_get_num_threads();
        //thread_bind(global_id); 
        int master_id = global_id / num_shcache;
        int local_id = global_id % num_shcache;

        int M_sub_size = n/num_threads;
        int M_remain = n % num_threads;

        /*  
         * A is row-based evenly decomposed
         * if not evenly distributed, some core gets one more starting from 0 */
        int M_start = global_id * M_sub_size;
        if (global_id < M_remain) {
            M_start += global_id;
            M_sub_size ++; 
        } else M_start += M_remain;
        //PAPI_accum(EventSet, cache);

        matmul_recursive_tile(A+M_start*n, B, C+M_start*n, M_sub_size, n, n, n, 0); 
        //PAPI_accum(EventSet, cache);
        //printf("DRT:thread %d, cache: %lld (%lld miss), L3: %lld (%lld miss)\n",global_id, cache[0],cache[1],cache[2],cache[3]);
        //printf("thread %d to work:\tA_sub row based (start:size): %d:%d\n", global_id, M_start, M_sub_size);
    }   
}

#ifdef USING_PAPI
#ifndef NO_NATIVE
PAPI_event_info_t* getEnergyEventInfo()
{

	int numcmp = PAPI_num_components();
	int retval, i,cid, j = 0,enum_modifier;
	const PAPI_component_info_t *component;
	PAPI_event_info_t info;
	PAPI_event_info_t *desiredInfo;
	desiredInfo = (PAPI_event_info_t *) calloc(3, sizeof(PAPI_event_info_t));
	unsigned int native = 0x0;

	for( cid = 0; cid < numcmp; cid++)
	{
		i = 0 | PAPI_NATIVE_MASK;
		component=PAPI_get_component_info(cid);
		if (component->disabled) continue;
		native = PAPI_NATIVE_MASK | i;
		retval=PAPI_enum_cmp_event( &i, PAPI_ENUM_FIRST, cid );
		do
		{
			memset( &info, 0, sizeof ( info ) );
			retval = PAPI_get_event_info( i, &info );
			if ( retval != PAPI_OK ) 
				continue;
			if( strcmp(info.symbol, "rapl:::PACKAGE_ENERGY:PACKAGE0") == 0 )
			{
				desiredInfo[0] = info;
				//printf("%d,%d - %s\n", cid, i, info.symbol);
				//printf("%d,%d - %s\n", cid, i, desiredInfo[0].symbol);
			}

			if( retval = strcmp(info.symbol, "rapl:::DRAM_ENERGY:PACKAGE0") == 0 )
			{
				desiredInfo[1] = info;
				//printf("%d,%d - %s\n", cid, i, info.symbol);
				//printf("%d,%d - %s\n", cid, i, desiredInfo[1].symbol);
			}

			if( strcmp(info.symbol, "rapl:::PP0_ENERGY:PACKAGE0") == 0)
			{
				desiredInfo[2] = info;
				//printf("%d,%d - %s\n", cid, i, info.symbol);
				//printf("%d,%d - %s\n", cid, i, desiredInfo[2].symbol);
			}

		} while (PAPI_enum_cmp_event( &i, enum_modifier, cid ) == PAPI_OK );
	}
	return desiredInfo;
}
#endif

PAPI_event_info_t* startPAPI(int *eventSet, int *nativeEventSet, unsigned int testEvents[], int numE)
{
	int retVal = 0;
	int i;
	int ret;
	PAPI_event_info_t *infoEnergy;

	papi_wrap((ret = PAPI_library_init( PAPI_VER_CURRENT) < 0) ? ret : 
            (ret == PAPI_VER_CURRENT ? PAPI_OK : ret),
            "PAPI library version mismatch");

        papi_wrap( PAPI_thread_init( (unsigned long (*)(void)) omp_get_thread_num),
            "PAPI thread initialization error");

	papi_wrap( PAPI_create_eventset(eventSet),
            "Error creating eventset");
#ifndef NO_NATIVE
	papi_wrap( PAPI_create_eventset(nativeEventSet),
		    "Error creating the native eventset");

	infoEnergy = getEnergyEventInfo();

	for(i=0;i<3;i++) 
        if(infoEnergy[i].event_code > 0)
    		papi_wrap( PAPI_add_event(*nativeEventSet, infoEnergy[i].event_code),
	    	    "PAPI error adding native event");

	papi_wrap(PAPI_start(*nativeEventSet),
            "Error starting the Native events");
#endif
	for(i=0; i < numE; i++)
		papi_wrap( PAPI_add_event(*eventSet, testEvents[i]),
			"PAPI error adding preset event");
	papi_wrap(PAPI_start(*eventSet),
            "Error starting the event set");

    return infoEnergy;
}
#endif

/*
   void start_papi(int *event_set, int *native_event_set, unsigned int test_events[], unsigned int native_events[])
   {
   int retval = PAPI_library_init(PAPI_VER_CURRENT);
   if (retval != PAPI_VER_CURRENT && retval > 0)
   handle_papi_error("PAPI library version mismatch!\n");
   if (retval < 0)
   handle_papi_error("PAPI library version init failure.\n");
   if (PAPI_thread_init((long unsigned int (*)(void))omp_get_thread_num) != PAPI_OK)
   handle_papi_error("PAPI thread init.\n");


   if (PAPI_create_eventset(event_set) != PAPI_OK)
   handle_papi_error("error creating eventset\n");

   if (PAPI_add_event(*event_set, PAPI_L2_TCA) != PAPI_OK)
   handle_papi_error("error adding event 1\n");
   if (PAPI_add_event(*event_set, PAPI_L2_TCM) != PAPI_OK)
   handle_papi_error("error adding event 2\n");
   if (PAPI_add_event(*event_set, PAPI_L3_TCA) != PAPI_OK)
   handle_papi_error("error adding event 3\n");
   if (PAPI_add_event(*event_set, PAPI_L3_TCM) != PAPI_OK)
   handle_papi_error("error adding event 4\n");
   if (PAPI_start(*event_set) != PAPI_OK)
   handle_papi_error("error starting eventset\n");

   if (PAPI_create_eventset(native_event_set) != PAPI_OK)
   handle_papi_error("error creating eventset\n");


   if( PAPI_event_name_to_code("rapl:::PACKAGE_ENERGY:PACKAGE0", &package_energy) != PAPI_OK);
   handle_papi_error("error translating event 5\n");
   if( PAPI_event_name_to_code("rapl:::PP0_ENERGY:PACKAGE0", &pp0_energy) != PAPI_OK);
   handle_papi_error("error translating event 6\n");
   if( PAPI_event_name_to_code("rapl:::DRAM_ENERGY:PACKAGE0", &dram_energy) != PAPI_OK);
   handle_papi_error("error translating event 7\n");

   if (PAPI_add_event(nativeEvents, package_energy) != PAPI_OK)
   handle_papi_error("error adding event 5\n");
   if (PAPI_add_event(nativeEvents, pp0_energy) != PAPI_OK)
   handle_papi_error("error adding event 6\n");
   if (PAPI_add_event(nativeEvents, dram_energy) != PAPI_OK)
   handle_papi_error("error adding event 7\n");
   if (PAPI_start(nativeEvents) != PAPI_OK)
   handle_papi_error("error starting native eventset\n");
   }*/
