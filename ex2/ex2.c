#include "ex2.h"

/**
 * Check if a given node is in a given list
 * @param list Pointer to list to look a node to.
 * @param node Pointer to the node to add look for.
 * @return Pointer to node if fund, NULL otherwise
 */
Node *find_node (LinkedList *list, Node *node);

/**
 * Counting the number of not empty nodes in the list
 * @param list Pointer to list
 * @return The number of not empty nodes in the list
 */
size_t count_not_empty_data (LinkedList *list);

/**
 * Calculates the average for a given vertex
 * @param data Pointer to data array
 * @param len The length of the given data array
 * @return The average of data
 */
double get_node_average (const int *data, size_t len);

/**
 * Do reallocation for a data array
 * @param data_array Pointer to data array that need realloc
 * @param new_size The new size for the data array
 * @return Pointer to the new data array if the reallocation was successful,
 * NULL otherwise
 */
void *data_reallocation (int *data_array, int new_size);

/**
 * Get a line from the file and creat a node for this line
 * @param token Pointer to the first integer in the line
 * @return Pointer to the new node if the allocations was successful,
 * NULL otherwise
 */
Node *parse_one_line (char *token);

/**
 * Creat a new node
 * @param data_array Pointer to the data array that needs to go
 * into the new node
 * @param data_size The size of the data array
 * @return Pointer to the new node if the allocations was successful,
 * NULL otherwise
 */
Node *create_node (int *data_array, int data_size);

/**
 * Checks if it is necessary to increase the data array
 * @param data_array Pointer to data array
 * @param capacity The current size of the array
 * @param data_index The number of the integers that already in the array
 * @return Pointer to the data array if everything went well,
 * NULL if the allocations was fail
 */
int *check_data_size (int *data_array, int *capacity, const int *data_index);

/**
 *
 * @param data_array Pointer to data array
 * @param capacity The current size of the array
 * @param final_data_size The final of integers in the data array
 * @return Pointer to the data array if everything went well,
 * NULL if the allocations was fail
 */
int *check_final_data_size
	(int *data_array, const int *capacity, const int *final_data_size);
/**
 * Adds a node as the head of the list.
 *
 * Assumptions:
 *    You cannot assume the pointers are valid.
 *
 * In case of errors:
 *    Invalid pointer - print error to stderr and return from function.
 *
 * @param list pointer to list to add a node to.
 * @param node pointer to the node to add to the list.
 */
void add_to_start_linked_list (LinkedList *const list, Node *const node)
{
  if (!list || !node)
	{
	  fprintf (stderr, INVALID_POINTER_ERROR);
	  return;
	}
  if (!list->head)
	{
	  list->head = node;
	  list->tail = node;
	  return;
	}
  node->next = list->head;
  list->head->prev = node;
  list->head = node;
}

/**
 * Adds a node as the tail of the list.
 *
 * Assumptions:
 *   You cannot assume the pointers are valid.
 *
 * In case of errors:
 *    Invalid pointer - print error to stderr and return from function.
 *
 * @param list pointer to list to add a node to.
 * @param node pointer to the node to add to the list.
 */
void add_to_end_linked_list (LinkedList *const list, Node *const node)
{
  if (!list || !node)
	{
	  fprintf (stderr, INVALID_POINTER_ERROR);
	  return;
	}
  if (!list->head)
	{
	  list->head = node;
	  list->tail = node;
	  return;
	}
  node->prev = list->tail;
  list->tail->next = node;
  list->tail = node;
}

/**
 * removes a node from the list and frees it's resources.
 *
 * Assumptions:
 *    You cannot assume the pointers are valid.
 *    You cannot assume the node is in the list. In this case
 *    don't free its resources.
 *    To be sure - you are supposed to compare the given node
 *    to the nodes in the list using == operator.
 *
 * In case of errors:
 *    Invalid pointer - print informative error message to stderr
 *    and return from function.
 *
 * @param list pointer to list to remove a node from.
 * @param node pointer to the node to remove from the list.
 */
void remove_node (LinkedList *const list, Node *const node)
{
  if (!list || !node)
	{
	  fprintf (stderr, INVALID_POINTER_ERROR);
	  return;
	}
  Node *tmp = find_node (list, node);
  if (!tmp)
	{
	  return;
	}
  if (!node->next)
	{
	  list->tail = node->prev;
	}
  else
	{
	  node->next->prev = node->prev;
	}
  if (!node->prev)
	{
	  list->head = node->next;
	}
  else
	{
	  node->prev->next = node->next;
	}
  free (node->data);
  free (node);
}

/**
 * check if the given node is in the given list.
 * @param list pointer to list to check a node in.
 * @param node pointer to the node to check if is in the list.
 * @return pointer to node if the given node is in the given list,
 * pointer to NULL otherwise
 */
Node *find_node (LinkedList *const list, Node *const node)
{
  Node *tmp = list->head;
  while (tmp)
	{
	  if (node == tmp)
		{
		  break;
		}
	  tmp = tmp->next;
	}
  return tmp;
}

/**
 * Frees the resources (all dynamic allocations) of the given list.
 *
 * Assumptions:
 *    You cannot assume the pointer is valid.
 *
 * In case of errors:
 *    Invalid pointer - This means there is nothing to free,
 *    just return from function.
 *
 * @param list the list to free.
 */
void free_linked_list (LinkedList *const list)
{
  if (!list)
	{
	  return;
	}
  Node *tmp = list->head;
  while (tmp)
	{
	  Node *next = tmp->next;
	  if (tmp->data)
		{
		  free (tmp->data);
		}
	  free (tmp);
	  tmp = next;
	}
  free (list);
}

/**
 * calculates the grade average of every node in the linked list.
 *
 * Assumptions:
 *    You cannot assume the pointers are valid.
 *    You don't know the number of nodes in the linkedlist in advance.
 *    You can assume that there is at least one node with
 *    data != NULL (i.e. len > 0).
 *    You can assume that for each node 'len' is indeed the length of 'data'
 *     (in particular len=0 <=> data=NULL).
 *
 * In case of errors:
 *    Invalid pointer - print informative message to stderr,
 *    free resources allocated by function,
 *                      return NULL from function.
 *    Allocation fail - print informative message to stderr,
 *    free resources allocated by function,
 *                      return NULL from function.
 *    Node with NULL data - don't count the node in the calculation.
 *
 * @param list: LinkedList pointer to linked list from whom to c
 * alculate grade averages.
 * @param num_elements_in_returned_array: pointer to unsigned long,
 * that should contain the number of nodes in the list
 * (for nodes with data != NULL) when the function finishes execution.
 * To be clear - at the start of the function,
 * (*num_elements_in_returned_array) is a garbage value, and this
 * function should set its value.
 *    @Note: Nodes with NULL data should not be count in the calculation.
 *    Therefore *num_elements_in_returned_array <= numOfNodes.
 * @return array of grade averages per node.
 * To be clear - this means you should
 * calculate the grade average of every node and save it into an array,
 * which you will return from the function.
 */
double *get_averages (LinkedList *const list,
					  size_t *const num_elements_in_returned_array)
{
  if (!list)
	{
	  fprintf (stderr, INVALID_POINTER_ERROR);
	  return NULL;
	}
  if (!num_elements_in_returned_array)
	{
	  fprintf (stderr, INVALID_POINTER);
	  return NULL;
	}
//	counting the number of not empty nodes in the linked list
  size_t num_of_nods_with_data = count_not_empty_data (list);
  *num_elements_in_returned_array = num_of_nods_with_data;
  double *averages_array =
	  malloc (sizeof (double) * num_of_nods_with_data);
  if (!averages_array)
	{
	  fprintf (stderr, ALLOCATION_ERROR);
	  return NULL;
	}
  Node *tmp = list->head;
  int index = 0;
  while (tmp)
	{
	  if (tmp->data)
		{
//		  calculates the average of the data in the current node
		  double node_average = get_node_average (tmp->data, tmp->len);
		  averages_array[index] = node_average;
		  index++;
		}
	  tmp = tmp->next;
	}
  return averages_array;
}

double get_node_average (const int *data, size_t len)
{
  double sum = 0;
  size_t counter = 0;
  while (counter < len)
	{
	  sum += data[counter];
	  counter++;
	}
  double node_average = sum / (double)counter;
  return node_average;
}

size_t count_not_empty_data (LinkedList *const list)
{
  size_t num_of_nods_with_data = 0;
  Node *tmp = list->head;
  while (tmp)
	{
	  if (tmp->data)
		{
		  num_of_nods_with_data++;
		}
	  Node *next = tmp->next;
	  tmp = next;
	}
  return num_of_nods_with_data;
}

/**
 * opens a file from a given filename and parses it's contents into
 * a LinkedList.
 *
 * Assumptions:
 *    You cannot assume the filename is OK
 *    (meaning - you cannot assume it is a valid path to a file).
 *    You cannot assume anything on the number of ints in a row of the file,
 *    just that it is >= 1.
 *    You can assume that if the file opened, then it is exactly in the
 *    format specified in the exercise PDF.
 *    You can assume max line length of 1024.
 *
 * In case of errors:
 *    Invalid pointer - print informative message to stderr, free resources
 *    allocated by function,
 *                      return NULL from function.
 *    File open fail - print informative message to stderr, free resources
 *    allocated by function,
 *                      return NULL from function.
 *    Allocation fail - print informative message to stderr, free resources
 *    allocated by function,
 *                      return NULL from function.
 *
 * Think - in what mode should we open this file? (read? write? append?)
 *
 * @param file filename of input file that needs to be parsed.
 * @return pointer to LinkedList instance, whose nodes and data arrays were
 * parsed from the given file.
 */
LinkedList *parse_linked_list (const char *const filename)
{
  FILE *fp = fopen (filename, FILE_OPEN_MODE);
  if (!fp)
	{
	  fprintf (stderr, INVALID_FILE_ERROR);
	  return NULL;
	}
  LinkedList *list = calloc (1, sizeof (LinkedList));
  if (!list)
	{
	  fprintf (stderr, ALLOCATION_ERROR);
	  return NULL;
	}
  char buffer[BUFFER_SIZE] = {0}, *token = NULL, *add_mode = NULL;
//  read one line from the file in each iteration
  while (fgets (buffer, BUFFER_SIZE, fp) != NULL)
	{
	  token = strtok (buffer, DELIMITERS);
	  add_mode = token;
//	  creat a new node with the data from  the line
	  Node *node = parse_one_line (token);
	  if (!node)
		{
		  fprintf (stderr, ALLOCATION_ERROR);
		  return NULL;
		}
//		inserts the mew node to the linked list
	  if (strcmp (add_mode, START) == 0)
		{
		  add_to_start_linked_list (list, node);
		}
	  else
		{
		  add_to_end_linked_list (list, node);
		}
	}
  fclose (fp);
  return list;
}

Node *parse_one_line (char *token)
{
  int *data = malloc (sizeof (int) * INITIAL_DATA_SIZE);
  if (!data)
	{
	  fprintf (stderr, ALLOCATION_ERROR);
	  return NULL;
	}
  int data_index = 0, capacity = INITIAL_DATA_SIZE;
  while ((token = strtok (NULL, DELIMITERS)))
	{
//	  checks if there is room in the data array for another int
	  data = check_data_size (data, &capacity, &data_index);
	  if (!data)
		{
		  return NULL;
		}
	  data[data_index] = (int)strtol (token, NULL, DECIMAL_BASE);
	  data_index++;
	}
//  checks if there is unnecessary space in the data array
  data = check_final_data_size (data, &capacity, &data_index);
  if (!data)
	{
	  return NULL;
	}
//	if data_index = 0, free node->data and node->data = NULL
  if (data_index == 0)
	{
	  free (data);
	  data = NULL;
	}
  Node *node = create_node (data, data_index);
  if (!node)
	{
	  return NULL;
	}
  return node;
}

int *check_final_data_size
	(int *data_array, const int *capacity, const int *final_data_size)
{
  if (*capacity > *final_data_size && *final_data_size > 0)
	{
	  int *tmp_data = data_reallocation (data_array, (*final_data_size + 1));
	  if (!tmp_data)
		{
		  return NULL;
		}
	  data_array = tmp_data;
	}
  return data_array;
}

int *check_data_size (int *data_array, int *capacity, const int *data_index)
{
  if (*data_index >= *capacity)
	{
	  int *tmp_data = data_reallocation (data_array, (*capacity
													  + INITIAL_DATA_SIZE));
	  if (!tmp_data)
		{
		  return NULL;
		}
	  data_array = tmp_data;
	  *capacity = *capacity + INITIAL_DATA_SIZE;
	}
  return data_array;
}

Node *create_node (int *data_array, int data_size)
{
  Node *node = calloc (1, sizeof (Node));
  if (!node)
	{
	  return NULL;
	}
  node->len = data_size;
  node->data = data_array;
  return node;
}

void *data_reallocation (int *data_array, int new_size)
{
  void *tmp = realloc (data_array, sizeof (int) * new_size);
  if (!tmp)
	{
	  free (data_array);
	  data_array = NULL;
	  return NULL;
	}
  return tmp;
}