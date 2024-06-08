#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>
#include <string.h>

int main() {
	
	int lb = 0, ub = 1000;
	int guess, result;
	srand(getpid());

	int fd_read = open("a2b", O_RDONLY);
	if(fd_read == -1) {
		perror("open a2b error");
		exit(1);
	}

	int fd_write = open("b2a", O_WRONLY);
	if(fd_write == -1) {
		perror("open b2a error");
		exit(1);
	}

	while(1) {
		
		guess = lb + random() % (ub - lb + 1);
		printf("B guessed %d\n", guess);

		if(write(fd_write, &guess, sizeof(int)) < 0) {
			perror("write error");
			exit(1);
		}

		if(read(fd_read, &result, sizeof(int)) < 0) {
			perror("read error");
			exit(1);
		}

		if(result == -1) {
			lb = guess;
			printf("Must look higher.\n");
		} else if(result == 1) {
			ub = guess;
			printf("Must look lower.\n");
		} else {
			printf("Got it!\n");
			break;
		}
	}

	close(fd_read);
	close(fd_write);
	
	exit(0);
}
