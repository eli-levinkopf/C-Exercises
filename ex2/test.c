#include <stdlib.h>
#include <stdio.h>
#include "ex2.h"
#include <stddef.h>
#define FIRST_ERROR "You failed the first test\n"
#define SECOND_ERROR "You failed the second test\n"
#define THIRD_ERROR "You failed the third test\n"
#define ARGUMENTS 4
#define ARGUMENTS_ERROR "You didnt give all the files."
#define SUCCESS "****************\npassed all test\n****************\n"
#define FIRST_TEST 1
#define SECOND_TEST 1
#define THIRD_TEST_ONE 2
#define THIRD_TEST_TWO 3


/**
 * The function test a simple test for ParseLinkedList and GetAverage.
 * @param arg pointer to arguments.
 * @return 0 if ok, 1 if not.
 */
int FirstTest(char *arg[]){
  const double average_first[] = {0.0, 50.0, 40.0, 40.0, 20.0};
  const size_t how_many_first = 5;
  struct LinkedList *list = parse_linked_list(arg[FIRST_TEST]);
  size_t how_many;
  double *average = get_averages(list, &how_many);
  if (how_many != how_many_first){
    printf("%s", FIRST_ERROR);
    free(average);
	  free_linked_list(list);
    return 1;
  }
  for (int i=0;i <= how_many_first-1; ++i){
    if (average[i] != average_first[i]){
      printf("%s", FIRST_ERROR);
      free(average);
		free_linked_list(list);
      return 1;
    }
  }
  free(average);
  free_linked_list(list);
  return 0;
}


/**The function check a simple test to remove node.
 * @param arg pointer to arguments.
 * @return 0 if ok, 1 if not.
 */
int SecondTest(char *arg[]){
  const double average_second[] = {40.0, 40.0};
  const size_t how_many_second = 2;
  size_t how_many;
  struct Node node;
  struct LinkedList *list = parse_linked_list(arg[SECOND_TEST]);
  struct Node *first = list->head;
  struct Node *last = list->tail;
  struct Node *middle = list->head->next;
  struct Node *non = calloc(1, sizeof(Node));
  remove_node (list, &node);
  remove_node(list, middle);
  remove_node(list, first);
  remove_node(list, last);
  remove_node(list, non);
  free(non);
  non = NULL;
  double *average = get_averages (list, &how_many);
  if (how_many != how_many_second){
    printf("%s", SECOND_ERROR);
    free(average);
    free_linked_list(list);
    return 1;
  }
  for (int i=0;i <= how_many_second-1; ++i){
    if (average[i] != average_second[i]){
      printf("%s", SECOND_ERROR);
      free(average);
      free_linked_list(list);
      return 1;
    }
  }
  free(average);
  average = NULL;
  free_linked_list(list);
  list = NULL;
  return 0;
}


/**
 * The function test when there is only one node in linkedlist.
 * @param arg pointer to arguments.
 * @return 0 if ok, 1 if not.
 */
int ThirdTest(char *arg[]){
  struct LinkedList *start = parse_linked_list(arg[THIRD_TEST_ONE]);
  struct LinkedList *end =parse_linked_list(arg[THIRD_TEST_TWO]);
  if ((start->head != start->tail) || (end->head != end->tail)){
    printf("%s", THIRD_ERROR);
    free_linked_list(start);
    free_linked_list(end);
    return 1;
  }
  free_linked_list(start);
  free_linked_list(end);
  return 0;
}


/**
 * The function check when you dont give valid arguments to the functions.
 */
void ErrorTest(void){
  struct Node *node = calloc(1, sizeof(struct Node));
  struct LinkedList *list = calloc(1, sizeof(struct LinkedList));
  size_t len = 0;
  fprintf(stderr, "1:");
  add_to_start_linked_list(list, NULL);
  fprintf(stderr, "2:");
  add_to_start_linked_list(NULL, node);
  fprintf(stderr, "3:");
  add_to_start_linked_list(list, NULL);
  fprintf(stderr, "4:");
  add_to_start_linked_list(NULL, node);
  fprintf(stderr, "5:");
  remove_node(list, NULL);
  fprintf(stderr, "6:");
  remove_node(NULL, node);
  fprintf(stderr, "7:\n");
  free_linked_list(NULL);
  fprintf(stderr, "8:");
  get_averages(list, NULL);
  fprintf(stderr, "9:");
  get_averages(NULL, &len);
  fprintf(stderr, "10:");
  parse_linked_list(NULL);
  free(node);
  free(list);
}

int main(int argc,char* argv[]){
  if (argc != ARGUMENTS){
    printf("%s", ARGUMENTS_ERROR);
    return 1;
  }
  int pass = 0;
  pass += FirstTest(argv);
  pass += SecondTest(argv);
  pass += ThirdTest(argv);
  ErrorTest();
  if (pass){
    return 1;
  }
  else{
    printf("%s", SUCCESS);
    return 0;
  }
}
