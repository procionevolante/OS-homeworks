/***
  Fanti Andrea 235808
  lab 10 ex. 03
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct {
	pthread_t	owner;
	long	bal;	// balance
	pthread_mutex_t	mtx;	// mutex for the account
} Account;

void* manage (void* arg){
	Account	*mine, *other;
	long	balance, amount;

	if (pthread_equal(((Account*)arg)->owner, pthread_self())){
		mine= (Account*)arg;
		other= ((Account*)arg)+1;
	}else{
		other= (Account*)arg;
		mine= ((Account*)arg)+1;
	}
	srandom(time(NULL)+ (int)mine->owner);

	while(1){
		sleep(random()%9);
		printf("[%lu] reading balance...\n", pthread_self());
		pthread_mutex_lock(&mine->mtx);
		balance= mine->bal;
		if (balance != 0){
			sleep(random()%5);
			printf("[%lu] moving money...\n", pthread_self());
			pthread_mutex_lock(&other->mtx);
			amount= (random()%4001)+ 1000;
			if (amount > balance)
				amount= balance;
			mine->bal -= amount;
			other->bal += amount;
			pthread_mutex_unlock(&other->mtx);
		}
		pthread_mutex_unlock(&mine->mtx);
		printf("[%lu] moved %ld euros. New balance: %ld\n", pthread_self(), amount, mine->bal);
	}
	
	return NULL;
}

int main (int argc, char* argv[]){
	Account acc[2];

	acc[0].bal= acc[1].bal= 100000L;
	pthread_mutex_init(&acc[0].mtx, NULL);
	pthread_mutex_init(&acc[1].mtx, NULL);

	pthread_create(&acc[0].owner, NULL, manage, (void*)acc);
	pthread_create(&acc[1].owner, NULL, manage, (void*)acc);

	pthread_join(acc[0].owner, NULL);
	pthread_join(acc[0].owner, NULL);
	pthread_mutex_destroy(&acc[0].mtx);
	pthread_mutex_destroy(&acc[1].mtx);

	return 0;
}
