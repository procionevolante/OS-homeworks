/***
  Fanti Andrea 235808
  lab 09 ex. 02
*/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int	hist[3];
int	error, success, terminate;

void sig_handler (int	sig){
	hist[0]= hist[1];
	hist[1]= hist[2];
	hist[2]= sig;
	/*
	for (int i=0; i < 3; i++)
		printf("%d ", hist[i]);
	putchar('\n');
	*/
	if (hist[2] == hist[1] && (hist[1] == SIGUSR1 || hist[1] == SIGUSR2)){
		success++;
		if (hist[0] == hist[1])
			terminate= 1;
	}
	else if ((hist[2] == SIGUSR1 && hist[1] == SIGUSR2) || (hist[2] == SIGUSR2 && hist[1] == SIGUSR1))
		error++;
}

void check (int sig){
	for ( ; success > 0; success--)
		printf("SUCCESS!\n");
	for ( ; error > 0; error--)
		printf("ERROR!\n");
	if (terminate)
		exit(0);
	alarm(5);
}

int main (int argc, char* argv[]){
	hist[0]= hist[1]= hist[2]= -1;
	error= success= terminate= 0;

	setbuf(stdout, 0);

	signal(SIGUSR1, sig_handler);
	signal(SIGUSR2, sig_handler);
	signal(SIGALRM, check);

	alarm(5);
	while(1){
		sleep(10);
	}

	return 0;
}
