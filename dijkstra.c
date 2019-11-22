#include "dijkstra.h"

adj_array_node  *dijkstraCommercial(adj_array_node *array, int src,  int types[], int length_cum[]){

	bool flag_abort=false;

	int node_selected = -1, i=0;
	int ngbr;
	int d_nhops[SIZE];
	int d_route[SIZE];
	int selected[SIZE];

	int client;
	int client_peer;
	int client_provider;
	int chosen = -1; // 1 - client, 2 - client_peer, 3 - client_prov
	int n_hops = -1;

    deque_node *queue_clients = NULL;
	deque_node *queue_clients_peers = NULL;
	deque_node *queue_clients_providers = NULL;
	deque_node *queue_clients_peers_tail = NULL;
	deque_node *queue_clients_providers_tail = NULL;
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
		selected[i]=0;
	}

	d_nhops[src]=0;
    d_route[src]=1;

    queue_providers_tail = append_right(queue_providers_tail, src);
	queue_providers = queue_providers_tail;




	//printf("Adeus");
    while(queue_clients != NULL || queue_peers != NULL || queue_providers != NULL || queue_clients_peers != NULL|| queue_clients_providers != NULL){
		while(true){
			if(queue_providers != NULL){
				node_selected = pop(&queue_providers);
				if(queue_providers == NULL)
					queue_providers_tail = NULL;
			}else if(queue_peers != NULL){
				node_selected = pop(&queue_peers);
				if(queue_peers == NULL)
					queue_peers_tail = NULL;
			}else if(queue_clients != NULL || queue_clients_providers != NULL || queue_clients_peers != NULL){
				n_hops = SIZE+1;
				client = getNode(queue_clients);
				client_peer = getNode(queue_clients_peers);
				client_provider = getNode(queue_clients_providers);
				if(client != -1)
				{
					n_hops = d_nhops[client];
					chosen = 1;
				}

				if(client_peer != -1)
				{
					if(d_nhops[client_peer] < n_hops){
						chosen = 2;
						n_hops = d_nhops[client_peer];
					}
				}

				if(client_provider != -1)
				{
					if(d_nhops[client_provider] < n_hops){
						chosen = 3;
						n_hops = d_nhops[client_provider];
					}
				}

				if(chosen == 1){
					node_selected = pop(&queue_clients);
					if(queue_clients == NULL)
						queue_clients_tail = NULL;
				}else if(chosen == 2){
					node_selected = pop(&queue_clients_peers);
					if(queue_clients_peers == NULL)
						queue_clients_peers_tail = NULL;
				}else if(chosen == 3){
					node_selected = pop(&queue_clients_providers);
					if(queue_clients_providers == NULL)
						queue_clients_providers_tail = NULL;
				}


				/*node_selected = pop(&queue_clients);
				if(queue_clients == NULL)
					queue_clients_tail = NULL;*/
			}

			else{
				flag_abort = true;
				break;
			}
			//printf("Node selected: %d\n", node_selected);
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
				/*queue_clients_tail = append_right(queue_clients_tail, ngbr);
				if(queue_clients == NULL)
					queue_clients = queue_clients_tail;*/
				if(d_route[node_selected] == 1 && node_selected != src){ //provider
					queue_clients_providers_tail = append_right(queue_clients_providers_tail, ngbr);
					if(queue_clients_providers == NULL)
						queue_clients_providers = queue_clients_providers_tail;
				}
				else if (d_route[node_selected] == 2 && node_selected != src)
				{
					queue_clients_peers_tail = append_right(queue_clients_peers_tail, ngbr);
					if(queue_clients_peers == NULL)
						queue_clients_peers = queue_clients_peers_tail;
				}
				else if (d_route[node_selected] == 3 || node_selected == src)
				{
					queue_clients_tail = append_right(queue_clients_tail, ngbr);
					if(queue_clients == NULL)
						queue_clients = queue_clients_tail;
				}

			}
			clients = getNext(clients);
		}
		if(d_route[node_selected] < 2){
			peers = getPeers(array, node_selected);
			while(peers != NULL){
				ngbr = getNode(peers);
				if(d_route[ngbr] > max(d_route[node_selected], 2)){
					d_nhops[ngbr] = d_nhops[node_selected] + 1;
					d_route[ngbr] = max(d_route[node_selected], 2);
					queue_peers_tail = append_right(queue_peers_tail, ngbr);
					if(queue_peers == NULL)
						queue_peers = queue_peers_tail;
				}
				peers = getNext(peers);
			}

			providers = getProviders(array, node_selected);
			while(providers != NULL){
				ngbr = getNode(providers);
				if(d_route[ngbr] > max(d_route[node_selected], 1)){
					d_nhops[ngbr] = d_nhops[node_selected] + 1;
					d_route[ngbr] = max(d_route[node_selected], 1);
					queue_providers_tail = append_right(queue_providers_tail, ngbr);
					if(queue_providers == NULL)
						queue_providers = queue_providers_tail;
				}
				providers = getNext(providers);
			}
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

adj_array_node *bfs(adj_array_node *array, int src, int count_hops[]){

	int discovered[SIZE] = {0};
	int i = 0, j = 1, count_nodes = 0;
	int node_selected = src;
	discovered[src] = 1;
	deque_node *queue_head = NULL;
	deque_node *queue_tail = NULL;
	deque_node *clients = NULL;
	deque_node *peers = NULL;
	deque_node *providers = NULL;
	int ngbr = 0;

	queue_tail = append_right(queue_tail, src);
	queue_head = queue_tail;

	while(queue_tail != NULL){

		while(j>0){
			node_selected = pop(&queue_head);
			if(queue_head == NULL)
				queue_tail = NULL;
			//printf("Node selected: %d\n", node_selected);

			//Verificar vizinhos de node_selected
			clients = getClients(array, node_selected);
			peers = getPeers(array, node_selected);
			providers = getProviders(array, node_selected);

			while(clients != NULL){
				ngbr = getNode(clients);
				if(discovered[ngbr] == 0){
					discovered[ngbr] = 1;
					count_hops[i+1]++;
					count_nodes++;
					queue_tail = append_right(queue_tail, ngbr);
					if(queue_head == NULL)
						queue_head = queue_tail;
				}
				clients = getNext(clients);

			}

			while(peers != NULL){
				ngbr = getNode(peers);
				if(discovered[ngbr] == 0){
					discovered[ngbr] = 1;
					count_hops[i+1]++;
					count_nodes++;
					queue_tail = append_right(queue_tail, ngbr);
					if(queue_head == NULL)
						queue_head = queue_tail;
				}
				peers = getNext(peers);

			}

			while(providers != NULL){
				ngbr = getNode(providers);
				if(discovered[ngbr] == 0){
					discovered[ngbr] = 1;
					count_hops[i+1]++;
					count_nodes++;
					queue_tail = append_right(queue_tail, ngbr);
					if(queue_head == NULL)
						queue_head = queue_tail;
				}
				providers = getNext(providers);

			}

			//Por cada vizinho não discovered adicionar na queue e fazer count_nodes++;

			j--;

		}
		j = count_nodes;
		count_nodes = 0;
		i++;
	}


	return array;
}


adj_array_node *dfs(adj_array_node *array, int discovered_g[],int discovered_l[], int src){
	deque_node *clients = getClients(array, src);
	discovered_g[src] = 1;
	discovered_l[src] = 1;
	int node;
	for(int i=0; i<SIZE; i++){
		if(isActive(array,i))
			printf("%d", discovered_l[i]);
	}
	while(clients != NULL){
		node = getNode(clients);
		if(discovered_l[node] == 0){
			array=dfs(array, discovered_g, discovered_l, node);
		}else if(discovered_l[node] == 1){
			printf("O grafo tem ciclos de fornecedor-cliente! A sair...\n");
			exit(-1);
		}
		clients=getNext(clients);
	}
	return array;
}


adj_array_node *check_cycles(adj_array_node *array){

	int i=0, j =0;
	int discovered_g[SIZE] = {0};
	int discovered_l[SIZE];
	for(j=0; j<SIZE; j++){
		discovered_g[j] = 0;
	}
	while (i < SIZE)
	{
		if(isActive(array, i) && discovered_g[i] == 0){
			printf("\n");
			for(j=0; j<SIZE; j++){
				discovered_l[j] = 0;
			}
			array=dfs(array, discovered_g, discovered_l, i);

		}
		i++;
	}






	return array;
}
