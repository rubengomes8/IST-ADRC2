#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include "adjlist.h"

void dijkstraCommercial(adj_array_node *array, int src,int d_nhops[], int d_route[], int parent[], int selected[], int *types[], int *length_cum[]);
int max(int a, int b);
