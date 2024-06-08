#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

// Write a C program that reads a number n from standard input and generates an array s of n random integers between 0 and 1000. After the array is created, the main process creates n + 1 threads. Each of the first n threads repeats the following steps until the array is sorted in ascending order:
// - generates 2 random integers between 0 and n-1, called i and j
// - if i < j and s[i] > s[j], exchanges the values of s[i] and s[j]
// - if i > j and s[i] < s[j], exchanges the values of s[i] and s[j]
// The n + 1'th thread waits until the array is sorted, after which it prints it to the console. Use appropriate synchronization mechanisms. 

typedef struct {
	
	int size;
	int index;
	int* array;
	pthread_barrier_t* barrier;
	pthread_mutex_t* mtx;
	
} data;

int sorted(int* array, int size) {
	
	for(int i = 0; i < size - 1; i++) {

		if(array[i] > array[i + 1])
			return 0;
	}
	
	return 1;
}

void* f(void* arg) {
	
	data* d = (data *) arg;

	while(1) {

		int i = random() % d->size;
		int j = random() % d->size;

		if(i != j) {

			pthread_mutex_lock(&d->mtx[i]);
			pthread_mutex_lock(&d->mtx[j]);

			if((i < j && d->array[i] > d->array[j]) || (i > j && d->array[i] < d->array[j])) {
			
				printf("thread[%d] swapping a[%d] = %d with a[%d] = %d\n", d->index, i, d->array[i], j, d->array[j]);

				int temp = d->array[i];
				d->array[i] = d->array[j];
				d->array[j] = temp;

			}

			pthread_mutex_unlock(&d->mtx[i]);
			pthread_mutex_unlock(&d->mtx[j]);
		}

		if(sorted(d->array, d->size)) {
			break;
		}
	}
	
	pthread_barrier_wait(d->barrier);
	return NULL;
}

void* printer(void* arg) {

	data* d = (data *) arg;

	pthread_barrier_wait(d->barrier);
	
	for(int i = 0; i < d->size; i++) {
	
		printf("%d ", d->array[i]);
	}

	return NULL;
}

int main() {

	int n, *array;
	scanf("%d", &n);
	array = malloc(sizeof(int) * n);
	srand(time(NULL));

	for(int i = 0; i < n; i++) {

		int randomValue = random() % 1001;
		array[i] = randomValue;
	}

	pthread_t td[n + 1];
	data args[n + 1];

	pthread_barrier_t barrier;
	pthread_barrier_init(&barrier, NULL, n + 1);

	pthread_mutex_t* mtx;
	mtx = malloc(sizeof(pthread_mutex_t) * n);
	for(int i = 0; i < n; i++) { 

		pthread_mutex_init(&mtx[i], NULL);
	}

	for(int i = 0; i < n; i++) {

		args[i].size = n;
		args[i].mtx = mtx;
		args[i].barrier = &barrier;
		args[i].index = i;
		args[i].array = array;
		pthread_create(&td[i], NULL, f, &args[i]);
	}

	args[n].size = n;
	args[n].mtx = mtx;
	args[n].barrier = &barrier;
	args[n].index = n;
	args[n].array = array;
	pthread_create(&td[n], NULL, printer, &args[n]);

	for(int i = 0; i <= n; i++) {

		pthread_join(td[i], NULL);
	}
}
