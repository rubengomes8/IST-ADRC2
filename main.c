#include "main.h"
#include "utils.h"
#include "adjlist.h"

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
		
		// Para cada nó aplicar Dijkstra Comercial e Dijkstra normal

		// Fazer estatísticas
	}

	printf("Por implementar...\n");
	fclose(fp);
}
