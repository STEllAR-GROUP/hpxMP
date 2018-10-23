#ifndef SPARSELU_H
#define SPARSELU_H

#define EPSILON 1.0E-6



float * allocate_clean_block(int submatrix_size);
void lu0(float *diag, int submatrix_size);
void bdiv(float *diag, float *row, int submatrix_size);
void bmod(float *row, float *col, float *inner, int submatrix_size);
void fwd(float *diag, float *col, int submatrix_size);

void sparselu_seq_call(float **BENCH, int matrix_size, int submatrix_size);
void sparselu_par_call(float **BENCH, int matrix_size, int submatrix_size);

#endif
