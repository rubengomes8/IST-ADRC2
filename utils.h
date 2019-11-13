#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include "adjlist.h"

adj_array_node *load_inverted_graph(FILE *fp, adj_array_node *adj_array);
