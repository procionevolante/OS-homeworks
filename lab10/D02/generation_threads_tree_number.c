/***
  Fanti Andrea 235808
  lab 10 ex. 02
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int	cur_id;	// last used ID
int*	gentree;	// generation tree
int	dim, nlvl; // dimension of gentree and tr, number of levels
pthread_mutex_t	print_mtx;	// mutex to make the threads print one at a time
sem_t	get_id;	// semaphore to make the parent thread wait until the child retrieved its id
pthread_mutex_t	gen_thread;	// only one thread may generate other threads at the same time

void print_gentree(int id){
	if (gentree[id] != 0)
		print_gentree(gentree[id]);
	printf(" %d", id);
}

int get_level (int id){
	int	cnt;
	
	for (cnt= 0; gentree[id] != 0; cnt++)
		id= gentree[id];

	return cnt;
}

void* tbody (void* nul) {
	int	myid;
	int	i;
	pthread_t	chld[2];
	
	myid= cur_id;
	cur_id++;
	sem_post(&get_id);	// unlock the parent thread

	if (get_level(myid) >= nlvl){
		pthread_mutex_lock(&print_mtx);
		printf("Thread tree:");
		print_gentree(myid);
		putchar('\n');
		pthread_mutex_unlock(&print_mtx);

		pthread_exit(NULL);
	}

	for (i= 0; i < 2; i++){
		pthread_mutex_lock(&gen_thread);
		sem_wait(&get_id);
		gentree[cur_id]= myid;	// the parent of the about-to-be-created thread is this thread
		pthread_create(&chld[i], NULL, tbody, NULL);
		sem_wait(&get_id);	// wait for the child to get its ID
		sem_post(&get_id);
		pthread_mutex_unlock(&gen_thread);
	}
	
	for (i= 0; i < 2; i++)
		pthread_join(chld[i], NULL);

	pthread_exit(NULL);
}

void* trymalloc (size_t size){
	void*	ret;
	if ((ret= malloc(size)) == NULL){
		fprintf(stderr, "ERROR: couldn't allocate %lu bytes\n", size);
		exit(10);
	}
	return ret;
}

int main (int argc, char* argv[]){
	if (argc != 2){
		fprintf(stderr, "USAGE: %s [num_levels]\n", argv[0]);
		return 1;
	}

	if (sscanf(argv[1], "%d", &nlvl) != 1 || nlvl < 0){
		fprintf(stderr, "ERROR: '%s' is not a valid number of levels\n", argv[1]);
		return 5;
	}
	dim= 1<<(nlvl+1); // dim= 2^(nlvl+1)
	gentree= (int*) trymalloc(dim*sizeof(int));

	cur_id= 1;
	pthread_mutex_init(&gen_thread, NULL);
	sem_init(&get_id, 0, 0); // get_id is initialized to locked
	pthread_mutex_init(&print_mtx, NULL);
	gentree[1]= 0;	// thread 1 (main thread) has no parent
	tbody(NULL);
	pthread_mutex_destroy(&gen_thread);
	sem_destroy(&get_id);
	pthread_mutex_destroy(&print_mtx);

	return 0;
}
