/**
 *
 * @file plasmatypes.h
 *
 *  PLASMA types header
 *  PLASMA is a software package provided by Univ. of Tennessee,
 *  Univ. of California Berkeley and Univ. of Colorado Denver
 *
 * @version 2.6.0
 * @author Jakub Kurzak
 * @author Mathieu Faverge
 * @date 2010-11-15
 *
 * Contains all common types to libcoreblas and libplasma.
 *
 **/
#ifndef _PLASMATYPES_H_
#define _PLASMATYPES_H_

/** ****************************************************************************
 *  PLASMA Release number
 **/
#define PLASMA_VERSION_MAJOR 2
#define PLASMA_VERSION_MINOR 6
#define PLASMA_VERSION_MICRO 0

/** ****************************************************************************
 *  PLASMA constants - success & error codes
 **/
#define PLASMA_SUCCESS                 0
#define PLASMA_ERR_NOT_INITIALIZED  -101
#define PLASMA_ERR_REINITIALIZED    -102
#define PLASMA_ERR_NOT_SUPPORTED    -103
#define PLASMA_ERR_ILLEGAL_VALUE    -104
#define PLASMA_ERR_NOT_FOUND        -105
#define PLASMA_ERR_OUT_OF_RESOURCES -106
#define PLASMA_ERR_INTERNAL_LIMIT   -107
#define PLASMA_ERR_UNALLOCATED      -108
#define PLASMA_ERR_FILESYSTEM       -109
#define PLASMA_ERR_UNEXPECTED       -110
#define PLASMA_ERR_SEQUENCE_FLUSHED -111

/** ****************************************************************************
 *  PLASMA types
 **/
typedef int  PLASMA_enum;
typedef int  PLASMA_bool;
typedef long PLASMA_index;
typedef long PLASMA_size;
typedef double PLASMA_Double_t;

/** ****************************************************************************
 *  PLASMA constants - precisions
 **/
#define PlasmaByte          0
#define PlasmaInteger       1
#define PlasmaRealFloat     2
#define PlasmaRealDouble    3
#define PlasmaComplexFloat  4
#define PlasmaComplexDouble 5

/** ****************************************************************************
 *
 *  PLASMA constants - CBLAS & LAPACK
 *  The naming and numbering is consistent with:
 *
 *    1) CBLAS from Netlib (http://www.netlib.org/blas/blast-forum/cblas.tgz),
 *    2) C Interface to LAPACK from Netlib (http://www.netlib.org/lapack/lapwrapc/).
 *
 **/
#define PlasmaRM            101
#define PlasmaCM            102
#define PlasmaCCRB          103
#define PlasmaCRRB          104
#define PlasmaRCRB          105
#define PlasmaRRRB          106

#define PlasmaNoTrans       111
#define PlasmaTrans         112
#define PlasmaConjTrans     113

#define PlasmaUpper         121
#define PlasmaLower         122
#define PlasmaUpperLower    123

#define PlasmaNonUnit       131
#define PlasmaUnit          132

#define PlasmaLeft          141
#define PlasmaRight         142

#define PlasmaOneNorm       171
#define PlasmaRealOneNorm   172
#define PlasmaTwoNorm       173
#define PlasmaFrobeniusNorm 174
#define PlasmaInfNorm       175
#define PlasmaRealInfNorm   176
#define PlasmaMaxNorm       177
#define PlasmaRealMaxNorm   178

#define PlasmaDistUniform   201
#define PlasmaDistSymmetric 202
#define PlasmaDistNormal    203

#define PlasmaHermGeev      241
#define PlasmaHermPoev      242
#define PlasmaNonsymPosv    243
#define PlasmaSymPosv       244

#define PlasmaNoPacking     291
#define PlasmaPackSubdiag   292
#define PlasmaPackSupdiag   293
#define PlasmaPackColumn    294
#define PlasmaPackRow       295
#define PlasmaPackLowerBand 296
#define PlasmaPackUpeprBand 297
#define PlasmaPackAll       298

#define PlasmaNoVec         301
#define PlasmaVec           302
#define PlasmaIvec          303
#define PlasmaAllVec        304

#define PlasmaForward       391
#define PlasmaBackward      392

#define PlasmaColumnwise    401
#define PlasmaRowwise       402

#define PlasmaW             501
#define PlasmaA2            502

/**
 * Type of matrices that can be generated with PLASMA_zplrntx family
 * functions. (See PLASMA_zplrntx() for more details)
 * The list is coming from the LAWN 263.
 */
enum matrix_type_e {
    PlasmaMatrixRandom    = 0,
    PlasmaMatrixHadamard  = 1,
    PlasmaMatrixHouse     = 2,
    PlasmaMatrixParter    = 3,
    PlasmaMatrixRis       = 4,
    PlasmaMatrixKms       = 5,
    PlasmaMatrixToeppen   = 6,   /* Unavailable */
    PlasmaMatrixCondex    = 7,
    PlasmaMatrixMoler     = 8,
    PlasmaMatrixCircul    = 9,
    PlasmaMatrixRandcorr  = 10,  /* Unavailable */
    PlasmaMatrixPoisson   = 11,  /* Unavailable */
    PlasmaMatrixHankel    = 12,
    PlasmaMatrixJordbloc  = 13,  /* Unavailable */
    PlasmaMatrixCompan    = 14,
    PlasmaMatrixPei       = 15,  /* Unavailable */
    PlasmaMatrixRandcolu  = 16,  /* Unavailable */
    PlasmaMatrixSprandn   = 17,  /* Unavailable */
    PlasmaMatrixRiemann   = 18,
    PlasmaMatrixCompar    = 19,  /* Unavailable */
    PlasmaMatrixTridiag   = 20,  /* Unavailable */
    PlasmaMatrixChebspec  = 21,  /* Unavailable */
    PlasmaMatrixLehmer    = 22,
    PlasmaMatrixToeppd    = 23,
    PlasmaMatrixMinij     = 24,
    PlasmaMatrixRandsvd   = 25,  /* Unavailable */
    PlasmaMatrixForsythe  = 26,  /* Unavailable */
    PlasmaMatrixFiedler   = 27,
    PlasmaMatrixDorr      = 28,
    PlasmaMatrixDemmel    = 29,
    PlasmaMatrixChebvand  = 30,
    PlasmaMatrixInvhess   = 31,
    PlasmaMatrixProlate   = 32,  /* Unavailable */
    PlasmaMatrixFrank     = 33,  /* Unavailable */
    PlasmaMatrixCauchy    = 34,
    PlasmaMatrixHilb      = 35,
    PlasmaMatrixLotkin    = 36,
    PlasmaMatrixKahan     = 37,  /* Unavailable */
    PlasmaMatrixOrthog    = 38,
    PlasmaMatrixWilkinson = 39,
    PlasmaMatrixFoster    = 40,
    PlasmaMatrixWright    = 41,
    PlasmaMatrixLangou    = 42
};

/** ****************************************************************************
 * PLASMA Complex numbers
 **/
#define PLASMA_HAS_COMPLEX_H 1

typedef float  _Complex PLASMA_Complex32_t;
typedef double _Complex PLASMA_Complex64_t;

/* Sun doesn't ship the complex.h header. Sun Studio doesn't have it and older GCC compilers don't have it either. */
#if defined(__SUNPRO_C) || defined(__SUNPRO_CC) || defined(sun) || defined(__sun)
#undef PLASMA_HAS_COMPLEX_H
#endif

#if (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 1))
#define PLASMA_DEPRECATED  __attribute__((__deprecated__))
#else
#define PLASMA_DEPRECATED
#endif /* __GNUC__ */

#ifdef PLASMA_HAS_COMPLEX_H
#include <complex.h>

#else

#ifdef __cplusplus
extern "C" {
#endif

/* These declarations will not clash with what C++ provides because the names in C++ are name-mangled. */
extern double cabs(PLASMA_Complex64_t z);
extern PLASMA_Complex64_t conj(PLASMA_Complex64_t z);
extern float cabsf(PLASMA_Complex32_t z);
extern double cimag(PLASMA_Complex64_t z);
extern double creal(PLASMA_Complex64_t z);

#ifdef __cplusplus
}
#endif
#endif /* defined(PLASMA_HAS_COMPLEX_H) */

#endif /* _PLASMATYPES_H_ */

