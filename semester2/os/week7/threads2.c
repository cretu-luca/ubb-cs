#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int n = 10;

void* f(void* a) {
	int i;
	for(i = 0; i < n; i++){
		printf("s\n", *(int*)a);
	}
	free(a);
	return NULL;
}

int main(int argc, char** argv) {
	int i;
	int* a;
	pthread_t t[10];
	
	for(i = 0; i < 10; i++){
		a = (int*) malloc(sizeof(int));
		*a = i;
		pthread_create(&t[i], NULL, f, a);
	}

	for(i = 0; i < n; i++) {
		printf("main\n");
	}

	for(i = 0; i < 10; i++) {
		pthread_join(t[i], NULL);
	}

	return 0;
}
