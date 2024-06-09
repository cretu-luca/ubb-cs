#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

// 31. Write a C program that receives a number N as a command-line argument. The program creates N threads that will generate random numbers between 0 and 111111 (inclusive) until one thread generates a number divisible by 1001. The threads will display the generated numbers, but the final number that is displayed must be the one that is divisible by 1001. No thread will start generating random numbers until all threads have been created. Do not use global variables.

typedef struct {

	int* flag;
	int id;
	pthread_mutex_t* mutex;
	pthread_barrier_t* barrier;
} args;

void* f(void* arg) {
	
	args* data = (args*) arg;
	pthread_barrier_wait(data->barrier);

	while(1) {
	
		pthread_mutex_lock(data->mutex);
		if(*(data->flag) == 0) {
			int rand = random() % 111112;

			printf("thread[%d] generated %d\n", data->id, rand); 
		
			if(rand % 1001 == 0) {
				*(data->flag) = 1;
			}

			pthread_mutex_unlock(data->mutex);
	
		} else {

			break;
		}
	}

	pthread_mutex_unlock(data->mutex);
	return NULL;
}

int main(int argc, char* argv[]) {

	srand(time(NULL));
	int n = atoi(argv[1]);
	
	int* flag = malloc(sizeof(int));
	*flag = 0;
	pthread_mutex_t* mutex = malloc(sizeof(pthread_mutex_t));
	pthread_barrier_t* barrier = malloc(sizeof(pthread_barrier_t));

	pthread_mutex_init(mutex, NULL);
	pthread_barrier_init(barrier, NULL, n);

	pthread_t td[n];
	args arg[n];

	for(int i = 0; i < n; i++) {
		arg[i].flag = flag;
		arg[i].id = i;
		arg[i].mutex = mutex;
		arg[i].barrier = barrier;
		pthread_create(&td[i], NULL, f, &arg[i]);
	}
	
	for(int i = 0; i < n; i++) {
		pthread_join(td[i], NULL);
	}
	
	pthread_barrier_destroy(barrier);
	pthread_mutex_destroy(mutex);
	free(flag);
}
