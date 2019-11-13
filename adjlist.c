#include "adjlist.h"

struct _routinglist
{
    int parent;
	int route_type;
	int no_hops;
};

struct _adjarraynode
{
    deque_node *head_clients;
	deque_node *head_peers;
	deque_node *head_providers;
	routing_list_node *routing_list;
	bool flag_active;
};

adj_array_node *create_adjacency_array(){
	int i = 0, j=0;
	adj_array_node *array = (adj_array_node *) malloc(SIZE*sizeof(adj_array_node));
	for(i=0; i<SIZE; i++){
		array[i].head_clients = NULL;
		array[i].head_peers = NULL;
		array[i].head_providers = NULL;
		array[i].routing_list = (routing_list_node *) malloc(SIZE*sizeof(routing_list_node));
		for(j=0; j<SIZE; j++){
				array[i].routing_list[j].parent = -1;
				array[i].routing_list[j].route_type = -1;
				array[i].routing_list[j].no_hops= -1;
		}
		array[i].flag_active = false;
	}

	return array;
}

void free_list(deque_node* head){
	deque_node *aux;
	while(head != NULL){
		aux = head;
		head = getNext(head);
		free(aux);
	}
}

void free_adjacency_array(adj_array_node* array){
	int i=0;
	for(i=0; i<SIZE; i++){
		free_list(array[i].head_clients);
		free_list(array[i].head_peers);
		free_list(array[i].head_providers);
		free(array[i].routing_list);

	}
}
