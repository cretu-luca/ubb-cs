#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

// Write a C program that receives a number N as a command line argument. The main
// process creates N groups of 3 threads each. After creating one group of threads, the
// main process waits for them to terminate before starting the next group. The main
// process starts all three threads of each group without any delays. One thread from each
// group will populate the elements of an array with 10 positions with random values
// between 0 and 100. After the array is fully populated, the other two threads each iterate
// through the elements of the array. Whichever thread encounters a non-zero value, it
// adds it to a local sum and sets that array value to 0, then sleeps for 10 milliseconds.
// Once the threads finish iterating through the array, they print their respective local sums
// and terminate.

pthread_barrier_t barrier;
pthread_mutex_t mutex;

typedef struct {
	int id;
	int sum;
	int* arr;
} data;

void* populate(void* arg) {
	
	data* d = (data*) arg;

	for(int i = 0; i < 3; i++) {
	
		d->arr[i] = rand() % 101;
		printf("%d ", d->arr[i]); 
	}

	printf("\n");
	pthread_barrier_wait(&barrier);

	return NULL;
}

void* process(void* arg) {
	
	data* d = (data*) arg;
	pthread_barrier_wait(&barrier);
	d->sum = 0;
	
	for(int i = 0; i < 3; i++) {
		
		pthread_mutex_lock(&mutex);
		if(d->arr[i] != 0) {
			d->sum += d->arr[i];
			d->arr[i] = 0;

			pthread_mutex_unlock(&mutex);
			usleep(10000);
		} else {
			pthread_mutex_unlock(&mutex);
		}
	}

	printf("Thread[%d] has the local sum %d\n", d->id, d->sum);

	return NULL;
}

int main(int argc, char* argv[]) {

	if(argc != 2) {
		perror("invalid number of arguments");
		exit(1);
	}

	srand(time(NULL));

	int n = atoi(argv[1]);
	pthread_t td[n][3];
	data args[n][3];

	int arrs[n][3];
	pthread_mutex_init(&mutex, NULL);
	pthread_barrier_init(&barrier, NULL, 3);

	for(int i = 0; i < n; i++) {

		for(int j = 0; j < 3; j++) {
			args[i][j].id = i * 3 + j;
			args[i][j].arr = arrs[i];
		}

		pthread_create(&td[i][0], NULL, populate, &args[i][0]);
		pthread_create(&td[i][1], NULL, process, &args[i][1]);
		pthread_create(&td[i][2], NULL, process, &args[i][2]);
	
		pthread_join(td[i][0], NULL);
		pthread_join(td[i][1], NULL);
		pthread_join(td[i][2], NULL);
	}

	pthread_mutex_destroy(&mutex);
	pthread_barrier_destroy(&barrier);

	return 0;
}
