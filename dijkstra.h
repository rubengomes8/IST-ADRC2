#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include "adjlist.h"

adj_array_node *dijkstraCommercial(adj_array_node *array, int src, int types[], int length_cum[]);
int max(int a, int b);
adj_array_node *bfs(adj_array_node *array, int src, int count_hops[]);

adj_array_node *dfs(adj_array_node *array, int discovered_g[],int discovered_l[],int src);
adj_array_node *check_cycles(adj_array_node *array);
