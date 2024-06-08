#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

// Write two C processes, A and B. Process A sends any command line arguments it receives via
// fifo to process B. Process B converts all the lowercase letters from the received strings to
// uppercase and sends them back.

int main(int argc, char* argv[]) {
	if(mkfifo("A2B", 0600) < 0) {
		perror("A2B fifo error");
		exit(1);
	}

	if(mkfifo("B2A", 0600) < 0) {
		perror("B2A fifo error");
		exit(1);
	}

	int fd_write = open("A2B", O_WRONLY);
	if(fd_write == -1) {
		perror("A2B write error");
		exit(1);
	}

	int fd_read = open("B2A", O_RDONLY);
	if(fd_read == -1) {
		perror("B2A read error");
		exit(1);
	}

	int newArgc = argc - 1;
	if(write(fd_write, &newArgc, sizeof(int)) < 0) {
		perror("write argc error");
		exit(1);
	}

	for(int i = 1; i < argc; i++) {
		
		int length = strlen(argv[i]);
		if(write(fd_write, &length, sizeof(int)) < 0) {
			perror("A2B write error");
			exit(1);
		}

		if(write(fd_write, argv[i], sizeof(char) * length + 1) < 0) {
			perror("A2B write error");
			exit(1);
		}

		char* word = (char *) malloc(sizeof(char) * length + 1);
		if(read(fd_read, word, sizeof(char) * length + 1) < 0) {
			perror("B2A read error");
			exit(1);
		}

		printf("A read %s\n", word);
	}

	close(fd_write);
	close(fd_read);
	if(unlink("A2B") < 0) {
		perror("A2B unlink error");
	}

	if(unlink("B2A") < 0) {
		perror("B2A unlink error");
	}

	exit(0);
}
