#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main() {
	int nr = 0;

	int fd_read = open("myfifo1", O_RDONLY);
	if(fd_read == -1) {
		perror("fd_write error");
		exit(1);
	}

	int fd_write = open("myfifo2", O_WRONLY);
	if(fd_write == -1) {
		perror("fd_read error");
		exit(1);
	}

	srand(getpid());
	while(1) {
		if(read(fd_read, &nr, sizeof(int)) < 0) {
			perror("read error");
			exit(1);
		}
		printf("B received %d\n", nr);
	
		if(nr == 10) {
			break;
		}

		nr = random() % 10 + 1;
		if(write(fd_write, &nr, sizeof(int)) < 0) {
			perror("write error");
			exit(1);
		}
		printf("B sent %d\n", nr);

		if(nr == 10) {
			break;
		}
	}

	return 0;
}
