/*
* Create a C program that receives any number of command line arguments.
* For each argument, the program will create a thread.
* Each thread converts any lowercase letter into uppercase letters and prints 
* the initial string and the result
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <ctype.h>
#include <string.h>

typedef struct {
	int id;
	char *s;
} data;

void* upcase(void* arg) {
	data* d = (data*) arg;
	char* copy = malloc(sizeof(char) * strlen(d->s) + 1);
	strcpy(copy, d->s);
	
	for(int i = 0; i < strlen(copy); i++)
		copy[i] = toupper(copy[i]);

	printf("thread %d - arg %s - result %s\n", d->id, d->s, copy);
	return copy;
}

int main(int argc, char* argv[]) { 
	int size = argc - 1;
	pthread_t th[size];
	data* args = malloc(sizeof(data) * size);

	for(int i = 0; i < size; i++) {
		args[i].id = i;
		args[i].s = argv[i + 1];
		
		if(pthread_create(&th[i], NULL, upcase, &args[i]) != 0) {
			perror("Oh no");
		}		
	}

	printf("end:\n");
	for(int i = 0; i < size; i++) {
		void* res;
		if(pthread_join(th[i], &res) != 0) {
			perror("error on join");
		}
		printf("result from thread %d is %s\n", i, (char*) res);
		free(res);
	}
	
	free(args);

	return 0;
}
