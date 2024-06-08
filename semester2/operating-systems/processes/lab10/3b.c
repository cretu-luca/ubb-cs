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

	char string[100];
	int length, x;

	srand(getpid());

	int fd_read = open("a2b", O_RDONLY);
	if(fd_read == -1) {
		perror("a2b open error");
		exit(1);
	}

	int fd_write = open("b2a", O_WRONLY);
	if(fd_write == -1) {
		perror("b2a open error");
		exit(1);
	}

	while(1) {

		if(read(fd_read, &length, sizeof(int)) < 0) {
			perror("read error");
			exit(1);
		}

		if(length != 0) {
			if(read(fd_read, string, sizeof(char) * length + 1)  < 0) {
				perror("read error");
				exit(1);
			}
		} else {

			break;
		}

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
	}

	close(fd_read);
	close(fd_write);

	if(unlink("b2a") < 0) {
		perror("unlink error");
		exit(1);
	}

	exit(0);
}
