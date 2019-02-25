/***
  Fanti Andrea 235808
  lab 07 ex. 02
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void*	print_recursive(void* n) {
	int	ns[2];
	pthread_t	t_ids[2];
	int	retvals[2];

	if (*(int*)n == 0){	//	termination condition
		printf("%ld\n", (unsigned long)pthread_self());
		pthread_exit(NULL);
	}

	ns[0]= ns[1]= *(int*)n-1;
	pthread_create(&t_ids[0], NULL, print_recursive, &ns[0]);
	pthread_create(&t_ids[1], NULL, print_recursive, &ns[1]);
	pthread_join(t_ids[0], (void**)&retvals[0]);
	pthread_join(t_ids[1], (void**)&retvals[1]);
	pthread_exit(NULL);
}

int main (int argc, char* argv[]){
	int	n;

	if (argc != 2){
		fprintf(stderr, "USAGE: %s [n]\n", argv[0]);
		exit(1);
	}
	if (sscanf(argv[1], "%d", &n) != 1 || n <= 0){
		fprintf(stderr, "error: %s is NOT an integer > 0\n", argv[1]);
		exit(1);
	}
	
	print_recursive(&n);

	return 0;
}
