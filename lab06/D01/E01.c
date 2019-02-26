#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>
#include <string.h>

/***
  Fanti Andrea 235808
  lab 06 ex. 01
*/
#define END_STR "end"
#define BUF_SIZE 4096

void producer (int w_fd){
	char	buf[BUF_SIZE];
	int	i, cnt;
	
	cnt= 0;
	while(1){
		fgets(buf, BUF_SIZE, stdin);
		//printf("received '%s'\n", buf);
		for (i= 0; buf[i]!='\0'; i++){
			write(w_fd, &buf[i], sizeof(char));
			if (buf[i] == END_STR[cnt]){
				cnt++;
				if (cnt == strlen(END_STR)){
					close(w_fd);
					exit(0);
				}
			}else
				cnt= 0;
		}
	}
}

void consumer(int r_fd){
	char	c;
	int	cnt;

	cnt= 0;
	while(1){
		read(r_fd, &c, sizeof(char));
		putchar(toupper(c));
		if (c == END_STR[cnt]){
			cnt++;
			if (cnt == strlen(END_STR)){
				close(r_fd);
				exit(0);
			}
		}else
			cnt= 0;
	}
}

int main (int argc, char* argv[]){
	int	pipe_fd[2];

	if (pipe(pipe_fd)){
		fprintf(stderr, "couldn't create a pipe\n");
		exit(1);
	}
	if(fork()){
		if (fork()){
			wait(NULL);
			wait(NULL);
			close(pipe_fd[1]);
			close(pipe_fd[0]);
		}else{
			close(pipe_fd[1]);
			consumer(pipe_fd[0]);
		}
	}else{
		close(pipe_fd[0]);
		producer(pipe_fd[1]);
	}
	
	return 0;
}
