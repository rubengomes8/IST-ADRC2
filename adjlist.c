#include "adjlist.h"

struct _adjarraynode
{
    deque_node *head_clients;
	deque_node *head_peers;
	deque_node *head_providers;
	bool flag_active;
};

adj_array_node *create_adjacency_array(){
	int i = 0;
	adj_array_node *array = (adj_array_node *) malloc(SIZE*sizeof(adj_array_node));
	for(i=0; i<SIZE; i++){
		array[i].head_clients = NULL;
		array[i].head_peers = NULL;
		array[i].head_providers = NULL;
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
	}
}

adj_array_node *append_provider(int head, int tail, adj_array_node *array){
	array[head].head_providers=append(array[head].head_providers, tail);
	return array;
}

adj_array_node *append_peer(int head, int tail, adj_array_node *array){
	array[head].head_peers=append(array[head].head_peers, tail);
	return array;
}

adj_array_node *append_client(int head, int tail, adj_array_node *array){
	array[head].head_clients=append(array[head].head_clients, tail);
	return array;
}

adj_array_node *setActive(int node, bool active, adj_array_node *array){
	array[node].flag_active = active;
	return array;
}

bool isAvtive(adj_array_node *array, int node){
	return array[node].flag_active;
}

deque_node *getClients(adj_array_node *array, int node){
	return array[node].head_clients;
}

deque_node *getPeers(adj_array_node *array, int node){
	return array[node].head_peers;
}

deque_node *getProviders(adj_array_node *array, int node){
	return array[node].head_providers;
}