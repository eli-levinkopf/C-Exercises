//
// Created by Eli Levinkopf on 12/11/2021.
//

#include "ex3.h"

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

int test_concatenate_vertically ()
{
  double expected_matrix[4][3] = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0},
								  {7.0, 8.0, 9.0}, {10.0, 11.0, 12.0}};
//  Creates an empty matrix
  matrix *top = create_matrix (3, 0);
//  Creates a matrix (4x3)
  matrix *bottom = create_matrix (4, 3);
//  Fills the matrix
  full_matrix (top);
  full_matrix (bottom);
//  Concatenate the empty matrix with non-empty matrix
  matrix *concatenated_mat = concatenate_vertically (top, bottom);

//  prints matrix
  puts ("\n===============================\n");
  print_matrix (top);
  printf ("%zu\n", top->n_rows);
  printf ("%zu\n", top->n_columns);
  puts ("\n===============================\n");
  print_matrix (bottom);
  printf ("%zu\n", bottom->n_rows);
  printf ("%zu\n", bottom->n_columns);
  puts ("\n===============================\n");
//  Check if concatenated_mat = NULL
  if (!concatenated_mat){
	printf("%s\n", "Concatenated_mat = NULL");
  }
  print_matrix (concatenated_mat);
  printf ("%zu\n", concatenated_mat->n_rows);
  printf ("%zu\n", concatenated_mat->n_columns);
  puts ("\n===============================\n");

//  Checking the matrix
  for (size_t i = 0; i < concatenated_mat->n_rows; i++)
	{
	  for (size_t j = 0; j < concatenated_mat->n_columns; j++)
		{
		  if (concatenated_mat->data[i][j] != expected_matrix[i][j])
			{
			  fprintf (stderr, "the values in the return matrix from concatenate_vertically is incorrect => fail in test_concatenate_vertically\n");
			  return 0;
			}
		}
	}
  free_matrix (top);
  free_matrix (bottom);
  free_matrix (concatenated_mat);
  return 1;
}

int main ()
{
  test_concatenate_vertically ();
  return 0;
}