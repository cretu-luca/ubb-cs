#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

// Write a C program that reads a number N and creates 2 threads. One of the threads will generate an even number and will append it to an array that is passed as a parameter to the thread. The other thread will do the same, but using odd numbers. Implement a synchronization between the two threads so that they alternate in appending numbers to the array, until they reach the maximum length N.

typedef struct {
	int* values;
	int* index;
	int n;

	pthread_mutex_t* mutex;
	pthread_cond_t* cond;
} data;

int n;

void* f_even(void* arg) {
    data* d = (data*) arg;

    pthread_mutex_lock(d->mutex);
    while (*(d->index) < d->n) {
        while (*(d->index) % 2 != 0 && *(d->index) < d->n) {
            pthread_cond_wait(d->cond, d->mutex);
        }

        if (*(d->index) < d->n) {
            d->values[*(d->index)] = *(d->index);
            (*(d->index))++;

            for (int i = 0; i < *(d->index); i++) {
                printf("%d ", d->values[i]);
            }
            printf("\n");

            pthread_cond_signal(d->cond);
        }
    }
    pthread_mutex_unlock(d->mutex);

    return NULL;
}

void* f_odd(void* arg) {
    data* d = (data*) arg;

    pthread_mutex_lock(d->mutex);
    while (*(d->index) < d->n) {
        while (*(d->index) % 2 != 1 && *(d->index) < d->n) {
            pthread_cond_wait(d->cond, d->mutex);
        }

        if (*(d->index) < d->n) {
            d->values[*(d->index)] = *(d->index);
            (*(d->index))++;

            for (int i = 0; i < *(d->index); i++) {
                printf("%d ", d->values[i]);
            }
            printf("\n");

            pthread_cond_signal(d->cond);
        }
    }
    pthread_mutex_unlock(d->mutex);

    return NULL;
}

int main(int argc, char* argv[]) {
	pthread_mutex_t mutex;
	pthread_cond_t cond;
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&cond, NULL);

	int n = atoi(argv[1]);
	int* arr = malloc(sizeof(int) * n);
	int index = 0;

	pthread_t td[2];
	data args;
	
	args.mutex = &mutex;
	args.values = arr;
	args.cond = &cond;
	args.index = &index;
	args.n = n;

	pthread_create(&td[0], NULL, f_even, (void*) &args);
	pthread_create(&td[1], NULL, f_odd, (void*) &args);

	pthread_join(td[0], NULL);
	pthread_join(td[1], NULL);

	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);
	free(arr);

	return 0;
}
