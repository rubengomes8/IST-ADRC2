#include "deque.h"

struct _deque
{
    int node;
	struct _deque *next;
};

deque_node *getNext(deque_node *head){
	return  head->next;
}

deque_node *append(deque_node *head, int payload){

	return head;
}


int pop(deque_node *head){
	return 0;
}
