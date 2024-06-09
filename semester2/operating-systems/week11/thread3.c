#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

// create N threads
// on startup each thread generates a value and stores it in a shared array
// after each thread generated its value, each thread attempts to steal 10% from another thread value

sem_t sem1, sem2, sem3;

pthread_barrier_t bar;
pthread_mutex_t* mutex;
int* arr, * indexes;
int n;

void* f(void* arg) {
	int index = *((int *) arg);
	printf("Thread %d started\n", index);
	sem_wait(&sem1);
	printf("Thread %d passed semaphore 1\n", index);
	sem_wait(&sem2);
	printf("Thread %d passed semaphore 2\n", index);
	sem_wait(&sem3);
	printf("Thread %d passed semaphore 3\n", index);
	sem_post(&sem1);
	printf("Thread %d unlocks semaphore 1\n", index);
	sem_post(&sem2);
	printf("Thread %d unlocks semaphore 2\n", index);
	sem_post(&sem3);
	printf("Thread %d unlocks semaphore 3\n", index);`
	return NULL;
}

int main(int argc, char* argv[]) {
	
	if(argc != 2) {
		exit(1);
	}

	n = atoi(argv[1]);
	srand(getpid());

	sem_init(&sem1, 0, n / 2);
	sem_init(&sem2, 0, n / 4);
	sem_init(&sem3, 0, n / 8);

	indexes = malloc(sizeof(int) * n);
	pthread_t th[n];

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

	free(indexes);

	return 0;
}
