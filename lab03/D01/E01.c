#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/***
  Fanti Andrea 235808
  lab 3 ex. 1
*/
int main (int argc, char* argv[]){
	int	n, lvl;
	if (argc != 2){
		fprintf(stderr, "USAGE: %s [number_of_levels]\n", argv[0]);
		return 1;
	}

	if (sscanf(argv[1], "%d", &n) != 1 || n < 1){
		fprintf(stderr, "error: the number of levels must be a positive integer\n");
		return 1;
	}

	for (lvl= 1; lvl < n; lvl++){
		if ((lvl%2) == 0){
			if (fork() && fork())
				lvl= n+1;
		}else if(fork())
			lvl= n+1;
	}

	if (lvl == n)
		printf("Process %d\n", getpid());

	return 0;
}
