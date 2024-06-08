#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>
#include <string.h>

// Write two C programs that communicate via FIFO. One program (A) will generate a random
// number N between 0 and 1000. The other program (B) will try to guess the generated number.
// B will start by generating a random number between 0 and 1000 and send it to A which will
// respond with -1 if the “guess” is lower than N, 1 if the “guess” is greater than N, and 0 if the
// guess is correct. B will continuously restrict the guesses based on the responses from A and
// will stop once it correctly guesses the number. Program A will create and destroy the FIFO

int main() {

	if(mkfifo("a2b", 0600) < 0) { 
		perror("mkfifo a2b error");
		exit(1);
	}

	if(mkfifo("b2a", 0600) < 0) {
		perror("mkfifo b2a error");
		exit(1);
	}

	int fd_write = open("a2b", O_WRONLY);
	if(fd_write == -1) {
		perror("open a2b error");
		exit(1);
	}

	int fd_read = open("b2a", O_RDONLY);
	if(fd_read == -1) {
		perror("open b2a error");
		exit(1);
	}

	srand(getpid());
	int num = random() % 1000 + 1;
	int guess, result;

	printf("A guessed %d\n", num);

	while(1) {

		if(read(fd_read, &guess, sizeof(int)) < 0) {
			perror("read error");
			exit(1);
		}

		printf("A read %d from B\n", guess);

		if(guess < num) {
			result = -1;
		} else if(guess > num) {
			result = 1;
		} else {
			result = 0;
		}

		if(write(fd_write, &result, sizeof(int)) < 0) {
			perror("write error");
			exit(1);
		}

		if(result == 0) {
			break;
		}

	}

	close(fd_read);
	close(fd_write);

	if(unlink("a2b") < 0) {
		perror("unlink a2b error");
		exit(1);
	}

	if(unlink("b2a") < 0) {
		perror("unlink b2a error");
		exit(1);
	}

	exit(0);
}
