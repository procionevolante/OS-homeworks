/***
  Fanti Andrea 235808
  lab 07 ex. 03
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct Pthread_tree_s Pthread_tree;
struct Pthread_tree_s{
	Pthread_tree*	p;	// parent
	int			lvl;	// remaining levels
	pthread_t	id;
};

void print_gen_tree (Pthread_tree* t, char* out){
	if (t->p != NULL)
		print_gen_tree(t->p, out);
	sprintf(out, "%s %ld", out, t->id);
}

int tree_depth (Pthread_tree* t){
	int	ret;

	for (ret= 0; t != NULL; t= t->p, ret++);

	return ret;
}

void*	populate(void* lt) {
	Pthread_tree	t_ids[2];
	int	retvals[2];
	Pthread_tree*	mytree;

	mytree= (Pthread_tree*) lt;

	if (mytree->lvl <= 0){	//	termination condition
		char*	out;
		if ((out= (char*) malloc(tree_depth(mytree)*20*sizeof(char))) == NULL){
			fprintf(stderr, "couldn't allocate array to print generation tree, exiting\n");
			pthread_exit(NULL);
		}
		print_gen_tree(mytree, out);
		printf("Thread tree:%s\n", out);
		free(out);
		pthread_exit(NULL);
	}

	t_ids[0].p= t_ids[1].p= mytree;
	t_ids[0].lvl= t_ids[1].lvl= mytree->lvl-1;
	pthread_create(&t_ids[0].id, NULL, populate, &t_ids[0]);
	pthread_create(&t_ids[1].id, NULL, populate, &t_ids[1]);
	pthread_join(t_ids[0].id, (void**)&retvals[0]);
	pthread_join(t_ids[1].id, (void**)&retvals[1]);
	pthread_exit(NULL);
}

int main (int argc, char* argv[]){
	int	n;
	Pthread_tree	root;

	if (argc != 2){
		fprintf(stderr, "USAGE: %s [n]\n", argv[0]);
		exit(1);
	}
	if (sscanf(argv[1], "%d", &n) != 1 || n <= 0){
		fprintf(stderr, "error: %s isn NOT a integer > 0\n", argv[1]);
		exit(1);
	}
	
	root.lvl= n;
	root.p= NULL;
	root.id= pthread_self();
	
	populate(&root);

	return 0;
}
