// Copyright (c) 2018 Tianyi Zhang
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef HPXMP_GCC_HPXMP_H
#define HPXMP_GCC_HPXMP_H

#include "kmp_ftn_os.h"
extern "C" void
xexpand(KMP_API_NAME_GOMP_PARALLEL)(void (*task)(void *), void *data, unsigned num_threads, unsigned int flags);
extern "C" void 
xexpand(KMP_API_NAME_GOMP_TASK)(void (*func)(void *), void *data, void (*copy_func)(void *, void *),
                                long arg_size, long arg_align, bool if_cond, unsigned gomp_flags);
extern "C" void
xexpand(KMP_API_NAME_GOMP_TASKWAIT)(void);

extern "C" int
xexpand(KMP_API_NAME_GOMP_SINGLE_START)(void);

extern "C" void *
xexpand(KMP_API_NAME_GOMP_SINGLE_COPY_START)(void);

extern "C" void
xexpand(KMP_API_NAME_GOMP_SINGLE_COPY_END)(void *data);

extern "C" void
xexpand(KMP_API_NAME_GOMP_BARRIER)(void);

extern "C" void
xexpand(KMP_API_NAME_GOMP_CRITICAL_START)(void);

extern "C" void
xexpand(KMP_API_NAME_GOMP_CRITICAL_END)(void);

extern "C" void
xexpand(KMP_API_NAME_GOMP_CRITICAL_NAME_START)(void** ptr);

extern "C" void
xexpand(KMP_API_NAME_GOMP_CRITICAL_NAME_END)(void** ptr);

extern "C" void
xexpand(KMP_API_NAME_GOMP_ATOMIC_START)(void);

extern "C" void
xexpand(KMP_API_NAME_GOMP_ATOMIC_END)(void);

extern "C" void
xexpand(KMP_API_NAME_GOMP_ORDERED_START)(void);

extern "C" void
xexpand(KMP_API_NAME_GOMP_ORDERED_END)(void);

#define DECLEAR_LOOP_START(func)                                               \
    extern "C" int func(                                                       \
        long lb, long ub, long str, long chunk_sz, long *p_lb, long *p_ub);
DECLEAR_LOOP_START(xexpand(KMP_API_NAME_GOMP_LOOP_STATIC_START))
DECLEAR_LOOP_START(xexpand(KMP_API_NAME_GOMP_LOOP_DYNAMIC_START))
DECLEAR_LOOP_START(xexpand(KMP_API_NAME_GOMP_LOOP_GUIDED_START))
DECLEAR_LOOP_START(xexpand(KMP_API_NAME_GOMP_LOOP_ORDERED_STATIC_START))
DECLEAR_LOOP_START(xexpand(KMP_API_NAME_GOMP_LOOP_ORDERED_DYNAMIC_START))
DECLEAR_LOOP_START(xexpand(KMP_API_NAME_GOMP_LOOP_ORDERED_GUIDED_START))

#define DECLEAR_LOOP_RUNTIME_START(func)                                            \
    int func(long lb, long ub, long str, long *p_lb, long *p_ub);
DECLEAR_LOOP_RUNTIME_START(xexpand(KMP_API_NAME_GOMP_LOOP_RUNTIME_START))
DECLEAR_LOOP_RUNTIME_START(xexpand(KMP_API_NAME_GOMP_LOOP_ORDERED_RUNTIME_START))

#define DECLEAR_LOOP_NEXT(func)                                               \
    extern "C" int func(long *p_lb, long *p_ub);
DECLEAR_LOOP_NEXT(xexpand(KMP_API_NAME_GOMP_LOOP_STATIC_NEXT))
DECLEAR_LOOP_NEXT(xexpand(KMP_API_NAME_GOMP_LOOP_DYNAMIC_NEXT))
DECLEAR_LOOP_NEXT(xexpand(KMP_API_NAME_GOMP_LOOP_GUIDED_NEXT))
DECLEAR_LOOP_NEXT(xexpand(KMP_API_NAME_GOMP_LOOP_RUNTIME_NEXT))
DECLEAR_LOOP_NEXT(xexpand(KMP_API_NAME_GOMP_LOOP_ORDERED_STATIC_NEXT))
DECLEAR_LOOP_NEXT(xexpand(KMP_API_NAME_GOMP_LOOP_ORDERED_DYNAMIC_NEXT))
DECLEAR_LOOP_NEXT(xexpand(KMP_API_NAME_GOMP_LOOP_ORDERED_GUIDED_NEXT))
DECLEAR_LOOP_NEXT(xexpand(KMP_API_NAME_GOMP_LOOP_ORDERED_RUNTIME_NEXT))

#define DECLEAR_PARALLEL_LOOP(func)                                            \
    extern "C" void func(void (*task)(void *), void *data,                     \
        unsigned num_threads, long lb, long ub, long str, long chunk_sz,       \
        unsigned flags);
DECLEAR_PARALLEL_LOOP(xexpand(KMP_API_NAME_GOMP_PARALLEL_LOOP_DYNAMIC))
DECLEAR_PARALLEL_LOOP(xexpand(KMP_API_NAME_GOMP_PARALLEL_LOOP_STATIC))
DECLEAR_PARALLEL_LOOP(xexpand(KMP_API_NAME_GOMP_PARALLEL_LOOP_GUIDED))
DECLEAR_PARALLEL_LOOP(xexpand(KMP_API_NAME_GOMP_PARALLEL_LOOP_RUNTIME))

extern "C" void
xexpand(KMP_API_NAME_GOMP_LOOP_END_NOWAIT)(void);

#endif //HPXMP_GCC_HPXMP_H
