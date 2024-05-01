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

int n = 0;
pthread_mutex_t rw;

void* r(void* arg) {
	for(int i = 0; i < 10; i++) {
		pthread_rwlock_rdlock(&rw);
		printf("%d\n", n);
		pthread_rwlock_unlock(&rw);
	}

	return NULL;
}

void* w(void* arg) { 
	for(int i = 0; i < 1000; i++) {
		pthread_rwlock_wrlock(&rw);
		n++;
		pthread_rwlock_unlock(&rw);
	}

	return NULL;
}

int main(int argc, char* argv[]) { 
	int r_size = 5, w_size = 2;

	pthread_t r_th[r_size];
	pthread_t w_th[w_size];
	pthread_mutex_init(&rw, NULL);

	for(int i = 0; i < w_size; i++) {
		if(pthread_create(&w_th[i], NULL, w, NULL) != 0) {
			perror("Oh no w");
		}		
	}
	
	for(int i = 0; i < r_size; i++) {
		if(pthread_create(&r_th[i], NULL, r, NULL) != 0) {
			perror("Oh no r");
		}		
	}
	
	for(int i = 0; i < w_size; i++) {
		if(pthread_join(w_th[i], NULL) != 0) {
			perror("error on join w");
		}
	}

	for(int i = 0; i < r_size; i++) {
		if(pthread_join(r_th[i], NULL) != 0) {
			perror("error on join r");
		}
	}
	pthread_rwlock_destroy(&rw);

	printf("n = %d\n", n);
	
	return 0;
}
