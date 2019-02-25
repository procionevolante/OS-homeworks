#include <stdio.h>
#include <stdlib.h>

int	main (int argc, char *argv[]){
	FILE*	fp;
	int	cnt;

	if (argc != 2){
		fprintf(stderr, "USAGE: %s [file]\n", argv[0]);
		return 1;
	}
	if ((fp= fopen(argv[1], "r")) == NULL){
		fprintf(stderr, "couldn't open '%s'\n", argv[1]);
		return 2;
	}
	//counting the number of words
	for(cnt= 0; fscanf(fp, "%*s") != EOF; cnt++) {}
	fclose(fp);

	printf("%s: %d word(s)\n", argv[1], cnt);
	
	return 0;
}
