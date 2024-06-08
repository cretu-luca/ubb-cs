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
// this is program B

int main() {	
	int A2B, B2A, nr, length;
	B2A = open("B2A", O_WRONLY);
	A2B = open("A2B", O_RDONLY);

	if(read(A2B, &nr, sizeof(int)) < 0) {
		perror("A2B - read error");
		exit(1);
	}

	for(int i = 0; i < nr; i++) {
		if(read(A2B, &length, sizeof(int)) < 0) {
			perror("A2B - read error");
			exit(1);
		}
		
		char* argv = malloc(sizeof(char) * length);
		if(read(A2B, argv, sizeof(char) * length) < 0) {
			perror("A2B - read error");
			exit(1);
		}
		
		printf("string before: %s\n", argv);
		for(int j = 0; j < length; j++) {
			argv[j] = toupper(argv[j]);
		}
		printf("string after: %s\n", argv);

		// write(B2A, &length, sizeof(int));
		write(B2A, argv, sizeof(char) * length);
		free(argv);
	}
	
	close(A2B);
	close(B2A);
}
