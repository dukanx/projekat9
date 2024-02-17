#include <stdio.h>

int ucitaj(FILE *fajl){
	

}




int main(int argc, char *argv[]){

	printf ("Ukupan broj argumenata je %d\n", argc);

	int i;
	
	for(i=0; i<argc; i++){
		printf("Vrednost argumenta %d je %s\n", i, argv[i]);
	}
	
	return 0;
	
}