/*
 * kmp_atomic.h - ATOMIC header file
 */

/* <copyright>
   Copyright (c) 1997-2014 Intel Corporation.  All Rights Reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:

 * Redistributions of source code must retain the above copyright
 notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright
 notice, this list of conditions and the following disclaimer in the
 documentation and/or other materials provided with the distribution.
 * Neither the name of Intel Corporation nor the names of its
 contributors may be used to endorse or promote products derived
 from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 </copyright> */

#ifndef KMP_ATOMIC_H
#define KMP_ATOMIC_H

//#include "kmp_os.h"
//#include "kmp_lock.h"


//#include <hpx/include/lcos.hpp>
#include "hpx_runtime.h"

typedef size_t kmp_size_t;

typedef float kmp_real32;
typedef double kmp_real64;

typedef int8_t kmp_int8;
typedef uint8_t kmp_uint8;

typedef int16_t kmp_int16;
typedef uint16_t kmp_uint16;

typedef int kmp_int32;
typedef uint32_t kmp_uint32;

typedef long long kmp_int64;
typedef uint64_t kmp_uint64;


//according to the RT; not sure why these arent long long/int64_t
typedef long kmp_intptr_t;
typedef unsigned long kmp_uintptr_t;

#define FALSE false
#define TRUE true

#define KMP_COMPILER_ICC 0
#define KMP_COMPILER_GCC 0
#define KMP_COMPILER_CLANG 0
#define KMP_COMPILER_MSVC 0

#if defined( __INTEL_COMPILER )
# undef KMP_COMPILER_ICC
# define KMP_COMPILER_ICC 1
#elif defined( __clang__ )
# undef KMP_COMPILER_CLANG
# define KMP_COMPILER_CLANG 1
#elif defined( __GNUC__ )
# undef KMP_COMPILER_GCC
# define KMP_COMPILER_GCC 1
#elif defined( _MSC_VER )
# undef KMP_COMPILER_MSVC
# define KMP_COMPILER_MSVC 1
#else
# error Unknown compiler
#endif

#define KMP_HAVE_QUAD 0
#if KMP_COMPILER_ICC
   /* _Quad is already defined for icc */
#  undef  KMP_HAVE_QUAD
#  define KMP_HAVE_QUAD 1
#elif KMP_COMPILER_CLANG
   /* Clang doesn't support a software-implemented
      128-bit extended precision type yet */
   typedef long double _Quad;
#elif KMP_COMPILER_GCC
   typedef __float128 _Quad;
#  undef  KMP_HAVE_QUAD
#  define KMP_HAVE_QUAD 1
#elif KMP_COMPILER_MSVC
   typedef long double _Quad;
#endif

# define KMP_ARCH_X86 0

//Is not set. When/why would I need it?
#ifdef USE_VOLATILE_CAST
# define VOLATILE_CAST(x)        (volatile x)
#else
# define VOLATILE_CAST(x)        (x)
#endif


//TODO: This might be a useful place to put a yield in
# define KMP_CPU_PAUSE()


# define KMP_TEST_THEN_INC32(p)                 __sync_fetch_and_add( (kmp_int32 *)(p), 1 )
# define KMP_TEST_THEN_INC_ACQ32(p)             __sync_fetch_and_add( (kmp_int32 *)(p), 1 )
# define KMP_TEST_THEN_INC64(p)                 __sync_fetch_and_add( (kmp_int64 *)(p), 1LL )
# define KMP_TEST_THEN_INC_ACQ64(p)             __sync_fetch_and_add( (kmp_int64 *)(p), 1LL )
# define KMP_TEST_THEN_ADD4_32(p)               __sync_fetch_and_add( (kmp_int32 *)(p), 4 )
# define KMP_TEST_THEN_ADD4_ACQ32(p)            __sync_fetch_and_add( (kmp_int32 *)(p), 4 )
# define KMP_TEST_THEN_ADD4_64(p)               __sync_fetch_and_add( (kmp_int64 *)(p), 4LL )
# define KMP_TEST_THEN_ADD4_ACQ64(p)            __sync_fetch_and_add( (kmp_int64 *)(p), 4LL )
# define KMP_TEST_THEN_DEC32(p)                 __sync_fetch_and_sub( (kmp_int32 *)(p), 1 )
# define KMP_TEST_THEN_DEC_ACQ32(p)             __sync_fetch_and_sub( (kmp_int32 *)(p), 1 )
# define KMP_TEST_THEN_DEC64(p)                 __sync_fetch_and_sub( (kmp_int64 *)(p), 1LL )
# define KMP_TEST_THEN_DEC_ACQ64(p)             __sync_fetch_and_sub( (kmp_int64 *)(p), 1LL )
# define KMP_TEST_THEN_ADD32(p, v)              __sync_fetch_and_add( (kmp_int32 *)(p), (v) )
# define KMP_TEST_THEN_ADD64(p, v)              __sync_fetch_and_add( (kmp_int64 *)(p), (v) )

# define KMP_TEST_THEN_OR32(p, v)               __sync_fetch_and_or( (kmp_int32 *)(p), (v) )
# define KMP_TEST_THEN_AND32(p, v)              __sync_fetch_and_and( (kmp_int32 *)(p), (v) )
# define KMP_TEST_THEN_OR64(p, v)               __sync_fetch_and_or( (kmp_int64 *)(p), (v) )
# define KMP_TEST_THEN_AND64(p, v)              __sync_fetch_and_and( (kmp_int64 *)(p), (v) )

# define KMP_COMPARE_AND_STORE_ACQ8(p, cv, sv)  __sync_bool_compare_and_swap( (volatile kmp_uint8 *)(p),(kmp_uint8)(cv),(kmp_uint8)(sv) )
# define KMP_COMPARE_AND_STORE_REL8(p, cv, sv)  __sync_bool_compare_and_swap( (volatile kmp_uint8 *)(p),(kmp_uint8)(cv),(kmp_uint8)(sv) )
# define KMP_COMPARE_AND_STORE_ACQ16(p, cv, sv) __sync_bool_compare_and_swap( (volatile kmp_uint16 *)(p),(kmp_uint16)(cv),(kmp_uint16)(sv) )
# define KMP_COMPARE_AND_STORE_REL16(p, cv, sv) __sync_bool_compare_and_swap( (volatile kmp_uint16 *)(p),(kmp_uint16)(cv),(kmp_uint16)(sv) )
# define KMP_COMPARE_AND_STORE_ACQ32(p, cv, sv) __sync_bool_compare_and_swap( (volatile kmp_uint32 *)(p),(kmp_uint32)(cv),(kmp_uint32)(sv) )
# define KMP_COMPARE_AND_STORE_REL32(p, cv, sv) __sync_bool_compare_and_swap( (volatile kmp_uint32 *)(p),(kmp_uint32)(cv),(kmp_uint32)(sv) )
# define KMP_COMPARE_AND_STORE_ACQ64(p, cv, sv) __sync_bool_compare_and_swap( (volatile kmp_uint64 *)(p),(kmp_uint64)(cv),(kmp_uint64)(sv) )
# define KMP_COMPARE_AND_STORE_REL64(p, cv, sv) __sync_bool_compare_and_swap( (volatile kmp_uint64 *)(p),(kmp_uint64)(cv),(kmp_uint64)(sv) )
# define KMP_COMPARE_AND_STORE_PTR(p, cv, sv)   __sync_bool_compare_and_swap( (volatile void **)(p),(void *)(cv),(void *)(sv) )

# define KMP_COMPARE_AND_STORE_RET8(p, cv, sv)  __sync_val_compare_and_swap( (volatile kmp_uint8 *)(p),(kmp_uint8)(cv),(kmp_uint8)(sv) )
# define KMP_COMPARE_AND_STORE_RET16(p, cv, sv) __sync_val_compare_and_swap( (volatile kmp_uint16 *)(p),(kmp_uint16)(cv),(kmp_uint16)(sv) )
# define KMP_COMPARE_AND_STORE_RET32(p, cv, sv) __sync_val_compare_and_swap( (volatile kmp_uint32 *)(p),(kmp_uint32)(cv),(kmp_uint32)(sv) )
# define KMP_COMPARE_AND_STORE_RET64(p, cv, sv) __sync_val_compare_and_swap( (volatile kmp_uint64 *)(p),(kmp_uint64)(cv),(kmp_uint64)(sv) )

#define KMP_XCHG_FIXED8(p, v)                   __sync_lock_test_and_set( (volatile kmp_uint8 *)(p), (kmp_uint8)(v) )
#define KMP_XCHG_FIXED16(p, v)                  __sync_lock_test_and_set( (volatile kmp_uint16 *)(p), (kmp_uint16)(v) )
#define KMP_XCHG_FIXED32(p, v)                  __sync_lock_test_and_set( (volatile kmp_uint32 *)(p), (kmp_uint32)(v) )
#define KMP_XCHG_FIXED64(p, v)                  __sync_lock_test_and_set( (volatile kmp_uint64 *)(p), (kmp_uint64)(v) )


inline kmp_real32 KMP_XCHG_REAL32( volatile kmp_real32 *p, kmp_real32 v) {
    kmp_int32 tmp = __sync_lock_test_and_set( (kmp_int32*)p, *(kmp_int32*)&v);
    return *(kmp_real32*)&tmp;
}

inline kmp_real64 KMP_XCHG_REAL64( volatile kmp_real64 *p, kmp_real64 v) {
    kmp_int64 tmp = __sync_lock_test_and_set( (kmp_int64*)p, *(kmp_int64*)&v);
    return *(kmp_real64*)&tmp;
}

//changed from struct ident_t
typedef struct ident_t ident_t;

// create shortcuts for c99 complex types
typedef float _Complex       kmp_cmplx32;
typedef double _Complex      kmp_cmplx64;
typedef long double _Complex kmp_cmplx80;
#if KMP_HAVE_QUAD
typedef _Quad _Complex       kmp_cmplx128;
#endif

#define QUAD_LEGACY _Quad
#define CPLX128_LEG kmp_cmplx128

extern "C" {

    extern int __kmp_atomic_mode;
    // Atomic locks can easily become contended, so we use queuing locks for them.
     
    //typedef kmp_queuing_lock_t kmp_atomic_lock_t;
    typedef hpx::lcos::local::spinlock kmp_atomic_lock_t;

    //typedef boost::shared_ptr<mutex_type> mtx_ptr;
    
    static inline void
        __kmp_acquire_atomic_lock( kmp_atomic_lock_t *lck, kmp_int32 gtid )
        {
            lck->lock();
            //__kmp_acquire_queuing_lock( lck, gtid );
        }

    static inline int
        __kmp_test_atomic_lock( kmp_atomic_lock_t *lck, kmp_int32 gtid )
        {
            return lck->try_lock();
            //return __kmp_test_queuing_lock( lck, gtid );
        }

    static inline void
        __kmp_release_atomic_lock( kmp_atomic_lock_t *lck, kmp_int32 gtid )
        {
            lck->unlock();
            //__kmp_release_queuing_lock( lck, gtid );
        }

    static inline void
        __kmp_init_atomic_lock( kmp_atomic_lock_t *lck )
        {
            //FIXME: not sure if this is correct/works.
            lck = new kmp_atomic_lock_t;

            //__kmp_init_queuing_lock( lck );
        }

    static inline void
        __kmp_destroy_atomic_lock( kmp_atomic_lock_t *lck )
        {
            delete lck;
            //__kmp_destroy_queuing_lock( lck );
        }

    // Global Locks

    extern kmp_atomic_lock_t __kmp_atomic_lock;    /* Control access to all user coded atomics in Gnu compat mode   */
    extern kmp_atomic_lock_t __kmp_atomic_lock_1i;  /* Control access to all user coded atomics for 1-byte fixed data types */
    extern kmp_atomic_lock_t __kmp_atomic_lock_2i;  /* Control access to all user coded atomics for 2-byte fixed data types */
    extern kmp_atomic_lock_t __kmp_atomic_lock_4i;  /* Control access to all user coded atomics for 4-byte fixed data types */
    extern kmp_atomic_lock_t __kmp_atomic_lock_4r;  /* Control access to all user coded atomics for kmp_real32 data type    */
    extern kmp_atomic_lock_t __kmp_atomic_lock_8i;  /* Control access to all user coded atomics for 8-byte fixed data types */
    extern kmp_atomic_lock_t __kmp_atomic_lock_8r;  /* Control access to all user coded atomics for kmp_real64 data type    */
    extern kmp_atomic_lock_t __kmp_atomic_lock_8c;  /* Control access to all user coded atomics for complex byte data type  */
    extern kmp_atomic_lock_t __kmp_atomic_lock_10r; /* Control access to all user coded atomics for long double data type   */
    extern kmp_atomic_lock_t __kmp_atomic_lock_16r; /* Control access to all user coded atomics for _Quad data type         */
    extern kmp_atomic_lock_t __kmp_atomic_lock_16c; /* Control access to all user coded atomics for double complex data type*/
    extern kmp_atomic_lock_t __kmp_atomic_lock_20c; /* Control access to all user coded atomics for long double complex type*/
    extern kmp_atomic_lock_t __kmp_atomic_lock_32c; /* Control access to all user coded atomics for _Quad complex data type */

    //  Below routines for atomic UPDATE are listed

    // 1-byte
    void __kmpc_atomic_fixed1_add(  ident_t *id_ref, int gtid, kmp_int8 * lhs, kmp_int8 rhs );
    void __kmpc_atomic_fixed1_andb( ident_t *id_ref, int gtid, kmp_int8 * lhs, kmp_int8 rhs );
    void __kmpc_atomic_fixed1_div(  ident_t *id_ref, int gtid, kmp_int8 * lhs, kmp_int8 rhs );
    void __kmpc_atomic_fixed1u_div( ident_t *id_ref, int gtid, kmp_uint8 * lhs, kmp_uint8 rhs );
    void __kmpc_atomic_fixed1_mul(  ident_t *id_ref, int gtid, kmp_int8 * lhs, kmp_int8 rhs );
    void __kmpc_atomic_fixed1_orb(  ident_t *id_ref, int gtid, kmp_int8 * lhs, kmp_int8 rhs );
    void __kmpc_atomic_fixed1_shl(  ident_t *id_ref, int gtid, kmp_int8 * lhs, kmp_int8 rhs );
    void __kmpc_atomic_fixed1_shr(  ident_t *id_ref, int gtid, kmp_int8 * lhs, kmp_int8 rhs );
    void __kmpc_atomic_fixed1u_shr( ident_t *id_ref, int gtid, kmp_uint8 * lhs, kmp_uint8 rhs );
    void __kmpc_atomic_fixed1_sub(  ident_t *id_ref, int gtid, kmp_int8 * lhs, kmp_int8 rhs );
    void __kmpc_atomic_fixed1_xor(  ident_t *id_ref, int gtid, kmp_int8 * lhs, kmp_int8 rhs );
    // 2-byte
    void __kmpc_atomic_fixed2_add(  ident_t *id_ref, int gtid, short * lhs, short rhs );
    void __kmpc_atomic_fixed2_andb( ident_t *id_ref, int gtid, short * lhs, short rhs );
    void __kmpc_atomic_fixed2_div(  ident_t *id_ref, int gtid, short * lhs, short rhs );
    void __kmpc_atomic_fixed2u_div( ident_t *id_ref, int gtid, unsigned short * lhs, unsigned short rhs );
    void __kmpc_atomic_fixed2_mul(  ident_t *id_ref, int gtid, short * lhs, short rhs );
    void __kmpc_atomic_fixed2_orb(  ident_t *id_ref, int gtid, short * lhs, short rhs );
    void __kmpc_atomic_fixed2_shl(  ident_t *id_ref, int gtid, short * lhs, short rhs );
    void __kmpc_atomic_fixed2_shr(  ident_t *id_ref, int gtid, short * lhs, short rhs );
    void __kmpc_atomic_fixed2u_shr( ident_t *id_ref, int gtid, unsigned short * lhs, unsigned short rhs );
    void __kmpc_atomic_fixed2_sub(  ident_t *id_ref, int gtid, short * lhs, short rhs );
    void __kmpc_atomic_fixed2_xor(  ident_t *id_ref, int gtid, short * lhs, short rhs );
    // 4-byte add / sub fixed
    void __kmpc_atomic_fixed4_add(  ident_t *id_ref, int gtid, kmp_int32 * lhs, kmp_int32 rhs );
    void __kmpc_atomic_fixed4_sub(  ident_t *id_ref, int gtid, kmp_int32 * lhs, kmp_int32 rhs );
    // 4-byte add / sub float
    void __kmpc_atomic_float4_add(  ident_t *id_ref, int gtid, kmp_real32 * lhs, kmp_real32 rhs );
    void __kmpc_atomic_float4_sub(  ident_t *id_ref, int gtid, kmp_real32 * lhs, kmp_real32 rhs );
    // 8-byte add / sub fixed
    void __kmpc_atomic_fixed8_add(  ident_t *id_ref, int gtid, kmp_int64 * lhs, kmp_int64 rhs );
    void __kmpc_atomic_fixed8_sub(  ident_t *id_ref, int gtid, kmp_int64 * lhs, kmp_int64 rhs );
    // 8-byte add / sub float
    void __kmpc_atomic_float8_add(  ident_t *id_ref, int gtid, kmp_real64 * lhs, kmp_real64 rhs );
    void __kmpc_atomic_float8_sub(  ident_t *id_ref, int gtid, kmp_real64 * lhs, kmp_real64 rhs );
    // 4-byte fixed
    void __kmpc_atomic_fixed4_andb( ident_t *id_ref, int gtid, kmp_int32 * lhs, kmp_int32 rhs );
    void __kmpc_atomic_fixed4_div(  ident_t *id_ref, int gtid, kmp_int32 * lhs, kmp_int32 rhs );
    void __kmpc_atomic_fixed4u_div( ident_t *id_ref, int gtid, kmp_uint32 * lhs, kmp_uint32 rhs );
    void __kmpc_atomic_fixed4_mul(  ident_t *id_ref, int gtid, kmp_int32 * lhs, kmp_int32 rhs );
    void __kmpc_atomic_fixed4_orb(  ident_t *id_ref, int gtid, kmp_int32 * lhs, kmp_int32 rhs );
    void __kmpc_atomic_fixed4_shl(  ident_t *id_ref, int gtid, kmp_int32 * lhs, kmp_int32 rhs );
    void __kmpc_atomic_fixed4_shr(  ident_t *id_ref, int gtid, kmp_int32 * lhs, kmp_int32 rhs );
    void __kmpc_atomic_fixed4u_shr( ident_t *id_ref, int gtid, kmp_uint32 * lhs, kmp_uint32 rhs );
    void __kmpc_atomic_fixed4_xor(  ident_t *id_ref, int gtid, kmp_int32 * lhs, kmp_int32 rhs );
    // 8-byte fixed
    void __kmpc_atomic_fixed8_andb( ident_t *id_ref, int gtid, kmp_int64 * lhs, kmp_int64 rhs );
    void __kmpc_atomic_fixed8_div(  ident_t *id_ref, int gtid, kmp_int64 * lhs, kmp_int64 rhs );
    void __kmpc_atomic_fixed8u_div( ident_t *id_ref, int gtid, kmp_uint64 * lhs, kmp_uint64 rhs );
    void __kmpc_atomic_fixed8_mul(  ident_t *id_ref, int gtid, kmp_int64 * lhs, kmp_int64 rhs );
    void __kmpc_atomic_fixed8_orb(  ident_t *id_ref, int gtid, kmp_int64 * lhs, kmp_int64 rhs );
    void __kmpc_atomic_fixed8_shl(  ident_t *id_ref, int gtid, kmp_int64 * lhs, kmp_int64 rhs );
    void __kmpc_atomic_fixed8_shr(  ident_t *id_ref, int gtid, kmp_int64 * lhs, kmp_int64 rhs );
    void __kmpc_atomic_fixed8u_shr( ident_t *id_ref, int gtid, kmp_uint64 * lhs, kmp_uint64 rhs );
    void __kmpc_atomic_fixed8_xor(  ident_t *id_ref, int gtid, kmp_int64 * lhs, kmp_int64 rhs );
    // 4-byte float
    void __kmpc_atomic_float4_div(  ident_t *id_ref, int gtid, kmp_real32 * lhs, kmp_real32 rhs );
    void __kmpc_atomic_float4_mul(  ident_t *id_ref, int gtid, kmp_real32 * lhs, kmp_real32 rhs );
    // 8-byte float
    void __kmpc_atomic_float8_div(  ident_t *id_ref, int gtid, kmp_real64 * lhs, kmp_real64 rhs );
    void __kmpc_atomic_float8_mul(  ident_t *id_ref, int gtid, kmp_real64 * lhs, kmp_real64 rhs );
    // 1-, 2-, 4-, 8-byte logical (&&, ||)
    void __kmpc_atomic_fixed1_andl( ident_t *id_ref, int gtid, kmp_int8 * lhs, kmp_int8 rhs );
    void __kmpc_atomic_fixed1_orl(  ident_t *id_ref, int gtid, kmp_int8 * lhs, kmp_int8 rhs );
    void __kmpc_atomic_fixed2_andl( ident_t *id_ref, int gtid, short * lhs, short rhs );
    void __kmpc_atomic_fixed2_orl(  ident_t *id_ref, int gtid, short * lhs, short rhs );
    void __kmpc_atomic_fixed4_andl( ident_t *id_ref, int gtid, kmp_int32 * lhs, kmp_int32 rhs );
    void __kmpc_atomic_fixed4_orl(  ident_t *id_ref, int gtid, kmp_int32 * lhs, kmp_int32 rhs );
    void __kmpc_atomic_fixed8_andl( ident_t *id_ref, int gtid, kmp_int64 * lhs, kmp_int64 rhs );
    void __kmpc_atomic_fixed8_orl(  ident_t *id_ref, int gtid, kmp_int64 * lhs, kmp_int64 rhs );
    // MIN / MAX
    void __kmpc_atomic_fixed1_max(  ident_t *id_ref, int gtid, kmp_int8 * lhs, kmp_int8 rhs );
    void __kmpc_atomic_fixed1_min(  ident_t *id_ref, int gtid, kmp_int8 * lhs, kmp_int8 rhs );
    void __kmpc_atomic_fixed2_max(  ident_t *id_ref, int gtid, short * lhs, short rhs );
    void __kmpc_atomic_fixed2_min(  ident_t *id_ref, int gtid, short * lhs, short rhs );
    void __kmpc_atomic_fixed4_max(  ident_t *id_ref, int gtid, kmp_int32 * lhs, kmp_int32 rhs );
    void __kmpc_atomic_fixed4_min(  ident_t *id_ref, int gtid, kmp_int32 * lhs, kmp_int32 rhs );
    void __kmpc_atomic_fixed8_max(  ident_t *id_ref, int gtid, kmp_int64 * lhs, kmp_int64 rhs );
    void __kmpc_atomic_fixed8_min(  ident_t *id_ref, int gtid, kmp_int64 * lhs, kmp_int64 rhs );
    void __kmpc_atomic_float4_max(  ident_t *id_ref, int gtid, kmp_real32 * lhs, kmp_real32 rhs );
    void __kmpc_atomic_float4_min(  ident_t *id_ref, int gtid, kmp_real32 * lhs, kmp_real32 rhs );
    void __kmpc_atomic_float8_max(  ident_t *id_ref, int gtid, kmp_real64 * lhs, kmp_real64 rhs );
    void __kmpc_atomic_float8_min(  ident_t *id_ref, int gtid, kmp_real64 * lhs, kmp_real64 rhs );
#if KMP_HAVE_QUAD
    void __kmpc_atomic_float16_max( ident_t *id_ref, int gtid, QUAD_LEGACY * lhs, QUAD_LEGACY rhs );
    void __kmpc_atomic_float16_min( ident_t *id_ref, int gtid, QUAD_LEGACY * lhs, QUAD_LEGACY rhs );
#endif
    // .NEQV. (same as xor)
    void __kmpc_atomic_fixed1_neqv( ident_t *id_ref, int gtid, kmp_int8 * lhs, kmp_int8 rhs );
    void __kmpc_atomic_fixed2_neqv( ident_t *id_ref, int gtid, short * lhs, short rhs );
    void __kmpc_atomic_fixed4_neqv( ident_t *id_ref, int gtid, kmp_int32 * lhs, kmp_int32 rhs );
    void __kmpc_atomic_fixed8_neqv( ident_t *id_ref, int gtid, kmp_int64 * lhs, kmp_int64 rhs );
    // .EQV. (same as ~xor)
    void __kmpc_atomic_fixed1_eqv(  ident_t *id_ref, int gtid, kmp_int8 * lhs, kmp_int8 rhs );
    void __kmpc_atomic_fixed2_eqv(  ident_t *id_ref, int gtid, short * lhs, short rhs );
    void __kmpc_atomic_fixed4_eqv(  ident_t *id_ref, int gtid, kmp_int32 * lhs, kmp_int32 rhs );
    void __kmpc_atomic_fixed8_eqv(  ident_t *id_ref, int gtid, kmp_int64 * lhs, kmp_int64 rhs );
    // long double type
    void __kmpc_atomic_float10_add( ident_t *id_ref, int gtid, long double * lhs, long double rhs );
    void __kmpc_atomic_float10_sub( ident_t *id_ref, int gtid, long double * lhs, long double rhs );
    void __kmpc_atomic_float10_mul( ident_t *id_ref, int gtid, long double * lhs, long double rhs );
    void __kmpc_atomic_float10_div( ident_t *id_ref, int gtid, long double * lhs, long double rhs );
    // _Quad type
#if KMP_HAVE_QUAD
    void __kmpc_atomic_float16_add( ident_t *id_ref, int gtid, QUAD_LEGACY * lhs, QUAD_LEGACY rhs );
    void __kmpc_atomic_float16_sub( ident_t *id_ref, int gtid, QUAD_LEGACY * lhs, QUAD_LEGACY rhs );
    void __kmpc_atomic_float16_mul( ident_t *id_ref, int gtid, QUAD_LEGACY * lhs, QUAD_LEGACY rhs );
    void __kmpc_atomic_float16_div( ident_t *id_ref, int gtid, QUAD_LEGACY * lhs, QUAD_LEGACY rhs );
#endif
    // routines for complex types
    void __kmpc_atomic_cmplx4_add(  ident_t *id_ref, int gtid, kmp_cmplx32 * lhs, kmp_cmplx32 rhs );
    void __kmpc_atomic_cmplx4_sub(  ident_t *id_ref, int gtid, kmp_cmplx32 * lhs, kmp_cmplx32 rhs );
    void __kmpc_atomic_cmplx4_mul(  ident_t *id_ref, int gtid, kmp_cmplx32 * lhs, kmp_cmplx32 rhs );
    void __kmpc_atomic_cmplx4_div(  ident_t *id_ref, int gtid, kmp_cmplx32 * lhs, kmp_cmplx32 rhs );
    void __kmpc_atomic_cmplx8_add(  ident_t *id_ref, int gtid, kmp_cmplx64 * lhs, kmp_cmplx64 rhs );
    void __kmpc_atomic_cmplx8_sub(  ident_t *id_ref, int gtid, kmp_cmplx64 * lhs, kmp_cmplx64 rhs );
    void __kmpc_atomic_cmplx8_mul(  ident_t *id_ref, int gtid, kmp_cmplx64 * lhs, kmp_cmplx64 rhs );
    void __kmpc_atomic_cmplx8_div(  ident_t *id_ref, int gtid, kmp_cmplx64 * lhs, kmp_cmplx64 rhs );
    void __kmpc_atomic_cmplx10_add( ident_t *id_ref, int gtid, kmp_cmplx80 * lhs, kmp_cmplx80 rhs );
    void __kmpc_atomic_cmplx10_sub( ident_t *id_ref, int gtid, kmp_cmplx80 * lhs, kmp_cmplx80 rhs );
    void __kmpc_atomic_cmplx10_mul( ident_t *id_ref, int gtid, kmp_cmplx80 * lhs, kmp_cmplx80 rhs );
    void __kmpc_atomic_cmplx10_div( ident_t *id_ref, int gtid, kmp_cmplx80 * lhs, kmp_cmplx80 rhs );
#if KMP_HAVE_QUAD
    void __kmpc_atomic_cmplx16_add( ident_t *id_ref, int gtid, CPLX128_LEG * lhs, CPLX128_LEG rhs );
    void __kmpc_atomic_cmplx16_sub( ident_t *id_ref, int gtid, CPLX128_LEG * lhs, CPLX128_LEG rhs );
    void __kmpc_atomic_cmplx16_mul( ident_t *id_ref, int gtid, CPLX128_LEG * lhs, CPLX128_LEG rhs );
    void __kmpc_atomic_cmplx16_div( ident_t *id_ref, int gtid, CPLX128_LEG * lhs, CPLX128_LEG rhs );
#endif

#if OMP_40_ENABLED
    // OpenMP 4.0: x = expr binop x for non-commutative operations.
    // Supported only on IA-32 architecture and Intel(R) 64
    void __kmpc_atomic_fixed1_sub_rev(  ident_t *id_ref, int gtid, kmp_int8 * lhs, kmp_int8 rhs );
    void __kmpc_atomic_fixed1_div_rev(  ident_t *id_ref, int gtid, kmp_int8 * lhs, kmp_int8 rhs );
    void __kmpc_atomic_fixed1u_div_rev( ident_t *id_ref, int gtid, kmp_uint8 * lhs, kmp_uint8 rhs );
    void __kmpc_atomic_fixed1_shl_rev(  ident_t *id_ref, int gtid, kmp_int8 * lhs, kmp_int8 rhs );
    void __kmpc_atomic_fixed1_shr_rev(  ident_t *id_ref, int gtid, kmp_int8 * lhs, kmp_int8 rhs );
    void __kmpc_atomic_fixed1u_shr_rev( ident_t *id_ref, int gtid, kmp_uint8 * lhs, kmp_uint8 rhs );
    void __kmpc_atomic_fixed2_sub_rev(  ident_t *id_ref, int gtid, short * lhs, short rhs );
    void __kmpc_atomic_fixed2_div_rev(  ident_t *id_ref, int gtid, short * lhs, short rhs );
    void __kmpc_atomic_fixed2u_div_rev( ident_t *id_ref, int gtid, unsigned short * lhs, unsigned short rhs );
    void __kmpc_atomic_fixed2_shl_rev(  ident_t *id_ref, int gtid, short * lhs, short rhs );
    void __kmpc_atomic_fixed2_shr_rev(  ident_t *id_ref, int gtid, short * lhs, short rhs );
    void __kmpc_atomic_fixed2u_shr_rev( ident_t *id_ref, int gtid, unsigned short * lhs, unsigned short rhs );
    void __kmpc_atomic_fixed4_sub_rev(  ident_t *id_ref, int gtid, kmp_int32 * lhs, kmp_int32 rhs );
    void __kmpc_atomic_fixed4_div_rev(  ident_t *id_ref, int gtid, kmp_int32 * lhs, kmp_int32 rhs );
    void __kmpc_atomic_fixed4u_div_rev( ident_t *id_ref, int gtid, kmp_uint32 * lhs, kmp_uint32 rhs );
    void __kmpc_atomic_fixed4_shl_rev(  ident_t *id_ref, int gtid, kmp_int32 * lhs, kmp_int32 rhs );
    void __kmpc_atomic_fixed4_shr_rev(  ident_t *id_ref, int gtid, kmp_int32 * lhs, kmp_int32 rhs );
    void __kmpc_atomic_fixed4u_shr_rev( ident_t *id_ref, int gtid, kmp_uint32 * lhs, kmp_uint32 rhs );
    void __kmpc_atomic_fixed8_sub_rev(  ident_t *id_ref, int gtid, kmp_int64 * lhs, kmp_int64 rhs );
    void __kmpc_atomic_fixed8_div_rev(  ident_t *id_ref, int gtid, kmp_int64 * lhs, kmp_int64 rhs );
    void __kmpc_atomic_fixed8u_div_rev( ident_t *id_ref, int gtid, kmp_uint64 * lhs, kmp_uint64 rhs );
    void __kmpc_atomic_fixed8_shl_rev(  ident_t *id_ref, int gtid, kmp_int64 * lhs, kmp_int64 rhs );
    void __kmpc_atomic_fixed8_shr_rev(  ident_t *id_ref, int gtid, kmp_int64 * lhs, kmp_int64 rhs );
    void __kmpc_atomic_fixed8u_shr_rev( ident_t *id_ref, int gtid, kmp_uint64 * lhs, kmp_uint64 rhs );
    void __kmpc_atomic_float4_sub_rev(  ident_t *id_ref, int gtid, float * lhs, float rhs );
    void __kmpc_atomic_float4_div_rev(  ident_t *id_ref, int gtid, float * lhs, float rhs );
    void __kmpc_atomic_float8_sub_rev(  ident_t *id_ref, int gtid, double * lhs, double rhs );
    void __kmpc_atomic_float8_div_rev(  ident_t *id_ref, int gtid, double * lhs, double rhs );
    void __kmpc_atomic_float10_sub_rev( ident_t *id_ref, int gtid, long double * lhs, long double rhs );
    void __kmpc_atomic_float10_div_rev( ident_t *id_ref, int gtid, long double * lhs, long double rhs );
#if KMP_HAVE_QUAD
    void __kmpc_atomic_float16_sub_rev( ident_t *id_ref, int gtid, QUAD_LEGACY * lhs, QUAD_LEGACY rhs );
    void __kmpc_atomic_float16_div_rev( ident_t *id_ref, int gtid, QUAD_LEGACY * lhs, QUAD_LEGACY rhs );
#endif
    void __kmpc_atomic_cmplx4_sub_rev(  ident_t *id_ref, int gtid, kmp_cmplx32 * lhs, kmp_cmplx32 rhs );
    void __kmpc_atomic_cmplx4_div_rev(  ident_t *id_ref, int gtid, kmp_cmplx32 * lhs, kmp_cmplx32 rhs );
    void __kmpc_atomic_cmplx8_sub_rev(  ident_t *id_ref, int gtid, kmp_cmplx64 * lhs, kmp_cmplx64 rhs );
    void __kmpc_atomic_cmplx8_div_rev(  ident_t *id_ref, int gtid, kmp_cmplx64 * lhs, kmp_cmplx64 rhs );
    void __kmpc_atomic_cmplx10_sub_rev( ident_t *id_ref, int gtid, kmp_cmplx80 * lhs, kmp_cmplx80 rhs );
    void __kmpc_atomic_cmplx10_div_rev( ident_t *id_ref, int gtid, kmp_cmplx80 * lhs, kmp_cmplx80 rhs );
#if KMP_HAVE_QUAD
    void __kmpc_atomic_cmplx16_sub_rev( ident_t *id_ref, int gtid, CPLX128_LEG * lhs, CPLX128_LEG rhs );
    void __kmpc_atomic_cmplx16_div_rev( ident_t *id_ref, int gtid, CPLX128_LEG * lhs, CPLX128_LEG rhs );
#endif // KMP_HAVE_QUAD

#endif //OMP_40_ENABLED

    // routines for mixed types

    // RHS=float8
    void __kmpc_atomic_fixed1_mul_float8( ident_t *id_ref, int gtid, kmp_int8 * lhs, kmp_real64 rhs );
    void __kmpc_atomic_fixed1_div_float8( ident_t *id_ref, int gtid, kmp_int8 * lhs, kmp_real64 rhs );
    void __kmpc_atomic_fixed2_mul_float8( ident_t *id_ref, int gtid, short * lhs, kmp_real64 rhs );
    void __kmpc_atomic_fixed2_div_float8( ident_t *id_ref, int gtid, short * lhs, kmp_real64 rhs );
    void __kmpc_atomic_fixed4_mul_float8( ident_t *id_ref, int gtid, kmp_int32 * lhs, kmp_real64 rhs );
    void __kmpc_atomic_fixed4_div_float8( ident_t *id_ref, int gtid, kmp_int32 * lhs, kmp_real64 rhs );
    void __kmpc_atomic_fixed8_mul_float8( ident_t *id_ref, int gtid, kmp_int64 * lhs, kmp_real64 rhs );
    void __kmpc_atomic_fixed8_div_float8( ident_t *id_ref, int gtid, kmp_int64 * lhs, kmp_real64 rhs );
    void __kmpc_atomic_float4_add_float8( ident_t *id_ref, int gtid, kmp_real32 * lhs, kmp_real64 rhs );
    void __kmpc_atomic_float4_sub_float8( ident_t *id_ref, int gtid, kmp_real32 * lhs, kmp_real64 rhs );
    void __kmpc_atomic_float4_mul_float8( ident_t *id_ref, int gtid, kmp_real32 * lhs, kmp_real64 rhs );
    void __kmpc_atomic_float4_div_float8( ident_t *id_ref, int gtid, kmp_real32 * lhs, kmp_real64 rhs );

    // RHS=float16 (deprecated, to be removed when we are sure the compiler does not use them)
#if KMP_HAVE_QUAD
    void __kmpc_atomic_fixed1_add_fp(  ident_t *id_ref, int gtid, kmp_int8 * lhs, _Quad rhs );
    void __kmpc_atomic_fixed1_sub_fp(  ident_t *id_ref, int gtid, kmp_int8 * lhs, _Quad rhs );
    void __kmpc_atomic_fixed1_mul_fp(  ident_t *id_ref, int gtid, kmp_int8 * lhs, _Quad rhs );
    void __kmpc_atomic_fixed1_div_fp(  ident_t *id_ref, int gtid, kmp_int8 * lhs, _Quad rhs );
    void __kmpc_atomic_fixed1u_div_fp( ident_t *id_ref, int gtid, kmp_uint8 * lhs, _Quad rhs );

    void __kmpc_atomic_fixed2_add_fp(  ident_t *id_ref, int gtid, short * lhs, _Quad rhs );
    void __kmpc_atomic_fixed2_sub_fp(  ident_t *id_ref, int gtid, short * lhs, _Quad rhs );
    void __kmpc_atomic_fixed2_mul_fp(  ident_t *id_ref, int gtid, short * lhs, _Quad rhs );
    void __kmpc_atomic_fixed2_div_fp(  ident_t *id_ref, int gtid, short * lhs, _Quad rhs );
    void __kmpc_atomic_fixed2u_div_fp( ident_t *id_ref, int gtid, unsigned short * lhs, _Quad rhs );

    void __kmpc_atomic_fixed4_add_fp(  ident_t *id_ref, int gtid, kmp_int32 * lhs, _Quad rhs );
    void __kmpc_atomic_fixed4_sub_fp(  ident_t *id_ref, int gtid, kmp_int32 * lhs, _Quad rhs );
    void __kmpc_atomic_fixed4_mul_fp(  ident_t *id_ref, int gtid, kmp_int32 * lhs, _Quad rhs );
    void __kmpc_atomic_fixed4_div_fp(  ident_t *id_ref, int gtid, kmp_int32 * lhs, _Quad rhs );
    void __kmpc_atomic_fixed4u_div_fp( ident_t *id_ref, int gtid, kmp_uint32 * lhs, _Quad rhs );

    void __kmpc_atomic_fixed8_add_fp(  ident_t *id_ref, int gtid, kmp_int64 * lhs, _Quad rhs );
    void __kmpc_atomic_fixed8_sub_fp(  ident_t *id_ref, int gtid, kmp_int64 * lhs, _Quad rhs );
    void __kmpc_atomic_fixed8_mul_fp(  ident_t *id_ref, int gtid, kmp_int64 * lhs, _Quad rhs );
    void __kmpc_atomic_fixed8_div_fp(  ident_t *id_ref, int gtid, kmp_int64 * lhs, _Quad rhs );
    void __kmpc_atomic_fixed8u_div_fp( ident_t *id_ref, int gtid, kmp_uint64 * lhs, _Quad rhs );

    void __kmpc_atomic_float4_add_fp(  ident_t *id_ref, int gtid, kmp_real32 * lhs, _Quad rhs );
    void __kmpc_atomic_float4_sub_fp(  ident_t *id_ref, int gtid, kmp_real32 * lhs, _Quad rhs );
    void __kmpc_atomic_float4_mul_fp(  ident_t *id_ref, int gtid, kmp_real32 * lhs, _Quad rhs );
    void __kmpc_atomic_float4_div_fp(  ident_t *id_ref, int gtid, kmp_real32 * lhs, _Quad rhs );

    void __kmpc_atomic_float8_add_fp(  ident_t *id_ref, int gtid, kmp_real64 * lhs, _Quad rhs );
    void __kmpc_atomic_float8_sub_fp(  ident_t *id_ref, int gtid, kmp_real64 * lhs, _Quad rhs );
    void __kmpc_atomic_float8_mul_fp(  ident_t *id_ref, int gtid, kmp_real64 * lhs, _Quad rhs );
    void __kmpc_atomic_float8_div_fp(  ident_t *id_ref, int gtid, kmp_real64 * lhs, _Quad rhs );

    void __kmpc_atomic_float10_add_fp( ident_t *id_ref, int gtid, long double * lhs, _Quad rhs );
    void __kmpc_atomic_float10_sub_fp( ident_t *id_ref, int gtid, long double * lhs, _Quad rhs );
    void __kmpc_atomic_float10_mul_fp( ident_t *id_ref, int gtid, long double * lhs, _Quad rhs );
    void __kmpc_atomic_float10_div_fp( ident_t *id_ref, int gtid, long double * lhs, _Quad rhs );
#endif // KMP_HAVE_QUAD

    // RHS=cmplx8
    void __kmpc_atomic_cmplx4_add_cmplx8( ident_t *id_ref, int gtid, kmp_cmplx32 * lhs, kmp_cmplx64 rhs );
    void __kmpc_atomic_cmplx4_sub_cmplx8( ident_t *id_ref, int gtid, kmp_cmplx32 * lhs, kmp_cmplx64 rhs );
    void __kmpc_atomic_cmplx4_mul_cmplx8( ident_t *id_ref, int gtid, kmp_cmplx32 * lhs, kmp_cmplx64 rhs );
    void __kmpc_atomic_cmplx4_div_cmplx8( ident_t *id_ref, int gtid, kmp_cmplx32 * lhs, kmp_cmplx64 rhs );

    // generic atomic routines
    void __kmpc_atomic_1(  ident_t *id_ref, int gtid, void* lhs, void* rhs, void (*f)( void *, void *, void * ) );
    void __kmpc_atomic_2(  ident_t *id_ref, int gtid, void* lhs, void* rhs, void (*f)( void *, void *, void * ) );
    void __kmpc_atomic_4(  ident_t *id_ref, int gtid, void* lhs, void* rhs, void (*f)( void *, void *, void * ) );
    void __kmpc_atomic_8(  ident_t *id_ref, int gtid, void* lhs, void* rhs, void (*f)( void *, void *, void * ) );
    void __kmpc_atomic_10( ident_t *id_ref, int gtid, void* lhs, void* rhs, void (*f)( void *, void *, void * ) );
    void __kmpc_atomic_16( ident_t *id_ref, int gtid, void* lhs, void* rhs, void (*f)( void *, void *, void * ) );
    void __kmpc_atomic_20( ident_t *id_ref, int gtid, void* lhs, void* rhs, void (*f)( void *, void *, void * ) );
    void __kmpc_atomic_32( ident_t *id_ref, int gtid, void* lhs, void* rhs, void (*f)( void *, void *, void * ) );

    // READ, WRITE, CAPTURE are supported only on IA-32 architecture and Intel(R) 64
    //  Below routines for atomic READ are listed

    kmp_int8         __kmpc_atomic_fixed1_rd(  ident_t *id_ref, int gtid, kmp_int8        * loc );
    short        __kmpc_atomic_fixed2_rd(  ident_t *id_ref, int gtid, short       * loc );
    kmp_int32    __kmpc_atomic_fixed4_rd(  ident_t *id_ref, int gtid, kmp_int32   * loc );
    kmp_int64    __kmpc_atomic_fixed8_rd(  ident_t *id_ref, int gtid, kmp_int64   * loc );
    kmp_real32   __kmpc_atomic_float4_rd(  ident_t *id_ref, int gtid, kmp_real32  * loc );
    kmp_real64   __kmpc_atomic_float8_rd(  ident_t *id_ref, int gtid, kmp_real64  * loc );
    long double  __kmpc_atomic_float10_rd( ident_t *id_ref, int gtid, long double * loc );
#if KMP_HAVE_QUAD
    QUAD_LEGACY  __kmpc_atomic_float16_rd( ident_t *id_ref, int gtid, QUAD_LEGACY * loc );
#endif
    // Fix for CQ220361: cmplx4 READ will return void on Windows* OS; read value will be
    // returned through an additional parameter
#if ( KMP_OS_WINDOWS )
    void  __kmpc_atomic_cmplx4_rd(  kmp_cmplx32 * out, ident_t *id_ref, int gtid, kmp_cmplx32 * loc );
#else
    kmp_cmplx32  __kmpc_atomic_cmplx4_rd(  ident_t *id_ref, int gtid, kmp_cmplx32 * loc );
#endif
    kmp_cmplx64  __kmpc_atomic_cmplx8_rd(  ident_t *id_ref, int gtid, kmp_cmplx64 * loc );
    kmp_cmplx80  __kmpc_atomic_cmplx10_rd( ident_t *id_ref, int gtid, kmp_cmplx80 * loc );
#if KMP_HAVE_QUAD
    CPLX128_LEG  __kmpc_atomic_cmplx16_rd( ident_t *id_ref, int gtid, CPLX128_LEG * loc );
#endif

    //  Below routines for atomic WRITE are listed

    void __kmpc_atomic_fixed1_wr(  ident_t *id_ref, int gtid, kmp_int8        * lhs, kmp_int8        rhs );
    void __kmpc_atomic_fixed2_wr(  ident_t *id_ref, int gtid, short       * lhs, short       rhs );
    void __kmpc_atomic_fixed4_wr(  ident_t *id_ref, int gtid, kmp_int32   * lhs, kmp_int32   rhs );
    void __kmpc_atomic_fixed8_wr(  ident_t *id_ref, int gtid, kmp_int64   * lhs, kmp_int64   rhs );
    void __kmpc_atomic_float4_wr(  ident_t *id_ref, int gtid, kmp_real32  * lhs, kmp_real32  rhs );
    void __kmpc_atomic_float8_wr(  ident_t *id_ref, int gtid, kmp_real64  * lhs, kmp_real64  rhs );
    void __kmpc_atomic_float10_wr( ident_t *id_ref, int gtid, long double * lhs, long double rhs );
#if KMP_HAVE_QUAD
    void __kmpc_atomic_float16_wr( ident_t *id_ref, int gtid, QUAD_LEGACY * lhs, QUAD_LEGACY rhs );
#endif
    void __kmpc_atomic_cmplx4_wr(  ident_t *id_ref, int gtid, kmp_cmplx32 * lhs, kmp_cmplx32 rhs );
    void __kmpc_atomic_cmplx8_wr(  ident_t *id_ref, int gtid, kmp_cmplx64 * lhs, kmp_cmplx64 rhs );
    void __kmpc_atomic_cmplx10_wr( ident_t *id_ref, int gtid, kmp_cmplx80 * lhs, kmp_cmplx80 rhs );
#if KMP_HAVE_QUAD
    void __kmpc_atomic_cmplx16_wr( ident_t *id_ref, int gtid, CPLX128_LEG * lhs, CPLX128_LEG rhs );
#endif

    //  Below routines for atomic CAPTURE are listed

    // 1-byte
    kmp_int8 __kmpc_atomic_fixed1_add_cpt(  ident_t *id_ref, int gtid, kmp_int8 * lhs, kmp_int8 rhs, int flag);
    kmp_int8 __kmpc_atomic_fixed1_andb_cpt( ident_t *id_ref, int gtid, kmp_int8 * lhs, kmp_int8 rhs, int flag);
    kmp_int8 __kmpc_atomic_fixed1_div_cpt(  ident_t *id_ref, int gtid, kmp_int8 * lhs, kmp_int8 rhs, int flag);
    kmp_uint8 __kmpc_atomic_fixed1u_div_cpt( ident_t *id_ref, int gtid, kmp_uint8 * lhs, kmp_uint8 rhs, int flag);
    kmp_int8 __kmpc_atomic_fixed1_mul_cpt(  ident_t *id_ref, int gtid, kmp_int8 * lhs, kmp_int8 rhs, int flag);
    kmp_int8 __kmpc_atomic_fixed1_orb_cpt(  ident_t *id_ref, int gtid, kmp_int8 * lhs, kmp_int8 rhs, int flag);
    kmp_int8 __kmpc_atomic_fixed1_shl_cpt(  ident_t *id_ref, int gtid, kmp_int8 * lhs, kmp_int8 rhs, int flag);
    kmp_int8 __kmpc_atomic_fixed1_shr_cpt(  ident_t *id_ref, int gtid, kmp_int8 * lhs, kmp_int8 rhs, int flag);
    kmp_uint8 __kmpc_atomic_fixed1u_shr_cpt( ident_t *id_ref, int gtid, kmp_uint8 * lhs, kmp_uint8 rhs, int flag);
    kmp_int8 __kmpc_atomic_fixed1_sub_cpt(  ident_t *id_ref, int gtid, kmp_int8 * lhs, kmp_int8 rhs, int flag);
    kmp_int8 __kmpc_atomic_fixed1_xor_cpt(  ident_t *id_ref, int gtid, kmp_int8 * lhs, kmp_int8 rhs, int flag);
    // 2-byte
    short __kmpc_atomic_fixed2_add_cpt(  ident_t *id_ref, int gtid, short * lhs, short rhs, int flag);
    short __kmpc_atomic_fixed2_andb_cpt( ident_t *id_ref, int gtid, short * lhs, short rhs, int flag);
    short __kmpc_atomic_fixed2_div_cpt(  ident_t *id_ref, int gtid, short * lhs, short rhs, int flag);
    unsigned short __kmpc_atomic_fixed2u_div_cpt( ident_t *id_ref, int gtid, unsigned short * lhs, unsigned short rhs, int flag);
    short __kmpc_atomic_fixed2_mul_cpt(  ident_t *id_ref, int gtid, short * lhs, short rhs, int flag);
    short __kmpc_atomic_fixed2_orb_cpt(  ident_t *id_ref, int gtid, short * lhs, short rhs, int flag);
    short __kmpc_atomic_fixed2_shl_cpt(  ident_t *id_ref, int gtid, short * lhs, short rhs, int flag);
    short __kmpc_atomic_fixed2_shr_cpt(  ident_t *id_ref, int gtid, short * lhs, short rhs, int flag);
    unsigned short __kmpc_atomic_fixed2u_shr_cpt( ident_t *id_ref, int gtid, unsigned short * lhs, unsigned short rhs, int flag);
    short __kmpc_atomic_fixed2_sub_cpt(  ident_t *id_ref, int gtid, short * lhs, short rhs, int flag);
    short __kmpc_atomic_fixed2_xor_cpt(  ident_t *id_ref, int gtid, short * lhs, short rhs, int flag);
    // 4-byte add / sub fixed
    kmp_int32  __kmpc_atomic_fixed4_add_cpt(  ident_t *id_ref, int gtid, kmp_int32  * lhs, kmp_int32 rhs, int flag);
    kmp_int32  __kmpc_atomic_fixed4_sub_cpt(  ident_t *id_ref, int gtid, kmp_int32  * lhs, kmp_int32 rhs, int flag);
    // 4-byte add / sub float
    kmp_real32 __kmpc_atomic_float4_add_cpt(  ident_t *id_ref, int gtid, kmp_real32 * lhs, kmp_real32 rhs, int flag);
    kmp_real32 __kmpc_atomic_float4_sub_cpt(  ident_t *id_ref, int gtid, kmp_real32 * lhs, kmp_real32 rhs, int flag);
    // 8-byte add / sub fixed
    kmp_int64  __kmpc_atomic_fixed8_add_cpt(  ident_t *id_ref, int gtid, kmp_int64  * lhs, kmp_int64 rhs, int flag);
    kmp_int64  __kmpc_atomic_fixed8_sub_cpt(  ident_t *id_ref, int gtid, kmp_int64  * lhs, kmp_int64 rhs, int flag);
    // 8-byte add / sub float
    kmp_real64 __kmpc_atomic_float8_add_cpt(  ident_t *id_ref, int gtid, kmp_real64 * lhs, kmp_real64 rhs, int flag);
    kmp_real64 __kmpc_atomic_float8_sub_cpt(  ident_t *id_ref, int gtid, kmp_real64 * lhs, kmp_real64 rhs, int flag);
    // 4-byte fixed
    kmp_int32  __kmpc_atomic_fixed4_andb_cpt( ident_t *id_ref, int gtid, kmp_int32  * lhs, kmp_int32  rhs, int flag);
    kmp_int32  __kmpc_atomic_fixed4_div_cpt(  ident_t *id_ref, int gtid, kmp_int32  * lhs, kmp_int32  rhs, int flag);
    kmp_uint32 __kmpc_atomic_fixed4u_div_cpt( ident_t *id_ref, int gtid, kmp_uint32 * lhs, kmp_uint32 rhs, int flag);
    kmp_int32  __kmpc_atomic_fixed4_mul_cpt(  ident_t *id_ref, int gtid, kmp_int32  * lhs, kmp_int32  rhs, int flag);
    kmp_int32  __kmpc_atomic_fixed4_orb_cpt(  ident_t *id_ref, int gtid, kmp_int32  * lhs, kmp_int32  rhs, int flag);
    kmp_int32  __kmpc_atomic_fixed4_shl_cpt(  ident_t *id_ref, int gtid, kmp_int32  * lhs, kmp_int32  rhs, int flag);
    kmp_int32  __kmpc_atomic_fixed4_shr_cpt(  ident_t *id_ref, int gtid, kmp_int32  * lhs, kmp_int32  rhs, int flag);
    kmp_uint32 __kmpc_atomic_fixed4u_shr_cpt( ident_t *id_ref, int gtid, kmp_uint32 * lhs, kmp_uint32 rhs, int flag);
    kmp_int32  __kmpc_atomic_fixed4_xor_cpt(  ident_t *id_ref, int gtid, kmp_int32  * lhs, kmp_int32  rhs, int flag);
    // 8-byte fixed
    kmp_int64  __kmpc_atomic_fixed8_andb_cpt( ident_t *id_ref, int gtid, kmp_int64  * lhs, kmp_int64  rhs, int flag);
    kmp_int64  __kmpc_atomic_fixed8_div_cpt(  ident_t *id_ref, int gtid, kmp_int64  * lhs, kmp_int64  rhs, int flag);
    kmp_uint64 __kmpc_atomic_fixed8u_div_cpt( ident_t *id_ref, int gtid, kmp_uint64 * lhs, kmp_uint64 rhs, int flag);
    kmp_int64  __kmpc_atomic_fixed8_mul_cpt(  ident_t *id_ref, int gtid, kmp_int64  * lhs, kmp_int64  rhs, int flag);
    kmp_int64  __kmpc_atomic_fixed8_orb_cpt(  ident_t *id_ref, int gtid, kmp_int64  * lhs, kmp_int64  rhs, int flag);
    kmp_int64  __kmpc_atomic_fixed8_shl_cpt(  ident_t *id_ref, int gtid, kmp_int64  * lhs, kmp_int64  rhs, int flag);
    kmp_int64  __kmpc_atomic_fixed8_shr_cpt(  ident_t *id_ref, int gtid, kmp_int64  * lhs, kmp_int64  rhs, int flag);
    kmp_uint64 __kmpc_atomic_fixed8u_shr_cpt( ident_t *id_ref, int gtid, kmp_uint64 * lhs, kmp_uint64 rhs, int flag);
    kmp_int64  __kmpc_atomic_fixed8_xor_cpt(  ident_t *id_ref, int gtid, kmp_int64  * lhs, kmp_int64  rhs, int flag);
    // 4-byte float
    kmp_real32 __kmpc_atomic_float4_div_cpt(  ident_t *id_ref, int gtid, kmp_real32 * lhs, kmp_real32 rhs, int flag);
    kmp_real32 __kmpc_atomic_float4_mul_cpt(  ident_t *id_ref, int gtid, kmp_real32 * lhs, kmp_real32 rhs, int flag);
    // 8-byte float
    kmp_real64 __kmpc_atomic_float8_div_cpt(  ident_t *id_ref, int gtid, kmp_real64 * lhs, kmp_real64 rhs, int flag);
    kmp_real64 __kmpc_atomic_float8_mul_cpt(  ident_t *id_ref, int gtid, kmp_real64 * lhs, kmp_real64 rhs, int flag);
    // 1-, 2-, 4-, 8-byte logical (&&, ||)
    kmp_int8      __kmpc_atomic_fixed1_andl_cpt( ident_t *id_ref, int gtid, kmp_int8      * lhs, kmp_int8      rhs, int flag);
    kmp_int8      __kmpc_atomic_fixed1_orl_cpt(  ident_t *id_ref, int gtid, kmp_int8      * lhs, kmp_int8      rhs, int flag);
    short     __kmpc_atomic_fixed2_andl_cpt( ident_t *id_ref, int gtid, short     * lhs, short     rhs, int flag);
    short     __kmpc_atomic_fixed2_orl_cpt(  ident_t *id_ref, int gtid, short     * lhs, short     rhs, int flag);
    kmp_int32 __kmpc_atomic_fixed4_andl_cpt( ident_t *id_ref, int gtid, kmp_int32 * lhs, kmp_int32 rhs, int flag);
    kmp_int32 __kmpc_atomic_fixed4_orl_cpt(  ident_t *id_ref, int gtid, kmp_int32 * lhs, kmp_int32 rhs, int flag);
    kmp_int64 __kmpc_atomic_fixed8_andl_cpt( ident_t *id_ref, int gtid, kmp_int64 * lhs, kmp_int64 rhs, int flag);
    kmp_int64 __kmpc_atomic_fixed8_orl_cpt(  ident_t *id_ref, int gtid, kmp_int64 * lhs, kmp_int64 rhs, int flag);
    // MIN / MAX
    kmp_int8        __kmpc_atomic_fixed1_max_cpt(  ident_t *id_ref, int gtid, kmp_int8      * lhs, kmp_int8      rhs, int flag);
    kmp_int8        __kmpc_atomic_fixed1_min_cpt(  ident_t *id_ref, int gtid, kmp_int8      * lhs, kmp_int8      rhs, int flag);
    short       __kmpc_atomic_fixed2_max_cpt(  ident_t *id_ref, int gtid, short     * lhs, short     rhs, int flag);
    short       __kmpc_atomic_fixed2_min_cpt(  ident_t *id_ref, int gtid, short     * lhs, short     rhs, int flag);
    kmp_int32   __kmpc_atomic_fixed4_max_cpt(  ident_t *id_ref, int gtid, kmp_int32 * lhs, kmp_int32 rhs, int flag);
    kmp_int32   __kmpc_atomic_fixed4_min_cpt(  ident_t *id_ref, int gtid, kmp_int32 * lhs, kmp_int32 rhs, int flag);
    kmp_int64   __kmpc_atomic_fixed8_max_cpt(  ident_t *id_ref, int gtid, kmp_int64 * lhs, kmp_int64 rhs, int flag);
    kmp_int64   __kmpc_atomic_fixed8_min_cpt(  ident_t *id_ref, int gtid, kmp_int64 * lhs, kmp_int64 rhs, int flag);
    kmp_real32  __kmpc_atomic_float4_max_cpt(  ident_t *id_ref, int gtid, kmp_real32 * lhs, kmp_real32 rhs, int flag);
    kmp_real32  __kmpc_atomic_float4_min_cpt(  ident_t *id_ref, int gtid, kmp_real32 * lhs, kmp_real32 rhs, int flag);
    kmp_real64  __kmpc_atomic_float8_max_cpt(  ident_t *id_ref, int gtid, kmp_real64 * lhs, kmp_real64 rhs, int flag);
    kmp_real64  __kmpc_atomic_float8_min_cpt(  ident_t *id_ref, int gtid, kmp_real64 * lhs, kmp_real64 rhs, int flag);
#if KMP_HAVE_QUAD
    QUAD_LEGACY __kmpc_atomic_float16_max_cpt( ident_t *id_ref, int gtid, QUAD_LEGACY * lhs, QUAD_LEGACY rhs, int flag);
    QUAD_LEGACY __kmpc_atomic_float16_min_cpt( ident_t *id_ref, int gtid, QUAD_LEGACY * lhs, QUAD_LEGACY rhs, int flag);
#endif
    // .NEQV. (same as xor)
    kmp_int8      __kmpc_atomic_fixed1_neqv_cpt( ident_t *id_ref, int gtid, kmp_int8      * lhs, kmp_int8      rhs, int flag);
    short     __kmpc_atomic_fixed2_neqv_cpt( ident_t *id_ref, int gtid, short     * lhs, short     rhs, int flag);
    kmp_int32 __kmpc_atomic_fixed4_neqv_cpt( ident_t *id_ref, int gtid, kmp_int32 * lhs, kmp_int32 rhs, int flag);
    kmp_int64 __kmpc_atomic_fixed8_neqv_cpt( ident_t *id_ref, int gtid, kmp_int64 * lhs, kmp_int64 rhs, int flag);
    // .EQV. (same as ~xor)
    kmp_int8      __kmpc_atomic_fixed1_eqv_cpt(  ident_t *id_ref, int gtid, kmp_int8      * lhs, kmp_int8      rhs, int flag);
    short     __kmpc_atomic_fixed2_eqv_cpt(  ident_t *id_ref, int gtid, short     * lhs, short     rhs, int flag);
    kmp_int32 __kmpc_atomic_fixed4_eqv_cpt(  ident_t *id_ref, int gtid, kmp_int32 * lhs, kmp_int32 rhs, int flag);
    kmp_int64 __kmpc_atomic_fixed8_eqv_cpt(  ident_t *id_ref, int gtid, kmp_int64 * lhs, kmp_int64 rhs, int flag);
    // long double type
    long double __kmpc_atomic_float10_add_cpt( ident_t *id_ref, int gtid, long double * lhs, long double rhs, int flag);
    long double __kmpc_atomic_float10_sub_cpt( ident_t *id_ref, int gtid, long double * lhs, long double rhs, int flag);
    long double __kmpc_atomic_float10_mul_cpt( ident_t *id_ref, int gtid, long double * lhs, long double rhs, int flag);
    long double __kmpc_atomic_float10_div_cpt( ident_t *id_ref, int gtid, long double * lhs, long double rhs, int flag);
#if KMP_HAVE_QUAD
    // _Quad type
    QUAD_LEGACY __kmpc_atomic_float16_add_cpt( ident_t *id_ref, int gtid, QUAD_LEGACY * lhs, QUAD_LEGACY rhs, int flag);
    QUAD_LEGACY __kmpc_atomic_float16_sub_cpt( ident_t *id_ref, int gtid, QUAD_LEGACY * lhs, QUAD_LEGACY rhs, int flag);
    QUAD_LEGACY __kmpc_atomic_float16_mul_cpt( ident_t *id_ref, int gtid, QUAD_LEGACY * lhs, QUAD_LEGACY rhs, int flag);
    QUAD_LEGACY __kmpc_atomic_float16_div_cpt( ident_t *id_ref, int gtid, QUAD_LEGACY * lhs, QUAD_LEGACY rhs, int flag);
#endif
    // routines for complex types
    // Workaround for cmplx4 routines - return void; captured value is returned via the argument
    void __kmpc_atomic_cmplx4_add_cpt(  ident_t *id_ref, int gtid, kmp_cmplx32 * lhs, kmp_cmplx32 rhs, kmp_cmplx32 * out, int flag);
    void __kmpc_atomic_cmplx4_sub_cpt(  ident_t *id_ref, int gtid, kmp_cmplx32 * lhs, kmp_cmplx32 rhs, kmp_cmplx32 * out, int flag);
    void __kmpc_atomic_cmplx4_mul_cpt(  ident_t *id_ref, int gtid, kmp_cmplx32 * lhs, kmp_cmplx32 rhs, kmp_cmplx32 * out, int flag);
    void __kmpc_atomic_cmplx4_div_cpt(  ident_t *id_ref, int gtid, kmp_cmplx32 * lhs, kmp_cmplx32 rhs, kmp_cmplx32 * out, int flag);

    kmp_cmplx64 __kmpc_atomic_cmplx8_add_cpt(  ident_t *id_ref, int gtid, kmp_cmplx64 * lhs, kmp_cmplx64 rhs, int flag);
    kmp_cmplx64 __kmpc_atomic_cmplx8_sub_cpt(  ident_t *id_ref, int gtid, kmp_cmplx64 * lhs, kmp_cmplx64 rhs, int flag);
    kmp_cmplx64 __kmpc_atomic_cmplx8_mul_cpt(  ident_t *id_ref, int gtid, kmp_cmplx64 * lhs, kmp_cmplx64 rhs, int flag);
    kmp_cmplx64 __kmpc_atomic_cmplx8_div_cpt(  ident_t *id_ref, int gtid, kmp_cmplx64 * lhs, kmp_cmplx64 rhs, int flag);
    kmp_cmplx80 __kmpc_atomic_cmplx10_add_cpt( ident_t *id_ref, int gtid, kmp_cmplx80 * lhs, kmp_cmplx80 rhs, int flag);
    kmp_cmplx80 __kmpc_atomic_cmplx10_sub_cpt( ident_t *id_ref, int gtid, kmp_cmplx80 * lhs, kmp_cmplx80 rhs, int flag);
    kmp_cmplx80 __kmpc_atomic_cmplx10_mul_cpt( ident_t *id_ref, int gtid, kmp_cmplx80 * lhs, kmp_cmplx80 rhs, int flag);
    kmp_cmplx80 __kmpc_atomic_cmplx10_div_cpt( ident_t *id_ref, int gtid, kmp_cmplx80 * lhs, kmp_cmplx80 rhs, int flag);
#if KMP_HAVE_QUAD
    CPLX128_LEG __kmpc_atomic_cmplx16_add_cpt( ident_t *id_ref, int gtid, CPLX128_LEG * lhs, CPLX128_LEG rhs, int flag);
    CPLX128_LEG __kmpc_atomic_cmplx16_sub_cpt( ident_t *id_ref, int gtid, CPLX128_LEG * lhs, CPLX128_LEG rhs, int flag);
    CPLX128_LEG __kmpc_atomic_cmplx16_mul_cpt( ident_t *id_ref, int gtid, CPLX128_LEG * lhs, CPLX128_LEG rhs, int flag);
    CPLX128_LEG __kmpc_atomic_cmplx16_div_cpt( ident_t *id_ref, int gtid, CPLX128_LEG * lhs, CPLX128_LEG rhs, int flag);
#endif

    void __kmpc_atomic_start(void);
    void __kmpc_atomic_end(void);

#if OMP_40_ENABLED

    // OpenMP 4.0: v = x = expr binop x; { v = x; x = expr binop x; } { x = expr binop x; v = x; }  for non-commutative operations.

    kmp_int8	       	__kmpc_atomic_fixed1_sub_cpt_rev(  ident_t *id_ref, int gtid, kmp_int8 * lhs, kmp_int8 rhs, int flag );
    kmp_int8		__kmpc_atomic_fixed1_div_cpt_rev(  ident_t *id_ref, int gtid, kmp_int8 * lhs, kmp_int8 rhs, int flag );
    kmp_uint8 	__kmpc_atomic_fixed1u_div_cpt_rev( ident_t *id_ref, int gtid, kmp_uint8 * lhs, kmp_uint8 rhs, int flag );
    kmp_int8 		__kmpc_atomic_fixed1_shl_cpt_rev(  ident_t *id_ref, int gtid, kmp_int8 * lhs, kmp_int8 rhs , int flag);
    kmp_int8		__kmpc_atomic_fixed1_shr_cpt_rev(  ident_t *id_ref, int gtid, kmp_int8 * lhs, kmp_int8 rhs, int flag );
    kmp_uint8 	__kmpc_atomic_fixed1u_shr_cpt_rev( ident_t *id_ref, int gtid, kmp_uint8 * lhs, kmp_uint8 rhs, int flag );
    short 		__kmpc_atomic_fixed2_sub_cpt_rev(  ident_t *id_ref, int gtid, short * lhs, short rhs, int flag );
    short 		__kmpc_atomic_fixed2_div_cpt_rev(  ident_t *id_ref, int gtid, short * lhs, short rhs, int flag );
    unsigned short 	__kmpc_atomic_fixed2u_div_cpt_rev( ident_t *id_ref, int gtid, unsigned short * lhs, unsigned short rhs, int flag );
    short 		__kmpc_atomic_fixed2_shl_cpt_rev(  ident_t *id_ref, int gtid, short * lhs, short rhs, int flag );
    short 		__kmpc_atomic_fixed2_shr_cpt_rev(  ident_t *id_ref, int gtid, short * lhs, short rhs, int flag );
    unsigned short 	__kmpc_atomic_fixed2u_shr_cpt_rev( ident_t *id_ref, int gtid, unsigned short * lhs, unsigned short rhs, int flag );
    kmp_int32 	__kmpc_atomic_fixed4_sub_cpt_rev(  ident_t *id_ref, int gtid, kmp_int32  * lhs, kmp_int32  rhs, int flag );
    kmp_int32 	__kmpc_atomic_fixed4_div_cpt_rev(  ident_t *id_ref, int gtid, kmp_int32  * lhs, kmp_int32  rhs, int flag );
    kmp_uint32 	__kmpc_atomic_fixed4u_div_cpt_rev( ident_t *id_ref, int gtid, kmp_uint32 * lhs, kmp_uint32 rhs, int flag );
    kmp_int32 	__kmpc_atomic_fixed4_shl_cpt_rev(  ident_t *id_ref, int gtid, kmp_int32  * lhs, kmp_int32  rhs, int flag );
    kmp_int32 	__kmpc_atomic_fixed4_shr_cpt_rev(  ident_t *id_ref, int gtid, kmp_int32  * lhs, kmp_int32  rhs, int flag );
    kmp_uint32 	__kmpc_atomic_fixed4u_shr_cpt_rev( ident_t *id_ref, int gtid, kmp_uint32 * lhs, kmp_uint32 rhs, int flag );
    kmp_int64 	__kmpc_atomic_fixed8_sub_cpt_rev(  ident_t *id_ref, int gtid, kmp_int64  * lhs, kmp_int64  rhs, int flag );
    kmp_int64 	__kmpc_atomic_fixed8_div_cpt_rev(  ident_t *id_ref, int gtid, kmp_int64  * lhs, kmp_int64  rhs, int flag );
    kmp_uint64      __kmpc_atomic_fixed8u_div_cpt_rev( ident_t *id_ref, int gtid, kmp_uint64 * lhs, kmp_uint64 rhs, int flag );
    kmp_int64 	__kmpc_atomic_fixed8_shl_cpt_rev(  ident_t *id_ref, int gtid, kmp_int64  * lhs, kmp_int64  rhs, int flag );
    kmp_int64 	__kmpc_atomic_fixed8_shr_cpt_rev(  ident_t *id_ref, int gtid, kmp_int64  * lhs, kmp_int64  rhs, int flag );
    kmp_uint64      __kmpc_atomic_fixed8u_shr_cpt_rev( ident_t *id_ref, int gtid, kmp_uint64 * lhs, kmp_uint64 rhs, int flag );
    float 		__kmpc_atomic_float4_sub_cpt_rev(  ident_t *id_ref, int gtid, float * lhs, float rhs, int flag );
    float 		__kmpc_atomic_float4_div_cpt_rev(  ident_t *id_ref, int gtid, float * lhs, float rhs, int flag );
    double 		__kmpc_atomic_float8_sub_cpt_rev(  ident_t *id_ref, int gtid, double * lhs, double rhs, int flag );
    double 		__kmpc_atomic_float8_div_cpt_rev(  ident_t *id_ref, int gtid, double * lhs, double rhs, int flag );
    long double 	__kmpc_atomic_float10_sub_cpt_rev( ident_t *id_ref, int gtid, long double * lhs, long double rhs, int flag );
    long double 	__kmpc_atomic_float10_div_cpt_rev( ident_t *id_ref, int gtid, long double * lhs, long double rhs, int flag );
#if KMP_HAVE_QUAD
    QUAD_LEGACY	__kmpc_atomic_float16_sub_cpt_rev( ident_t *id_ref, int gtid, QUAD_LEGACY * lhs, QUAD_LEGACY rhs, int flag );
    QUAD_LEGACY	__kmpc_atomic_float16_div_cpt_rev( ident_t *id_ref, int gtid, QUAD_LEGACY * lhs, QUAD_LEGACY rhs, int flag );
#endif
    // Workaround for cmplx4 routines - return void; captured value is returned via the argument
    void     	__kmpc_atomic_cmplx4_sub_cpt_rev(  ident_t *id_ref, int gtid, kmp_cmplx32 * lhs, kmp_cmplx32 rhs, kmp_cmplx32 * out, int flag );
    void 	        __kmpc_atomic_cmplx4_div_cpt_rev(  ident_t *id_ref, int gtid, kmp_cmplx32 * lhs, kmp_cmplx32 rhs, kmp_cmplx32 * out, int flag );
    kmp_cmplx64 	__kmpc_atomic_cmplx8_sub_cpt_rev(  ident_t *id_ref, int gtid, kmp_cmplx64 * lhs, kmp_cmplx64 rhs, int flag );
    kmp_cmplx64 	__kmpc_atomic_cmplx8_div_cpt_rev(  ident_t *id_ref, int gtid, kmp_cmplx64 * lhs, kmp_cmplx64 rhs, int flag );
    kmp_cmplx80 	__kmpc_atomic_cmplx10_sub_cpt_rev( ident_t *id_ref, int gtid, kmp_cmplx80 * lhs, kmp_cmplx80 rhs, int flag );
    kmp_cmplx80 	__kmpc_atomic_cmplx10_div_cpt_rev( ident_t *id_ref, int gtid, kmp_cmplx80 * lhs, kmp_cmplx80 rhs, int flag );
#if KMP_HAVE_QUAD
    CPLX128_LEG  	__kmpc_atomic_cmplx16_sub_cpt_rev( ident_t *id_ref, int gtid, CPLX128_LEG * lhs, CPLX128_LEG rhs, int flag );
    CPLX128_LEG  	__kmpc_atomic_cmplx16_div_cpt_rev( ident_t *id_ref, int gtid, CPLX128_LEG * lhs, CPLX128_LEG rhs, int flag );
#endif

    //   OpenMP 4.0 Capture-write (swap): {v = x; x = expr;}
    kmp_int8 		__kmpc_atomic_fixed1_swp(  ident_t *id_ref, int gtid, kmp_int8        * lhs, kmp_int8        rhs );
    short           __kmpc_atomic_fixed2_swp(  ident_t *id_ref, int gtid, short       * lhs, short       rhs );
    kmp_int32       __kmpc_atomic_fixed4_swp(  ident_t *id_ref, int gtid, kmp_int32   * lhs, kmp_int32   rhs );
    kmp_int64 	__kmpc_atomic_fixed8_swp(  ident_t *id_ref, int gtid, kmp_int64   * lhs, kmp_int64   rhs );
    float 		__kmpc_atomic_float4_swp(  ident_t *id_ref, int gtid, float       * lhs, float  rhs );
    double		__kmpc_atomic_float8_swp(  ident_t *id_ref, int gtid, double      * lhs, double  rhs );
    long double	__kmpc_atomic_float10_swp( ident_t *id_ref, int gtid, long double * lhs, long double rhs );
#if KMP_HAVE_QUAD
    QUAD_LEGACY    	__kmpc_atomic_float16_swp( ident_t *id_ref, int gtid, QUAD_LEGACY * lhs, QUAD_LEGACY rhs );
#endif
    // !!! TODO: check if we need a workaround here
    void        	__kmpc_atomic_cmplx4_swp(  ident_t *id_ref, int gtid, kmp_cmplx32 * lhs, kmp_cmplx32 rhs, kmp_cmplx32 * out );
    //kmp_cmplx32   	__kmpc_atomic_cmplx4_swp(  ident_t *id_ref, int gtid, kmp_cmplx32 * lhs, kmp_cmplx32 rhs );

    kmp_cmplx64 	__kmpc_atomic_cmplx8_swp(  ident_t *id_ref, int gtid, kmp_cmplx64 * lhs, kmp_cmplx64 rhs );
    kmp_cmplx80	__kmpc_atomic_cmplx10_swp( ident_t *id_ref, int gtid, kmp_cmplx80 * lhs, kmp_cmplx80 rhs );
#if KMP_HAVE_QUAD
    CPLX128_LEG 	__kmpc_atomic_cmplx16_swp( ident_t *id_ref, int gtid, CPLX128_LEG * lhs, CPLX128_LEG rhs );
#endif

    // End of OpenMP 4.0 capture

#endif //OMP_40_ENABLED

} // extern "C"

#endif /* KMP_ATOMIC_H */

