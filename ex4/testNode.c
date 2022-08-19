//
// Created by Eli Levinkopf on 22/11/2021.
//

#include <string.h>
#include <stdlib.h>
#include<stdio.h>
#include "Node.h"


void *int_copy_func (const void *elem)
{
  const char* char_elem = elem;
  void *elem_copy = malloc (sizeof (int) + 1);
  memcpy(elem_copy, char_elem, sizeof (int) + 1);
  return elem_copy;
}

void *str_copy_func (const void *elem)
{
  const char* char_elem = elem;
  void *elem_copy = malloc (strlen(char_elem) + 1);
  memcpy(elem_copy, char_elem, strlen(char_elem) + 1);
  return elem_copy;
}

int str_cmp_func (const void *elem1, const void *elem2)
{
  const char *char_elem1 = (const char *)elem1;
  const char *char_elem2 = (const char *)elem2;
  if (!strcmp (char_elem1, char_elem2))
	{
	  return 1;
	}
  return 0;
}

void str_free_func (void **elem)
{
  char *str_elem = (char *)(*elem);
  free (str_elem);
  *elem = NULL;
}

int main ()
{
  Node *node1 = node_alloc (str_copy_func, str_cmp_func, str_free_func);
  Node *node2 = node_alloc (str_copy_func, str_cmp_func, str_free_func);
  Node *node3 = node_alloc (str_copy_func, str_cmp_func, str_free_func);
  set_node_data (node1, (void*)"hello");
  set_node_data (node1, (void*) "world");
  set_node_data (node1, (void*) "hi");
  set_node_data (node2, (void*) "hello2");
  set_node_data (node3, (void*) "hello3");
  printf("%d", check_node (node1, (void*) "hi"));
  clear_node(node2);
  get_hash_count (node1);
  node_free (&node1);
  node_free (&node2);
  node_free (&node3);
}


////=======================================================
////
//// Created by Eli Levinkopf on 22/11/2021.
////
//
//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>
//#include "HashSet.h"
//
//#define HASH_SET_DIVISION_FACTOR 0.5
//#define FAILURE 0
//#define TRUE_FLAG 1
//#define TRUE_FLAG_1 -1
//#define SUCCESS 1
//#define INITIALIZATION 0
//#define ERROR_FLAG -1
//#define INCREASE "increase"
//#define DECREASE "decrease"
//
///**
// * allocation an array of pointers to Nodes
// * @param hash_set pointer to hash set
// * @return pointer to an array of pointers to Nodes
// */
//Node **nodes_list_allocation (HashSet *hash_set);
//
///**
// * check if a given value is a data in one of the nodes in the list
// * @param hash_set pointer to hash set to look for the value
// * @param value value to search the list
// * @return pointer to Node that ist data is value if there is such a node,
// * 0 otherwise
// */
//Node *find_node (HashSet *hash_set, Value value);
//
///**
// * reallocation the NodesList array (decreases / increases)
// * @param hash_set pointer to hash set
// * @param flag "decreases" if the array needs to be reduced and "increases"
// * if the array needs to be increased
// */
//void nodes_list_reallocation (HashSet *hash_set, char *flag);
//
///**
// * create an array of all values in the hash set
// * @param hash_set pointer to hash set
// * @return pointer to an array of values
// */
//Value *get_values_list (HashSet *hash_set);
//
///**
// * re-hashing the hash set
// * @param hash_set pointer to hash set
// * @param values_list pointer to an array of values to re-hashing
// * @param num_of_values num of values that need to be re-hashing
// */
//void re_hashing (HashSet *hash_set, Value *values_list, size_t num_of_values);
//
///**
// * cecks if the load factor is valid or needs to be re-hashing
// * @param hash_set pointer to hash set
// * @param flag "decreases" if the array needs to be reduced and "increases"
// * if the array needs to be increased
// * @return 1 if needs to increase and -1 if needs to decrease
// */
//int check_load_factor (HashSet *hash_set, char *flag);
//
///**
// * frees the value list and all its elements.
// * @param hash_set pointer to hash set
// * @param values_list pointer to an array of values
// * @param num_of_values num of value in the array
// */
//void free_values_list (HashSet *hash_set, Value *values_list,
//					   size_t num_of_values);
//
///**
// * frees all nodes list and their data
// * @param hash_set pointer to hash set
// */
//void free_nodes (HashSet *hash_set);
//
//HashSet *hash_set_alloc (HashFunc hash_func, HashSetValueCpy value_cpy,
//						 HashSetValueCmp value_cmp,
//						 HashSetValueFree value_free)
//{
//  if (!hash_func || !value_cpy || !value_cmp || !value_free)
//	{
//	  return NULL;
//	}
//  HashSet *new_hash_set = malloc (sizeof (HashSet));
//  new_hash_set->size = INITIALIZATION;
//  new_hash_set->capacity = HASH_SET_INITIAL_CAP;
//  new_hash_set->hash_func = hash_func;
//  new_hash_set->value_cpy = value_cpy;
//  new_hash_set->value_cmp = value_cmp;
//  new_hash_set->value_free = value_free;
//  Node **nodes_list = nodes_list_allocation (new_hash_set);
//  new_hash_set->NodesList = nodes_list;
//  return new_hash_set;
//}
//
//Node **nodes_list_allocation (HashSet *hash_set)
//{
//  Node **nodes_list = malloc (sizeof (Node *) * HASH_SET_INITIAL_CAP);
//  for (size_t i = 0; i < HASH_SET_INITIAL_CAP; i++)
//	{
//	  nodes_list[i] = node_alloc (hash_set->value_cpy,
//								  hash_set->value_cmp, hash_set->value_free);
//	}
//  return nodes_list;
//}
//
//void hash_set_free (HashSet **p_hash_set)
//{
//  if (!p_hash_set || !(*p_hash_set))
//	{
//	  return;
//	}
//  HashSet *hash_set = *p_hash_set;
//  for (size_t i = 0; i < hash_set->capacity; i++)
//	{
//	  node_free (&(hash_set->NodesList[i]));
//	}
//  free (hash_set->NodesList);
//  free (hash_set);
//}
//
//int hash_set_insert (HashSet *hash_set, Value value)
//{
//  if (!hash_set || !value || !hash_set->hash_func || !hash_set->value_cpy ||
//	  !hash_set->value_free || !hash_set->value_cmp
//	  || find_node (hash_set, value))
//	{
//	  return FAILURE;
//	}
//  size_t hash_key = hash_set->hash_func (value);
//  for (size_t i = 0; i < hash_set->capacity; i++)
//	{
//	  size_t node_idx =
//		  (hash_key + (size_t)((i + i * i) / 2)) & (hash_set->capacity - 1);
//	  Node *cur_node = hash_set->NodesList[node_idx];
//	  i == 0 ? cur_node->hashCount++ : cur_node->hashCount;
//	  if (!(cur_node->data))
//		{
//		  set_node_data (cur_node, value);
//		  hash_set->size++;
//		  break;
//		}
//	}
//  if (check_load_factor (hash_set, INCREASE) == TRUE_FLAG)
//	{
//	  nodes_list_reallocation (hash_set, INCREASE);
//	}
//  return SUCCESS;
//}
//
//int check_load_factor (HashSet *hash_set, char *flag)
//{
//  double load_factor = hash_set_get_load_factor (hash_set);
//  if (!strcmp (flag, INCREASE) && load_factor >= HASH_SET_MAX_LOAD_FACTOR)
//	{
//	  return TRUE_FLAG;
//	}
//  if (!strcmp (flag, DECREASE) && load_factor <= HASH_SET_MIN_LOAD_FACTOR)
//	{
//	  return TRUE_FLAG_1;
//	}
//  return FAILURE;
//}
//
//void nodes_list_reallocation (HashSet *hash_set, char *flag)
//{
////	  TODO: save all ALPHABET to re-hash
//  size_t new_capacity = hash_set->capacity * HASH_SET_GROWTH_FACTOR;
//  if (!strcmp (flag, DECREASE))
//	{
//	  new_capacity = hash_set->capacity * HASH_SET_DIVISION_FACTOR;
//	}
//  Value *values_list = get_values_list (hash_set);
//  free_nodes (hash_set);
//  hash_set->capacity = new_capacity;
//  hash_set->NodesList = realloc (hash_set->NodesList,
//								 new_capacity * sizeof (Node *));
//  re_hashing (hash_set, values_list, hash_set->size);
//}
//
//void free_nodes (HashSet *hash_set)
//{
//  for (size_t i = 0; i < hash_set->capacity; i++)
//	{
//	  Node *cur_node = hash_set->NodesList[i];
//	  node_free (&cur_node);
//	}
//}
//
//void re_hashing (HashSet *hash_set, Value *values_list, size_t num_of_values)
//{
//  for (size_t i = 0; i < hash_set->capacity; i++)
//	{
////	  initial the table
//	  hash_set->NodesList[i] = node_alloc (hash_set->value_cpy, hash_set
//		  ->value_cmp, hash_set->value_free);
//	}
//  hash_set->size = INITIALIZATION;
//  for (size_t i = 0; i < num_of_values; i++)
//	{
//	  Value cur_value = values_list[i];
//	  hash_set_insert (hash_set, cur_value);
//	}
//  free_values_list (hash_set, values_list, num_of_values);
//}
//
//void free_values_list (HashSet *hash_set, Value *values_list,
//					   size_t num_of_values)
//{
//  for (size_t i = 0; i < num_of_values; i++)
//	{
//	  Value cur_value = values_list[i];
//	  hash_set->value_free (&cur_value);
//	}
//  free (values_list);
//}
//
//Value *get_values_list (HashSet *hash_set)
//{
//  Value *values_list = calloc (hash_set->size, sizeof (Value));
//  size_t idx = INITIALIZATION;
//  for (size_t i = 0; i < hash_set->capacity; i++)
//	{
//	  Node *cur_node = hash_set->NodesList[i];
//	  if (cur_node->data)
//		{
//		  Value data_cpy = hash_set->value_cpy (cur_node->data);
//		  values_list[idx] = data_cpy;
//		  idx++;
//		  if (idx == hash_set->size)
//			{
//			  break;
//			}
//		}
//	}
//  return values_list;
//}
//
//int hash_set_contains_value (HashSet *hash_set, Value value)
//{
//  if (!hash_set || !value)
//	{
//	  return FAILURE;
//	}
//  return find_node (hash_set, value) ? SUCCESS : FAILURE;
//}
//
//int hash_set_erase (HashSet *hash_set, Value value)
//{
//  if (!hash_set || !value || !hash_set->hash_func || !hash_set->value_cmp
//	  || !hash_set->value_free || !hash_set->value_cpy)
//	{
//	  return FAILURE;
//	}
//  Node *node_to_erase = find_node (hash_set, value);
//  if (!node_to_erase)
//	{
//	  return FAILURE;
//	}
//  clear_node (node_to_erase);
//  size_t hash_key = hash_set->hash_func (value) & (hash_set->capacity - 1);
//  hash_set->NodesList[hash_key]->hashCount--;
//  hash_set->size--;
//  if (check_load_factor (hash_set, DECREASE) == TRUE_FLAG_1)
//	{
//	  nodes_list_reallocation (hash_set, DECREASE);
//	}
//  return SUCCESS;
//}
//
//// fast find_node:
////Node *find_node (HashSet *hash_set, Value value)
////{
////  size_t hash_key = hash_set->hash_func (value);
////  size_t search_idx = hash_key & (hash_set->capacity - 1);
////  Node *cur_node = hash_set->NodesList[search_idx];
////  int hash_count = cur_node->hashCount;
////  if (!hash_count){
////	return NULL;
////  }
////  for (int i = 0; i <= hash_count;)
////	{
////	  if (cur_node->data && check_node (cur_node, value))
////		{
////		  return cur_node;
////		}
////	  i++;
////	  search_idx = (hash_key + (size_t)((i + i * i) / 2)) & (hash_set->capacity - 1);
////	  cur_node = hash_set->NodesList[search_idx];
////	}
////  return NULL;
////}
//
//Node *find_node (HashSet *hash_set, Value value)
//{
//  size_t hash_key = hash_set->hash_func (value);
//  size_t search_idx = hash_key & (hash_set->capacity - 1);
//  Node *first_node = hash_set->NodesList[search_idx];
//  if (!first_node->hashCount)
//	{
//	  return NULL;
//	}
//  for (size_t i = 0; i < hash_set->capacity; i++)
//	{
//	  Node *cur_node = hash_set->NodesList[i];
//	  if (cur_node->data && check_node (cur_node, value))
//		{
//		  return cur_node;
//		}
//	}
//  return NULL;
//}
//
//double hash_set_get_load_factor (HashSet *hash_set)
//{
//  if (!hash_set)
//	{
//	  return ERROR_FLAG;
//	}
//  if (!hash_set->size)
//	{
//	  return FAILURE;
//	}
//  double size = (double)hash_set->size;
//  double capacity = (double)hash_set->capacity;
//  double load_factor = size / capacity;
//  return load_factor;
//}
//
//void hash_set_clear (HashSet *hash_set)
//{
//  if (!hash_set)
//	{
//	  return;
//	}
//  for (size_t i = 0; i < hash_set->capacity; i++)
//	{
//	  Node *cur_node = hash_set->NodesList[i];
//	  if (cur_node->data)
//		{
//		  hash_set->size--;
//		}
//	  clear_node (cur_node);
//	  cur_node->hashCount = INITIALIZATION;
//	}
//}
//
//Value hash_set_at (HashSet *hash_set, int value)
//{
//  if (!hash_set || !hash_set->NodesList || value >= (int)hash_set->capacity
//	  || value < 0 || !hash_set->NodesList[value])
//	{
//	  return NULL;
//	}
//  return hash_set->NodesList[value]->data;
//}



//==========================================


