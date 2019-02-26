#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/***
  Fanti Andrea 235808
  lab 4 ex. 2
*/

/*
	returns a random number that belongs to the interval [min,max]
*/
int rnd(int min, int max){
	return rand()%(max-min+1)+min;
}

int main (int argc, char* argv[]){
	pid_t	pid;
	int	n;
	int	r;

	pid= fork();
	if (pid == -1){
		fprintf(stderr, "couldn't fork\n");
		exit(1);
	}

	srand(getpid());
	n= rnd(0, 100);

	if(pid){
		printf("n1= %d\n", n);
		sleep(n);
		wait(&n);
		printf("[parent:%d] child returned %d\n", getpid(), WEXITSTATUS(n));
	}else{
		printf("n2= %d\n", n);
		printf("[child:%d] parent PID= %d\n", getpid(), getppid());
		sleep(n);
		r= rnd(0,255);
		printf("[child:%d] parent PID= %d, r= %d\n", getpid(), getppid(), r);
		exit(r);
	}

	exit(0);
}
