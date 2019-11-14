#include "main.h"
#include "utils.h"
#include "adjlist.h"
#include "dijkstra.h"

int main(int argc, char *argv[]){

	FILE *fp ;
	adj_array_node *adj_array = NULL;

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
		print_graph(adj_array);
		
		// Para cada nó aplicar Dijkstra Comercial e Dijkstra normal
		int i=0;
		int d_nhops[SIZE]; 
		int d_route[SIZE];
		for(i=0; i<SIZE;i++){
			d_nhops[i]=66000;
			d_route[i]=4;
		}
		for(i=0; i<SIZE; i++){
			if (isAvtive(adj_array, i)==true){
				dijkstraCommercial(adj_array, i, d_nhops,d_route);
			}
		}

		// Fazer estatísticas
	}

	printf("Por implementar...\n");
	fclose(fp);
}
