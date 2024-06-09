#include <stdio.h>
#include <stdlib.h>
#include <threads.h>

// Write a C program that calculates the sum of elements on each column of a
// matrix of integers. The implementation will calculate the required sums sequentially and
// then use threads (one thread per column).

int n, m, sum;
pthread_mutex_t mtx;

typedef struct {

	int** mat;
	int column;

} args;

void* f(void* arg) {

	args* data = (args*) arg;
	
	int currSum = 0;
	for(int i = 0; i < n; i++) {
		currSum += data->mat[i][data->column];
	}

	pthread_mutex_lock(&mtx);
	sum += currSum;
	pthread_mutex_unlock(&mtx);

	return NULL;
}

int main() { 
	
	FILE* fd = fopen("bigmat.txt", "r");

	fscanf(fd, "%d", &n);
	fscanf(fd, "%d", &m);


	int** mat;
	mat = (int**) malloc(sizeof(int*) * n);
	for(int i = 0; i < n; i++) {
		mat[i] = (int*) malloc(sizeof(int) * m);
	}

	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			fscanf(fd, "%d", &mat[i][j]);

	pthread_mutex_init(&mtx, NULL);
	pthread_t td[m];
	args arg[m];

	for(int i = 0; i < m; i++) {
		arg[i].mat = mat;
		arg[i].column = i;
		pthread_create(&td[i], NULL, f, &arg[i]);
	}

	for(int i = 0; i < m; i++) {
		pthread_join(td[i], NULL);
	}
	
	pthread_mutex_destroy(&mtx);

	printf("%d", sum);

	return 0;
}
