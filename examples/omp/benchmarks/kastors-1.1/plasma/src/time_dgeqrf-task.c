/**
 *
 * @generated d Tue Jan  7 11:45:25 2014
 *
 **/
#define _TYPE  double
#define _PREC  double
#define _LAMCH LAPACKE_dlamch_work

#define _NAME  "PLASMA_dgeqrf_Tile"
/* See Lawn 41 page 120 */
#define _FMULS FMULS_GEQRF( M, N )
#define _FADDS FADDS_GEQRF( M, N )

#include "./timing.inc"

static double
RunTest(real_Double_t *t_, struct user_parameters* params)
{
    double t;
    PLASMA_desc *descT;
    int64_t N     = params->matrix_size;
    int64_t IB    = params->iblocksize;
    int64_t NB    = params->blocksize;
    int check     = params->check;
    double check_res = 0;

    /* Allocate Data */
    PLASMA_desc *descA = NULL;
    double *ptr = (double*)malloc(N * N * sizeof(double));
    PLASMA_Desc_Create(&descA, ptr, PlasmaRealDouble, NB, NB, NB*NB, N, N, 0, 0, N, N);

#pragma omp parallel
#pragma omp master
    plasma_pdpltmg_quark(*descA, 5373 );

    /* Save A for check */
    double *A = NULL;
    if ( check ) {
        A = (double*)malloc(N * N * sizeof(double));
        plasma_pdtile_to_lapack_quark(*descA, (void*)A, N);
    }

    /* Allocate Workspace */
    plasma_alloc_ibnb_tile(N, N, PlasmaRealDouble, &descT, IB, NB);

    /* Do the computations */
    START_TIMING();
#pragma omp parallel
#pragma omp master
    plasma_pdgeqrf_quark( *descA, *descT , IB);
    STOP_TIMING();

    /* Check the solution */
    if ( check )
    {
        /* Allocate B for check */
        PLASMA_desc *descB = NULL;
        double* ptr = (double*)malloc(N * sizeof(double));
        PLASMA_Desc_Create(&descB, ptr, PlasmaRealDouble, NB, NB, NB*NB, N, 1, 0, 0, N, 1);

        /* Initialize and save B */
        plasma_pdpltmg_seq(*descB, 2264 );
        double *B = (double*)malloc(N * sizeof(double));
        plasma_pdtile_to_lapack_quark(*descB, (void*)B, N);

        /* Compute the solution */
        PLASMA_dgeqrs_Tile( descA, descT, descB , IB);

        /* Copy solution to X */
        double *X = (double*)malloc(N * sizeof(double));
        plasma_pdtile_to_lapack_quark(*descB, (void*)X, N);

        check_res = d_check_solution(N, N, 1, A, N, B, X, N);

        /* Free checking structures */
        PASTE_CODE_FREE_MATRIX( descB );
        free( A );
        free( B );
        free( X );
    }

    /* Free data */
    PLASMA_Dealloc_Handle_Tile(&descT);
    PASTE_CODE_FREE_MATRIX( descA );

    return check_res;
}
