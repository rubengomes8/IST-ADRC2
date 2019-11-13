#include "deque.h"

struct _deque
{
    int node;
	struct _deque *next;
};

deque_node *getNext(deque_node *head){
	return  head->next;
}

deque_node *append(deque_node *head, int node){
	deque_node *aux = head;
	deque_node *new = (deque_node *) malloc (sizeof(deque_node));
	new->node = node;
	head = new;
	head->next = aux;
	return head;
}


int pop(deque_node *head){
	int node = head->node;
	deque_node *aux = head;
	head = head->next;
	free(aux);
	return node;
}
