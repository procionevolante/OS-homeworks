/***
  Fanti Andrea 235808
  lab 09 ex. 01
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <ctype.h>

typedef struct {
	FILE*	fp;
	int	c;
}Reader_arg;

FILE* tryfopen (char* fname, char* mode){
	FILE*	ret;

	if ((ret= fopen(fname, mode)) == NULL){
		fprintf(stderr, "ERROR: file '%s' can't be opened in mode '%s'\n", fname, mode);
		exit(5);
	}

	return ret;
}

void try_pthread_create (pthread_t* tid, pthread_attr_t* attr, void* (*func)(void*), void* arg){
	if (pthread_create(tid, attr, func, arg)){
		fprintf(stderr, "ERROR while creating thread\n");
		exit(5);
	}
}

void* reader_f (void* arg){
	Reader_arg*	myarg;

	myarg= (Reader_arg*) arg;
	myarg->c= fgetc(myarg->fp);
	pthread_exit(NULL);
}

void* writer_f (void* arg){
	int*	myarg;

	myarg= (int*) arg;
	if (*myarg != EOF && *myarg != '\0')
		putchar(*myarg);
	pthread_exit(NULL);
}

void* transf_f (void* arg){
	int*	myarg;

	myarg= (int*) arg;
	if (isprint(*myarg))
		*myarg= toupper(*myarg);
	pthread_exit(NULL);
}

int main (int argc, char* argv[]){
	Reader_arg	read_arg;
	pthread_t	tids[3];
	int	c2, c3;	// characters 2 and 3

	if (argc != 2){
		fprintf(stderr, "USAGE: %s [file_in]\n", argv[0]);
		exit(1);
	}

	read_arg.fp= tryfopen(argv[1], "r");
	read_arg.c= c2= c3= (int) '\0';
	while(c3 != EOF){
		try_pthread_create(&tids[0], NULL, reader_f, &read_arg); // T1
		try_pthread_create(&tids[1], NULL, transf_f, &c2); // T2
		try_pthread_create(&tids[2], NULL, writer_f, &c3); // T3
		pthread_join(tids[1], NULL);
		pthread_join(tids[2], NULL);
		c3= c2;
		pthread_join(tids[0], NULL);
		c2= read_arg.c;
	}

	fclose(read_arg.fp);

	return 0;
}
