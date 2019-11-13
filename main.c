#include "main.h"
#include "utils.h"
#include "adjlist.h"

int main(int argc, char *argv[]){

	FILE *fp ;
	if(argc<2){
		printf("Falta de argumentos\nExemplo: ./main links.txt");
		return -1;
	}
	else if(argc > 2){
		printf("Excesso de argumentos\nExemplo: ./lmp links.txt");
		return -1;
	}
	else{
		fp=fopen(argv[1], "r");
	}
	
	printf("Por implementar...\n");
	fclose(fp);
}
