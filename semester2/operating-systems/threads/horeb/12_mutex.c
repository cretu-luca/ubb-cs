#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Write a C program that reads a matrix of integers from a file. It then creates as many threads as there are rows in the matrix, each thread calculates the sum of the numbers on a row. The main process waits for the threads to finish, then prints the sums.

pthread_mutex_t mtx;
int sum = 0;

struct arg_t {
	int** matrix;
	int cols;
	int index;
};

void* f(void* arg) {

	struct arg_t* data = (struct arg_t*) arg;
	
	for(int i = 0; i < data->cols; i++) {
	
		pthread_mutex_lock(&mtx);
		sum += data->matrix[data->index][i];
		pthread_mutex_unlock(&mtx);

	}
}

int main(int argc, char* argv[]) {
	
	int rows, cols;
	int** mat;

	if(argc != 2) {
		perror("invalid number of arguments");
		exit(1);
	}

	FILE* fd_read = fopen(argv[1], "r");
	if(fd_read == NULL) {
		perror("error opening file");
		exit(1);
	}
	
	fscanf(fd_read, "%d %d", &rows, &cols);
	
	mat = (int**) malloc(sizeof(int*) * rows);
	for(int i = 0; i < rows; i++) {
		mat[i] = (int*) malloc(sizeof(int) * cols);
	}

	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			fscanf(fd_read, "%d", &mat[i][j]);
		}
	}

	fclose(fd_read);

	pthread_t td[rows];
	pthread_mutex_init(&mtx, NULL);
	struct arg_t args[rows];
	
	for(int i = 0; i < rows; i++) {
		args[i] = (struct arg_t) {mat, cols, i};
		pthread_create(&td[i], NULL, f, &args[i]);
	}	

	for(int i = 0; i < rows; i++) {
		pthread_join(td[i], NULL);
	}
	
	printf("total sum is %d\n", sum);

	for(int i = 0; i < rows; i++) {
		free(mat[i]);
	}

	free(mat);
	pthread_mutex_destroy(&mtx);

	return 0;
}
