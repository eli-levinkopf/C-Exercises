
//Created by
//Eli Levinkopf
//on 30/10/2021.

#include <stdio.h>

//int *create_data ();
//int add_num_to_data
//	(int *new_data, char *data_to_add, size_t index, size_t *capacity);
//int check_data_size
// (int *new_data, size_t data_size, const size_t *capacity);
//void *data_reallocation (int *new_data, size_t new_size);
//int parse_one_line (LinkedList *list, char *token);


//LinkedList *parse_linked_list (const char *const filename)
//{
//  FILE *fp = fopen (filename, FILE_OPEN_MODE);
//  if (!fp)
//	{
//	  fprintf (stderr, INVALID_FILE_ERROR);
//	  return NULL;
//	}
//  LinkedList *list = calloc (1, sizeof (LinkedList));
//  if (!list)
//	{
//	  fprintf (stderr, ALLOCATION_ERROR);
//	  return NULL;
//	}
//  char buffer[BUFFER_SIZE] = {0}, *token = NULL;
//  while (fgets (buffer, BUFFER_SIZE, fp) != NULL)
//	{
//
//	  token = strtok (buffer, DELIMITERS);
//	  if (!parse_one_line (list, token))
//		{
//		  return NULL;
//		}
//	}
//  fclose (fp);
//  return list;
//}
//
//int parse_one_line (LinkedList *list, char *token)
//{
//  int data_index = 0;
//  size_t capacity = INITIAL_DATA_SIZE;
//  char *mode = token;
//  Node *new_node = create_node ();
//  if (!new_node)
//	{
//	  fprintf (stderr, ALLOCATION_ERROR);
//	  return FAILURE;
//	}
//  while ((token = strtok (NULL, DELIMITERS)))
//	{
//	  if (!add_num_to_data (new_node, token, data_index, &capacity))
//		{
//		  fprintf (stderr, ALLOCATION_ERROR);
//		  return FAILURE;
//		}
//	  data_index++;
//	}
//  if (!check_data_size (new_node, new_node->len, &capacity))
//	{
//	  fprintf (stderr, ALLOCATION_ERROR);
//	  return FAILURE;
//	}
//  if (strcmp (mode, START) == 0)
//	{
//	  add_to_start_linked_list (list, new_node);
//	}
//  else
//	{
//	  add_to_end_linked_list (list, new_node);
//	}
//  return SUCCESS;
//}
//
//Node *create_node ()
//{
//  Node *new_node = calloc (1, sizeof (Node));
//  int *data = calloc (INITIAL_DATA_SIZE, sizeof (int));
//  if (!new_node || !data)
//	{
//	  return NULL;
//	}
//  new_node->data = data;
////  new_node->len = INITIAL_DATA_SIZE;
//  return new_node;
//}
//
//int check_data_size (Node *node, size_t data_size, const size_t *capacity)
//{
//  if (node->len == 0)
//	{
//	  node->data = NULL;
//	}
//  if (data_size != (*capacity))
//	{
//	  if (!data_reallocation (node, data_size))
//		{
//		  return FAILURE;
//		}
//	}
//  return SUCCESS;
//}
//
//int add_num_to_data
//	(Node *node, char *data_to_add, int index, size_t *capacity)
//{
//  if (index >= (int)(*capacity))
//	{
////	  capacity += 1;
//	  if (!data_reallocation (node, INITIAL_DATA_SIZE + (*capacity)))
//		{
//		  return FAILURE;
//		}
//	  (*capacity) += INITIAL_DATA_SIZE;
//	}
//  int num = (int)strtol (data_to_add, NULL, DECIMAL_BASE);
//  node->data[index] = num;
//  node->len++;
//  return SUCCESS;
//}
//
//void *data_reallocation (Node *node, size_t new_size)
//{
//  void *tmp;
//  tmp = realloc (node->data, sizeof (int) * new_size);
//  if (!tmp)
//	{
//	  free (node->data);
//	  node->data = NULL;
//	  return NULL;
//	}
//  node->data = tmp;
////  node->len = new_size;
//  return tmp;
//}


//int main(){
//  int  arr[1025];
//  for(int i = 0;i<=1024;i++){
//	  arr[i]=i;
//  }
//  printf ("%d\n", arr[1024]);
//}


//Node *create_node (int *data_array, int data_size)
//{
//  Node *node = calloc (1, sizeof (Node));
//  if (!node)
//	{
//	  return NULL;
//	}
//  node->len = data_size;
////  if node->len = 0, free node->data and node->data = NULL
////  if (!node->len)
////	{
////	  free (data_array);
////	  data_array = NULL;
////	}
//  node->data = data_array;
//
//  return node;
//}
//
//void *data_reallocation (int *data_array, int new_size)
//{
//  if (new_size == 1)
//	{
//	  free (data_array);
//	  data_array = NULL;
//	  return data_array;
//	}
//  void *tmp = realloc (data_array, sizeof (int) * new_size);
//  if (!tmp)
//	{
//	  free (data_array);
//	  data_array = NULL;
//	  return NULL;
//	}
//  return tmp;
//}

void func(char * c){
  printf("%s", c);
}

int main(){
  char * c = " dghb";
  func(c);
  return 0;
}