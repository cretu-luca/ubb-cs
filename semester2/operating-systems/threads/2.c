#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Write a C program that will read from keyboard N numbers and will send them to N separate threads.
// The main process will also initiate 2 vectors L and U, and an integer named S.

// Each thread will receive the correspondent number read from keyboard (thread i will receive the i-th number read from keyboard), variable S, and the 2 vectors L and U as function argument, and WILL NOT START until all threads were created.
// After all threads were created and initiated, each thread will check if the number received starts with an even or an odd digit:
// If it starts with an even digit it will be added in vector U, otherwise in vector L.
// It will also sum the number received to the variable S.

// Before inserting the thread will verify if it was the FIRST thread to insert a value in one of the 2 vectors and print a corresponding message on the screen.

// In the end the master will print the size of L and U and the value of S

// Use optimal lock mechanisms to make sure there are no data corruptions, and a proper synchronization method to make all threads wait until all threads were created.

typedef struct {
		
	int* L;
	int* V;
	int* s;

	int* LIndex;
	int* VIndex;

	int value;
	int index;

	pthread_barrier_t* barrier;
	pthread_mutex_t* mtx;

} data;

void* f(void* arg) {

	data* d = (data*) arg;

	pthread_barrier_wait(d->barrier);

	pthread_mutex_lock(d->mtx);

	*d->s += d->value;
	int temp = d->value;
	while(temp >= 10) {
		temp /= 10;
	}

	if(temp % 2 == 0) {

		d->V[(*d->VIndex)++] = d->value; 
	} else {

		d->L[(*d->LIndex)++] = d->value;
	}

	pthread_mutex_unlock(d->mtx);

	printf("thread[%d] received %d\n", d->index, d->value);

	return NULL;
}

int main(int argc, char* argv[]) {

	int n = atoi(argv[1]);
	int* L = malloc(sizeof(int) * n);
	int* V = malloc(sizeof(int) * n);
	int s = 0;

	int LIndex = 0;
	int VIndex = 0;

	data args[n];
	pthread_t td[n];
	pthread_barrier_t barrier;
	pthread_barrier_init(&barrier, NULL, n);

	pthread_mutex_t mtx;
	pthread_mutex_init(&mtx, NULL);

	for(int i = 0; i < n; i++) {
	
		printf("value %d:\n", i + 1);
		scanf("%d", &args[i].value);
		args[i].L = L;
		args[i].V = V;
		args[i].LIndex = &LIndex;
		args[i].VIndex = &VIndex;
		args[i].s = &s;
		args[i].index = i;
		args[i].barrier = &barrier;
		args[i].mtx = &mtx;
		pthread_create(&td[i], NULL, f, &args[i]);
	}

	for(int i = 0; i < n; i++) {

		pthread_join(td[i], NULL);
	}

	printf("V:\n");
	for(int i = 0; i < VIndex; i++) {

		printf("%d ", V[i]);
	}

	printf("\nL:\n");
	for(int i = 0; i < LIndex; i++) {

		printf("%d ", L[i]);
	}

	printf("\ns=%d\n", s); 
}

