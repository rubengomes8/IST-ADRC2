#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include "deque.h"
#define SIZE 65536


typedef struct _adjarraynode adj_array_node;

adj_array_node *create_adjacency_array();
void free_list(deque_node* head);
void free_adjacency_array(adj_array_node* array);
adj_array_node *append_provider(int head, int tail, adj_array_node *array);
adj_array_node *append_peer(int head, int tail, adj_array_node *array);
adj_array_node *append_client(int head, int tail, adj_array_node *array);
adj_array_node *setActive(int node, bool active, adj_array_node *array);
