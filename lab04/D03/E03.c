#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

/***
  Fanti Andrea 235808
  lab 4 ex. 3
*/
void*	trymalloc(size_t size){
	void*	ret;
	if( (ret= malloc(size)) == NULL){
		fprintf(stderr, "couldn't allocate array\n");
		exit(1);
	}

	return ret;
}

int main (int argc, char* argv[]){
	int	n, i;
	int	statLoc;
	pid_t*	pids;
	int*	v;

	do{
		printf("insert n: ");
	}while(scanf("%d", &n) != 1);

	v= trymalloc(n*sizeof(int));
	pids= trymalloc(n*sizeof(pid_t));

	for (i= 0; i < n; i++){
		printf("insert v[%d]: ", i);
		scanf("%d", &v[i]);
	}

	for (i= 0; i < n; i++)
		if ( (pids[i]= fork()) == 0){
			sleep(n-i);
			exit(n-i);
		}

	for(i= 0; i < n; i++){
		waitpid(pids[i], &statLoc, 0);
		printf("child %d exited with return code %d, v[%d]= %d\n", pids[i], WEXITSTATUS(statLoc), i, v[i]);
	}

	return 0;
}
