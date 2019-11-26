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
	int a, b, c;

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

	//printf("\nSOURCE: %d\n", src);
	for(i=0; i<SIZE;i++){
		d_nhops[i] = 66000;
		d_route[i] = 4;
		selected[i]=0;
	}

		d_nhops[src]=0;
    d_route[src]=1;

    queue_providers_tail = append_right(queue_providers_tail, src);
	queue_providers = queue_providers_tail;

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
				n_hops = SIZE+2;
				client = getNode(queue_clients);
				client_peer = getNode(queue_clients_peers);
				client_provider = getNode(queue_clients_providers);
				if(client != -1)
					a = d_nhops[client];
				else
					a = -1;
				if(client_peer != -1)
					b = d_nhops[client_peer];
				else
					b = -1;
				if(client_provider != -1)
					c = d_nhops[client_provider];
				else
					c = -1;
				chosen = get_min(a, b, c);

				/*if(client != -1)
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
				}*/

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
		//printf("Node selected: %d\n", node_selected);
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
			if(d_route[ngbr] > max(d_route[node_selected], 3) || (d_route[ngbr] == max(d_route[node_selected], 3) && d_nhops[ngbr] > (d_nhops[node_selected] + 1))){
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
				else{
					printf("A\n");
				}

			}
			clients = getNext(clients);
		}
		if(d_route[node_selected] < 2){
			peers = getPeers(array, node_selected);
			while(peers != NULL){
				ngbr = getNode(peers);
				if(d_route[ngbr] > max(d_route[node_selected], 2) || (d_route[ngbr] == max(d_route[node_selected], 2) && d_nhops[ngbr] > (d_nhops[node_selected] + 1))){
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
				if(d_route[ngbr] > max(d_route[node_selected], 1 ) || (d_route[ngbr] == max(d_route[node_selected], 1) && d_nhops[ngbr] > (d_nhops[node_selected] + 1))){
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

		/*for (i=0; i<SIZE;i++){
			if(isActive(array,i)){
				printf("Node: %d | Rota: %d | Hops: %d\n", i, d_route[i], d_nhops[i]);
			}
		}*/

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


bool dfs(adj_array_node *array, bool discovered[], bool visited[], bool recursiveArr[], int src){
	deque_node *clients = getClients(array, src);
	int node;
	discovered[src] = true;
	visited[src] = true;
	recursiveArr[src] = true;
	adj_array_node *aux_array = array;

	/*for(int i=0; i<SIZE; i++){
		if(isActive(array,i))
			printf("%d", discovered_l[i]);
	}*/

	while(clients != NULL){
		node = getNode(clients);
		if(!visited[node] && 	dfs(aux_array, discovered, visited, recursiveArr, node)){
			return true;
		}else if(recursiveArr[node]){
			return true;
		}
		clients=getNext(clients);
	}
	recursiveArr[src] = false;
	return false;
}


bool check_cycles(adj_array_node *array){

	int i=0, j=0;
	bool discovered[SIZE];
	bool visited[SIZE];
	bool recursiveArr[SIZE];
	adj_array_node *aux_array = array;

	for(j=0; j<SIZE; j++){
		discovered[j] = false;
	}
	while (i < SIZE)
	{
		if(isActive(aux_array, i) && !discovered[i]){
			for(j=0; j<SIZE; j++){
				visited[j] = false;
				recursiveArr[j] = false;
			}
			if(dfs(aux_array, discovered, visited, recursiveArr, i))
				return true;
		}
		i++;
	}
	return false;
}

int get_min(int a, int b, int c){

	if(a == -1){
		if(b != -1){
			if(c != -1)
				return b < c ? 2 : 3;
			return 2;
		}
		return 3;
	}

	if(b != -1){
		if(c != -1){
			if(a < b && a < c)
				return 1;
			return b < c ? 2 : 3;
		}
		return b < a ? 2 : 1;
	} else {
		if(c != -1)
			return a < c ? 1 : 3;
		return 1;
	}
}
