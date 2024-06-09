#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Write a C program that creates N threads (N is a command line argument).
// Each thread will receive a unique index I from the main process between 0 and N-1 inclusively.
// Each thread will execute M rounds (M also a command line argument) with the following steps:
//     - generate 2 random numbers (A - between 1 and 20, B - between 1 and 3) and will add A*B to a thread local variable and will print its new value
//    - increment the appropriate position in a shared frequency vector for the values of A
//    - increment the appropriate position in a shared frequency vector for the values of B
//    - wait for all the threads to finish their current round before beginning a new one
// Once all threads terminate the main process will print the frequency vectors for A and B.

typedef pthread_mutex_t mutex;

typedef struct {

	int index;
	int M;

	int* FA;
	int* FB;

	mutex* Amtx;
	mutex* Bmtx;

	pthread_barrier_t* barrier;

} data;

void* f(void* arg) {
	
	data* d = (data*) arg;
	int local = 0;

	for(int i = 0; i < d->M; i++) {

		int a = rand() % 20 + 1;
		int b = rand() % 3 + 1;

		local += (a * b);
		printf("td[%d]: a - %d, b - %d\n", d->index, a, b); 
		printf("td[%d] local value - %d\n", d->index, local);
		printf("\n");

		pthread_mutex_lock(&d->Amtx[a]);
		pthread_mutex_lock(&d->Bmtx[b]);

		d->FA[a]++;
		d->FB[b]++;

		pthread_mutex_unlock(&d->Amtx[a]);
		pthread_mutex_unlock(&d->Bmtx[b]);

		pthread_barrier_wait(d->barrier);
	}

	return NULL;
}

int main(int argc, char* argv[]) {

	if(argc != 3) {
		perror("invalid arguments");
		exit(1);
	}

	srand(time(NULL));

	int n = atoi(argv[1]);
	int m = atoi(argv[2]);

	int* FA = malloc(sizeof(int) * 21);
	int* FB = malloc(sizeof(int) * 4);

	mutex* Amtx = malloc(sizeof(mutex) * 21);
	mutex* Bmtx = malloc(sizeof(mutex) * 4);

	for(int i = 0; i < 21; i++) {

		pthread_mutex_init(&Amtx[i], NULL);
	}

	for(int i = 0; i < 4; i++) {
		
		pthread_mutex_init(&Bmtx[i], NULL);
	}

	pthread_barrier_t barrier;
	pthread_barrier_init(&barrier, NULL, n);

	pthread_t td[n];
	data args[n];

	for(int i = 0; i < n; i++) {

		args[i].index = i;
		args[i].M = m;
		args[i].FA = FA;
		args[i].FB = FB;
		args[i].Amtx = Amtx;
		args[i].Bmtx = Bmtx;
		args[i].barrier = &barrier;
		pthread_create(&td[i], NULL, f, &args[i]);
	}

	for(int i = 0; i < n; i++) {

		pthread_join(td[i], NULL);
	}

	printf("FA:\n");
	for(int i = 0; i < 21; i++) {
		printf("%d ", FA[i]); 
	}

	printf("\nFB:\n");
	for(int i = 0; i < 4; i++) {
		printf("%d ", FB[i]);
	}
	printf("\n");

	free(FA);
	free(FB);
}
