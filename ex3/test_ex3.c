//
// Created by Eli Levinkopf on 05/11/2021.
//
#include "ex3.h"
#define FAILURE 0
#define SUCCESS 1

void full_matrix (matrix *mat)
{
  double sum = 1;
  for (size_t i = 0; i < mat->n_rows; i++)
	{
	  for (size_t j = 0; j < mat->n_columns; j++)
		{
		  mat->data[i][j] = sum;
		  sum++;
		}
	}
}

void print_matrix (matrix *mat)
{
  for (size_t i = 0; i < mat->n_rows; i++)
	{
	  for (size_t j = 0; j < mat->n_columns; j++)
		{
		  printf ("%f  ", mat->data[i][j]);
		}
	  puts ("\n");
	}
}

int test_create_matrix ()
{
  size_t rows[4] = {3, 1, 0, 4}, cols[4] = {4, 4, 1, 0};
  size_t expected_rows[4] = {3, 1, 0, 0}, expected_cols[4] = {4, 4, 0, 0};
  for (int i = 0; i < 4; i++)
	{
	  matrix *mat = create_matrix (rows[i], cols[i]);
	  if (mat->n_rows != expected_rows[i]
		  || mat->n_columns != expected_cols[i])
		{
		  fprintf (stderr, "The number of rows or columns is incorrect => fail in test_create_matrix\n");
		  free_matrix (mat);
		  return FAILURE;
		}
	  if ((i == 2 || i == 3) && mat->data)
		{
		  fprintf (stderr, "The number of rows or columns is 0 and matrix->data != NULL => fail in test_create_matrix\n");
		  free_matrix (mat);
		  return FAILURE;
		}
	  free_matrix (mat);
	}
  printf ("%s", "pass test_create_matrix\n");
  return SUCCESS;
}

int test_by_index ()
{
  size_t rows = 3, cols = 4;
  matrix *mat = create_matrix (rows, cols);
  size_t rows_index[4] = {0, 1, 2, 3}, cols_index[4] = {0, 3, 4, 2};
  full_matrix (mat);
  double expected_val[2] = {1.0, 8.0};
  for (int i = 0; i < 4; i++)
	{
	  if ((i == 2 || i == 3)
		  && get_by_index (mat, rows_index[i], cols_index[i]))
		{
		  fprintf (stderr, "rows_index or cols_index is invalid and get_by_index return value != NULL => fail in test_by_index\n");
		  free_matrix (mat);
		  return FAILURE;
		}
	  if ((i == 0 || i == 1) && (expected_val[i]
								 != *get_by_index (mat, rows_index[i], cols_index[i])))
		{
		  fprintf (stderr, "get_by_index return incorrect value => fail in test_by_index\n");
		  free_matrix (mat);
		  return FAILURE;
		}
	}
  free_matrix (mat);
  printf ("%s", "pass test_by_index\n");
  return SUCCESS;
}

int test_slice ()
{
  size_t rows = 3, cols = 4;
  matrix *mat = create_matrix (rows, cols);
  full_matrix (mat);
  size_t row_start[5] = {0, 1, 1, 4, 0};
  size_t row_end[5] = {2, 2, 4, 1, 2};
  size_t cols_start[5] = {1, 0, 1, 5, 3};
  size_t cols_end[5] = {4, 4, 5, 1, 1};
  size_t expected_rows[5] = {2, 1, 2, 0, 0};
  size_t expected_cols[5] = {3, 4, 3, 0, 0};
  double expected_slice_1[2][3] = {{2.0, 3.0, 4.0}, {6.0, 7.0, 8.0}};
  double expected_slice_2[1][4] = {{5.0, 6.0, 7.0, 8.0}};
  double expected_slice_3[2][3] = {{6.0, 7.0, 8.0}, {10.0, 11.0, 12.0}};
  for (int k = 0; k < 5; k++)
	{
	  matrix *slice_mat = slice (mat, row_start[k], row_end[k], cols_start[k], cols_end[k]);
	  if (slice_mat->n_rows != expected_rows[k]
		  || slice_mat->n_columns != expected_cols[k])
		{
		  fprintf (stderr, "matrix->n_rows or matrix->n_columns in the return matrix from slice is incorrect => fail in test_slice\n");
		  free_matrix (mat);
		  free_matrix (slice_mat);
		  return FAILURE;
		}
	  if (k == 0)
		{
		  for (size_t i = 0; i < slice_mat->n_rows; i++)
			{
			  for (size_t j = 0; j < slice_mat->n_columns; j++)
				{
				  if (slice_mat->data[i][j] != expected_slice_1[i][j])
					{
					  fprintf (stderr, "the values in the return matrix from slice is incorrect => fail in test_slice\n");
					  free_matrix (mat);
					  free_matrix (slice_mat);
					  return FAILURE;
					}
				}
			}
		}
	  else if (k == 1)
		{
		  for (size_t i = 0; i < slice_mat->n_rows; i++)
			{
			  for (size_t j = 0; j < slice_mat->n_columns; j++)
				{
				  if (slice_mat->data[i][j] != expected_slice_2[i][j])
					{
					  fprintf (stderr, "the values in the return matrix from slice is incorrect => fail in test_slice\n");
					  free_matrix (mat);
					  free_matrix (slice_mat);
					  return FAILURE;
					}
				}
			}
		}
	  else if (k == 2)
		{
		  for (size_t i = 0; i < slice_mat->n_rows; i++)
			{
			  for (size_t j = 0; j < slice_mat->n_columns; j++)
				{
				  if (slice_mat->data[i][j] != expected_slice_3[i][j])
					{
					  fprintf (stderr, "the values in the return matrix from slice is incorrect => fail in test_slice\n");
					  free_matrix (mat);
					  free_matrix (slice_mat);
					  return FAILURE;
					}
				}
			}
		}
	  else if ((k == 3 || k == 4) && slice_mat->data)
		{
		  fprintf (stderr, "invalid index and matrix->data != NULL (in the return matrix from slice) => fail in test_slice\n");
		  free_matrix (mat);
		  free_matrix (slice_mat);
		  return FAILURE;
		}
	  free_matrix (slice_mat);
	}
  free_matrix (mat);
  printf ("%s", "pass test_slice\n");
  return SUCCESS;
}

int test_concatenate_vertically ()
{
  size_t rows_top[3] = {4, 3, 0};
  size_t cols_top[3] = {3, 1, 3};
  size_t rows_bottom[3] = {2, 2, 4};
  size_t cols_bottom[3] = {3, 1, 3};
  size_t expected_rows[2] = {6, 5};
  size_t expected_cols[2] = {3, 1};
  double expected_matrix_1[6][3] = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0},
									{7.0, 8.0, 9.0}, {10.0, 11.0, 12.0},
									{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
  double expected_matrix_2[5][1] = {{1.0}, {2.0}, {3.0}, {1.0}, {2.0}};
  for (size_t k = 0; k < 3; k++)
	{
	  matrix *top = create_matrix (rows_top[k], cols_top[k]);
	  matrix *bottom = create_matrix (rows_bottom[k], cols_bottom[k]);
	  full_matrix (top);
	  full_matrix (bottom);
	  matrix *concatenated_mat = concatenate_vertically (top, bottom);
	  if (k == 0 || k == 1)
		{
		  if (concatenated_mat->n_rows != expected_rows[k]
			  || concatenated_mat->n_columns != expected_cols[k])
			{
			  fprintf (stderr, "matrix->n_rows or matrix->n_columns in the return matrix from concatenate_vertically is incorrect => fail in test_concatenate_vertically\n");
			  return FAILURE;
			}
		}
	  if (k == 0)
		{
		  for (size_t i = 0; i < concatenated_mat->n_rows; i++)
			{
			  for (size_t j = 0; j < concatenated_mat->n_columns; j++)
				{
				  if (concatenated_mat->data[i][j] != expected_matrix_1[i][j])
					{
					  fprintf (stderr, "the values in the return matrix from concatenate_vertically is incorrect => fail in test_concatenate_vertically\n");
					  return FAILURE;
					}
				}
			}
		}
	  else if (k == 1)
		{
		  for (size_t i = 0; i < concatenated_mat->n_rows; i++)
			{
			  for (size_t j = 0; j < concatenated_mat->n_columns; j++)
				{
				  if (concatenated_mat->data[i][j] != expected_matrix_2[i][j])
					{
					  fprintf (stderr, "the values in the return matrix from concatenate_vertically is incorrect => fail in test_concatenate_vertically\n");
					  return FAILURE;
					}
				}
			}
		}
	  else if (k == 2 && concatenated_mat)
		{
		  fprintf (stderr, "top->columns != bottom->columns and concatenated_mat != NULL (in the return matrix from concatenate_horizontally) => fail in test_concatenate_horizontally\n");
		  return FAILURE;
		}
	  free_matrix (top);
	  free_matrix (bottom);
	  if (concatenated_mat)
		{
		  free_matrix (concatenated_mat);
		}
	}
  printf ("%s", "pass test_concatenate_vertically\n");
  return SUCCESS;
}

int test_concatenate_horizontally ()
{
  size_t rows_left[3] = {3, 1, 3};
  size_t cols_left[3] = {3, 4, 0};
  size_t rows_right[3] = {3, 1, 3};
  size_t cols_right[3] = {4, 5, 4};
  size_t expected_rows[2] = {3, 1};
  size_t expected_cols[2] = {7, 9};
  double expected_matrix_1[3][7] = {{1.0, 2.0, 3.0, 1.0, 2.0, 3.0, 4.0},
									{4.0, 5.0, 6.0, 5.0, 6.0, 7.0, 8.0},
									{7.0, 8.0, 9.0, 9.0, 10.0, 11.0, 12.0}};
  double expected_matrix_2[1][9] =
	  {{1.0, 2.0, 3.0, 4.0, 1.0, 2.0, 3.0, 4.0, 5.0}};
  for (size_t k = 0; k < 3; k++)
	{
	  matrix *left = create_matrix (rows_left[k], cols_left[k]);
	  matrix *right = create_matrix (rows_right[k], cols_right[k]);
	  full_matrix (left);
	  full_matrix (right);
	  matrix *concatenated_mat = concatenate_horizontally (left, right);
	  if (k == 0 || k == 1)
		{
		  if (concatenated_mat->n_rows != expected_rows[k]
			  || concatenated_mat->n_columns != expected_cols[k])
			{
			  fprintf (stderr, "matrix->n_rows or matrix->n_columns in the return matrix from concatenate_horizontally is incorrect => fail in test_concatenate_horizontally\n");
			  free_matrix (right);
			  free_matrix (left);
			  free_matrix (concatenated_mat);
			  return FAILURE;
			}
		}
	  if (k == 0)
		{
		  for (size_t i = 0; i < concatenated_mat->n_rows; i++)
			{
			  for (size_t j = 0; j < concatenated_mat->n_columns; j++)
				{
				  if (concatenated_mat->data[i][j] != expected_matrix_1[i][j])
					{
					  fprintf (stderr, "the values in the return matrix from concatenate_horizontally is incorrect => fail in test_concatenate_horizontally\n");
					  free_matrix (right);
					  free_matrix (left);
					  free_matrix (concatenated_mat);
					  return FAILURE;
					}
				}
			}
		}
	  else if (k == 1)
		{
		  for (size_t i = 0; i < concatenated_mat->n_rows; i++)
			{
			  for (size_t j = 0; j < concatenated_mat->n_columns; j++)
				{
				  if (concatenated_mat->data[i][j] != expected_matrix_2[i][j])
					{
					  fprintf (stderr, "the value in the return matrix from concatenate_horizontally is incorrect => fail in test_concatenate_horizontally\n");
					  free_matrix (right);
					  free_matrix (left);
					  free_matrix (concatenated_mat);
					  return FAILURE;
					}
				}
			}
		}
	  else if (k == 2 && concatenated_mat)
		{
		  fprintf (stderr, "left->rows != right->rows and concatenated_mat != NULL (in the return matrix from concatenate_horizontally) => fail in test_concatenate_horizontally\n");
		  free_matrix (right);
		  free_matrix (left);
		  free_matrix (concatenated_mat);
		  return FAILURE;
		}
	  free_matrix (right);
	  free_matrix (left);
	  if (concatenated_mat)
		{
		  free_matrix (concatenated_mat);
		}
	}
  printf ("%s", "pass test_concatenate_horizontally\n");
  return SUCCESS;
}

int test_transpose ()
{
  size_t rows[4] = {4, 1, 1, 0};
  size_t cols[4] = {3, 1, 5, 2};
  size_t expected_rows[4] = {3, 1, 5, 0};
  size_t expected_cols[4] = {4, 1, 1, 0};
  for (size_t k = 0; k < 4; k++)
	{
	  matrix *mat = create_matrix (rows[k], cols[k]);
	  matrix *transpose_mat = transpose (mat);
	  if (transpose_mat->n_rows != expected_rows[k]
		  || transpose_mat->n_columns != expected_cols[k])
		{
		  fprintf (stderr, "matrix->n_rows or matrix->n_columns in the return matrix from transpose is incorrect => fail in test_transpose\n");
		  free_matrix (mat);
		  free_matrix (transpose_mat);
		  return FAILURE;
		}
	  for (size_t i = 0; i < transpose_mat->n_rows; i++)
		{
		  for (size_t j = 0; j < transpose_mat->n_columns; j++)
			{
			  if (transpose_mat->data[i][j] != mat->data[j][i])
				{
				  fprintf (stderr, "the value in the return matrix from transpose is incorrect => fail in test_transpose\n");
				  free_matrix (mat);
				  free_matrix (transpose_mat);
				  return FAILURE;
				}
			}
		}
	  free_matrix (mat);
	  free_matrix (transpose_mat);
	}
  printf ("%s", "pass test_transpose\n");
  return SUCCESS;
}

int test_ravel ()
{
  size_t rows[3] = {3, 1, 0};
  size_t cols[3] = {4, 5, 3};
  double expected_vector_1[12] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0,
								  10.0, 11.0, 12.0};
  double expected_vector_2[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
  for (size_t k = 0; k < 3; k++)
	{
	  matrix *mat = create_matrix (rows[k], cols[k]);
	  full_matrix (mat);
	  double *return_vector = ravel (mat);
	  if (k == 0)
		{
		  for (size_t i = 0; i < rows[k] * cols[k]; i++)
			{
			  if (return_vector[i] != expected_vector_1[i])
				{
				  fprintf (stderr, "the value in the return vector from ravel is incorrect => fail in test_ravel\n");
				  free_matrix (mat);
				  free (return_vector);
				  return FAILURE;
				}
			}
		}
	  else if (k == 1)
		{
		  for (size_t i = 0; i < rows[k] * cols[k]; i++)
			{
			  if (return_vector[i] != expected_vector_2[i])
				{
				  fprintf (stderr, "the value in the return vector from ravel is incorrect => fail in test_ravel\n");
				  free_matrix (mat);
				  free (return_vector);
				  return FAILURE;
				}
			}
		}
	  free_matrix (mat);
	  free (return_vector);
	}

  printf ("%s", "pass test_ravel\n");
  return SUCCESS;
}

int main ()
{
  int test_1 = test_create_matrix ();
  int test_2 = test_by_index ();
  int test_3 = test_slice ();
  int test_4 = test_concatenate_vertically ();
  int test_5 = test_concatenate_horizontally ();
  int test_6 = test_transpose ();
  int test_7 = test_ravel ();
  if (test_1 && test_2 && test_3 && test_4 && test_5 && test_6 && test_7)
	{
	  printf ("%s",
			  "\n*******************\n* passed all test *\n*******************\n\n");
	  return 0;
	}
  return 1;
}

