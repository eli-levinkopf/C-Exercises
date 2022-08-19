//
// Created by Eli Levinkopf on 23/11/2021.
//

#include <stdlib.h>
#include <stdio.h>
# include "Utils.h"
#include "Hash.h"
#include "HashSet.h"

#define ERASE_ALL 1
#define INT 1
#define DOUBLE 2
#define CHAR 3
#define ERASE_SOME 0
char ALPHABET[52] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
							'J', 'K',
							'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
							'U', 'V',
							'W', 'X', 'Y', 'Z',
							'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
							'j', 'k',
							'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
							'u', 'v',
							'w', 'x', 'y', 'z'};

int test_counter = 0;

HashSet *create_int_hash_set (int size)
{
  HashSet *int_hash_set = hash_set_alloc (hash_int, int_key_cpy, int_key_cmp, int_key_free);
  for (int i = 0; i < size; i++)
	{
	  hash_set_insert (int_hash_set, (Value)&i);
	}
  return int_hash_set;
}

HashSet *create_double_hash_set (int size)
{
  HashSet *int_hash_set = hash_set_alloc (hash_double, double_key_cpy, double_key_cmp, double_key_free);
  for (int i = 0; i < size; i++)
	{
	  double d = i;
	  hash_set_insert (int_hash_set, (Value)&d);
	}
  return int_hash_set;
}

//char print_alphabet ()
//{
//  char c;
//  for (c = 'A'; c <= 'Z'; ++c)
//	printf ("'%c', ", c);
//  for (c = 'a'; c <= 'z'; ++c)
//	printf ("'%c', ", c);
//  return c;
//}

HashSet *create_char_hash_set (int size)
{
  HashSet *int_hash_set = hash_set_alloc (hash_char, char_key_cpy, char_key_cmp, char_key_free);
  for (int i = 0; i < size; i++)
	{
	  char c = ALPHABET[i];
	  hash_set_insert (int_hash_set, (Value)&c);
	}
  return int_hash_set;
}

int test_invalid_pointer ()
{
  HashSet *check_1 = hash_set_alloc (NULL, int_key_cpy, int_key_cmp, int_key_free);
  HashSet *check_2 = hash_set_alloc (hash_int, NULL, int_key_cmp, int_key_free);
  HashSet *check_3 = hash_set_alloc (hash_int, int_key_cpy, NULL, int_key_free);
  HashSet *check_4 = hash_set_alloc (hash_int, int_key_cpy, int_key_cmp, NULL);
  if (check_1 || check_2 || check_3 || check_4)
	{
	  fprintf (stderr, "'create_int_hash_set' got a NULL pointer and returned a value != 0 => fail in 'test_invalid_pointer'\n");
	  return 0;
	}
  int val = 5;
  Value value = (void *)&val;
  HashSet *hash_set = hash_set_alloc (hash_int, int_key_cpy, int_key_cmp, int_key_free);
  int check_5 = hash_set_insert (NULL, value);
  int check_6 = hash_set_insert (hash_set, NULL);
  if (check_5 || check_6)
	{
	  fprintf (stderr, "'hash_set_insert' got a NULL pointer and returned a value != 0 => fail in 'test_invalid_pointer'\n");
	  hash_set_free (&hash_set);
	  return 0;
	}
  int check_7 = hash_set_contains_value (NULL, value);
  int check_8 = hash_set_contains_value (hash_set, NULL);
  if (check_7 || check_8)
	{
	  fprintf (stderr, "'hash_set_contains_value' got a NULL pointer and returned a value != 0 => fail in 'test_invalid_pointer'\n");
	  hash_set_free (&hash_set);
	  return 0;
	}
  int check_9 = hash_set_erase (NULL, value);
  int check_10 = hash_set_erase (hash_set, NULL);
  if (check_9 || check_10)
	{
	  fprintf (stderr, "'hash_set_erase' got a NULL pointer and returned a value != 0 => fail in 'test_invalid_pointer'\n");
	  hash_set_free (&hash_set);
	  return 0;
	}
  double check_11 = hash_set_get_load_factor (NULL);
  if (check_11 != -1)
	{
	  fprintf (stderr, "'hash_set_get_load_factor' got a NULL pointer and returned a value != -1 => fail in 'test_invalid_pointer'\n");
	  hash_set_free (&hash_set);
	  return 0;
	}
  int big_index = (int)(hash_set->capacity);
  Value check_12 = hash_set_at (NULL, val);
  Value check_13 = hash_set_at (hash_set, big_index);

  if (check_12 || check_13)
	{
	  fprintf (stderr, "'hash_set_at' got a invalid parameter and returned a value != 0 => fail in 'test_invalid_pointer'\n");
	  hash_set_free (&hash_set);
	  return 0;
	}
  hash_set_free (&hash_set);
  test_counter++;
  fprintf (stdout, "pass test_invalid_pointer\n");
  return 1;
}

int check_values (HashSet *hash_set, size_t num_of_node, int flag)
{
  int val_idx = 0;
  for (int i = 0; i < (int)num_of_node; i++)
	{
	  Node *cur_node = hash_set->NodesList[i];
	  if (!cur_node->data)
		{
		  continue;
		}
	  Value cur_value = cur_node->data;
	  if (flag == INT)
		{
		  int int_value = *(int *)cur_value;
		  if (i != int_value)
			{
			  return 0;
			}
		}
	  else if (flag == DOUBLE)
		{
		  double double_value = *(double *)cur_value;
		  if ((double)i != double_value)
			{
			  return 0;
			}
		}
	  if (flag == CHAR)
		{
		  char char_value = *(char *)cur_value;
		  if (ALPHABET[val_idx] != char_value)
			{
			  return 0;
			}
		  val_idx++;
		}
	}
  return 1;
}

int
check_size_and_capacity (HashSet *hash_set, size_t expected_capacity, size_t expected_size, char flag)
{
  for (size_t i = 0; i < expected_size; i++)
	{

	  if (flag == INT)
		{
		  int int_val = (int)i;
		  hash_set_insert (hash_set, (Value)&int_val);
		}
	  else if (flag == DOUBLE)
		{
		  double double_val = (double)i;
		  hash_set_insert (hash_set, (Value)&double_val);
		}
	  else if (flag == CHAR)
		{
		  char char_val = ALPHABET[i];
		  hash_set_insert (hash_set, (Value)&char_val);
		}
	}
  if (hash_set->capacity != expected_capacity
	  || hash_set->size != expected_size)
	{
	  return 0;
	}
  return 1;
}

int test_hash_set_alloc ()
{

  HashSet *int_hash_set = create_int_hash_set (48);
  if (!int_hash_set)
	{
	  hash_set_free (&int_hash_set);
	  fprintf (stderr, "fail in 'test_hash_set_alloc'\n");
	  return 0;

	}
  test_counter++;
  fprintf (stdout, "pass test_hash_set_alloc\n");
  hash_set_free (&int_hash_set);
  return 1;
}

int test_int_hash_set_insert ()
{
  size_t expected_capacity[3] = {16, 32, 128};
  size_t expected_size[3] = {11, 12, 48};
  for (int i = 0; i < 1; i++)
	{
	  HashSet *int_hash_set = hash_set_alloc (hash_int, int_key_cpy, int_key_cmp, int_key_free);
	  if (!check_size_and_capacity (int_hash_set, expected_capacity[i], expected_size[i], INT))
		{
		  fprintf (stderr, "incorrect capacity or size => fail in 'test_int_hash_set_insert' (in sub test check_size_and_capacity)\n");
		  hash_set_free (&int_hash_set);
		  return 0;
		}
	  if (!check_values (int_hash_set, expected_capacity[i], INT))
		{
		  fprintf (stderr, "incorrect value in hash_set => fail in 'test_int_hash_set_insert' (in sub test check_values)\n");
		  hash_set_free (&int_hash_set);
		  return 0;
		}
	  hash_set_free (&int_hash_set);
	}
  test_counter++;
  fprintf (stdout, "pass test_int_hash_set_insert\n");
  return 1;
}

int test_double_hash_set_insert ()
{
  size_t expected_capacity[3] = {16, 32, 128};
  size_t expected_size[3] = {11, 12, 48};
  for (int i = 0; i < 3; i++)
	{
	  HashSet *double_hash_set = hash_set_alloc (hash_double, double_key_cpy, double_key_cmp, double_key_free);
	  if (!check_size_and_capacity (double_hash_set, expected_capacity[i], expected_size[i], DOUBLE))
		{
		  fprintf (stderr, "incorrect capacity or size => fail in 'test_double_hash_set_insert' (in sub test check_size_and_capacity)\n");
		  hash_set_free (&double_hash_set);
		  return 0;
		}
	  if (!check_values (double_hash_set, expected_capacity[i], DOUBLE))
		{
		  fprintf (stderr, "incorrect value in hash_set => fail in 'test_double_hash_set_insert' (in sub test check_values)\n");
		  hash_set_free (&double_hash_set);
		  return 0;
		}
	  hash_set_free (&double_hash_set);
	}
  test_counter++;
  fprintf (stdout, "pass test_double_hash_set_insert\n");
  return 1;
}

int test_char_hash_set_insert ()
{
  size_t expected_capacity[3] = {16, 32, 128};
  size_t expected_size[3] = {11, 12, 48};
  for (int i = 0; i < 3; i++)
	{
	  HashSet *char_hash_set = hash_set_alloc (hash_int, int_key_cpy, int_key_cmp, int_key_free);
	  if (!check_size_and_capacity (char_hash_set, expected_capacity[i], expected_size[i], CHAR))
		{
		  fprintf (stderr, "incorrect capacity or size => fail in 'test_char_hash_set_insert' (in sub test check_size_and_capacity)\n");
		  hash_set_free (&char_hash_set);
		  return 0;
		}
	  if (!check_values (char_hash_set, expected_capacity[i], CHAR))
		{
		  fprintf (stderr, "incorrect value in hash_set => fail in 'test_char_hash_set_insert' (in sub test check_values)\n");
		  hash_set_free (&char_hash_set);
		  return 0;
		}
	  hash_set_free (&char_hash_set);
	}
  test_counter++;
  fprintf (stdout, "pass test_char_hash_set_insert\n");
  return 1;
}

int test_int_hash_set_contains_value ()
{
  HashSet *int_hash_set = create_int_hash_set (48);
  for (int i = 0; i < (int)int_hash_set->size; i++)
	{
	  Value cur_value = (Value)&i;
	  if (hash_set_contains_value (int_hash_set, cur_value) != 1)
		{
		  fprintf (stderr, "cur_value is in the hash_set and 'hash_set_contains_value' returns value != 1 => fail in 'test_int_hash_set_contains_value'\n");
		  hash_set_free (&int_hash_set);
		  return 0;
		}
	}
  hash_set_free (&int_hash_set);
  test_counter++;
  fprintf (stdout, "pass test_int_hash_set_contains_value\n");
  return 1;
}

int test_double_hash_set_contains_value ()
{
  HashSet *double_hash_set = create_double_hash_set (48);
  for (int i = 0; i < (int)double_hash_set->size; i++)
	{
	  double j = (double)i;
	  Value cur_value = (Value)&j;
	  if (hash_set_contains_value (double_hash_set, cur_value) != 1)
		{
		  fprintf (stderr, "cur_value is in the hash_set and 'hash_set_contains_value' returns value != 1 => fail in 'test_double_hash_set_contains_value'\n");
		  hash_set_free (&double_hash_set);
		  return 0;
		}
	}
  hash_set_free (&double_hash_set);
  test_counter++;
  fprintf (stdout, "pass test_double_hash_set_contains_value\n");
  return 1;
}

int test_char_hash_set_contains_value ()
{
  HashSet *char_hash_set = create_char_hash_set (48);
  for (int i = 0; i < (int)char_hash_set->size; i++)
	{
	  Value cur_value = (Value)&ALPHABET[i];
	  if (hash_set_contains_value (char_hash_set, cur_value) != 1)
		{
		  fprintf (stderr, "cur_value is in the hash_set and 'hash_set_contains_value' returns value != 1 => fail in 'test_char_hash_set_contains_value'\n");
		  hash_set_free (&char_hash_set);
		  return 0;
		}
	}
  hash_set_free (&char_hash_set);
  test_counter++;
  fprintf (stdout, "pass test_char_hash_set_contains_value\n");
  return 1;
}

int test_int_hash_set_erase (int flag)
{
  HashSet *int_hash_set = create_int_hash_set (48);
  double expected_final_capacity = 64;
  double expected_final_capacity1 = 1;
  size_t expected_final_size = 24;
  size_t expected_final_size1 = 0;
  size_t start_size = int_hash_set->size;
  size_t start_capacity = int_hash_set->capacity;
  for (size_t i = 0; i < start_capacity; i++)
	{
	  if (!flag && i % 2 == 0)
		{
		  continue;
		}
	  Value value_to_erase = (Value)&i;
	  if (i >= start_size && hash_set_erase (int_hash_set, value_to_erase))
		{
		  fprintf (stderr, "value_to_erase not in the hashset and 'hash_set_erase' returns value != 0 => fail in 'test_int_hash_set_erase'\n");
		  hash_set_free (&int_hash_set);
		  return 0;
		}
	  else if (i < start_size
			   && (hash_set_erase (int_hash_set, value_to_erase) != 1))
		{
		  fprintf (stderr, "value_to_erase in the hashset and 'hash_set_erase' returns value != 1 => fail in 'test_int_hash_set_erase'\n");
		  hash_set_free (&int_hash_set);
		  return 0;
		}
	}
  if ((!flag && (int_hash_set->size != expected_final_size ||
				 int_hash_set->capacity != expected_final_capacity)) ||
	  (flag && (int_hash_set->size != expected_final_size1 ||
				int_hash_set->capacity != expected_final_capacity1)))
	{
	  fprintf (stderr, "the size or capacity after erasing is different from the expected value => fail in 'test_int_hash_set_erase'\n");
	  hash_set_free (&int_hash_set);
	  return 0;
	}
  hash_set_free (&int_hash_set);
  test_counter++;
  fprintf (stdout, "pass test_int_hash_set_erase\n");
  return 1;
}

int test_double_hash_set_erase (int flag)
{
  HashSet *double_hash_set = create_double_hash_set (48);
  double expected_final_capacity = 64;
  double expected_final_capacity1 = 1;
  size_t expected_final_size = 24;
  size_t expected_final_size1 = 0;
  size_t start_size = double_hash_set->size;
  size_t start_capacity = double_hash_set->capacity;
  for (size_t i = 0; i < start_capacity; i++)
	{
	  if (!flag && i % 2 == 0)
		{
		  continue;
		}
	  double j = (double)i;
	  Value value_to_erase = (Value)&j;
	  if (i >= start_size && hash_set_erase (double_hash_set, value_to_erase))
		{
		  fprintf (stderr, "value_to_erase not in the hashset and 'hash_set_erase' returns value != 0 => fail in 'test_double_hash_set_erase'\n");
		  hash_set_free (&double_hash_set);
		  return 0;
		}
	  else if (i < start_size
			   && (hash_set_erase (double_hash_set, value_to_erase) != 1))
		{
		  fprintf (stderr, "value_to_erase in the hashset and 'hash_set_erase' returns value != 1 => fail in 'test_double_hash_set_erase'\n");
		  hash_set_free (&double_hash_set);
		  return 0;
		}
	}
  if ((!flag && (double_hash_set->size != expected_final_size ||
				 double_hash_set->capacity != expected_final_capacity)) ||
	  (flag && (double_hash_set->size != expected_final_size1 ||
				double_hash_set->capacity != expected_final_capacity1)))
	{
	  fprintf (stderr, "the size or capacity after erasing is different from the expected value => fail in 'test_double_hash_set_erase'\n");
	  hash_set_free (&double_hash_set);
	  return 0;
	}
  hash_set_free (&double_hash_set);
  test_counter++;
  fprintf (stdout, "pass test_double_hash_set_erase\n");
  return 1;
}

int test_char_hash_set_erase (int flag)
{
  HashSet *char_hash_set = create_char_hash_set (48);
  double expected_final_capacity = 64;
  double expected_final_capacity1 = 1;
  size_t expected_final_size = 24;
  size_t expected_final_size1 = 0;
  size_t start_size = char_hash_set->size;
  size_t start_capacity = char_hash_set->capacity;
  for (size_t i = 0; i < start_capacity; i++)
	{
	  if (!flag && i % 2 == 0)
		{
		  continue;
		}
	  char c = (char)ALPHABET[i];
	  Value value_to_erase = (Value)&c;
	  if (i >= start_size && hash_set_erase (char_hash_set, value_to_erase))
		{
		  fprintf (stderr, "value_to_erase is not in the hashset and 'hash_set_erase' returns value != 0 => fail in 'test_char_hash_set_erase'\n");
		  hash_set_free (&char_hash_set);
		  return 0;
		}
	  else if (i < start_size
			   && (hash_set_erase (char_hash_set, value_to_erase) != 1))
		{
		  fprintf (stderr, "value_to_erase is in the hashset and 'hash_set_erase' returns value != 1 => fail in 'test_char_hash_set_erase'\n");
		  hash_set_free (&char_hash_set);
		  return 0;
		}
	}
  if ((!flag && (char_hash_set->size != expected_final_size ||
				 char_hash_set->capacity != expected_final_capacity)) ||
	  (flag && (char_hash_set->size != expected_final_size1 ||
				char_hash_set->capacity != expected_final_capacity1)))
	{
	  fprintf (stderr, "the size or capacity after erasing is different from the expected value => fail in 'test_char_hash_set_erase'\n");
	  hash_set_free (&char_hash_set);
	  return 0;
	}
  hash_set_free (&char_hash_set);
  test_counter++;
  fprintf (stdout, "pass test_char_hash_set_erase\n");
  return 1;
}

int test_int_hash_set_clear ()
{
  HashSet *int_hash_set = create_int_hash_set (48);
  size_t capacity = int_hash_set->capacity;
  hash_set_clear (int_hash_set);
  if (int_hash_set->size != 0 || int_hash_set->capacity != capacity)
	{
	  fprintf (stderr, "after hash_set_clear, the size should be 0 and the capacity doesn't change => fail in 'test_int_hash_set_clear'\n");
	  hash_set_free (&int_hash_set);
	  return 0;
	}
  hash_set_free (&int_hash_set);
  test_counter++;
  fprintf (stdout, "pass test_int_hash_set_clear\n");
  return 1;
}

int test_double_hash_set_clear ()
{
  HashSet *double_hash_set = create_double_hash_set (48);
  size_t capacity = double_hash_set->capacity;
  hash_set_clear (double_hash_set);
  if (double_hash_set->size != 0 || double_hash_set->capacity != capacity)
	{
	  fprintf (stderr, "after hash_set_clear, the size should be 0 and the capacity doesn't change => fail in 'test_double_hash_set_clear'\n");
	  hash_set_free (&double_hash_set);
	  return 0;
	}
  hash_set_free (&double_hash_set);
  test_counter++;
  fprintf (stdout, "pass test_double_hash_set_clear\n");
  return 1;
}

int test_char_hash_set_clear ()
{
  HashSet *char_hash_set = create_char_hash_set (48);
  size_t capacity = char_hash_set->capacity;
  hash_set_clear (char_hash_set);
  if (char_hash_set->size != 0 || char_hash_set->capacity != capacity)
	{
	  fprintf (stderr, "after hash_set_clear, the size should be 0 and the capacity doesn't change => fail in 'test_char_hash_set_clear'\n");
	  hash_set_free (&char_hash_set);
	  return 0;
	}
  hash_set_free (&char_hash_set);
  test_counter++;
  fprintf (stdout, "pass test_char_hash_set_clear\n");
  return 1;
}

int test_int_hash_set_at ()
{
  HashSet *int_hash_set = create_int_hash_set (48);
  for (int i = 0; i < (int)int_hash_set->capacity; i++)
	{
	  Value *cur_value = hash_set_at (int_hash_set, i);
	  if ((i > 47 && cur_value) || (i <= 47 && !cur_value))
		{
		  hash_set_free (&int_hash_set);
		  fprintf (stderr, "'hash_set_at' returns an incorrect value => fail in 'test_int_hash_set_at'\n");
		  return 0;
		}
	  if (!cur_value)
		{
		  continue;
		}
	  int cur_int_value = *((int *)cur_value);
	  if (cur_int_value != i)
		{
		  fprintf (stderr, "'hash_set_at' returns an incorrect value => fail in 'test_int_hash_set_at'\n");
		  hash_set_free (&int_hash_set);
		  return 0;
		}
	}
  hash_set_free (&int_hash_set);
  test_counter++;
  fprintf (stdout, "pass test_int_hash_set_at\n");
  return 1;
}

int test_double_hash_set_at ()
{
  HashSet *double_hash_set = create_double_hash_set (48);
  for (int i = 0; i < (int)double_hash_set->capacity; i++)
	{
	  Value *cur_value = hash_set_at (double_hash_set, i);
	  if ((i > 47 && cur_value) || (i <= 47 && !cur_value))
		{
		  fprintf (stderr, "'hash_set_at' returns an incorrect value => fail in 'test_double_hash_set_at'\n");
		  hash_set_free (&double_hash_set);
		  return 0;
		}
	  if (!cur_value)
		{
		  continue;
		}
	  double j = (double)i;
	  double cur_int_value = *((double *)cur_value);
	  if (cur_int_value != j)
		{

		  hash_set_free (&double_hash_set);
		  return 0;
		}
	}
  hash_set_free (&double_hash_set);
  test_counter++;
  fprintf (stdout, "pass test_double_hash_set_at\n");
  return 1;
}

int test_char_hash_set_at ()
{
  HashSet *char_hash_set = create_char_hash_set (48);
  int val_idx = 0;
  for (int i = 0; i < (int)char_hash_set->capacity; i++)
	{
	  Value *cur_value = hash_set_at (char_hash_set, i);
	  if (!cur_value)
		{
		  continue;
		}
	  char c = (char)ALPHABET[val_idx];
	  char cur_int_value = *((char *)cur_value);
	  if (cur_int_value != c)
		{
		  fprintf (stderr, "'hash_set_at' returns an incorrect value => fail in 'test_char_hash_set_at'\n");
		  hash_set_free (&char_hash_set);
		  return 0;
		}
	  val_idx++;
	}
  hash_set_free (&char_hash_set);
  test_counter++;
  fprintf (stdout, "pass test_char_hash_set_at\n");
  return 1;
}

int test_hash_set_get_load_factor ()
{
  HashSet *int_hash_set = create_int_hash_set (48);
  double expected_load_factor = 0.375000;
  if (hash_set_get_load_factor (int_hash_set) != expected_load_factor)
	{
	  fprintf (stderr, "the load factor is different from the expected value => fail in 'test_hash_set_get_load_factor'\n");
	  hash_set_free (&int_hash_set);
	  return 0;
	}
  hash_set_free (&int_hash_set);
  test_counter++;
  fprintf (stdout, "pass test_hash_set_get_load_factor\n");
  return 1;
}

int test_hashCount ()
{
  HashSet *int_hash_set = create_int_hash_set (48);
  for (int i = 0; i < 24; i++)
	{
	  int val = (int)(i + 128);
	  hash_set_insert (int_hash_set, (Value)&val);
	}
  for (size_t i = 0; i < int_hash_set->capacity; i++)
	{
	  if (i < 24 && int_hash_set->NodesList[i]->hashCount != 2)
		{
		  fprintf (stderr, "hashCount is different from the expected hashCount (expected = 2) => fail in 'test_hashCount'\n");
		  hash_set_free (&int_hash_set);
		  return 0;
		}
	  else if (i >= 24 && i < 48 && int_hash_set->NodesList[i]->hashCount != 1)
		{
		  fprintf (stderr, "hashCount is different from the expected hashCount (expected = 1) => fail in 'test_hashCount'\n");
		  hash_set_free (&int_hash_set);
		  return 0;
		}
	  else if (i >= 48 && int_hash_set->NodesList[i]->hashCount != 0)
		{
		  fprintf (stderr, "hashCount is different from the expected hashCount (expected = 0) => fail in 'test_hashCount'\n");
		  hash_set_free (&int_hash_set);
		  return 0;
		}
	}
  hash_set_free (&int_hash_set);
  test_counter++;
  fprintf (stdout, "pass test_hashCount\n");
  return 1;
}

int test_module ()
{
  HashSet *int_hash_set = hash_set_alloc (hash_int, int_key_cpy, int_key_cmp, int_key_free);
  int val = 0;
  for (int i = 0; i < 11; i++)
	{
	  Value value = (void *)&val;
	  hash_set_insert (int_hash_set, value);
	  if (i == 0)
		{
		  val = (int)(int_hash_set->capacity);
		}
	  else
		{
		  val *= 2;
		}
	}
  if (int_hash_set->NodesList[0]->hashCount != 11)
	{
	  fprintf (stderr, " => incorrect hashCount => fail in 'test_module'\n");
	  hash_set_free (&int_hash_set);
	  return 0;
	}
  hash_set_free (&int_hash_set);
  test_counter++;
  fprintf (stdout, "pass test_module\n");
  return 1;
}

int main ()
{
  test_invalid_pointer ();
  test_hash_set_alloc ();
  test_int_hash_set_insert ();
  test_double_hash_set_insert ();
  test_char_hash_set_insert ();
  test_int_hash_set_contains_value ();
  test_double_hash_set_contains_value ();
  test_char_hash_set_contains_value ();
  test_int_hash_set_erase (ERASE_SOME);
  test_int_hash_set_erase (ERASE_ALL);
  test_double_hash_set_erase (ERASE_SOME);
  test_double_hash_set_erase (ERASE_ALL);
  test_char_hash_set_erase (ERASE_SOME);
  test_char_hash_set_erase (ERASE_ALL);
  test_int_hash_set_clear ();
  test_double_hash_set_clear ();
  test_char_hash_set_clear ();
  test_int_hash_set_at ();
  test_double_hash_set_at ();
  test_char_hash_set_at ();
  test_hash_set_get_load_factor ();
  test_hashCount ();
  test_module ();

  if (test_counter == 23)
	{
	  fprintf (stdout,
			   "\n*******************\n* passed all test *\n*******************\n\n");
	  return 0;
	}


  return 1;
}
