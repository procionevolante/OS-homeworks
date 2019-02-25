#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>

/***
  Fanti Andrea 235808
  lab 05 ex. 04
*/

#define MAX_LINE_LENGTH 4096

int	n_sig_rx;	// number of SIGUSR2 received
int	ign_after;	// ignore 5 sigusr1 after this number of signals


int rnd (int min, int max){
	return random()%(max-min+1)+ min;
}

void parent_proc(FILE* fp){
	char	line[MAX_LINE_LENGTH+1];
	int	linenum;
	
	linenum= 1;
	while(1){
		if (fgets(line, MAX_LINE_LENGTH+1, fp) == NULL){
			rewind(fp);
			linenum= 1;
		}else{
			if (!(n_sig_rx%2)) // if we received an even number of SIGUSR1s
				printf("%d\t%s", linenum, line);
			linenum++;
		}
	}
}

void sigusr1_handler(int sig){
	n_sig_rx++;
	if (n_sig_rx == ign_after)
		signal(SIGUSR1, SIG_IGN);
	else if (n_sig_rx > ign_after){ // exit
		printf("received %d signals (of which 5 have been ignored)\n", n_sig_rx+5);
		exit(EXIT_SUCCESS);
	}
}

// SIGUSR2 is used to reactivate reception of SIGUSR1s (after ignoring 5 of them)
void sigusr2_handler(int sig){
	signal(SIGUSR1, sigusr1_handler);
}

int main (int argc, char* argv[]){
	pid_t	ch_pid;
	FILE*	fp;

	if (argc != 2){
		fprintf(stderr, "USAGE: %s [file]\n", argv[0]);
		return 1;
	}

	n_sig_rx= 0;

	srandom(time(NULL)+ getpid());
	ign_after= rnd(10,20);

	ch_pid= fork();
	if (ch_pid < 0)
		perror("couldn't generate a child process");
	else if (ch_pid > 0){
		/* parent */
		if ( (fp= fopen(argv[1], "r")) == NULL){
			fprintf(stderr, "couldn't open the file '%s'\n", argv[1]);
			kill(ch_pid, SIGTERM);
			exit(2);
		}
		signal(SIGUSR1, sigusr1_handler);
		signal(SIGUSR2, sigusr2_handler);
		parent_proc(fp);
	}else{
		/* child */
		for (n_sig_rx= 0; n_sig_rx<ign_after+6; n_sig_rx++){
			sleep(rnd(1,10));
			kill(getppid(), SIGUSR1);
			if(n_sig_rx == ign_after+4)
				kill(getppid(), SIGUSR2);
		}
	}
	
	return 0;
}
