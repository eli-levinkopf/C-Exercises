//
// Created by Eli Levinkopf on 04/11/2021.
//

#include "ex3.h"

/**
 * Checks if the start and end values for the rows and columns are valid
 * @param mat A pointer to the matrix
 * @param row_start index for starting the sub matrix rows
 * @param row_end index for ending the sub matrix rows
 * @param col_start index for starting the sub matrix cols
 * @param col_end index for ending the sub matrix cols
 * @param num_rows Pointer to number of row in the sub matrix
 * @param num_cols Pointer to number of columns in the sub matrix
 */
void check_index_for_slice (matrix *matrix, size_t row_start, size_t row_end,
							size_t col_start, size_t col_end, size_t *num_rows,
							size_t *num_cols);

/**
 * Allocation a memory to a two-dimensional (of double) array according to the
 * rows_size and col_size. If the allocation fails, the function frees all the
 * allocated so far
 * @param mat A pointer to the matrix
 * @param rows_size The number of rows in two-dimensional array
 * @param col_size The number of columns in two-dimensional array
 * @return A pointer to a two-dimensional array, NULL if the allocation failed
 */
double **data_allocation (matrix *mat, size_t rows_size, size_t col_size);

/**
 * Checks whether the indexes of the two matrices are valid - for
 * concatenate_vertically checks if the number of cols of the two matrices is
 * equal and for concatenate_horizontally checks if the number of rows of the
 * two matrices is equal. And finally calculates the number of rows and
 * columns of the concatenation matrix.
 * @param first_matrix Pointer to the first matrix to concatenate
 * @param second_matrix Pointer to the second matrix to concatenate
 * @param num_rows Pointer to the number of rows in the concatenation matrix.
 * @param num_cols Pointer to the number of cols in the concatenation matrix.
 * @param mode Flag 'h' for horizontally and 'v' for vertically
 * @return 1 if the indexes of the two matrices are valid, 0 otherwise.
 */
int get_index_for_concatenation (matrix *first_matrix,
								 matrix *second_matrix, size_t *num_rows,
								 size_t *num_cols, char mode);

matrix *create_matrix (size_t n_rows, size_t n_columns)
{
  matrix *new_matrix = calloc (1, sizeof (matrix));
  if (!new_matrix)
	{

	  fprintf (stderr, ALLOCATION_ERROR);
	  return NULL;
	}
  if (n_rows == EMPTY || n_columns == EMPTY)
	{
	  new_matrix->n_rows = EMPTY, new_matrix->n_columns = EMPTY;
	  new_matrix->data = NULL;
	  return new_matrix;
	}
  double **data = data_allocation (new_matrix, n_rows, n_columns);
  if (!data)
	{
	  return NULL;
	}
  for (size_t i = 0; i < n_rows; i++)
	{
	  new_matrix->data[i] = calloc (n_columns, sizeof (double));
	  if (!new_matrix->data[i])
		{
		  new_matrix->n_rows = i;
		  free_matrix (new_matrix);
		  fprintf (stderr, ALLOCATION_ERROR);
		  return NULL;
		}
	}
  return new_matrix;
}

double *get_by_index (matrix *mat, size_t row_index, size_t col_index)
{
  if (row_index >= mat->n_rows || col_index >= mat->n_columns)
	{
	  fprintf (stderr, INVALID_INDEX);
	  return NULL;
	}
  return &mat->data[row_index][col_index];
}

matrix *slice (matrix *mat, size_t row_start,
			   size_t row_end, size_t col_start, size_t col_end)
{
  size_t num_rows = row_end - row_start, num_cols = col_end - col_start;
  check_index_for_slice (mat, row_start, row_end, col_start,
						 col_end, &num_rows, &num_cols);
  matrix *sub_mat = create_matrix (num_rows, num_cols);
  if (!sub_mat)
	{
	  return NULL;
	}
  for (size_t i = 0; i < sub_mat->n_rows; i++)
	{
	  for (size_t j = 0; j < sub_mat->n_columns; j++)
		{
		  sub_mat->data[i][j] = mat->data[i + row_start][j + col_start];
		}
	}
  return sub_mat;
}

matrix *concatenate_vertically (matrix *top, matrix *bottom)
{
  size_t num_rows = EMPTY, num_cols = EMPTY;
  char mode = VERTICALLY;
  if (!get_index_for_concatenation (top, bottom, &num_rows, &num_cols, mode))
	{
	  return NULL;
	}
  matrix *vertical_concatenated_mat = create_matrix (num_rows, num_cols);
  if (!vertical_concatenated_mat)
	{
	  return NULL;
	}
  for (size_t i = 0; i < vertical_concatenated_mat->n_rows; i++)
	{
	  if (i < top->n_rows)
		{
		  for (size_t j = 0; j < top->n_columns; j++)
			{
			  vertical_concatenated_mat->data[i][j] = top->data[i][j];
			}
		}
	  else
		{
		  for (size_t k = 0; k < bottom->n_columns; k++)
			{
			  vertical_concatenated_mat->data[i][k] =
				  bottom->data[i - top->n_rows][k];
			}
		}
	}
  return vertical_concatenated_mat;
}

matrix *concatenate_horizontally (matrix *left, matrix *right)
{
  size_t num_rows = EMPTY, num_cols = EMPTY;
  char mode = HORIZONTALLY;
  if (!get_index_for_concatenation (left, right, &num_rows, &num_cols, mode))
	{
	  return NULL;
	}
  matrix *horizontal_concatenated_mat = create_matrix (
	  left->n_rows, left->n_columns + right->n_columns);
  if (!horizontal_concatenated_mat)
	{
	  return NULL;
	}
  for (size_t i = 0; i < horizontal_concatenated_mat->n_columns; i++)
	{
	  if (i < left->n_columns)
		{
		  for (size_t j = 0; j < left->n_rows; j++)
			{
			  horizontal_concatenated_mat->data[j][i] = left->data[j][i];
			}
		}
	  else
		{
		  for (size_t k = 0; k < right->n_rows; k++)
			{
			  horizontal_concatenated_mat->data[k][i] =
				  right->data[k][i - left->n_columns];
			}
		}
	}
  return horizontal_concatenated_mat;
}

matrix *transpose (matrix *mat)
{
  matrix *transposed_matrix = create_matrix (mat->n_columns, mat->n_rows);
  if (!transposed_matrix)
	{
	  return NULL;
	}
  for (size_t i = 0; i < transposed_matrix->n_rows; i++)
	{
	  for (size_t j = 0; j < transposed_matrix->n_columns; j++)
		{
		  transposed_matrix->data[i][j] = mat->data[j][i];
		}
	}
  return transposed_matrix;
}

double *ravel (matrix *mat)
{
  size_t vector_size = mat->n_columns * mat->n_rows;
  double *return_vector = malloc (sizeof (double) * vector_size);
  if (!return_vector)
	{
	  fprintf (stderr, ALLOCATION_ERROR);
	  return NULL;
	}
  size_t rows_counter = EMPTY, cols_counter = EMPTY;
  for (size_t i = 0; i < vector_size; i++)
	{
	  return_vector[i] = mat->data[cols_counter][rows_counter];
	  rows_counter++;
	  if (rows_counter == mat->n_columns)
		{
		  rows_counter = EMPTY;
		  cols_counter++;
		}
	}
  return return_vector;
}

void free_matrix (matrix *mat)
{
  if (!mat)
	{
	  return;
	}
  for (size_t i = 0; i < mat->n_rows; i++)
	{
	  free (mat->data[i]);
	}
  free (mat->data);
  free (mat);
}

double **data_allocation (matrix *mat, size_t rows_size, size_t col_size)
{
  double **sub_data = calloc (rows_size, sizeof (double *));
  if (!sub_data)
	{
	  free (mat);
	  fprintf (stderr, ALLOCATION_ERROR);
	  mat = NULL;
	  return NULL;
	}
  mat->data = sub_data;
  mat->n_rows = rows_size;
  mat->n_columns = col_size;
  return sub_data;
}

void check_index_for_slice (matrix *matrix, size_t row_start, size_t row_end,
							size_t col_start, size_t col_end, size_t *num_rows,
							size_t *num_cols)
{
  if (row_start > matrix->n_rows || col_start > matrix->n_columns
	  || row_end <= row_start || col_end <= col_start)
	{
	  *num_rows = EMPTY, *num_cols = EMPTY;
	}
  else if (row_end > matrix->n_rows)
	{
	  *num_rows = matrix->n_rows - row_start;
	}
  if (col_end > matrix->n_columns)
	{
	  *num_cols = matrix->n_columns - col_start;
	}
}

int get_index_for_concatenation (matrix *first_matrix, matrix *second_matrix,
								 size_t *num_rows, size_t *num_cols, char mode)
{
  if (mode == VERTICALLY)
	{
	  if (first_matrix->n_columns != second_matrix->n_columns)
		{
		  fprintf (stderr, INVALID_COLS_NUMBER);
		  return FAILURE;
		}
	  *num_rows = first_matrix->n_rows + second_matrix->n_rows;
	  *num_cols = first_matrix->n_columns;
	}
  else
	{
	  if (first_matrix->n_rows != second_matrix->n_rows)
		{
		  fprintf (stderr, INVALID_ROWS_NUMBER);
		  return FAILURE;
		}
	  *num_cols = first_matrix->n_columns + second_matrix->n_columns;
	  *num_rows = first_matrix->n_rows;
	}

  return SUCCESS;
}
