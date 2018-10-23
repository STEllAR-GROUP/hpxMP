/**
 *
 * @generated d Tue Jan  7 11:45:24 2014
 *
 **/
#define _TYPE  double
#define _PREC  double
#define _LAMCH LAPACKE_dlamch_work

#define _NAME  "PLASMA_dgetrf_Tile"
/* See Lawn 41 page 120 */
#define _FMULS FMULS_GETRF(M, N)
#define _FADDS FADDS_GETRF(M, N)

#include "./timing.inc"

static double
RunTest(real_Double_t *t_, struct user_parameters* params)
{
    double  t;
    int64_t N     = params->matrix_size;
    int64_t NB    = params->blocksize;
    int check     = params->check;
    double check_res = 0;

    /* Allocate Data */
    PLASMA_desc *descA = NULL;
    double* ptr = malloc(N * N * sizeof(double));
    PLASMA_Desc_Create(&descA, ptr, PlasmaRealDouble, NB, NB, NB*NB, N, N, 0, 0, N, N);

    int* piv = (int*)malloc(N * sizeof(double));

#pragma omp parallel
#pragma omp master
    plasma_pdpltmg_quark(*descA, 3456);

    /* Save AT in lapack layout for check */
    double *A = NULL;
    if(check) {
        A = (double*)malloc(N * N * sizeof(double));
        plasma_pdtile_to_lapack_quark(*descA, (void*)A, N);
    }

    START_TIMING();
#pragma omp parallel
#pragma omp master
    plasma_pdgetrf_rectil_quark(*descA, piv);
    STOP_TIMING();

    /* Check the solution */
    if ( check )
    {
        PLASMA_desc *descB = NULL;
        double* ptr = (double*)malloc(N * sizeof(double));
        PLASMA_Desc_Create(&descB, ptr, PlasmaRealDouble, NB, NB, NB*NB, N, 1, 0, 0, N, 1);

        plasma_pdpltmg_seq(*descB, 7732 );
        double* b = (double*)malloc(N * sizeof(double));
        plasma_pdtile_to_lapack_quark(*descB, (void*)b, N);

        PLASMA_dgetrs_Tile( PlasmaNoTrans, descA, piv, descB );

        double* x = (double*)malloc(N * sizeof(double));
        plasma_pdtile_to_lapack_quark(*descB, (void*)x, N);

        check_res = d_check_solution(N, N, 1, A, N, b, x, N);

        PASTE_CODE_FREE_MATRIX( descB );
        free(A); free(b); free(x);
    }

    PASTE_CODE_FREE_MATRIX( descA );
    free( piv );

    return check_res;
}
