#include "utils.h"

adj_array_node *load_inverted_graph(FILE *fp, adj_array_node *adj_array, deque_node **tier_ones){
	int tier_ones_array[SIZE];
	int tail, head, type;
	int i = 0;
	for(i=0; i<SIZE; i++){
		tier_ones_array[i]=1;
	}
	if(fp != NULL){
		while(fscanf(fp, "%d %d %d", &tail, &head, &type) != EOF){
			//printf("tail: %d || head: %d || type: %d\n", tail, head, type);
			adj_array = setActive(tail, true, adj_array);
			adj_array = setActive(head, true, adj_array);

			if(type == 1){
				adj_array = append_provider(head, tail, adj_array);
				//printf("tail: %d\n", tail);
				tier_ones_array[head] = 0;
			}else if(type == 2){
				adj_array = append_peer(head, tail, adj_array);
			}else if(type == 3){
				adj_array = append_client(head, tail, adj_array);
				//printf("head: %d\n", head);
				tier_ones_array[tail] = 0;
			}else{
				printf("Erro no ficheiro de texto. A sair...");
				exit(-1);
			}

		}
	}

	for(i=0;i<SIZE;i++){
		if(tier_ones_array[i] == 1){
			printf("TIER-1: %d\n", i);
			*tier_ones = append(*tier_ones, i);
		}
	}
	return adj_array;
}


void print_graph(adj_array_node * array){
	int i=0;
	deque_node *clients, *peers, *providers;
	for(i=0; i <SIZE; i++){
		if (isActive(array, i)==true){
			printf("\nNode: %d\n", i);
			clients=getClients(array,i);
			printf("Clients:\n");
			while (clients!=NULL)
			{
				printf("%d -> ", getNode(clients));
				clients=getNext(clients);
			}
			peers=getPeers(array,i);
			printf("\n");
			printf("Peers:\n");
			while (peers!=NULL)
			{
				printf("%d ->", getNode(peers));
				peers=getNext(peers);
			}
			providers=getProviders(array,i);
			printf("\n");
			printf("Providers:\n");
			while (providers!=NULL)
			{
				printf("%d -> ", getNode(providers));
				providers=getNext(providers);
			}
			printf("\n");
		}
	}
}

bool isCommerciallyConex(adj_array_node *adj_array, deque_node *tier_ones){
	deque_node *aux = tier_ones;
	deque_node *peers;
	while(aux != NULL){
		peers = getPeers(adj_array, getNode(aux));
		if(peers == NULL){
			return false;
		}
		aux=getNext(aux);
	}
	return true;
}
