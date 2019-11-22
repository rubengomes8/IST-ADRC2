#include "main.h"
#include "utils.h"
#include "adjlist.h"
#include "dijkstra.h"

int main(int argc, char *argv[]){

	FILE *fp ;
	adj_array_node *adj_array = NULL;
	int i=0;
	int hops_max;
	int *count_hops = NULL;
	unsigned int sum=0;
	int no_tier1 = 0;
	deque_node *tier_ones = NULL;



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
		adj_array = load_inverted_graph(fp, adj_array, &no_tier1, &tier_ones);

		// Imprimir grafo invertido
		//print_graph(adj_array);

		// Verificar se grafo é comercialmente conexo
		//printf("Number of Tier-1s: %d\n", no_tier1);
		printf("OLA\n");
		if(no_tier1 > 1){
			if(!isCommerciallyConex(adj_array, tier_ones)){
				printf("O grafo não é comercialmente conexo! A sair...\n");
				exit(-1);
			}
		}
		printf("Grafo conexo\n");

		// Para cada nó aplicar Dijkstra Comercial e Dijkstra normal
		if(check_cycles(adj_array)){
			printf("Existe pelo menos um ciclo fornecedor-cliente! A sair...\n");
			exit(-1);
		}
		printf("Grafo não tem ciclos\n");

		for(i=0; i<SIZE;i++){
			length_cum[i]=0;
		}
		for(i=0; i<3;i++){
			types[i]=0;
		}
		for(i=0; i<SIZE; i++){
			if (isActive(adj_array, i)==true){
				//printActive(adj_array);
				//printf("Dijkstra for node: %d\n", i);

				//dijkstraCommercial(adj_array, i, d_nhops, d_route, parent, selected, &types, &length_cum);
				adj_array=dijkstraCommercial(adj_array, i, types, length_cum);
				if (i % 500 == 0)
                    printf("Dijkstra done for source : %d\n", i);

			}
		}

		//Fazer estatisticas
		for(i=0; i<3;i++){
			printf("%d\n",types[i]);
			sum=sum+types[i];
		}
		printf("Providers: %f\n", (float) types[0]/sum * 100);
		printf("Peers: %f\n", (float) types[1]/sum * 100);
		printf("Clients: %f\n", (float) types[2]/sum * 100);

		i=1;
		while(length_cum[i] != 0){
			printf("#hops = %d = %d\n", i, length_cum[i]);
			i++;
		}

		i=SIZE-1;
		for(i=SIZE-1; i>0; i--)
			length_cum[i-1] = length_cum[i] + length_cum[i-1]; //P(#hops) >= X)

		i=1;
		while(length_cum[i] != 0){
			printf("(#hops) >= %d: %d\n", i, length_cum[i]);
			printf("P(#hops) >= %d = %f\n", i, ((float) length_cum[i]/sum * 100));
			i++;
		}

		hops_max = i-1;
		count_hops = create_count_hops(hops_max);
		i=0;
		printf("Created count hops\n");
		for(i=0; i<SIZE; i++){
			if (isActive(adj_array, i)){
				adj_array = bfs(adj_array, i, count_hops);
				if (i % 1000 == 0)
					printf("Bfs done for node: %d\n", i);
			}
		}
		printf("BFS done\n");
		/*for(i=0; i<(hops_max+1);i++){
			printf("(#hops = %d): %d\n", i, count_hops[i]);
		};*/

		for(i=hops_max+1; i>0; i--)
			count_hops[i-1] = count_hops[i] + count_hops[i-1]; //P(#hops) >= X)

		for(i=1; i<hops_max+1; i++){
			printf("(#hops) >= %d: %d\n", i, count_hops[i]);
			printf("P(#hops) >= %d = %f\n", i, ( (float) count_hops[i]/sum * 100));
		}
		// Libertar memória
		//free_adjacency_array(adj_array);

	}


	//fclose(fp);
	exit(1);
}
