#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>

// Write two C processes, A and B. Process A sends any command line arguments it receives via
// fifo to process B. Process B converts all the lowercase letters from the received strings to
// uppercase and prints them.
// this is program A

int main(int argc, char* argv[]) {
	int A2B, B2A;	
	A2B = open("A2B", O_WRONLY);
	B2A = open("B2A", O_RDONLY);

	if(write(A2B, &argc, sizeof(int)) < 0) {
		perror("A2B - write error");
		exit(1);
	}

	for(int i = 0; i < argc; i++) {
		if(write(A2B, strlen(argv[i]) + 1, sizeof(char) * strlen(argv[i]) + 1) < 0) {
			perror("A2B - write error");
			exit(1);
		}

		if(write(A2B, argv[i], sizeof(char) * strlen(argv[i]) + 1) < 0) {
			perror("A2B - write error");
			exit(1);
		}
	}
	
	char* newArgs[10];
	for(int i = 0; i < argc; i++) {
		if(read(B2A, newArgs[i], sizeof(char) * strlen(argv[i]) + 1) < 0) {
			perror("B2A - read error");
			exit(1);
		}
	}

	for(int i = 0; i < argc; i++) {
		printf("%s", newArgs[i]);
	}

	close(A2B);
	close(B2A);
}	
