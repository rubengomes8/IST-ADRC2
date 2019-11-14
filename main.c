#include "main.h"
#include "utils.h"
#include "adjlist.h"
#include "dijkstra.h"

int main(int argc, char *argv[]){

	FILE *fp ;
	adj_array_node *adj_array = NULL;
	int i=0;
	


	int *types = (int *) malloc(3*sizeof(int));
	int *length_cum = (int *) malloc(SIZE*sizeof(int));

	if(argc<2){
		printf("Falta de argumentos\nExemplo: ./main links.txt");
		return -1;
	}
	else if(argc > 2){
		printf("Excesso de argumentos\nExemplo: ./lmp links.txt");
		return -1;
	}
	else{

		fp = fopen(argv[1], "r");

		// Criar lista de adjacências
		adj_array = create_adjacency_array();


		// Preencher grafo invertido a partir do ficheiro
		adj_array = load_inverted_graph(fp, adj_array);

		// Imprimir grafo invertido
		//print_graph(adj_array);

		// Para cada nó aplicar Dijkstra Comercial e Dijkstra normal
		/*
		printf("Active nodes\n");
		for(i=0; i<SIZE;i++){
			if (isActive(adj_array, i)){
				printf("node: %d\n", i); 
			}
		}*/
		for(i=0; i<SIZE; i++){			
			if (isActive(adj_array, i)==true){
				//printActive(adj_array);
				//printf("Dijkstra for node: %d\n", i);

				//dijkstraCommercial(adj_array, i, d_nhops, d_route, parent, selected, &types, &length_cum);
				adj_array=dijkstraCommercial(adj_array, i, &types, &length_cum);
				if (i % 500 == 0)
                    printf("Dijkstra done for source : %d\n", i);
				
			}
		}

		//printf("\nTYPES: %d", types[0]);
		// Fazer estatísticas

		// Libertar memória
		//free_adjacency_array(adj_array);
		
	}

	printf("Por implementar...\n");
	//fclose(fp);
	exit(1);
}
