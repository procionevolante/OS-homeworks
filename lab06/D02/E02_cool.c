/***
  Fanti Andrea 235808
  lab 06 ex. 02

  This is an alternative implementation of the exercise 2 of lab 6 of OS.
  The difference with respect to the original text is that this version actually
  parallelizes the file sorting.

  This code can be further improved by starting to collect replies from child
  processes once a lot of files has been sent, since the whole program would
  lock if the child tries to write the answer to a full pipe.
  (main process waiting for a ready child, and the children do not qualify as
  ready until the reply has been sent to the parent)
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

#define CMD_MAXLEN 1024

FILE*	tryfopen(char* fn, char* mode){
	FILE*	ret;

	if ((ret= fopen(fn, mode)) == NULL){
		fprintf(stderr, "[%d] couldn't open file '%s' in mode '%s'\n", getpid(), fn, mode);
		exit(3);
	}
	return ret;
}
void* trymalloc (size_t size){
	void*	ret;
	if ((ret= malloc(size)) == NULL){
		fprintf(stderr, "couldn't allocate %ld bytes\n", size);
		exit(1);
	}
	return ret;
}

/***
	count the lines of the file with filename passed as parameters
*/
int num_lines (char* fname){
	FILE*	fp;
	int	cnt;
	char	c;

	fp = tryfopen(fname, "r");

	cnt= 0;
	while((c= fgetc(fp)) != EOF)
		if (c == '\n')
			cnt++;
	fclose(fp);

	return cnt;
}

void parent (int* lock, FILE* list_fp, int num_children, int** cnts, int req_fd, int data_fd, int ans_fd){
	char*	fname;
	int	len, tmp;
	int	reply[2];
	int	nfiles;

	fname= (char*)trymalloc(FILENAME_MAX*sizeof(char));

	write(lock[1], &tmp, 1);//unlock
	for(nfiles= 0; (fgets(fname, FILENAME_MAX, list_fp)) != NULL; nfiles++){
		len= strlen(fname);
		fname[len-1]= '\0';
		printf("[parent:%d] read '%s' from file\n", getpid(), fname);
		printf("[parent:%d] about to send file '%s', filename length=%d\n", getpid(), fname, len);
		// waiting for request
		read(req_fd, &tmp, 1);
		// writing a reply
		write(data_fd, &len, sizeof(int));
		write(data_fd, fname, len*sizeof(char));
	}

	printf("[parent:%d] %d files sent, reading replies\n", getpid(), nfiles);
	for (len= 0; len < nfiles; len++){
		// reading a reply
		read(ans_fd, reply, 2*sizeof(int));
		for(tmp= 0; tmp<num_children &&  cnts[tmp][0] != reply[0]; tmp++) ;
		cnts[tmp][1]+= reply[1];
	}
	for (len= 0; len < num_children; len++)
		kill(cnts[len][0], SIGPIPE);	// default action is to terminate the process

	fclose(list_fp);
	close(req_fd);
	close(data_fd);
	close(ans_fd);
	printf("\n#files sorted= %d\n", num_lines("list.txt"));
	printf("PID\tlines sorted\n");
	
	for (len= tmp= 0; len < num_children; len++){
		printf("%d\t%d\n", cnts[len][0], cnts[len][1]);
		tmp+= cnts[len][1];
	}
	
	printf("\ttotal %d\n", tmp);
	
	free(fname);
}

void sigpipe_handler (int sig){
	if (sig==SIGPIPE){
		printf("[%d] exiting due to SIGPIPE\n", getpid());
		exit(0);
	}
}

void child (int* lock, int req_fd, int data_fd, int ans_fd){
	char*	fname;
	char*	cmd;
	int	fname_len;
	int	ans[2];

	while(1){
		// send a request (a random byte)
		write(req_fd, &fname_len, 1);
		// read the filename
		read(lock[0], &fname_len, 1);//lock
		printf("[%d] READY, request sent\n", getpid());
		if (read(data_fd, &fname_len, sizeof(int)) != sizeof(int)){
			fprintf(stderr, "[%d] could not retrieve fname_length from pipe\n", getpid());;
			exit(-1);
		}
		printf("[%d] len=%d\n", getpid(), fname_len);
		fname= trymalloc(fname_len*sizeof(char));
		read(data_fd, fname, fname_len*sizeof(char));
		printf("[%d] fname '%s'\n", getpid(), fname);
		write(lock[1], &fname_len, 1);//unlock
		// elaborate the file
		cmd= (char*)trymalloc((2*fname_len+20)*sizeof(char));
		sprintf(cmd, "sort -o '%s' '%s'", fname, fname);
		printf("[%d]$ %s\n", getpid(), cmd);
		system(cmd);
		free(cmd);
		// writing response
		ans[0]= getpid();
		ans[1]= num_lines(fname);
		free(fname);
		write(ans_fd, ans, sizeof(ans));
	}
}

int main (int argc, char* argv[]){
	int	data_pipe[2], request_pipe[2], answer_pipe[2];
	int	lock[2];
	int**	cnts;
	char	cmd[CMD_MAXLEN+1];
	int	i, c;
	FILE*	fp;
	pid_t	p;

	if (argc != 3){
		fprintf(stderr, "USAGE: %s [C] [dir]\n", argv[0]);
		exit(1);
	}
	
	snprintf(cmd, CMD_MAXLEN+1, "ls '%s' > list.txt", argv[2]);
	if (system(cmd)){
		fprintf(stderr, "error while generating list.txt, exiting...\n");
		exit(2);
	}

	if (sscanf(argv[1], "%d", &c) != 1){
		perror("");
		exit(2);
	}
	cnts= (int**)trymalloc(c* sizeof(int*));
	for(i= 0; i < c; i++){
		cnts[i]= (int*) trymalloc(2*sizeof(int));
		cnts[i][1]= 0;
	}
	pipe(request_pipe);
	pipe(data_pipe);
	pipe(answer_pipe);
	pipe(lock);

	fp= tryfopen("list.txt", "r");

	for (i= 0 ; i<c; i++){
		if ((p= fork()) == 0){
			if (chdir(argv[2]) == -1){
				perror("[child] couldn't do chdir");
				exit(2);
			}
			close(request_pipe[0]);
			close(data_pipe[1]);
			close(answer_pipe[0]);
			signal(SIGPIPE, sigpipe_handler);
			child(lock, request_pipe[1], data_pipe[0], answer_pipe[1]);
		}else
			cnts[i][0]= p;
	}
	if (p){
		close(request_pipe[1]);
		close(data_pipe[0]);
		close(answer_pipe[1]);
		parent(lock, fp, c, cnts, request_pipe[0], data_pipe[1], answer_pipe[0]);
		sprintf(cmd, "sort -m -o all_sorted.txt %s/*", argv[2]);
		system(cmd);
	}
	
	return 0;
}
