#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>

int main(int argc, char* argv[]) {
	
	int sum, product;
	int fd_read = open(argv[1], O_RDONLY);
	if(fd_read == -1) {
		perror("open error");
	}

	if(read(fd_read, &sum, sizeof(int)) < 0) {
		perror("read error");
		exit(1);
	}

	if(read(fd_read, &product, sizeof(int)) < 0) {
		perror("read error");
		exit(1);
	}

	printf("sum = %d, product = %d\n", sum, product);

	close(fd_read);
	exit(0);
}
