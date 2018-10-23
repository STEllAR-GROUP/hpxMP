# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <time.h>
# include <string.h>

#if defined(_OPENMP)
# include <omp.h>
#endif

# include "poisson.h"
# include "main.h"
# include "timer.h"


double r8mat_rms(int dx, int dy, double *a_);
void rhs(int dx, int dy, double *f_, int block_size);
void timestamp(void);
double u_exact(double x, double y);
double uxxyy_exact(double x, double y);

/*
 * Purpose:
 *   MAIN is the main program for POISSON_OPENMP.
 * Discussion:
 *   POISSON_OPENMP is a program for solving the Poisson problem.
 *   This program uses OpenMP for parallel execution.
 *   The Poisson equation
 *     - DEL^2 U(X,Y) = F(X,Y)
 *   is solved on the unit square [0,1] x [0,1] using a grid of NX by
 *   NX evenly spaced points.  The first and last points in each direction
 *   are boundary points.
 *   The boundary conditions and F are set so that the exact solution is
 *     U(x,y) = sin ( pi * x * y)
 *   so that
 *     - DEL^2 U(x,y) = pi^2 * ( x^2 + y^2) * sin ( pi * x * y)
 *   The Jacobi iteration is repeatedly applied until convergence is detected.
 *   For convenience in writing the discretized equations, we assume that NX = NY.
 * Licensing:
 *  This code is distributed under the GNU LGPL license.
 * Modified:
 *   14 December 2011
 * Author:
 *   John Burkardt
 */

/******************************************************************************/

void check_params( struct user_parameters* params, int matrix_size, 
                   int block_size, double dx, double dy, double *f_,
                   int niter, double *u_, double *unew_) 
{
    double x, y;
    int i, j;
    double *udiff_ =(double*)malloc(matrix_size * matrix_size * sizeof(double));
    double (*udiff)[matrix_size][matrix_size] = (double (*)[matrix_size][matrix_size])udiff_;
    double (*unew)[matrix_size][matrix_size] = (double (*)[matrix_size][matrix_size])unew_;
    double (*u)[matrix_size][matrix_size] = (double (*)[matrix_size][matrix_size])u_;
    double (*f)[matrix_size][matrix_size] = (double (*)[matrix_size][matrix_size])f_;

    // Check for convergence.
    for (j = 0; j < matrix_size; j++) {
        y = (double) (j) / (double) (matrix_size - 1);
        for (i = 0; i < matrix_size; i++) {
            x = (double) (i) / (double) (matrix_size - 1);
            (*udiff)[i][j] = (*unew)[i][j] - u_exact(x, y);
            if( (*udiff)[i][j] > 1.0E-6 ) { 
                printf("error: %d, %d: %f\n", i, j, (*udiff)[i][j]);
            }
        }
    }
    double error = r8mat_rms(matrix_size, matrix_size, udiff_);

    double error1;
    // Set the right hand side array F.
    rhs(matrix_size, matrix_size, f_, block_size);

    for (j = 0; j < matrix_size; j++) {
        for (i = 0; i < matrix_size; i++) {
            if (i == 0 || i == matrix_size - 1 || j == 0 || j == matrix_size - 1) {
                (*unew)[i][j] = (*f)[i][j];
                (*u)[i][j] = (*f)[i][j];
            } else {
                (*unew)[i][j] = 0.0;
                (*u)[i][j] = 0.0;
            }
        }
    }

    sweep_seq(matrix_size, matrix_size, dx, dy, f_, 0, niter, u_, unew_);

    // Check for convergence.
    for (j = 0; j < matrix_size; j++) {
        y = (double) (j) / (double) (matrix_size - 1);
        for (i = 0; i < matrix_size; i++) {
            x = (double) (i) / (double) (matrix_size - 1);
            (*udiff)[i][j] = (*unew)[i][j] - u_exact(x, y);
            if( (*udiff)[i][j] > 1.0E-6 ) { 
                printf("error: %d, %d: %f\n", i, j, (*udiff)[i][j]);
            }
        }
    }
    error1 = r8mat_rms(matrix_size, matrix_size, udiff_);
    params->succeed = fabs(error - error1) < 1.0E-6;
    if(!params->succeed) {
        printf("error = %f, error1 = %f\n", error, error1);
    }
    free(udiff_);
}

double run(struct user_parameters* params)
{
    int matrix_size = params->matrix_size;
    if (matrix_size <= 0) {
        matrix_size = 512;
        params->matrix_size = matrix_size;
    }
    int block_size = params->blocksize;
    if (block_size <= 0) {
        block_size = 128;
        params->blocksize = block_size;
    }
    if ( (matrix_size % block_size) || (matrix_size % block_size) ) {
        params->succeed = 0;
        params->string2display = "*****ERROR: blocsize must divide NX and NY";
        return 0;
    }
    int niter = params->titer;
    if (niter <= 0) {
        niter = 4;
        params->titer = niter;
    }
    int ii,i,jj,j;
    double *f_ = (double*)malloc(matrix_size * matrix_size * sizeof(double));
    double (*f)[matrix_size][matrix_size] = (double (*)[matrix_size][matrix_size])f_;
    double *u_ = (double*)malloc(matrix_size * matrix_size * sizeof(double));
    double *unew_ = (double*)malloc(matrix_size * matrix_size * sizeof(double));
    double (*unew)[matrix_size][matrix_size] = (double (*)[matrix_size][matrix_size])unew_;
    double (*u)[matrix_size][matrix_size] = (double (*)[matrix_size][matrix_size])u_;

    double dx = 1.0 / (double) (matrix_size - 1);
    double dy = 1.0 / (double) (matrix_size - 1);

    rhs(matrix_size, matrix_size, f_, block_size);

    //Set the initial solution estimate UNEW.
    //We are "allowed" to pick up the boundary conditions exactly.
#pragma omp parallel
#pragma omp master
    for (j = 0; j < matrix_size; j+= block_size)
        for (i = 0; i < matrix_size; i+= block_size)
#pragma omp task firstprivate(i,j) private(ii,jj)
            for (jj=j; jj<j+block_size; ++jj)
                for (ii=i; ii<i+block_size; ++ii) {
                    if (ii == 0 || ii == matrix_size - 1 || jj == 0 || jj == matrix_size - 1) {
                        (*unew)[ii][jj] = (*f)[ii][jj];
                        (*u)[ii][jj] = (*f)[ii][jj];
                    } else {
                        (*unew)[ii][jj] = 0.0;
                        (*u)[ii][jj] = 0.0;
                    }
                }
    /// KERNEL INTENSIVE COMPUTATION
    START_TIMER;
#ifndef _OPENMP
    sweep_seq(matrix_size, matrix_size, dx, dy, f_, 0, niter, u_, unew_);
#else
    sweep(matrix_size, matrix_size, dx, dy, f_, 0, niter, u_, unew_, block_size);
#endif
    END_TIMER;

#ifdef _OPENMP
    if(params->check) {
        check_params(params, matrix_size, block_size, dx, dy, f_, niter, u_, unew_) ;
    }
#else
    params->succeed = 1;
#endif
    free(f_);
    free(u_);
    free(unew_);
    return TIMER;
}

/* R8MAT_RMS returns the RMS norm of a vector stored as a matrix. */
double r8mat_rms(int matrix_size, int matrix_size2, double *a_) {
    double (*a)[matrix_size][matrix_size] = (double (*)[matrix_size][matrix_size])a_;
    int i;
    int j;
    double v;

    v = 0.0;

    for (j = 0; j < matrix_size; j++) {
        for (i = 0; i < matrix_size; i++) {
            v = v + (*a)[i][j] * (*a)[i][j];
        }
    }
    v = sqrt(v / (double) (matrix_size * matrix_size));

    return v;
}

/* RHS initializes the right hand side "vector". */
void rhs(int matrix_size, int matrix_size2, double *f_, int block_size)
{
    double (*f)[matrix_size][matrix_size] = (double (*)[matrix_size][matrix_size])f_;
    int i,ii;
    int j,jj;
    double x;
    double y;

    // The "boundary" entries of F store the boundary values of the solution.
    // The "interior" entries of F store the right hand sides of the Poisson equation.

#pragma omp parallel
#pragma omp master
    //for collapse(2)
    for (j = 0; j < matrix_size; j+=block_size)
        for (i = 0; i < matrix_size; i+=block_size)
#pragma omp task firstprivate(block_size,i,j,matrix_size) private(ii,jj,x,y)
            for (jj=j; jj<j+block_size; ++jj)
            {
                y = (double) (jj) / (double) (matrix_size - 1);
                for (ii=i; ii<i+block_size; ++ii)
                {
                    x = (double) (ii) / (double) (matrix_size - 1);
                    if (ii == 0 || ii == matrix_size - 1 || jj == 0 || jj == matrix_size - 1)
                        (*f)[ii][jj] = u_exact(x, y);
                    else
                        (*f)[ii][jj] = - uxxyy_exact(x, y);
                }
            }
}

/* Evaluates the exact solution. */
double u_exact(double x, double y) {
    double pi = 3.141592653589793;
    double value;

    value = sin(pi * x * y);

    return value;
}

/* Evaluates (d/dx d/dx + d/dy d/dy) of the exact solution. */
double uxxyy_exact(double x, double y) {
    double pi = 3.141592653589793;
    double value;

    value = - pi * pi * (x * x + y * y) * sin(pi * x * y);

    return value;
}

