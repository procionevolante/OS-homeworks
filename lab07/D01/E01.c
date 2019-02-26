/***
  Fanti Andrea 235808
  lab 07 ex. 01
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void* thr_fnct (void* arg){
	int	n;
	int*	exitCode;
	
	n=  *(int*)arg;
	printf("Thread id: %ld, PID: %d \n", (unsigned long)pthread_self(), (int)getpid());
	sleep(n);
	printf("what will be my exit code? ");
	exitCode= (int*)malloc(sizeof(int));
	scanf("%d", exitCode);

	pthread_exit(exitCode);
}

int main (int argc, char* argv[]){
	pthread_t	t;
	int	n;
	int*	t_exitcode;

	if (argc != 2){
		fprintf(stderr, "USAGE: %s [n]\n", argv[0]);
		exit(1);
	}
	if (sscanf(argv[1], "%d", &n) != 1){
		fprintf(stderr, "error: %s isn NOT a integer > 0\n", argv[1]);
		exit(1);
	}

	pthread_create(&t, NULL, thr_fnct, &n);

	pthread_join(t, (void**)&t_exitcode);

	printf("thread %ld exited with exit value %d\n", t, *t_exitcode);
	free(t_exitcode);

	return 0;
}
