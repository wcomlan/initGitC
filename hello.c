

#include <stdio.h>

int main(int argc, char **argv){

	printf("hello World.... et puis c'est toutzz!\n");

int inc = 0;

	printf("%d arguments\n", argc);

	for(inc = 0; inc < argc; inc++){
		if (inc == 0){
			printf("le nom de la commande est %s\n",*argv);
		}else{
			printf("le nom de l'argument n°%d est %s\n", inc, *argv);
		}			
		
		argv++;
		
	}

	printf("Fin\n");

	return 0;

}
