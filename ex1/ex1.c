
#ifndef BONUS

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "cipher.h"

#define FORMAT_ERROR "Usage: cipher <encode|decode> <k> <source path file> \
<output path file>\n"
#define INVALID_COMMAND_ERROR "The given command is invalid\n"
#define INVALID_SHIFT_ERROR "The given shifts value is invalid\n"
#define INVALID_FILE_ERROR "The given file is invalid\n"
#define ENCRYPTION_COMMAND "encode"
#define DECRYPTION_COMMAND "decode"
#define MINUS_SIGN '-'
#define BUFFER_SIZE 129
#define FIRST_ARGUMENT 1
#define SECOND_ARGUMENT 2
#define THIRD_ARGUMENT 3
#define FOURTH_ARGUMENT 4
#define ARGUMENTS_NUMBER 5
#define DECIMAL_BASE 10
#define FAILURE 0
/**
 * Check if the given shift (k) is a valid number
 * @param shift given shift (k)
 * @return 1 if shift (k) is a valid number, 0 otherwise
 */
int check_if_shift_isdigit (const char *shift);

/**
 * Check if the given command is a valid command
 * @param command the given command
 * @return 1 if the given command is a valid command, 0 otherwise
 */
int check_command (const char *command);
/**
 * Check if the given paths are valid
 * @param input_file Path to the input file
 * @param output_file Path to the output file
 * @return 1 if the given paths are valid, 0 otherwise
 */
int check_file_path (const char *input_file, const char *output_file);

/**
 * Encryption/decryption the input file content to the output file
 * @param command 'encode' for encryption and 'decode' for decryption
 * @param shift Encryption/decryption key
 * @param input_file Pointer to the input file
 * @param output_file Pointer to the output file
 * @return EXIT_FAILURE (1) if one of the files is invalid path, 0 otherwise
 */
int
cipher (const char *command, int shift, FILE *input_file, FILE *output_file);

int main (int argc, const char *argv[])
{
  if (argc != ARGUMENTS_NUMBER)
    {
      fprintf (stderr, "%s", FORMAT_ERROR);
      return EXIT_FAILURE;
    }
  if (check_if_shift_isdigit (argv[SECOND_ARGUMENT]) == FAILURE)
    {
      fprintf (stderr, "%s", INVALID_SHIFT_ERROR);
      return EXIT_FAILURE;
    }
  if (check_command (argv[FIRST_ARGUMENT]) == FAILURE)
    {
      fprintf (stderr, "%s", INVALID_COMMAND_ERROR);
      return EXIT_FAILURE;
    }
  if (check_file_path (argv[THIRD_ARGUMENT], argv[FOURTH_ARGUMENT]) == FAILURE)
    {
      fprintf (stderr, "%s", INVALID_FILE_ERROR);
      return EXIT_FAILURE;
    }
  FILE *fp_input = fopen (argv[THIRD_ARGUMENT], "r");
  FILE *fp_output = fopen (argv[FOURTH_ARGUMENT], "w");
  if (fp_input == NULL || fp_output == NULL)
    {
      if (fp_output == NULL && fp_input != NULL)
        {
          fclose (fp_input);
        }
      if (fp_input == NULL && fp_output != NULL)
        {
          fclose (fp_output);
        }
      fprintf (stderr, "%s", INVALID_FILE_ERROR);
      return EXIT_FAILURE;
    }
  int shift = strtol (argv[SECOND_ARGUMENT], NULL, DECIMAL_BASE);
  cipher (argv[FIRST_ARGUMENT], shift, fp_input, fp_output);
  return 0;
}

int
cipher (const char *command, int shift, FILE *input_file, FILE *output_file)
{
  char buffer[BUFFER_SIZE] = {0};
  shift = strcmp (command, ENCRYPTION_COMMAND) ? -shift : shift;
  while (fgets (buffer, BUFFER_SIZE - 1, input_file) != NULL)
    {
      encode (buffer, shift);
      fprintf (output_file, "%s", buffer);
    }
  fclose (input_file);
  fclose (output_file);
  return 0;
}

int check_file_path (const char *input_file, const char *output_file)
{
  if (strchr (input_file, ' ') != NULL
      || strchr (output_file, ' ') != NULL
      || strcmp (input_file, output_file) == 0)
    {
      return FAILURE;
    }
  return 1;
}

int check_command (const char *command)
{
  if (strcmp (command, ENCRYPTION_COMMAND) != 0
      && strcmp (command, DECRYPTION_COMMAND) != 0)
    {
      return FAILURE;
    }
  return 1;
}

int check_if_shift_isdigit (const char *shift)
{
  int i = 0;
  while (shift[i] != '\0')
    {
      if (i == 0 && strlen (shift) > 1 && shift[i] == MINUS_SIGN)
        {
          i++;
          continue;
        }
      if (isdigit (shift[i]) == 0)
        {
          return FAILURE;
        }
      i++;
    }
  return 1;
}

#endif
