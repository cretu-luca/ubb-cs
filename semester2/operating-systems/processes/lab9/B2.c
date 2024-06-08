#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>

int main() {
	
	int argc = 0;
	int fd_read = open("A2B", O_RDONLY);
	if(fd_read == -1) {
		perror("A2B open read error");
		exit(1);
	}

	int fd_write = open("B2A", O_WRONLY);
	if(fd_write == -1) {
		perror("B2A open write error");
		exit(1);
	}

	if(read(fd_read, &argc, sizeof(int)) < 0) {
		perror("A2B read error");
		exit(1);
	}
	
	printf("%d arguments coming down the pipe!\n", argc);

	for(int i = 1; i <= argc; i++) {
		
		int length;
		if(read(fd_read, &length, sizeof(int)) < 0) {
			perror("read length error");
			exit(1);
		}

		char* word = (char *) malloc(sizeof(char) * length + 1);
		if(read(fd_read, word, sizeof(char) * length + 1) < 0) {
			perror("read word error");
			exit(1);
		}

		for(int i = 0; i < length; i++) {
			word[i] = toupper(word[i]);
		}
				
		printf("%s has length %d\n", word, length);

		if(write(fd_write, word, sizeof(char) * length + 1) < 0) {
			perror("write word error");
			exit(1);
		}
	}

	close(fd_read);
	close(fd_write);
}
