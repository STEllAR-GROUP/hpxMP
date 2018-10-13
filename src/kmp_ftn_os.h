/*
 * kmp_ftn_os.h -- KPTS Fortran defines header file.
 */


//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.txt for details.
//
//===----------------------------------------------------------------------===//


#ifndef KMP_FTN_OS_H
#define KMP_FTN_OS_H

/* ------------------------------------------------------------------ */
/* -------------------------- GOMP API NAMES ------------------------ */
// All GOMP_1.0 symbols
#define KMP_API_NAME_GOMP_ATOMIC_END                   GOMP_atomic_end
#define KMP_API_NAME_GOMP_ATOMIC_START                 GOMP_atomic_start
#define KMP_API_NAME_GOMP_BARRIER                      GOMP_barrier
#define KMP_API_NAME_GOMP_CRITICAL_END                 GOMP_critical_end
#define KMP_API_NAME_GOMP_CRITICAL_NAME_END            GOMP_critical_name_end
#define KMP_API_NAME_GOMP_CRITICAL_NAME_START          GOMP_critical_name_start
#define KMP_API_NAME_GOMP_CRITICAL_START               GOMP_critical_start
#define KMP_API_NAME_GOMP_LOOP_DYNAMIC_NEXT            GOMP_loop_dynamic_next
#define KMP_API_NAME_GOMP_LOOP_DYNAMIC_START           GOMP_loop_dynamic_start
#define KMP_API_NAME_GOMP_LOOP_END                     GOMP_loop_end
#define KMP_API_NAME_GOMP_LOOP_END_NOWAIT              GOMP_loop_end_nowait
#define KMP_API_NAME_GOMP_LOOP_GUIDED_NEXT             GOMP_loop_guided_next
#define KMP_API_NAME_GOMP_LOOP_GUIDED_START            GOMP_loop_guided_start
#define KMP_API_NAME_GOMP_LOOP_ORDERED_DYNAMIC_NEXT    GOMP_loop_ordered_dynamic_next
#define KMP_API_NAME_GOMP_LOOP_ORDERED_DYNAMIC_START   GOMP_loop_ordered_dynamic_start
#define KMP_API_NAME_GOMP_LOOP_ORDERED_GUIDED_NEXT     GOMP_loop_ordered_guided_next
#define KMP_API_NAME_GOMP_LOOP_ORDERED_GUIDED_START    GOMP_loop_ordered_guided_start
#define KMP_API_NAME_GOMP_LOOP_ORDERED_RUNTIME_NEXT    GOMP_loop_ordered_runtime_next
#define KMP_API_NAME_GOMP_LOOP_ORDERED_RUNTIME_START   GOMP_loop_ordered_runtime_start
#define KMP_API_NAME_GOMP_LOOP_ORDERED_STATIC_NEXT     GOMP_loop_ordered_static_next
#define KMP_API_NAME_GOMP_LOOP_ORDERED_STATIC_START    GOMP_loop_ordered_static_start
#define KMP_API_NAME_GOMP_LOOP_RUNTIME_NEXT            GOMP_loop_runtime_next
#define KMP_API_NAME_GOMP_LOOP_RUNTIME_START           GOMP_loop_runtime_start
#define KMP_API_NAME_GOMP_LOOP_STATIC_NEXT             GOMP_loop_static_next
#define KMP_API_NAME_GOMP_LOOP_STATIC_START            GOMP_loop_static_start
#define KMP_API_NAME_GOMP_ORDERED_END                  GOMP_ordered_end
#define KMP_API_NAME_GOMP_ORDERED_START                GOMP_ordered_start
#define KMP_API_NAME_GOMP_PARALLEL_END                 GOMP_parallel_end
#define KMP_API_NAME_GOMP_PARALLEL_LOOP_DYNAMIC_START  GOMP_parallel_loop_dynamic_start
#define KMP_API_NAME_GOMP_PARALLEL_LOOP_GUIDED_START   GOMP_parallel_loop_guided_start
#define KMP_API_NAME_GOMP_PARALLEL_LOOP_RUNTIME_START  GOMP_parallel_loop_runtime_start
#define KMP_API_NAME_GOMP_PARALLEL_LOOP_STATIC_START   GOMP_parallel_loop_static_start
#define KMP_API_NAME_GOMP_PARALLEL_SECTIONS_START      GOMP_parallel_sections_start
#define KMP_API_NAME_GOMP_PARALLEL_START               GOMP_parallel_start
#define KMP_API_NAME_GOMP_SECTIONS_END                 GOMP_sections_end
#define KMP_API_NAME_GOMP_SECTIONS_END_NOWAIT          GOMP_sections_end_nowait
#define KMP_API_NAME_GOMP_SECTIONS_NEXT                GOMP_sections_next
#define KMP_API_NAME_GOMP_SECTIONS_START               GOMP_sections_start
#define KMP_API_NAME_GOMP_SINGLE_COPY_END              GOMP_single_copy_end
#define KMP_API_NAME_GOMP_SINGLE_COPY_START            GOMP_single_copy_start
#define KMP_API_NAME_GOMP_SINGLE_START                 GOMP_single_start

// All GOMP_2.0 symbols
#define KMP_API_NAME_GOMP_TASK                           GOMP_task
#define KMP_API_NAME_GOMP_TASKWAIT                       GOMP_taskwait
#define KMP_API_NAME_GOMP_LOOP_ULL_DYNAMIC_NEXT          GOMP_loop_ull_dynamic_next
#define KMP_API_NAME_GOMP_LOOP_ULL_DYNAMIC_START         GOMP_loop_ull_dynamic_start
#define KMP_API_NAME_GOMP_LOOP_ULL_GUIDED_NEXT           GOMP_loop_ull_guided_next
#define KMP_API_NAME_GOMP_LOOP_ULL_GUIDED_START          GOMP_loop_ull_guided_start
#define KMP_API_NAME_GOMP_LOOP_ULL_ORDERED_DYNAMIC_NEXT  GOMP_loop_ull_ordered_dynamic_next
#define KMP_API_NAME_GOMP_LOOP_ULL_ORDERED_DYNAMIC_START GOMP_loop_ull_ordered_dynamic_start
#define KMP_API_NAME_GOMP_LOOP_ULL_ORDERED_GUIDED_NEXT   GOMP_loop_ull_ordered_guided_next
#define KMP_API_NAME_GOMP_LOOP_ULL_ORDERED_GUIDED_START  GOMP_loop_ull_ordered_guided_start
#define KMP_API_NAME_GOMP_LOOP_ULL_ORDERED_RUNTIME_NEXT  GOMP_loop_ull_ordered_runtime_next
#define KMP_API_NAME_GOMP_LOOP_ULL_ORDERED_RUNTIME_START GOMP_loop_ull_ordered_runtime_start
#define KMP_API_NAME_GOMP_LOOP_ULL_ORDERED_STATIC_NEXT   GOMP_loop_ull_ordered_static_next
#define KMP_API_NAME_GOMP_LOOP_ULL_ORDERED_STATIC_START  GOMP_loop_ull_ordered_static_start
#define KMP_API_NAME_GOMP_LOOP_ULL_RUNTIME_NEXT          GOMP_loop_ull_runtime_next
#define KMP_API_NAME_GOMP_LOOP_ULL_RUNTIME_START         GOMP_loop_ull_runtime_start
#define KMP_API_NAME_GOMP_LOOP_ULL_STATIC_NEXT           GOMP_loop_ull_static_next
#define KMP_API_NAME_GOMP_LOOP_ULL_STATIC_START          GOMP_loop_ull_static_start

// All GOMP_3.0 symbols
#define KMP_API_NAME_GOMP_TASKYIELD                      GOMP_taskyield

// All GOMP_4.0 symbols
// TODO: As of 2013-10-14, none of the GOMP_4.0 functions are implemented in libomp
#define KMP_API_NAME_GOMP_BARRIER_CANCEL                 GOMP_barrier_cancel
#define KMP_API_NAME_GOMP_CANCEL                         GOMP_cancel
#define KMP_API_NAME_GOMP_CANCELLATION_POINT             GOMP_cancellation_point
#define KMP_API_NAME_GOMP_LOOP_END_CANCEL                GOMP_loop_end_cancel
#define KMP_API_NAME_GOMP_PARALLEL_LOOP_DYNAMIC          GOMP_parallel_loop_dynamic
#define KMP_API_NAME_GOMP_PARALLEL_LOOP_GUIDED           GOMP_parallel_loop_guided
#define KMP_API_NAME_GOMP_PARALLEL_LOOP_RUNTIME          GOMP_parallel_loop_runtime
#define KMP_API_NAME_GOMP_PARALLEL_LOOP_STATIC           GOMP_parallel_loop_static
#define KMP_API_NAME_GOMP_PARALLEL_SECTIONS              GOMP_parallel_sections
#define KMP_API_NAME_GOMP_PARALLEL                       GOMP_parallel
#define KMP_API_NAME_GOMP_SECTIONS_END_CANCEL            GOMP_sections_end_cancel
#define KMP_API_NAME_GOMP_TASKGROUP_START                GOMP_taskgroup_start
#define KMP_API_NAME_GOMP_TASKGROUP_END                  GOMP_taskgroup_end
/* Target functions should be taken care of by liboffload */
#define KMP_API_NAME_GOMP_TARGET                         GOMP_target
#define KMP_API_NAME_GOMP_TARGET_DATA                    GOMP_target_data
#define KMP_API_NAME_GOMP_TARGET_END_DATA                GOMP_target_end_data
#define KMP_API_NAME_GOMP_TARGET_UPDATE                  GOMP_target_update
#define KMP_API_NAME_GOMP_TEAMS                          GOMP_teams

#ifdef KMP_USE_VERSION_SYMBOLS
#define xstr(x) str(x)
    #define str(x) #x

    // If Linux, xexpand prepends __kmp_api_ to the real API name
    #define xexpand(api_name) expand(api_name)
    #define expand(api_name) __kmp_api_##api_name

    #define xaliasify(api_name,ver) aliasify(api_name,ver)
    #define aliasify(api_name,ver) __typeof__(__kmp_api_##api_name) __kmp_api_##api_name##_##ver##_alias __attribute__((alias(xstr(__kmp_api_##api_name))))

    #define xversionify(api_name, version_num, version_str) versionify(api_name, version_num, version_str, "VERSION")
    #define versionify(api_name, version_num, version_str, default_ver) \
    __asm__(".symver " xstr(__kmp_api_##api_name##_##version_num##_alias) "," xstr(api_name) "@" version_str "\n\t"); \
    __asm__(".symver " xstr(__kmp_api_##api_name) "," xstr(api_name) "@@" default_ver "\n\t")

#else // KMP_USE_VERSION_SYMBOLS
#define xstr(x) /* Nothing */
#define str(x)  /* Nothing */

// if Windows or Mac, xexpand does no name transformation
#define xexpand(api_name) expand(api_name)
#define expand(api_name) api_name

#define xaliasify(api_name,ver) /* Nothing */
#define aliasify(api_name,ver)  /* Nothing */

#define xversionify(api_name, version_num, version_str) /* Nothing */
#define versionify(api_name, version_num, version_str, default_ver) /* Nothing */

#endif // KMP_USE_VERSION_SYMBOLS

#endif /* KMP_FTN_OS_H */

