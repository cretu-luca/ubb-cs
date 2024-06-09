#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>

typedef struct {

	FILE* fd;
	int* wordIndex;
	pthread_mutex_t* mutex;
	pthread_barrier_t* barrier;

} data;

void* f(void* arg) {
	
	data* d = (data*) arg;

	while(1) {

		pthread_mutex_lock(d->mutex);
			
		int wordsToCount = random() % 3 + 1;
		int wordsFinalIndex = *d->wordIndex + wordsToCount;

		while(fscanf(fd, "%s", 

		pthread_mutex_unlock(d->mutex);

		pthread_barrier_wait(d->barrier);
	}
	
}

int main(int argc, char* argv[]) {

	FILE* fd = fopen(argv[1], "r");

	int n = atoi(argv[2]);
	int* wordIndex = malloc(sizeof(int) * 100);
	*wordIndex = 0;

	pthread_mutex_t mutex;
	pthread_mutex_init(&mutex, NULL);

	pthread_barrier_t barrier;
	pthread_barrier_init(&barrier, NULL, n);

	pthread_t td[n];
	data arg[n];
	
	for(int i = 0; i < n; i++) {
		
		arg[i].path = path;
		arg[i].wordIndex = wordIndex;
		arg[i].mutex = &mutex;
		pthread_create(&td[i], NULL, f, &arg[i]); 
	}

	
	for(int i = 0; i < n; i++) {

		pthread_join(td[i], NULL);
	}

	free(wordIndex);
}
