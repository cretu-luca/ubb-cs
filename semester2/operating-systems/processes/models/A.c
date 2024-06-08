#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>

// Write 2 c programs.
// Program nr. 1:
// The program will receive 2 integer numbers as command line arguments. The
// program will spawn 2 child precesses, one process will calculate the sum and
// the other one the product of the numbers received as a command line
// arguments. Afte doing the calculations both processes will write the results
// into a fifo.
// Program nr. 2:
// The program will read 2 numbers from the fifo previously mentioned and
// display on the standard output the greatest common divisor of the 2 numbers.
// The name of the fifo will be passed as a command line argument.

int main(int argc, char* argv[]) {
	
	if(mkfifo(argv[1], 0600) < 0) {
		perror("mkfifo error");
		exit(1);
	}

	int fd_write = open(argv[1], O_WRONLY);
	if(fd_write == -1) {
		perror("open error");
		exit(1);
	}

	for(int i = 0; i < 2; i++) {
		
		int f = fork();
		if(f == -1) {
			perror("fork error");
			exit(1);
		} else if(f == 0) {
			
			if(i == 0) {
				printf("%d %d %d\n", i, atoi(argv[2]), atoi(argv[3]));
				int sum = atoi(argv[2]) + atoi(argv[3]);
				if(write(fd_write, &sum, sizeof(int)) < 0) {
					perror("write error");
					exit(1);
				}

				printf("sum = %d\n", sum);
			} else if(i == 1) {
				printf("%d %d %d\n", i, atoi(argv[2]), atoi(argv[3]));
				int product = atoi(argv[2]) * atoi(argv[3]);
				if(write(fd_write, &product, sizeof(int)) < 0) {
					perror("write error");
					exit(1);
				}

				printf("product = %d\n", product);
			}

			exit(0);
		} else {
			wait(0);
		}
	}

	wait(0);
	wait(0);
	close(fd_write);

	if(unlink(argv[1]) == -1) {
		perror("unlink error");
	}

	exit(0);
}
