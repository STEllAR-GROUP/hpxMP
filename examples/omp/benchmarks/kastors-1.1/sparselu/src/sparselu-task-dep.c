/**********************************************************************************************/
/*  This program is part of the Barcelona OpenMP Tasks Suite                                  */
/*  Copyright (C) 2009 Barcelona Supercomputing Center - Centro Nacional de Supercomputacion  */
/*  Copyright (C) 2009 Universitat Politecnica de Catalunya                                   */
/*                                                                                            */
/*  This program is free software; you can redistribute it and/or modify                      */
/*  it under the terms of the GNU General Public License as published by                      */
/*  the Free Software Foundation; either version 2 of the License, or                         */
/*  (at your option) any later version.                                                       */
/*                                                                                            */
/*  This program is distributed in the hope that it will be useful,                           */
/*  but WITHOUT ANY WARRANTY; without even the implied warranty of                            */
/*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                             */
/*  GNU General Public License for more details.                                              */
/*                                                                                            */
/*  You should have received a copy of the GNU General Public License                         */
/*  along with this program; if not, write to the Free Software                               */
/*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA            */
/**********************************************************************************************/

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include "sparselu.h"


void sparselu_par_call(float **BENCH, int matrix_size, int submatrix_size)
{
    int ii, jj, kk;

#pragma omp parallel private(kk,ii,jj) shared(BENCH)
#pragma omp single /* nowait */
    {
        /*#pragma omp task untied*/
        for (kk=0; kk<matrix_size; kk++)
        {
#pragma omp task firstprivate(kk) shared(BENCH) depend(inout: BENCH[kk*matrix_size+kk:submatrix_size*submatrix_size])
            lu0(BENCH[kk*matrix_size+kk], submatrix_size);
            for (jj=kk+1; jj<matrix_size; jj++)
                if (BENCH[kk*matrix_size+jj] != NULL)
                {
#pragma omp task firstprivate(kk, jj) shared(BENCH) depend(in: BENCH[kk*matrix_size+kk:submatrix_size*submatrix_size]) depend(inout: BENCH[kk*matrix_size+jj:submatrix_size*submatrix_size])
                    fwd(BENCH[kk*matrix_size+kk], BENCH[kk*matrix_size+jj], submatrix_size);
                }
            for (ii=kk+1; ii<matrix_size; ii++)
                if (BENCH[ii*matrix_size+kk] != NULL)
                {
#pragma omp task firstprivate(kk, ii) shared(BENCH) depend(in: BENCH[kk*matrix_size+kk:submatrix_size*submatrix_size]) depend(inout: BENCH[ii*matrix_size+kk:submatrix_size*submatrix_size])
                    bdiv (BENCH[kk*matrix_size+kk], BENCH[ii*matrix_size+kk], submatrix_size);
                }

            for (ii=kk+1; ii<matrix_size; ii++)
                if (BENCH[ii*matrix_size+kk] != NULL)
                    for (jj=kk+1; jj<matrix_size; jj++)
                        if (BENCH[kk*matrix_size+jj] != NULL)
                        {
                            if (BENCH[ii*matrix_size+jj]==NULL) BENCH[ii*matrix_size+jj] = allocate_clean_block(submatrix_size);
#pragma omp task firstprivate(kk, jj, ii) shared(BENCH) \
                            depend(in: BENCH[ii*matrix_size+kk:submatrix_size*submatrix_size], BENCH[kk*matrix_size+jj:submatrix_size*submatrix_size]) \
                            depend(inout: BENCH[ii*matrix_size+jj:submatrix_size*submatrix_size])
                            bmod(BENCH[ii*matrix_size+kk], BENCH[kk*matrix_size+jj], BENCH[ii*matrix_size+jj], submatrix_size);
                        }

        }
#pragma omp taskwait
    }
}
