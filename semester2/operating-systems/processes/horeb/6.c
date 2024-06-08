// Create a C program that generates N random integers (N given at the command line). It then creates a child, sends the numbers via pipe. The child calculates the average and sends the result back.

#include <stdlib.h>
#include <stdio.h>

// pipe[0] -> used for reading
// pipe[1] -> used for writing

int main(int argc, char* argv[]) {
	if(argc != 2) {
		printf("invalid number of arguments");
		exit(1);
	}

	int p2c[2], c2p[2];
	pipe(p2c);
	pipe(c2p);

	int f = fork();
	if(f == -1) {
		perror("error on fork");
		exit(1);
	} else if(f == 0) {
		close(p2c[1]);
		close(c2p[0]);

		int n = 0, nr;
		float rez = 0;
		if(read(p2c[0], &n, sizeof(int)) < 0) { 
			perror("error on read from parent");
			close(p2c[0]);
			close(c2p[1]);
			exit(1);
		}

		for(int i = 0; i < n; i++) {
			if(read(p2c[0], &nr, sizeof(int)) < 0) {
				perror("error on read from parent");
				close(p2c[0]);
				close(c2p[1]);
				exit(1);
			}

			rez += nr;
		}

		rez /= n;
		if(write(c2p[1], &rez, sizeof(float)) < 0) { 
			perror("error on write result to parent");
			close(p2c[0]);
			close(c2p[1]);
			exit(1);
		}

		close(p2c[0]);
		close(c2p[1]);
	} else {
		close(p2c[0]);
		close(c2p[1]);

		int n = atoi(argv[1]);
		int i, nr;
		float rez = -1;

		srandom(time(0));
		if(write(p2c[1], &n, sizeof(int)) < 0) {
			perror("error on write n to child");
			close(p2c[1]);
			close(c2p[0]);

			wait(0);
			exit(1);
		}

		for(int i = 0; i < n; i++) {
		
			nr = random() % 100;
			printf("parent generated %d\n", nr);
			if(write(p2c[1], &nr, sizeof(int)) < 0) {
				perror("error on write number to child");
				close(p2c[1]);
				close(c2p[0]);
			}
		}
		wait(0);
		if(read(c2p[0], &rez, sizeof(float)) < 0) { 
			perror("error on read result from child");
		}
		printf("average is %f\n", rez);
		close(p2c[1]);
		close(c2p[0]);
	}
	return 0;
}
