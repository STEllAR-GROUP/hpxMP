//
// Created by tianyi on 9/17/18.
//

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
#endif //HPXMP_GCC_HPXMP_H
