#include "deque.h"

struct _deque
{
    int node;
	struct _deque *next;
};

deque_node *getNext(deque_node *head){
	return  head->next;
}

int getNode(deque_node *head){
	if(head == NULL)
		return -1;
	return  head->node;
}

deque_node *append(deque_node *head, int node){
	deque_node *aux = head;
	deque_node *new = (deque_node *) malloc (sizeof(deque_node));
	new->node = node;
	head = new;
	head->next = aux;
	return head;
}

deque_node *append_right(deque_node *tail, int node){

	deque_node *new = (deque_node *) malloc (sizeof(deque_node));
	new->node = node;
	new->next = NULL;

	if(tail == NULL){
		return new;
	}else{
		tail->next = new;
		return new;
	}
}


int pop(deque_node **head){
	int node = (*head)->node;
	deque_node *aux = *head;
	*head = (*head)->next;
	aux->next = NULL;
	free(aux);
	return node;
}

void print_list(deque_node *head){
	if (head == NULL)
		printf("Cannot print an empty list");
	else{
		while(head != NULL){
			printf("%d\t", head->node);
			head = getNext(head);
		}
	}
	printf("\n");
}
