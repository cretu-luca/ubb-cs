#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>
#include <string.h>

// Write two C programs (A, B). Process A reads a string (maximum 100 characters) from
// standard input, removes the last X characters from the string, where X is randomly 
// generated (0 < X < 4), and sends the new string to process B via FIFO. Process B 
// also removes the last X characters from the string (X is generated with the same 
// rules as above) and sends the new string back to A. The algorithm repeats until 
// one process removes the last character from the string, at which point it prints a 
// message and both processes terminate.

int main() {
	
	char string[100];
	int length, x;

	srand(getpid());
	scanf("%s", string);
	length = strlen(string);

	if(mkfifo("a2b", 0600) < 0) {
		perror("a2b fifo error");
		exit(1);
	}

	if(mkfifo("b2a", 0600) < 0) {
		perror("b2a fifo error");
		exit(1);
	}	

	int fd_write = open("a2b", O_WRONLY);
	if(fd_write == -1) {
		perror("open error");
		exit(1);
	}

	int fd_read = open("b2a", O_RDONLY);
	if(fd_read == -1) {
		perror("open error");
		exit(1);
	}

	while(1) {
		x = random() % 3 + 1;

		if(x >= length) {
			
			length = 0;
			if(write(fd_write, &length, sizeof(int)) < 0) {
				perror("write error");
				exit(1);
			}

			printf("removed last %d\n", x);
			break;

		} else {
			printf("removed %d\n", x);
			
			length -= x;
			string[length] = '\0';

			printf("obtained %s\n", string); 

			if(write(fd_write, &length, sizeof(int)) < 0) {
				perror("write error");
				exit(1);
			}

			if(write(fd_write, string, sizeof(char) * (length + 1)) < 0) {
				perror("write error");
				exit(1);
			}
		}

		if(read(fd_read, &length, sizeof(int)) < 0) {
			perror("read error");
			exit(1);
		}
	
		if(length == 0) {
			break;

		} else {

			if(read(fd_read, string, sizeof(char) * length + 1) < 0) {
				perror("read error");
				exit(1);
			}
		}
	}

	close(fd_read);
	close(fd_write);

	if(unlink("a2b") < 0) {
		perror("unlink error");
		exit(1);
	}
	
	if(unlink("b2a") < 0) {
		perror("unlink error");
		exit(1);
	}

	exit(0);
}
