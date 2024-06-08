#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

// 10. Create two processes A and B. A generates a random number n between 50 and 200. If it is even, it sends it to B, if it is odd it sends n+1 to B. B receives the number and divides it by 2 and sends it back to A. The process repeats until n is smaller than 5. The processes will print the value of n at each step.

int main() {
	int c2p[2], p2c[2], f, n;
	srand(time(0));

	if(pipe(c2p) == -1) {
		perror("1st pipe error");
		exit(1);
	}

	if(pipe(p2c) == -1) {
		perror("2nd pipe error");
		exit(1);
	}

	f = fork();
	if(f == -1) {
		perror("fork error");
		exit(1);
	} else if(f == 0) {
		close(p2c[1]);
		close(c2p[0]);

		n = random() % 151 + 50;
		printf("child generated %d\n", n);

		while(1) {
			if(n % 2 == 1) {
				n = n + 1;
			}
	
			if(write(c2p[1], &n, sizeof(int)) < 0) {
				perror("child write error");
				exit(1);
			}

			if(n < 5) {
				break;
			}

			if(read(p2c[0], &n, sizeof(int)) < 0) {
				perror("child read error");
				exit(1);
			}

			printf("child read %d\n", n);
		}
	
		close(p2c[0]);
		close(c2p[1]);
		exit(0);

	} else {
		close(p2c[0]);
		close(c2p[1]);

		while(1) {
			if(read(c2p[0], &n, sizeof(int)) < 0) {
				perror("parent read error");
				exit(1);
			}

			printf("parent read %d\n", n);

			n /= 2;

			if(n < 5) {
				break;
			}

			if(write(p2c[1], &n, sizeof(int)) < 0) {
				perror("parent write error");
				exit(1);
			}
		}

		close(p2c[1]);
		close(c2p[0]);
		wait(0);
	}

	return 0;
}
