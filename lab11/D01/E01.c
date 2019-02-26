/***
  Fanti Andrea 235808
  lab 11 ex. 01
*/
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <time.h>
#include <pthread.h>

void tcore(char* s){
	struct timespec	time;

	time.tv_sec= 0;
	time.tv_nsec= (rand()%1001)*1000000;	// converted to milliseconds
	nanosleep(&time, NULL);
	puts(s);
}

void* a (void* arg){
	sem_t* sems;

	sems= (sem_t*) arg;
	tcore("A");
	sem_post(&sems[0]);
	sem_post(&sems[0]);

	pthread_exit(NULL);
}

void* b (void* arg){
	sem_t* sems;

	sems= (sem_t*) arg;
	sem_wait(&sems[0]);
	tcore("B");
	sem_post(&sems[1]);

	pthread_exit(NULL);
}

void* c (void* arg){
	sem_t* sems;

	sems= (sem_t*) arg;
	sem_wait(&sems[0]);
	tcore("C");
	sem_post(&sems[1]);

	pthread_exit(NULL);
}

void* d (void* arg){
	sem_t* sems;

	sems= (sem_t*) arg;
	sem_wait(&sems[1]);
	sem_wait(&sems[1]);
	tcore("D");

	pthread_exit(NULL);
}

int main (int argc, char* argv[]){
	sem_t	sems[2];
	int	i;
	pthread_t	tids[4];

	srand(time(NULL));
	for (i= 0; i < 2; i++)
		sem_init(&sems[i], 0, 0);
	pthread_create(&tids[0], NULL, a, sems);
	pthread_create(&tids[1], NULL, b, sems);
	pthread_create(&tids[2], NULL, c, sems);
	pthread_create(&tids[3], NULL, d, sems);

	for (i= 0; i < 4; i++)
		pthread_join(tids[i], NULL);
	for (i= 0; i < 2; i++)
		sem_destroy(&sems[i]);

	return 0;
}
