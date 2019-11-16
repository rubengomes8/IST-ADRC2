#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct _deque deque_node;

deque_node *getNext(deque_node *head);
deque_node *append_right(deque_node *tail, int node);
deque_node *append(deque_node *head, int node); //left
int pop(deque_node **head);

int getNode(deque_node *head);
void print_list(deque_node *head);
