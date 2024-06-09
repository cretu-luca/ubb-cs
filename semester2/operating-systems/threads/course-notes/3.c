#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// create N threads
// on startup each thread generates a value and stores it in a shared array
// after each thread generated its value, each thread attempts to steal 10% from another thread value

typedef struct {
	
	int index;
	int n;
	int* arr;
	pthread_barrier_t* barrier;
	pthread_mutex_t** mutex;

} args;

void* f(void* arg) {

	args* data = (args*) arg;

	int randomValue = random() % 100;
	
	printf("thread[%d] generated %d, now waiting at the barrier\n", data->index, randomValue);
	
	pthread_mutex_lock(data->mutex[data->index]);
	data->arr[data->index] = randomValue;
	pthread_mutex_unlock(data->mutex[data->index]);

	pthread_barrier_wait(data->barrier);

	printf("thread[%d] passed the barrier\n", data->index);
	
	randomValue = random() % 100;
	int index = random() % data->n;
	while(index == data->index)
		index = random() % data->n;

	pthread_mutex_lock(data->mutex[data->index]);
	int previousValue = data->arr[index];
	data->arr[index] -= randomValue;
	pthread_mutex_unlock(data->mutex[data->index]);

	pthread_barrier_wait(data->barrier);

	printf("thread[%d] stole %d from thread[%d]; %d - %d\n", data->index, randomValue, index, previousValue, randomValue);

	return NULL;
}

int main(int argc, char* argv[]) {

	srand(time(NULL));

	int n = atoi(argv[1]);
	int* array;
	array = (int*) malloc(sizeof(int) * n);
	pthread_t td[n];
	args argument[n];

	pthread_barrier_t* barrier = malloc(sizeof(pthread_barrier_t));
	pthread_mutex_t** mutex;
	mutex = (pthread_mutex_t**) malloc(sizeof(pthread_mutex_t*) * n);
	for(int i = 0; i < n; i++) {
		mutex[i] = (pthread_mutex_t*) malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(mutex[i], NULL);
	}

	pthread_barrier_init(barrier, NULL, n);	
	for(int i = 0; i < n; i++) {
		argument[i].index = i;
		argument[i].n = n;
		argument[i].arr = array;
		argument[i].barrier = barrier;
		argument[i].mutex = mutex;
		pthread_create(&td[i], NULL, f, &argument[i]);
	}

	for(int i = 0; i < n; i++) {
		pthread_join(td[i], NULL);
	}

	for(int i = 0; i < n; i++) {
		printf("%d ", array[i]);
	}

	printf("\n");
	
	free(array);
	return 0;
}
