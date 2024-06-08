#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

// Write a C program that creates two child processes. The two child processes will alternate sending random integers between 1 and 10 (inclusively) to one another until one of them sends the number 10. Print messages as the numbers are sent.

int main() {
	int c1c2[2], c2c1[2], f;
	pipe(c1c2);
	pipe(c2c1);

	srand(time(0));

	f = fork();
	if(f == -1) {
		perror("fork error 1st process");
		exit(1);
	} else if(f == 0) { // in child 1
		// child 1 will read from child 2
		// child 1 will write to child 2
		close(c2c1[1]); // child 2 writing to child 1
		close(c1c2[0]); // child 2 reading from child 1
		int n;
		
		if(read(c2c1[0], &n, sizeof(int)) < 0) { 
			perror("Child 1: error on read");
			exit(1);
		}

		printf("Child 1 read %d\n", n);
		while(n != 10) {
	
			n = random() % 10 + 1;
			if(write(c1c2[1], &n, sizeof(int)) < 0) {
				perror("Child 1: error on write");
				exit(1);
			}

			if(n == 10) {
				break;
			}

			if(read(c2c1[0], &n, sizeof(int)) < 0) {
				perror("Child 1: error on reading");
				exit(1);
			}
			
			printf("Child 1 read %d\n", n);
		}

		close(c2c1[0]);
		close(c1c2[1]);
		exit(0);
	}

	f = fork();
	if(f == -1) {
		perror("fork error 2nd process");
		exit(1);
	} else {
		
		close(c2c1[0]);
		close(c1c2[1]);

		int n = 0;
		while(n != 10) { 
	
			n = random() % 10 + 1;
			if(write(c2c1[1], &n, sizeof(int)) < 0) {
				perror("Child 2: error on write");
				exit(1);
			}

			if(n == 10) {
				break;
			}

			if(read(c1c2[0], &n, sizeof(int)) < 0) {
				perror("Child 2: error on read");
				exit(1);
			}
			
			printf("Child 2 read %d\n", n);
		}
		
		close(c2c1[1]);
		close(c1c2[0]);
		exit(0);
	}

	wait(0);
	wait(0);
	return 0;
}
