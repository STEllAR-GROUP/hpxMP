/**
 *
 * @file flops.h
 *
 *  File provided by Univ. of Tennessee,
 *
 * @version 1.0.0
 * @author Mathieu Faverge
 * @date 2010-12-20
 *
 **/
/*
 * This file provide the flops formula for all Level 3 BLAS and some
 * Lapack routines.  Each macro uses the same size parameters as the
 * function associated and provide one formula for additions and one
 * for multiplications. Example to use these macros:
 *
 *    FLOPS_ZGEMM( m, n, k )
 *
 * All the formula are reported in the LAPACK Lawn 41:
 *     http://www.netlib.org/lapack/lawns/lawn41.ps
 */
#ifndef _FLOPS_H_
#define _FLOPS_H_

/************************************************************************
 *           Generic formula coming from LAWN 41
 ***********************************************************************/

/*
 * Lapack
 */
#define FMULS_GETRF(__m, __n) ( ((__m) < (__n)) ? (0.5 * (double)(__m) * ((double)(__m) * ((double)(__n) - (1./3.) * (__m) - 1. ) + (double)(__n)) + (2. / 3.) * (__m)) \
                                :                 (0.5 * (double)(__n) * ((double)(__n) * ((double)(__m) - (1./3.) * (__n) - 1. ) + (double)(__m)) + (2. / 3.) * (__n)) )
#define FADDS_GETRF(__m, __n) ( ((__m) < (__n)) ? (0.5 * (double)(__m) * ((double)(__m) * ((double)(__n) - (1./3.) * (__m)      ) - (double)(__n)) + (1. / 6.) * (__m)) \
                                :                 (0.5 * (double)(__n) * ((double)(__n) * ((double)(__m) - (1./3.) * (__n)      ) - (double)(__m)) + (1. / 6.) * (__n)) )
#define FMULS_POTRF(__n) ((double)(__n) * (((1. / 6.) * (double)(__n) + 0.5) * (double)(__n) + (1. / 3.)))
#define FADDS_POTRF(__n) ((double)(__n) * (((1. / 6.) * (double)(__n)      ) * (double)(__n) - (1. / 6.)))

#define FMULS_GEQRF(__m, __n) (((__m) > (__n)) ? ((double)(__n) * ((double)(__n) * (  0.5-(1./3.) * (double)(__n) + (double)(__m)) +    (double)(__m) + 23. / 6.)) \
                               :                 ((double)(__m) * ((double)(__m) * ( -0.5-(1./3.) * (double)(__m) + (double)(__n)) + 2.*(double)(__n) + 23. / 6.)) )
#define FADDS_GEQRF(__m, __n) (((__m) > (__n)) ? ((double)(__n) * ((double)(__n) * (  0.5-(1./3.) * (double)(__n) + (double)(__m))                    +  5. / 6.)) \
                               :                 ((double)(__m) * ((double)(__m) * ( -0.5-(1./3.) * (double)(__m) + (double)(__n)) +    (double)(__n) +  5. / 6.)) )

#endif /* _FLOPS_H_ */
