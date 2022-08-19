
#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <math.h>
#include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
#define SUCCESS 1
#define FAILURE 0
#define EMPTY 0
#define VERTICALLY 'v'
#define HORIZONTALLY 'h'
#define ALLOCATION_ERROR "ERROR: memory allocation failed\n"
#define INVALID_INDEX "ERROR: row/col index is an invalid index\n"
#define INVALID_COLS_NUMBER "ERROR: the number of columns in top and\
 bottom is not equal\n"
#define INVALID_ROWS_NUMBER "ERROR: the number of rows in left and\
right is not equal\n"
typedef struct matrix {
    double **data;
    size_t n_rows;
    size_t n_columns;
} matrix;


/**
 * create a new matrix (in size n_rows * n_columns) on the heap. If the
 * allocation fails, the function frees all the allocated so far
 * @param n_rows number of rows in the new matrix.
 * @param n_columns number of columns in the new matrix.
 * @return A pointer to the new matrix struct, NULL if the allocation failed
 */
matrix *create_matrix (size_t n_rows, size_t n_columns);

/**
 * Get value based on index.
 * @param matrix A pointer to the matrix
 * @param row_index The row number we want to access
 * @param col_index The column number we want to access
 * @return the value in matrix[row_index,col_index] if the indent is valid,
 * NULL otherwise
 */
double *get_by_index (matrix *mat, size_t row_index, size_t col_index);

/**
 * Creates a new matrix (on the heap) that contains a sub-matrix of the
 * original matrix, according to the index.
 * @param mat A pointer to the matrix
 * @param row_start index for starting the sub matrix rows
 * @param row_end index for ending the sub matrix rows
 * @param col_start index for starting the sub matrix cols
 * @param col_end index for ending the sub matrix cols
 * @return A pointer matrix that contains a sub-matrix from the original
 * matrix as follows: all cells so that their row index is greater than/equal
 * to row_start and less than row_end, and their col index is greater
 * than/equal to col_start and less than col_end. if the index is invali,
 * return matrix with data = NULL and n_rows = n_columns = 0 and NULL if
 * the allocation failed
 */
matrix *slice (matrix *mat, size_t row_start,
               size_t row_end, size_t col_start, size_t col_end);

/**
 * Performs VERTICALLY concatenate matrix on the heap
 * @param top Pointer to the top matrix
 * @param bottom Pointer to the bottom matrix
 * @return Pointer to the concatenate matrix if the n_columns of top matrix
 * and the n_columns of bottom matrix are equal, NULL if not or if the
 * allocation failed
 */
matrix *concatenate_vertically (matrix *top, matrix *bottom);

/**
 * Performs HORIZONTALLY concatenate matrix on the heap
 * @param left Pointer to the left matrix
 * @param right Pointer to the right matrix
 * @return Pointer to the concatenate matrix if the n_rows of left matrix
 * and the n_rows of right matrix are equal, NULL if not or if the
 * allocation failed
 */
matrix *concatenate_horizontally (matrix *left, matrix *right);

/**
 * Creates a new matrix (on the heap) that represents the transpose matrix
 * of the original matrix
 * @param matrix Pointer to the matrix
 * @return Pointer to the represents matrix, NULL if not or if the allocation
 * failed
 */
matrix *transpose (matrix *mat);

/**
 * Creates a one-dimensional vector (on the heap) representing the original
 * matrix. The order in relation to the original matrix  is line by line.
 * @param matrix Pointer to the matrix
 * @return Pointer to the vector, NULL if not or if the allocation failed.
 */
double *ravel (matrix *mat);

/**
 * Frees all the resources of the matrix - data[i], data and matrix
 * @param matrix Pointer to the matrix
 */
void free_matrix (matrix *mat);

#endif //_MATRIX_H_
