#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Write a C program that creates N threads (N given as a command line argument). The threads
// will keep adding random numbers between -500 and +500 to a shared variable that initially has
// the value 0. The threads will terminate when the shared variable has an absolute value greater
// than 500. Ensure proper synchronization Print a message every time a thread modifies the
// variable.

typedef struct {

	int* shared;
	pthread_mutex_t* mtx;
	
} data;

void* f(void* arg) {

	data* d = (data*) arg;

	while(1) {

		int randomValue = random() % 500;
		int sign = random() % 2;

		if(sign == 0) {
			randomValue *= -1;
		}

		pthread_mutex_lock(d->mtx);

		if(*d->shared > 500 || *d->shared < -500) {
			pthread_mutex_unlock(d->mtx);
			break;
		} else {
			*d->shared += randomValue;
			printf("value is %d\n", *d->shared);
		}

		pthread_mutex_unlock(d->mtx);
	}

	return NULL;
}

int main(int argc, char* argv[]) {

	int n = atoi(argv[1]);
	int* shared = malloc(sizeof(int));
	*shared = 0;

	srand(time(NULL));

	pthread_t td[n];
	pthread_mutex_t* mtx = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(mtx, NULL);

	data args[n];

	for(int i = 0; i < n; i++) {

		args[i].shared = shared;
		args[i].mtx = mtx;
		pthread_create(&td[i], NULL, f, &args[i]);
	}

	for(int i = 0; i < n; i++) {

		pthread_join(td[i], NULL);
	}

	printf("value is %d", *shared); 
}
