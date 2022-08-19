//
// Created by Eli Levinkopf on 22/11/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include "Node.h"

#define INITIALIZATION 1
#define FAILURE 0
#define SUCCESS 1
#define ERROR_FLAG -1

Node *node_alloc (NodeElemCpy elem_copy_func,
				  NodeElemCmp elem_cmp_func,
				  NodeElemFree elem_free_func)
{
  if (!elem_copy_func || !elem_cmp_func || !elem_free_func)
	{
	  return NULL;
	}
  Node *new_node = calloc (INITIALIZATION, sizeof (Node));
  new_node->elem_copy_func = elem_copy_func;
  new_node->elem_cmp_func = elem_cmp_func;
  new_node->elem_free_func = elem_free_func;
  return new_node;
}

void node_free (Node **p_Node)
{
  if (!p_Node || !*p_Node || !(*p_Node)->elem_free_func)
	{
	  return;
	}
  if ((*p_Node)->data)
	{
	  (*p_Node)->elem_free_func (&((*p_Node)->data));
	}
  free (*p_Node);
  (*p_Node) = NULL;
}

int check_node (Node *Node, void *value)
{
  if (!Node || !value || !Node->elem_cmp_func)
	{
	  return ERROR_FLAG;
	}
  if (Node->data && !(Node->elem_cmp_func (Node->data, value)))
	{
	  return FAILURE;
	}
  return SUCCESS;
}

int set_node_data (Node *Node, void *value)
{
  if (!Node || !value || !Node->elem_copy_func || !Node->elem_free_func)
	{
	  return FAILURE;
	}
  if (Node->data)
	{
	  Node->elem_free_func (&Node->data);
	}
  Value new_elem = Node->elem_copy_func (value);
  Node->data = (Value)new_elem;
  return SUCCESS;
}

void clear_node (Node *Node)
{
  if (!Node || !Node->elem_free_func)
	{
	  return;
	}
  if (Node->data)
	{
	  Node->elem_free_func (&Node->data);
	}
  Node->data = NULL;
}

int get_hash_count (Node *node)
{
  if (!node)
	{
	  return ERROR_FLAG;
	}
  return node->hashCount;
}
