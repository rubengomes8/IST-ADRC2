#include "utils.h"

adj_array_node *load_inverted_graph(FILE *fp, adj_array_node *adj_array){

	int tail, head, type;
	if(fp != NULL){
		while(fscanf(fp, "%d %d %d", &tail, &head, &type) != EOF){
			//printf("tail: %d || head: %d || type: %d\n", tail, head, type);
			adj_array = setActive(tail, true, adj_array);
			adj_array = setActive(head, true, adj_array);

			if(type == 1){
				adj_array = append_provider(head, tail, adj_array);
			}else if(type == 2){
				adj_array = append_peer(head, tail, adj_array);
			}else if(type == 3){
				adj_array = append_client(head, tail, adj_array);
			}else{
				printf("Erro no ficheiro de texto. A sair...");
				exit(-1);
			}

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
