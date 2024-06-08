#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>

int main() {
	int c1c2[2], c2c1[2], f, n;
	if(pipe(c1c2) == -1) {
		perror("1st pipe error");
	}
	 
	if(pipe(c2c1) == -1) {
		perror("2nd pipe error");
	}

	srand(time(0));

	f = fork();
	if(f == -1) {
		perror("1st fork error");
		exit(1);
	} else if(f == 0) {
		close(c1c2[0]);
		close(c2c1[1]);

		n = random() % 10 + 1;
		if(write(c1c2[1], &n, sizeof(int)) < 0) {
			perror("child 1 - error on writing");
			exit(1);
		}

		while(n != 10) {
			if(read(c2c1[0], &n, sizeof(int)) < 0) {
				perror("child 1 - error on reading");
				exit(1);
			}
	
			printf("child 1 read %d\n", n);

			if(n == 10) {
				break;
			}

			if(write(c1c2[1], &n, sizeof(int)) < 0) {
				perror("child 1 - error on writing");
				exit(1);
			}
		}
		
		close(c1c2[1]);
		close(c2c1[0]);
		exit(0);
	}

	f = fork();
	if(f == -1) {
		perror("2nd fork error");
		exit(1);
	} else if(f == 0) {
		close(c1c2[1]);
		close(c2c1[0]);

		int n = 0;
		while(n != 10) {
			if(read(c1c2[0], &n, sizeof(int)) < 0) {
				perror("child 2 - error on read");
				exit(1);
			}

			printf("child 2 read %d\n", n);

			if(n == 10) {
				break;
			}

			n = random() % 10 + 1;

			if(write(c2c1[1], &n, sizeof(int)) < 0) {
				perror("child 2 - error on write");
				exit(1);
			}
		}

		close(c2c1[1]);
		close(c1c2[0]);
		exit(0);
	}
	
	wait(0);
	wait(0);
	return 0;
}
