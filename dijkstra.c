#include "dijkstra.h"

adj_array_node  *dijkstraCommercial(adj_array_node *array, int src,  int types[], int length_cum[]){

	bool flag_abort=false;

	int node_selected, i=0;
	int ngbr;
	int d_nhops[SIZE];
	int d_route[SIZE];
	int parent[SIZE];
	int selected[SIZE];

    deque_node *queue_clients = NULL;
    deque_node *queue_peers = NULL;
    deque_node *queue_providers = NULL;
	deque_node *queue_clients_tail = NULL;
    deque_node *queue_peers_tail = NULL;
    deque_node *queue_providers_tail = NULL;
	deque_node *clients = NULL;
	deque_node *peers = NULL;
	deque_node *providers = NULL;

	for(i=0; i<SIZE;i++){
		d_nhops[i] = 66000;
		d_route[i] = 4;
		parent[i]=0;
		selected[i]=0;
	}

	d_nhops[src]=0;
    d_route[src]=1;
    parent[src]=src;

    queue_providers_tail = append_right(queue_providers_tail, src);
	queue_providers = queue_providers_tail;




	//printf("Adeus");
    while(queue_clients != NULL || queue_peers != NULL || queue_providers != NULL){
		while(true){
			if(queue_providers != NULL){
				node_selected = pop(&queue_providers);
				if(queue_providers == NULL)
					queue_providers_tail = NULL;
			}else if(queue_peers != NULL){
				node_selected = pop(&queue_peers);
				if(queue_peers == NULL)
					queue_peers_tail = NULL;
			}else if(queue_clients != NULL){
				node_selected = pop(&queue_clients);
				if(queue_clients == NULL)
					queue_clients_tail = NULL;
			}

			else{
				flag_abort = true;
				break;
			}
			printf("Node selected: %d\n", node_selected);
			if(selected[node_selected] == 1){
			}else{
				break;
			}
		}
		if(flag_abort)
			continue;
		if(node_selected != src){
			types[3 - d_route[node_selected]] ++;
            length_cum[d_nhops[node_selected]] ++;
		}
		selected[node_selected] = 1; // mark it as already selected
		clients = getClients(array, node_selected);
		while(clients != NULL){

			ngbr = getNode(clients);
			if(d_route[ngbr] > max(d_route[node_selected], 3)){
				d_nhops[ngbr] = d_nhops[node_selected] + 1;
				d_route[ngbr] = 3;
				parent[ngbr] = node_selected;
				queue_clients_tail = append_right(queue_clients_tail, ngbr);
				if(queue_clients == NULL)
					queue_clients = queue_clients_tail;
			}
			clients = getNext(clients);
		}
		if(d_route[node_selected] <= 2){
			peers = getPeers(array, node_selected);
			while(peers != NULL){
				ngbr = getNode(peers);
				if(d_route[ngbr] > max(d_route[node_selected], 2)){
					d_nhops[ngbr] = d_nhops[node_selected] + 1;
					d_route[ngbr] = max(d_route[node_selected], 2);
					parent[ngbr] = node_selected;
					queue_peers_tail = append_right(queue_peers_tail, ngbr);
					if(queue_peers == NULL)
						queue_peers = queue_peers_tail;
				}
				peers = getNext(peers);
			}
			if(d_route[node_selected] <= 1){
				providers = getProviders(array, node_selected);
				while(providers != NULL){
					ngbr = getNode(providers);
					if(d_route[ngbr] > max(d_route[node_selected], 1)){
						d_nhops[ngbr] = d_nhops[node_selected] + 1;
						d_route[ngbr] = max(d_route[node_selected], 1);
						parent[ngbr] = node_selected;
						queue_providers_tail = append_right(queue_providers_tail, ngbr);
						if(queue_providers == NULL)
							queue_providers = queue_providers_tail;
					}
					providers = getNext(providers);
				}
			}
		}
    }
	for(int i=0; i<SIZE; i++){
		if(isActive(array,i)){
			printf("Node %d -> parent %d\n", i, parent[i]);
		}
	}

	return array;
}

int max(int a, int b){
	if(a >= b){
		return a;
	}else{
		return b;
	}
}
