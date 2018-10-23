/**
 *
 * @generated d Tue Jan  7 11:45:24 2014
 *
 **/
#define _TYPE  double
#define _PREC  double
#define _LAMCH LAPACKE_dlamch_work

#include "omp.h"

#define _NAME  "PLASMA_dpotrf_Tile"
/* See Lawn 41 page 120 */
#define _FMULS FMULS_POTRF( N )
#define _FADDS FADDS_POTRF( N )

#include "./timing.inc"

static double
RunTest(real_Double_t *t_, struct user_parameters* params)
{
    double  t;
    int64_t N     = params->matrix_size;
    int64_t NB    = params->blocksize;
    int check     = params->check;
    int uplo = PlasmaUpper;
    double check_res = 0;

    /* Allocate Data */
    PLASMA_desc *descA = NULL;
    double* ptr = malloc(N * N * sizeof(double));
    PLASMA_Desc_Create(&descA, ptr, PlasmaRealDouble, NB, NB, NB*NB, N, N, 0, 0, N, N);

#pragma omp parallel
#pragma omp master
    plasma_pdplgsy_quark( (double)N, *descA, 51 );

    /* Save A for check */
    double *A = NULL;
    if(check) {
        A = (double*)malloc(N * N * sizeof(double));
        plasma_pdtile_to_lapack_quark(*descA, (void*)A, N);
    }

    /* PLASMA DPOSV */
    START_TIMING();
#pragma omp parallel
#pragma omp master
    plasma_pdpotrf_quark(uplo, *descA);
    STOP_TIMING();

    /* Check the solution */
    if ( check )
    {
        PLASMA_desc *descB = NULL;
        double* ptr = (double*)malloc(N * sizeof(double));
        PLASMA_Desc_Create(&descB, ptr, PlasmaRealDouble, NB, NB, NB*NB, N, 1, 0, 0, N, 1);

        plasma_pdpltmg_seq(* descB, 7672 );
        double* B = (double*)malloc(N * sizeof(double));
        plasma_pdtile_to_lapack_quark(*descB, (void*)B, N);

        PLASMA_dpotrs_Tile( uplo, descA, descB );

        double* X = (double*)malloc(N * sizeof(double));
        plasma_pdtile_to_lapack_quark(*descB, (void*)X, N);

        check_res = d_check_solution(N, N, 1, A, N, B, X, N);

        PASTE_CODE_FREE_MATRIX( descB );
        free( A );
        free( B );
        free( X );
    }

    PASTE_CODE_FREE_MATRIX( descA );

    return check_res;
}
