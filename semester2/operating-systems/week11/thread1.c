#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// create N threads
// on startup each thread generates a value and stores it in a shared array
// after each thread generated its value, each thread attempts to steal 10% from another thread value

pthread_barrier_t bar;
pthread_mutex_t* mutex;
int* arr, * indexes;
int n;

void* f(void* arg) {
	int index = *((int *) arg);
	arr[index] = rand() % 1000;
	printf("id %d - value %d\n", index, arr[index]);
	
	pthread_barrier_wait(&bar);
	
	int other_index = rand() % n;
	while(other_index == index) {
		other_index = rand() % n;
	}

	pthread_mutex_lock(&mutex[index]);
	pthread_mutex_lock(&mutex[other_index]);

	int stolen = arr[other_index] / 10;

	arr[index] += stolen;
	arr[other_index] -= stolen;

	printf("Thread %d stolen %d from thread %d\n", index, stolen, other_index);

	pthread_mutex_unlock(&mutex[other_index]);
	pthread_mutex_unlock(&mutex[index]);

	// printf("After barrier\n");
	return NULL;
}

int main(int argc, char* argv[]) {
	
	if(argc != 2) {
		exit(1);
	}

	srand(getpid());

	n = atoi(argv[1]);
	arr = malloc(sizeof(int) * n);
	indexes = malloc(sizeof(int) * n);
	pthread_t th[n];

	pthread_barrier_init(&bar, NULL, n);

	mutex = malloc(sizeof(pthread_mutex_t) * n);
	for(int i = 0; i < n; i++) {
		pthread_mutex_init(&mutex[i], NULL);
	}

	for(int i = 0; i < n; i++) {
		indexes[i] = i;
		if(pthread_create(&th[i], NULL, f, &indexes[i]) < 0) {
			perror("thread went bad");
			exit(1);
		}
	}
	
	for(int i = 0; i < n; i++) {
		pthread_join(th[i], NULL);
	}

	for(int i = 0; i < n; i++) {
		printf("arr[%d] = %d\n", i, arr[i]);
	}

	free(arr);
	free(indexes);

	return 0;
}
