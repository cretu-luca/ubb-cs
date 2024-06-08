#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

// Write a C program that receives a filename as a command line argument and creates a child
// process. The file will contain only integers, the first number, N (0 < N < 100, so the entire
// content of the file can be loaded in memory) will represent the total number of numbers in the
// file, excluding itself. The child process will read the numbers from the file and send them to the
// parent. The parent will display N first and will await input from the user. The user will input an
// integer number X and the parent process will print the first X numbers (or N, if X > N). If
// numbers are left, the parent process will prompt the user to input a new value for X and the
// parent will print the next X numbers. The process ends when there are no numbers left to print
// or when the user inputs a number less or equal to 0.

int main(int argc, char* argv[]) {
	int c2p[2], number, f;
	FILE* file;

	if(argc != 2) {
		perror("invalid number of arguments");
		fclose(file);
		exit(1);
	}	
		
	if(pipe(c2p) == -1) {
		perror("2nd pipe error");
		fclose(file);
		exit(1);
	}

	file = fopen(argv[1], "r");
	if(file == NULL) {
		perror("error opening file");
		fclose(file);
		exit(1);
	}

	f = fork();
	if(f == -1) {
		perror("fork error");
		fclose(file);
		exit(1);
	} else if(f == 0) {
		int size, number;
		
		fscanf(file, "%d", &size);
		if(write(c2p[1], &size, sizeof(int)) < 0) {
			perror("child - write error");
			exit(1);
		}

		while(fscanf(file, "%d", &number) == 1) {
			if(write(c2p[1], &number, sizeof(int)) < 0) {
				perror("child - write error");
				exit(1);
			}
		}

		fclose(file);
		exit(0);
	} else {
		int index = 0, number, size, is_valid = 1;
		int* numbers;
	
		if(read(c2p[0], &size, sizeof(int)) < 0) {
			perror("parent - read error");
			fclose(file);
			exit(1);
		}
		numbers = (int*) malloc(sizeof(int) * size);

		for(int i = 0; i < size; i++) {
			if(read(c2p[0], &number, sizeof(int)) < 0) {
				perror("parent - read error");
				fclose(file);
				exit(1);
			}
			numbers[index++] = number;
		}

		printf("file contains %d numbers\n", size);
		printf("\n");

		int valuesLeft = size, valuesToPrint, indexInArray = 0;
		while(is_valid) {
			printf("enter number of values to display:\n");
			scanf("%d", &valuesToPrint);

			if(valuesLeft >= valuesToPrint) {
				for(int i = indexInArray; i < indexInArray + valuesToPrint; i++) {
					printf("%d ", numbers[i]);
				}
				
				valuesLeft = valuesLeft - valuesToPrint;
				indexInArray = indexInArray + valuesToPrint;
				printf("\n");
			} else if(valuesToPrint < 0) {
				is_valid = 0;	
			} if(valuesLeft <= 0) {
				is_valid = 0;
			}
		}		
		wait(0);
	}

	exit(0);
	fclose(file);
}
