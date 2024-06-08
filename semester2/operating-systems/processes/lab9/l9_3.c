#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// Write a C program that creates two child processes. Each child process generates 
// a random number between 0 and 1000 and sends it via pipe to the parent. The parent 
// will compare the numbers and send 1 to the process that generated the higher number, 
// and -1 to the other process. If the numbers are equal, the parent sends 0 to both 
// processes.

int main(int argc, char* argv[]) {
	int f, A2B[2], A2C[2], B2A[2], C2A[2];

	if(pipe(A2B) == -1) {
		perror("A2B - error");
		exit(1);
	}		
	
	if(pipe(A2C) == -1) {
		perror("A2C - error");
		exit(1);
	}		
	
	if(pipe(B2A) == -1) {
		perror("B2A - error");
		exit(1);
	}		

	if(pipe(C2A) == -1) {
		perror("C2A - error");
		exit(1);
	}
	
	f = fork();
	if(f == -1) {
		perror("1st fork error");
		exit(1);
	} else if(f == 0) {
		srand(time(0) + getpid());
		close(B2A[0]);
		close(A2B[1]);
		
		int nr = random() % 1001, result;
		printf("B generated %d\n", nr);
		if(write(B2A[1], &nr, sizeof(int)) < 0) {
			perror("B2A - write error");
			exit(1);
		}

		if(read(A2B[0], &result, sizeof(int)) < 0) {
			perror("A2B - read error");
			exit(1);
		}
		printf("B read %d\n", result);
		
		close(B2A[1]);
		close(A2B[0]);
		exit(0);
	}

	f = fork();	
	
	if(f == -1) {
		perror("2nd fork error");
		exit(1);
	} else if(f == 0) {
		srand(time(0) + getpid());
		close(C2A[0]);
		close(A2C[1]);
		
		int nr = random() % 1001, result;
		printf("C generated %d\n", nr);
		if(write(C2A[1], &nr, sizeof(int)) < 0) {
			perror("C2A - write error");
			exit(1);
		}

		if(read(A2C[0], &result, sizeof(int)) < 0) {
			perror("A2C - read error");
			exit(1);
		}

		printf("C read %d\n", result);
		close(C2A[1]);
		close(A2C[0]);
		exit(0);
 	} else {
		close(B2A[1]);
		close(A2B[0]);
		close(C2A[1]);
		close(A2C[0]);

		int nrB, nrC, one = 1, minus_one = -1, zero = 0;
		if(read(B2A[0], &nrB, sizeof(int)) < 0) {
			perror("B2A - read error");
			exit(1);
		}
		printf("A read %d from B\n", nrB);

		if(read(C2A[0], &nrC, sizeof(int)) < 0) {
			perror("C2A - read error");
			exit(1);
		}
		printf("A read %d from C\n", nrC);

		if(nrB > nrC) {
			if(write(A2B[1], &one, sizeof(int)) < 0) {
				perror("A2B - write error");
				exit(1);
			}

			if(write(A2C[1], &minus_one, sizeof(int)) < 0) {
				perror("A2C - write error");
				exit(1);
			}
		}

		if(nrC > nrB) {
			if(write(A2C[1], &one, sizeof(int)) < 0) {
				perror("A2C - write error");
				exit(1);
			}

			if(write(A2B[1], &minus_one, sizeof(int)) < 0) {
				perror("A2B - write error");
				exit(1);
			}
		}

		if(nrB == nrC) {
			if(write(A2C[1], &zero, sizeof(int)) < 0) {
				perror("A2C - write error");
				exit(1);
			}


			if(write(A2B[1], &zero, sizeof(int)) < 0) {
				perror("A2B - write error");
				exit(1);
			}
		}

		wait(0);
		wait(0);
	}

	return 0;
}
