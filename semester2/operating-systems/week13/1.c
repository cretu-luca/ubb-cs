#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

typedef struct {
	
	int index;
	int* shared;
	pthread_mutex_t* mutex;
} data;

void* f(void* arg) {
	
	data* d = (data*) arg;

	while(1) {
		pthread_mutex_lock(d->mutex);
		
		if(*d->shared > 500 || *d->shared < -500) {
	
			pthread_mutex_unlock(d->mutex);
			break;
		}

		int sign = random() % 2;
		int value;

		if(sign == 0) {
			value = (random() % 501) * (-1);
		} else {
			value = random() % 501;
		}

		printf("thread[%d] modified %d by %d\n", d->index, *d->shared, value);
		*(d->shared) += value;
	
		pthread_mutex_unlock(d->mutex);
	}

	return NULL;
}

int main(int argc, char* argv[]) {

	srand(time(NULL));
	int n = atoi(argv[1]);
	int* sharedValue = malloc(sizeof(int));
	*sharedValue = 0;

	pthread_t td[n];
	pthread_mutex_t mutex;
	pthread_mutex_init(&mutex, NULL);

	data arg[n];

	for(int i = 0; i < n; i++) {

		arg[i].index = i;
		arg[i].shared = sharedValue;
		arg[i].mutex = &mutex;
		pthread_create(&td[i], NULL, f, &arg[i]);
	}

	for(int i = 0; i < n; i++) {
		pthread_join(td[i], NULL);
	}

	printf("value - %d", *sharedValue);

	free(sharedValue);
}
