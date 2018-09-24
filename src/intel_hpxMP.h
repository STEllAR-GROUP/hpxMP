#include "hpx_runtime.h"
#include <cstdarg>

extern "C" void start_backend();
typedef int kmp_int32;
typedef long long kmp_int64;

typedef mutex_type omp_lock_t;

typedef void (*microtask_t)( int *gtid, int *tid, ... );

typedef int  (*launch_t)( int gtid );

typedef void (*kmpc_micro)  ( kmp_int32 * global_tid, kmp_int32 * bound_tid, ... );

typedef kmp_int32 kmp_critical_name[8];
/*
typedef struct kmp_depend_info {
    int64_t                    base_addr;
    size_t                     len;
    struct {
        bool                   in:1;
        bool                   out:1;
    } flags;
} kmp_depend_info_t;
*/

extern "C" int __kmp_invoke_microtask( microtask_t pkfn, int gtid, int tid, int argc, void **argv );

enum sched_type {
        kmp_sch_lower                     = 32,   /**< lower bound for unordered values */
        kmp_sch_static_chunked            = 33,
        kmp_sch_static                    = 34,   /**< static unspecialized */
        kmp_sch_dynamic_chunked           = 35,
        kmp_sch_guided_chunked            = 36,   /**< guided unspecialized */
        kmp_sch_runtime                   = 37,
        kmp_sch_auto                      = 38,   /**< auto */
        kmp_sch_trapezoidal               = 39,
        /* accessible only through KMP_SCHEDULE environment variable */
        kmp_sch_static_greedy             = 40,
        kmp_sch_static_balanced           = 41,
        /* accessible only through KMP_SCHEDULE environment variable */
        kmp_sch_guided_iterative_chunked  = 42,
        kmp_sch_guided_analytical_chunked = 43,
        kmp_sch_static_steal              = 44,   /**< accessible only through KMP_SCHEDULE environment variable */
        /* accessible only through KMP_SCHEDULE environment variable */
        kmp_sch_upper                     = 45,   /**< upper bound for unordered values */
        kmp_ord_lower                     = 64,   /**< lower bound for ordered values, must be power of 2 */
        kmp_ord_static_chunked            = 65,
        kmp_ord_static                    = 66,   /**< ordered static unspecialized */
        kmp_ord_dynamic_chunked           = 67,
        kmp_ord_guided_chunked            = 68,
        kmp_ord_runtime                   = 69,
        kmp_ord_auto                      = 70,   /**< ordered auto */
        kmp_ord_trapezoidal               = 71,
        kmp_ord_upper                     = 72,   /**< upper bound for ordered values */
#if OMP_40_ENABLED
        /* Schedules for Distribute construct */
        kmp_distribute_static_chunked     = 91,   /**< distribute static chunked */
        kmp_distribute_static             = 92,   /**< distribute static unspecialized */
#endif
        kmp_nm_lower                      = 160,  /**< lower bound for nomerge values */
        kmp_nm_static_chunked             = (kmp_sch_static_chunked - kmp_sch_lower + kmp_nm_lower),
        kmp_nm_static                     = 162,  /**< static unspecialized */
        kmp_nm_dynamic_chunked            = 163,
        kmp_nm_guided_chunked             = 164,  /**< guided unspecialized */
        kmp_nm_runtime                    = 165,
        kmp_nm_auto                       = 166,  /**< auto */
        kmp_nm_trapezoidal                = 167,
        /* accessible only through KMP_SCHEDULE environment variable */
        kmp_nm_static_greedy              = 168,
        kmp_nm_static_balanced            = 169,
        /* accessible only through KMP_SCHEDULE environment variable */
        kmp_nm_guided_iterative_chunked   = 170,
        kmp_nm_guided_analytical_chunked  = 171,
        kmp_nm_static_steal               = 172,  /* accessible only through OMP_SCHEDULE environment variable */
        kmp_nm_ord_static_chunked         = 193,
        kmp_nm_ord_static                 = 194,  /**< ordered static unspecialized */
        kmp_nm_ord_dynamic_chunked        = 195,
        kmp_nm_ord_guided_chunked         = 196,
        kmp_nm_ord_runtime                = 197,
        kmp_nm_ord_auto                   = 198,  /**< auto */
        kmp_nm_ord_trapezoidal            = 199,
        kmp_nm_upper                      = 200,  /**< upper bound for nomerge values */
        kmp_sch_default = kmp_sch_static  /**< default scheduling algorithm */
};


//changed to forward decleartion because of in gcc_hpxMP, kmp_atomic.h and this header is included.
struct ident_t {
    kmp_int32 reserved_1;   /**<  m ght be used in Fortran; see above  */
    kmp_int32 flags;        /**<  also f.flags; KMP_IDENT_xxx flags; KMP_IDENT_KMPC identifies this union member  */
    kmp_int32 reserved_2;   /**<  not really used in Fortran any more; see above */
    kmp_int32 reserved_3;   /**< source[4] in Fortran, do not use for C++  */
    char const *psource;    /**< String describing the source location.*/
};

typedef struct kmp_tasking_flags {          /* Total struct must be exactly 32 bits */
    /* Compiler flags */                    /* Total compiler flags must be 16 bits */
    unsigned tiedness    : 1;               /* task is either tied (1) or untied (0) */
    unsigned final       : 1;               /* task is final(1) so execute immediately */
    unsigned merged_if0  : 1;               /* no __kmpc_task_{begin/complete}_if0 calls in if0 code path */
#if OMP_40_ENABLED
    unsigned destructors_thunk : 1;         /* set if the compiler creates a thunk to invoke destructors from the runtime */
    unsigned reserved    : 12;              /* reserved for compiler use */
#else // OMP_40_ENABLED
    unsigned reserved    : 13;              /* reserved for compiler use */
#endif // OMP_40_ENABLED
    /* Library flags */                     /* Total library flags must be 16 bits */
    unsigned tasktype    : 1;               /* task is either explicit(1) or implicit (0) */
    unsigned task_serial : 1;               /* this task is executed immediately (1) or deferred (0) */
    unsigned tasking_ser : 1;               /* all tasks in team are either executed immediately (1) or may be deferred (0) */
    unsigned team_serial : 1;               /* entire team is serial (1) [1 thread] or parallel (0) [>= 2 threads] */
                                            /* If either team_serial or tasking_ser is set, task team may be NULL */
    /* Task State Flags: */
    unsigned started     : 1;               /* 1==started, 0==not started     */
    unsigned executing   : 1;               /* 1==executing, 0==not executing */
    unsigned complete    : 1;               /* 1==complete, 0==not complete   */
    unsigned freed       : 1;               /* 1==freed, 0==allocateed        */
    unsigned native      : 1;               /* 1==gcc-compiled task, 0==intel */
    unsigned reserved31  : 7;               /* reserved for library use */
} kmp_tasking_flags_t;


typedef kmp_int32 (* kmp_routine_entry_t)( kmp_int32, void * );



//typedef struct kmp_task {                   /* GEH: Shouldn't this be aligned somehow? */
//    void *              shareds;            /**< pointer to block of pointers to shared vars   */
//    kmp_routine_entry_t routine;            /**< pointer to routine to call for executing task */
//    kmp_int32           part_id;            /**< part id for the task                          */
//#if OMP_40_ENABLED
//    kmp_routine_entry_t destructors;        /* pointer to function to invoke deconstructors of firstprivate C++ objects */
//#endif // OMP_40_ENABLED
//    //private variables are also tacked on here
//} kmp_task_t;

extern "C" kmp_task_t*
__kmpc_omp_task_alloc( ident_t *loc_ref, kmp_int32 gtid, kmp_int32 flags,
                       size_t sizeof_kmp_task_t, size_t sizeof_shareds,
                       kmp_routine_entry_t task_entry );
extern "C" int 
__kmpc_omp_task( ident_t *loc_ref, kmp_int32 gtid, kmp_task_t * new_task);
extern "C" int
__kmpc_omp_task_with_deps( ident_t *loc_ref, kmp_int32 gtid, kmp_task_t * new_task,
                           kmp_int32 ndeps, kmp_depend_info_t *dep_list,
                           kmp_int32 ndeps_noalias, kmp_depend_info_t *noalias_dep_list );
extern "C" int
__kmpc_omp_taskyield(ident_t *loc_ref, kmp_int32 gtid, int end_part );
extern "C" int
__kmpc_omp_taskwait( ident_t *loc_ref, kmp_int32 gtid );
extern "C" void 
__kmpc_omp_wait_deps( ident_t *loc_ref, kmp_int32 gtid, kmp_int32 ndeps, 
                      kmp_depend_info_t *dep_list, kmp_int32 ndeps_noalias, 
                      kmp_depend_info_t *noalias_dep_list );
extern "C" int 
__kmpc_omp_task_parts( ident_t *loc_ref, int gtid, kmp_task_t * new_task);
extern "C" void 
__kmpc_omp_task_begin_if0( ident_t *loc_ref, kmp_int32 gtid, kmp_task_t * task );
extern "C" void
__kmpc_omp_task_complete_if0( ident_t *loc_ref, kmp_int32 gtid, kmp_task_t *task );

extern "C" void
__kmpc_taskgroup( ident_t * loc, int gtid );
extern "C" void
__kmpc_end_taskgroup( ident_t * loc, int gtid );


extern "C" int  __kmpc_ok_to_fork(ident_t *loc);//used in icc
extern "C" void __kmpc_begin( ident_t *, kmp_int32 flags );//used in icc
extern "C" void __kmpc_end(ident_t *loc);//used in icc

extern "C" void __kmpc_fork_call          ( ident_t *, kmp_int32 nargs, kmpc_micro microtask, ... );
extern "C" int  __kmpc_global_thread_num(ident_t *loc);
extern "C" void __kmpc_push_num_threads ( ident_t *loc, kmp_int32 global_tid, kmp_int32 num_threads );
extern "C" int  __kmpc_cancel_barrier(ident_t* loc_ref, kmp_int32 gtid);

extern "C" void __kmpc_barrier(ident_t *loc, kmp_int32 global_tid);

extern "C" int  __kmpc_single(ident_t *loc, int tid);
extern "C" void __kmpc_end_single(ident_t *loc, int tid);

extern "C" int  __kmpc_master(ident_t *loc, int global_tid);
extern "C" void __kmpc_end_master(ident_t *loc, int global_tid);


extern "C" void __kmpc_critical( ident_t * loc, kmp_int32 global_tid, kmp_critical_name * crit );
extern "C" void __kmpc_end_critical(ident_t *loc, kmp_int32 global_tid, kmp_critical_name *crit);

extern "C" void __kmpc_flush(ident_t *loc, ...);


extern "C" void* 
__kmpc_threadprivate_cached( ident_t *loc, kmp_int32 tid, void *data, size_t size, void ***cache);

extern "C" void*
__kmpc_future_cached( ident_t * loc, kmp_int32 global_tid, void * data, size_t size, void *** cache );


extern "C" void
__kmpc_copyprivate( ident_t *loc, kmp_int32 gtid, size_t cpy_size, 
                    void *cpy_data, void(*cpy_func)(void*,void*), kmp_int32 didit);


extern "C" int 
__kmpc_reduce( ident_t *loc, kmp_int32 global_tid, kmp_int32 num_vars, size_t size,
               void *data, void (*func)(void *lhs, void *rhs), kmp_critical_name *lck );

extern "C" void
__kmpc_end_reduce( ident_t *loc, kmp_int32 global_tid, kmp_critical_name *lck );

extern "C" int
__kmpc_reduce_nowait( ident_t *loc, kmp_int32 global_tid, kmp_int32 num_vars,
                      size_t reduce_size, void *reduce_data, 
                      void (*reduce_func)(void *lhs_data, void *rhs_data),
                      kmp_critical_name *lck );
extern "C" void 
__kmpc_end_reduce_nowait( ident_t *loc, kmp_int32 global_tid, kmp_critical_name *lck );

extern "C" void __kmpc_init_lock( ident_t *loc, kmp_int32 gtid,  void **user_lock );
extern "C" void __kmpc_init_nest_lock( ident_t *loc, kmp_int32 gtid, void **user_lock );
extern "C" void __kmpc_destroy_lock( ident_t *loc, kmp_int32 gtid, void **user_lock );
extern "C" void __kmpc_destroy_nest_lock( ident_t *loc, kmp_int32 gtid, void **user_lock );
extern "C" void __kmpc_set_lock( ident_t *loc, kmp_int32 gtid, void **user_lock );
extern "C" void __kmpc_set_nest_lock( ident_t *loc, kmp_int32 gtid, void **user_lock );
extern "C" void __kmpc_unset_lock( ident_t *loc, kmp_int32 gtid, void **user_lock );
extern "C" void __kmpc_unset_nest_lock( ident_t *loc, kmp_int32 gtid, void **user_lock );
extern "C" int __kmpc_test_lock( ident_t *loc, kmp_int32 gtid, void **user_lock );
extern "C" int __kmpc_test_nest_lock( ident_t *loc, kmp_int32 gtid, void **user_lock );

extern "C" void __kmpc_serialized_parallel( ident_t *, kmp_int32 global_tid );
extern "C" void __kmpc_end_serialized_parallel ( ident_t *, kmp_int32 global_tid );



//library_calls:
extern "C" int  omp_get_thread_num();
extern "C" int  omp_get_num_threads();
extern "C" void omp_set_num_threads(int);
extern "C" int  omp_get_max_threads();
extern "C" int  omp_get_num_procs();

extern "C" double omp_get_wtime();
extern "C" double omp_get_wtick();
extern "C" int omp_in_parallel();

//ICV get and put functions:
extern "C" void omp_set_dynamic(int dynamic_threads);
extern "C" int omp_get_dynamic();


extern "C" void omp_init_lock(omp_lock_t **lock);
extern "C" void omp_init_nest_lock(omp_lock_t **lock);

extern "C" void omp_destroy_lock(omp_lock_t **lock);
extern "C" void omp_destroy_nest_lock(omp_lock_t **lock);

extern "C" void omp_set_lock(omp_lock_t **lock);
extern "C" void omp_set_nest_lock(omp_lock_t **lock);

extern "C" void omp_unset_lock(omp_lock_t **lock);
extern "C" void omp_unset_nest_lock(omp_lock_t **lock);

extern "C" int omp_test_lock(omp_lock_t **lock);
extern "C" int omp_test_nest_lock(omp_lock_t **lock);

