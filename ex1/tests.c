
# include <stdio.h>
#include "cipher.h"
#include <string.h>

#define STR_LENGTH 4
#define K_1 2
#define K_2 -5
#define K_3 28
#define K_4 3
#define EXPECTED_OUTPUT_1 "ccc"
#define EXPECTED_OUTPUT_2 "Cfa"
#define EXPECTED_OUTPUT_3 "v@T"
#define EXPECTED_OUTPUT_4 "c#A"
#define EXPECTED_OUTPUT_5 "cde"
#define EXPECTED_OUTPUT_6 "XyZ"
#define EXPECTED_OUTPUT_7 "C$b"
#define EXPECTED_OUTPUT_8 "Y$z"
#define INPUT_TEST_1 {'a', 'a', 'a'}
#define INPUT_TEST_2 {'A', 'd', 'y'}
#define INPUT_TEST_3 {'a', '@', 'Y'}
#define INPUT_TEST_4 {'a', '#', 'Y'}
#define INPUT_TEST_5 {'e', 'f', 'g'}
#define INPUT_TEST_6 {'A', 'b', 'C'}
#define INPUT_TEST_7 {'X', '$', 'w'}
#define INPUT_TEST_8 {'A', '$', 'b'}

int test_encode_1 ()
{
  char non_cyclic_input[STR_LENGTH] = INPUT_TEST_1;
  int k = K_1;
  encode (non_cyclic_input, k);
  if (strcmp (non_cyclic_input, EXPECTED_OUTPUT_1) == 0)
    {
      return 1;
    }
  return 0;
}

int test_encode_2 ()
{
  char cyclic_input[STR_LENGTH] = INPUT_TEST_2;
  int k = K_1;
  encode (cyclic_input, k);
  if (strcmp (cyclic_input, EXPECTED_OUTPUT_2) == 0)
    {
      return 1;
    }
  return 0;
}

int test_encode_3 ()
{
  char re_cyclic_input[STR_LENGTH] = INPUT_TEST_3;
  int k = K_2;
  encode (re_cyclic_input, k);
  if (strcmp (re_cyclic_input, EXPECTED_OUTPUT_3) == 0)
    {
      return 1;

    }
  return 0;
}

int test_encode_4 ()
{
  char input_str[STR_LENGTH] = INPUT_TEST_4;
  int k = K_3;
  encode (input_str, k);
  if (strcmp (input_str, EXPECTED_OUTPUT_4) == 0)
    {
      return 1;
    }

  return 0;
}

int test_decode_1 ()
{
  char non_cyclic_input[STR_LENGTH] = INPUT_TEST_5;
  int k = K_1;
  decode (non_cyclic_input, k);
  if (strcmp (non_cyclic_input, EXPECTED_OUTPUT_5) == 0)
    {
      return 1;
    }
  return 0;
}

int test_decode_2 ()
{
  int k = K_4;
  char cyclic_input[STR_LENGTH] = INPUT_TEST_6;
  decode (cyclic_input, k);
  if (strcmp (cyclic_input, EXPECTED_OUTPUT_6) == 0)
    {
      return 1;
    }
  return 0;
}

int test_decode_3 ()
{
  int k = K_2;
  char re_cyclic_input[STR_LENGTH] = INPUT_TEST_7;
  decode (re_cyclic_input, k);
  if (strcmp (re_cyclic_input, EXPECTED_OUTPUT_7) == 0)
    {
      return 1;
    }
  return 0;
}

int test_decode_4 ()
{
  int k = K_3;
  char input_str[STR_LENGTH] = INPUT_TEST_8;
  decode (input_str, k);
  if (strcmp (input_str, EXPECTED_OUTPUT_8) == 0)
    {
      return 1;
    }
  return 0;
}
