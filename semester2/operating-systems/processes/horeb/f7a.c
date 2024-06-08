#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>

// 7a. Write two C programs that communicate via fifo. The two processes will alternate sending random integers between 1 and 10 (inclusively) to one another until one of them sends the number 10. Print messages as the numbers are sent. One of the two processes must be responsible for creating and deleting the fifos.

int main() {
	
	if(mkfifo("./myfifo1", 0600) < 0) {
		perror("mkfifo myfifo1 error");
		exit(1);
	}
		
	if(mkfifo("./myfifo2", 0600) < 0) {
		perror("mkfifo myfifo2 error");
		exit(1);
	}

	int fd_write = open("./myfifo1", O_WRONLY);
	if(fd_write == -1) {
		perror("open myfifo1 error");
		exit(1);
	}

	int fd_read = open("./myfifo2", O_RDONLY);
	if(fd_read == -1) {
		perror("open myfifo2 error");
		exit(1);
	}

	srand(getpid());
	int nr = 0;

	while(1) {

		nr = random() % 10 + 1;
		if(write(fd_write, &nr, sizeof(int)) < 0) {
			perror("write error");
			exit(1);
		}
		printf("A sent: %d\n", nr);
		
		if(nr == 10) {
			break;
		}

		if(read(fd_read, &nr, sizeof(int)) < 0) {
			perror("read error");
			exit(1);
		}
		printf("A received %d\n", nr);
			
		if(nr == 10) {
			break;
		}
	}
	
	close(fd_write);
	close(fd_read);

	if(unlink("myfifo1") < 0) {
		perror("unlink myfifo1 error");
	}

	if(unlink("myfifo2") < 0) {
		perror("unlink myfifo2 error");
	}

	return 0;
}	
