#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

// 2 threads
// 1 thread produces values and adds them in an array until it's full (array has size n)
// once the array is full, the second thread 

int arr[10];
int repeats = 100, full = 0;

pthread_cond_t cond;
pthread_mutex_t mtx;

void* producer(void* arg) {
	int n = repeats;

	while(n > 0) {

		pthread_mutex_lock(&mtx);
		while(full) 
			pthread_cond_wait(&cond, &mtx);

		for(int i = 0; i < 10; i++) {
			arr[i] = rand() % 100;
		}
		
		usleep(100000);
		full = 1;
		n--;
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mtx);
	}

	return NULL;
}

void* consumer(void* arg) {
	int n = repeats;

	while(n > 0) {

		pthread_mutex_lock(&mtx);
		while(!full) 
			pthread_cond_wait(&cond, &mtx);

		for(int i = 0; i < 10; i++) {
			printf("%4d", arr[i]);
			arr[i] = 0;
		}

		printf("\n");
		full = 0;
		n--;
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mtx);
	}

	return NULL;
}

int main(int argc, char* argv[]) {
	
	pthread_cond_init(&cond, NULL);
	pthread_mutex_init(&mtx, NULL);

	pthread_t th[2];
	pthread_create(&th[0], NULL, producer, NULL);
	pthread_create(&th[1], NULL, consumer, NULL);	
	
	for(int i = 0; i < 2; i++) {
		pthread_join(th[i], NULL);
	}
	
	return 0;
}
