#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Write a C program that reads a matrix of integers from a file. It then creates as many threads as there are rows in the matrix, each thread calculates the sum of the numbers on a row. The main process waits for the threads to finish, then prints the sums.

struct arg_t {
	int* row;
	int cols;
	int index;
};

void* f(void* arg) {

	struct arg_t* data = (struct arg_t*) arg;
	int* row = data->row;
	int cols = data->cols;
	int index = data->index;

	int sum = 0;
	for(int i = 0; i < cols; i++) {
		sum += row[i];
	}

	printf("thread %d computed %d\n", index, sum);

	int* result = malloc(sizeof(int));
	*result = sum;

	return result;
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
	struct arg_t args[rows];
	for(int i = 0; i < rows; i++) {
		args[i] = (struct arg_t) {mat[i], cols, i};
		pthread_create(&td[i], NULL, f, &args[i]);
	}	

	int* sums[rows];
	for(int i = 0; i < rows; i++) {
		sums[i] = 0;
		pthread_join(td[i], (void**) &sums[i]);
	}

	
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			printf("%d ", mat[i][j]);
		}

		printf("\n");
	}
	
	int sum = 0;
	for(int i = 0; i < rows; i++) {
		printf("sum on row %d is %d\n", i, *sums[i]);
		sum += *sums[i];
		free(sums[i]);
	}

	printf("total sum is %d\n", sum);

	for(int i = 0; i < rows; i++) {
		free(mat[i]);
	}

	free(mat);
	return 0;
}
