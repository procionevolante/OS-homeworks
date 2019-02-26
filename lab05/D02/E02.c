#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

/***
  Fanti Andrea 235808
  lab 05 ex. 02
*/

#define RND_MIN 0
#define RND_MAX 1000000
#define FILE1 "F1"
#define FILE2 "F2"
#define FILESORTED "F12.sorted"

int rnd (int min, int max){
	return random()%(max-min+1)+ min;
}

FILE* tryfopen(char *fn, char *mode){
	FILE* ret;

	if ((ret= fopen(fn, mode)) == NULL){
		fprintf(stderr, "couldn't open '%s' in '%s' mode\n", fn, mode);
		exit(2);
	}
	return ret;
}

void write_rnd_numbers(char* file1, char* file2, int n){
	FILE	*fp1, *fp2;
	int	i;

	fp1= tryfopen(file1, "w");
	fp2= tryfopen(file2, "w");

	srandom(235808);

	for (i=0; i<n; i++){
		fprintf(fp1, "%d\n", rnd(RND_MIN, RND_MAX));
		fprintf(fp2, "%d\n", rnd(RND_MIN, RND_MAX));
	}

	fflush(fp1);
	fflush(fp2);

	fclose(fp1);
	fclose(fp2);
}

void int_txt2bin(char *fin_name, char* fout_name){
	int	n;
	FILE*	fin, *fout;;

	fin= tryfopen(fin_name, "r");
	fout= tryfopen(fout_name, "wb");

	while(fscanf(fin, "%d", &n) != EOF)
		fwrite(&n, sizeof(int), 1, fout);

	fclose(fin);
	fclose(fout);
}

void merge_and_sort(char *f1_name, char *f2_name, char *fsorted_name){
	FILE	*fin1, *fin2;
	FILE	*fsorted;
	int	n1, n2;
	int	nread1, nread2;
	
	fin1= tryfopen(f1_name, "rb");
	fin2= tryfopen(f2_name, "rb");
	fsorted= tryfopen(fsorted_name, "wb");

	nread1= fread(&n1, sizeof(int), 1, fin1);
	nread2= fread(&n2, sizeof(int), 1, fin2);

	while(nread1 == 1 && nread2 == 1)
		if(n1 < n2){
			fwrite(&n1, sizeof(int), 1, fsorted);
			nread1= fread(&n1, sizeof(int), 1, fin1);
		}else{
			fwrite(&n2, sizeof(int), 1, fsorted);
			nread2= fread(&n2, sizeof(int), 1, fin2);
		}
	
	// writing remaining of files
	if (nread1 > 0)
		do{
			fwrite(&n1, sizeof(int), 1, fsorted);
		}while(fread(&n1, sizeof(int), 1, fin1) == 1);
	if (nread2 > 0)
		do{
			fwrite(&n2, sizeof(int), 1, fsorted);
		}while(fread(&n2, sizeof(int), 1, fin2) == 1);

	fclose(fin1);
	fclose(fin2);
	fclose(fsorted);
}

int main (int argc, char* argv[]){
	int	k;

	if (argc != 2){
		fprintf(stderr, "USAGE: %s [k]\n", argv[0]);
		return 1;
	}

	if (sscanf(argv[1], "%d", &k) != 1 || k < 1){
		fprintf(stderr, "ERROR: k must be a positive integer number\n");
		return 2;
	}

	write_rnd_numbers(FILE1".txt", FILE2".txt", k);
	if(fork()){
		if (!fork()){
			execlp("sort", "sort", "-o", FILE1".txt", "-n", FILE1".txt", NULL);
			exit(16);
		}
		wait(NULL);
		wait(NULL);
	}else{
		execlp("sort", "sort", "-o", FILE2".txt", "-n", FILE2".txt", NULL);
		exit(16);
	}

	int_txt2bin(FILE1".txt", FILE1".bin");
	int_txt2bin(FILE2".txt", FILE2".bin");

	merge_and_sort(FILE1".bin", FILE2".bin", FILESORTED);

	unlink(FILE1".bin");
	unlink(FILE2".bin");

	return 0;
}
