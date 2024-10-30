#include <stdio.h>
#include <stdlib.h>

int fatorial (int n){
	if (n==0)
		return 1;
	return n*fatorial(n-1);
}

int main (int argc,char* argv[]){
	printf("Argumentos Passados:%i\n",argc-1);
	if (argc < 2){
		return 0;
	}
	else{
		char *aux = argv[1];
		int n = fatorial(atoi(argv[1]));
		printf("Fatorial de %s: %i\n",aux, n );
	}
	return 0;
}