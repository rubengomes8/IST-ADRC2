#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include "deque.h"
#define SIZE 65536

typedef struct _routinglist routing_list_node;
typedef struct _adjarraynode adj_array_node;

adj_array_node *create_adjacency_array();
void free_list(deque_node* head);
void ffree_adjacency_array(adj_array_node* array);
