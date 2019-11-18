#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include "adjlist.h"
#include "deque.h"

adj_array_node *load_inverted_graph(FILE *fp, adj_array_node *adj_array, deque_node **tier_ones, int *no_tier1);
void print_graph(adj_array_node * array);
bool isCommerciallyConex(adj_array_node *adj_array, deque_node *tier_ones);
int *create_count_hops(int hops_max);