/***
  Fanti Andrea 235808
  lab 11 ex. 03
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>
#include <pthread.h>

#define NUM_SEMAPHORES 6

typedef struct {
	sem_t*	sems;
	int	num_cycles;
} Thr_args;

void tcore(char* s){
	struct timespec	time;

	time.tv_sec= 0;
	time.tv_nsec= (rand()%1001)*1000000;	// converted to milliseconds
	nanosleep(&time, NULL);
	puts(s);
}

void* a (void* t_arg){
	Thr_args* arg;
	int	i;
	
	arg= (Thr_args*) t_arg;
	for (i= 0; i < arg->num_cycles; i++){
		sem_wait(&arg->sems[0]);	// wait for permission to start the cycle
		tcore("A");
		// unlocks B and C
		sem_post(&arg->sems[1]);
		sem_post(&arg->sems[2]);
	}
	pthread_exit(NULL);
}

void* b (void* t_arg){
	Thr_args* arg;
	int	i;

	arg= (Thr_args*) t_arg;
	for (i= 0; i < arg->num_cycles; i++){
		sem_wait(&arg->sems[1]);
		tcore("B");
		sem_post(&arg->sems[3]);
		sem_post(&arg->sems[3]);
	}
	pthread_exit(NULL);
}

void* c (void* t_arg){
	Thr_args* arg;
	int	i;

	arg= (Thr_args*) t_arg;
	for (i= 0; i < arg->num_cycles; i++){
		sem_wait(&arg->sems[2]);
		tcore("C");
		sem_post(&arg->sems[4]);
		sem_post(&arg->sems[4]);
	}
	pthread_exit(NULL);
}

void* d (void* t_arg){
	Thr_args* arg;
	int	i;

	arg= (Thr_args*) t_arg;
	for (i= 0; i < arg->num_cycles; i++){
		sem_wait(&arg->sems[3]);
		sem_wait(&arg->sems[4]);
		tcore("D");
		sem_post(&arg->sems[5]);
	}
	pthread_exit(NULL);
}

void* e (void* t_arg){
	Thr_args* arg;
	int	i;

	arg= (Thr_args*) t_arg;
	for (i= 0; i < arg->num_cycles; i++){
		sem_wait(&arg->sems[3]);
		sem_wait(&arg->sems[4]);
		tcore("E");
		sem_post(&arg->sems[5]);
	}
	pthread_exit(NULL);
}

void* f (void* t_arg){
	Thr_args* arg;
	int	i;

	arg= (Thr_args*) t_arg;
	for (i= 0; i < arg->num_cycles; i++){
		sem_wait(&arg->sems[5]);
		sem_wait(&arg->sems[5]);
		tcore("F");
		sem_post(&arg->sems[0]);
	}
	
	for (i= 0; i <  NUM_SEMAPHORES; i++)
		sem_destroy(&arg->sems[i]);

	pthread_exit(NULL);
}

int main (int argc, char* argv[]){
	sem_t*	sems;
	pthread_t	tids[6];
	Thr_args*	tharg;
	int	i;

	if (argc != 2){
		fprintf(stderr, "USAGE: %s [number_of_cycles]\n", argv[0]);
		exit(1);
	}
	if ((sems= (sem_t*) malloc(NUM_SEMAPHORES*sizeof(sem_t))) == NULL){
		fprintf(stderr, "couldn't allocate the needed semaphores\n");
		exit(5);
	}
	if ((tharg= (Thr_args*) malloc(sizeof(Thr_args))) == NULL){
		fprintf(stderr, "couldn't allocate the thread arguments\n");
		exit(5);
	}
	if (sscanf(argv[1], "%d", &tharg->num_cycles) != 1 || tharg->num_cycles<1){
		fprintf(stderr, "ERROR: '%s' is not a valid number of cycles\n", argv[1]);
		exit(10);
	}

	for (i= 0; i < NUM_SEMAPHORES; i++)
		sem_init(&sems[i], 0, 0);
	tharg->sems= sems;
	
	pthread_create(&tids[0], NULL, a, tharg);
	pthread_create(&tids[1], NULL, b, tharg);
	pthread_create(&tids[2], NULL, c, tharg);
	pthread_create(&tids[3], NULL, d, tharg);
	pthread_create(&tids[4], NULL, e, tharg);
	pthread_create(&tids[5], NULL, f, tharg);
	
	sem_post(&tharg->sems[0]);

	pthread_exit(NULL);
}
