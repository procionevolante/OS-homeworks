/***
  Fanti Andrea 235808
  lab 11 ex. 02
*/
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <time.h>
#include <pthread.h>

#define NUM_LOOPS 10
#define NUM_SEM 4

void tcore(char* s){
	struct timespec	time;

	time.tv_sec= 0;
	time.tv_nsec= (rand()%1001)*1000000;	// converted to milliseconds
	nanosleep(&time, NULL);
	puts(s);
}

void* a (void* arg){
	sem_t* sems;
	int	i;

	sems= (sem_t*) arg;
	for (i= 0; i < NUM_LOOPS; i++){
		sem_wait(&sems[0]);
		tcore("A");
		sem_post(&sems[1]);
		sem_post(&sems[2]);
	}

	pthread_exit(NULL);
}

void* b (void* arg){
	sem_t* sems;
	int	i;

	for (i= 0; i < NUM_LOOPS; i++){
		sems= (sem_t*) arg;
		sem_wait(&sems[1]);
		tcore("B");
		sem_post(&sems[3]);
	}

	pthread_exit(NULL);
}

void* c (void* arg){
	sem_t* sems;
	int	i;

	for (i= 0; i < NUM_LOOPS; i++){
		sems= (sem_t*) arg;
		sem_wait(&sems[2]);
		tcore("C");
		sem_post(&sems[3]);
	}

	pthread_exit(NULL);
}

void* d (void* arg){
	sem_t* sems;
	int	i;

	for (i= 0; i < NUM_LOOPS; i++){
		sems= (sem_t*) arg;
		sem_wait(&sems[3]);
		sem_wait(&sems[3]);
		tcore("D");
		sem_post(&sems[0]);
	}

	for (i= 0; i < 2; i++)
		sem_destroy(&sems[i]);
	free(sems);

	pthread_exit(NULL);
}

int main (int argc, char* argv[]){
	sem_t*	sems;
	int	i;
	pthread_t	tids[4];

	srand(time(NULL));
	if ((sems= (sem_t*)malloc(NUM_SEM*sizeof(sem_t))) == NULL){
		fprintf(stderr, "couldn't allocate the needed semaphores\n");
		exit(1);
	}

	for (i= 0; i < NUM_SEM; i++)
		sem_init(&sems[i], 0, 0);
	pthread_create(&tids[0], NULL, a, sems);
	pthread_create(&tids[1], NULL, b, sems);
	pthread_create(&tids[2], NULL, c, sems);
	pthread_create(&tids[3], NULL, d, sems);
	// sems[0] is used to implement the cycle
	sem_post(&sems[0]);

	/*
	for (i= 0; i < 4; i++)
		pthread_join(tids[i], NULL);
	*/

	pthread_exit(NULL);
}
