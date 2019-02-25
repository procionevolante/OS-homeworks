// copy a source file to a destination fil
#include <stdio.h>
#include <string.h>

#define fileNameR "In.txt"
#define fileNameW "Out.txt"

#define L 1024

void f1 (char *, char *);

int main (int argc,  char *argv[]){
  char name[L];

  sprintf (name, "%s.v1", fileNameW);
  f1 (fileNameR, name);

  return(0);
}

void f1 (char *nameR, char *nameW){
  FILE *fpR, *fpW;
  char c;

  fpR = fopen (nameR, "r");
  fpW = fopen (nameW, "w");
  if (fpR==NULL || fpW==NULL) {
    fprintf (stderr, "Error opening file.\n");
    return;
  }
  while (!feof(fpR)) {
    c = fgetc (fpR);
    fputc (c, fpW);
  }
  fclose(fpR);
  fclose(fpW);
}


