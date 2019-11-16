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
		for(i=0; i<SIZE;i++){
			length_cum[i]=0;
		}
		for(i=0; i<3;i++){
			types[i]=0;
		}
		for(i=0; i<SIZE; i++){			
			if (isActive(adj_array, i)==true){
				//printActive(adj_array);
				printf("Dijkstra for node: %d\n", i);

				//dijkstraCommercial(adj_array, i, d_nhops, d_route, parent, selected, &types, &length_cum);
				adj_array=dijkstraCommercial(adj_array, i, types, length_cum);
				if (i % 500 == 0)
                    printf("Dijkstra done for source : %d\n", i);
				
			}
		}

		//Fazer estatisticas
		float sum=0;
		for(i=0; i<3;i++){
			printf("%d\n",types[i]);
			sum=sum+types[i];
		}
		printf("Providers: %f\n", types[0]/sum * 100);
		printf("Peers: %f\n", types[1]/sum * 100);
		printf("Clients: %f\n", types[2]/sum * 100);

		i=SIZE-1;
		for(i=SIZE-1; i>0; i--)
			length_cum[i-1] = length_cum[i] + length_cum[i-1]; //P(#hops) >= X)

		i=1;
		while(length_cum[i] != 0){
			printf("P(#hops) >= %d = %f\n", i, (length_cum[i]/sum * 100));
			i++;
		}


		// Libertar memória
		//free_adjacency_array(adj_array);
		
	}

	
	//fclose(fp);
	exit(1);
}
