/***
  Fanti Andrea 235808
  lab 10 ex. 01
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char* argv[]){
	int*	ids;
	int	n,  lvl;
	int	nextid;

	if (argc != 2){
		fprintf(stderr, "USAGE: %s [num_levels]\n", argv[0]);
		return 1;
	}

	if (sscanf(argv[1], "%d", &n) != 1 || n < 0){
		fprintf(stderr, "ERROR: '%s' is not a valid number of levels\n", argv[1]);
		return 5;
	}
	n++;
		
	if ((ids= malloc(n*sizeof(int))) == NULL){
		fprintf(stderr, "error in allocating the array\n");
		return 10;
	}
	
	nextid= 1;
	ids[0]= 1;
	for (lvl= 1; lvl < n; lvl++){
		nextid<<=1;
		if (fork()){
			nextid++;
			if (fork())
				exit(0);
		}
		ids[lvl]= nextid;
	}

	printf("Process tree:");
	for (lvl= 0; lvl < n; lvl++)
		printf(" %d", ids[lvl]);
	putchar('\n');

	return 0;
}
