#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main() {
	int A2D[2], B2D[2], C2D[2], D2B[2], D2C[2];
	int nrA, nrB, nrC, running = 1;

	srand(time(0));

	if(pipe(A2D) == -1) {
		perror("A2D error");
		exit(1);
	}

	if(pipe(B2D) == -1) {
		perror("B2D error");
		exit(1);
	}

	if(pipe(C2D) == -1) {
		perror("C2D error");
		exit(1);
	}

	if(pipe(D2B) == -1) {
		perror("D2B error");
		exit(1);
	}

	if(pipe(D2C) == -1) {
		perror("D2C error");
		exit(0);
	}

	int f = fork();
	if(f == -1) {
		perror("1st fork error");
		exit(1);
	} else if(f == 0) { // process B
	
		while(1) {
			nrB = random() % 200 + 1;

			printf("B generated %d\n", nrB);
			
			if(write(B2D[1], &nrB, sizeof(int)) < 0) {
				perror("B2D - write error");
				exit(1);
			}

			if(read(D2B[0], &running, sizeof(int)) < 0) {
				perror("D2B - read error");
				exit(1);
			}

			if(running == 1) {
				break;
			}
		}

		exit(0);

	} else {
		
		int n = random() % 20 + 1;
		
		printf("A generated %d\n", n);

		if(write(A2D[1], &n, sizeof(int)) < 0) {
			perror("A - write error");
			exit(1);
		}
	}

	f = fork();
	printf("forked\n");
	if(f == -1) {
		perror("2nd fork error");
		exit(1);
	} else if(f == 0) { 
		
		while(1) {
				
			nrC = random() % 200 + 1;

			printf("C generated %d\n", nrC);

			if(write(C2D[1], &nrC, sizeof(int)) < 0) {
				perror("C2D - write error");
				exit(1);
			}

			if(read(D2C[0], &running, sizeof(int)) < 0) {
				perror("D2C - read error");
				exit(1);
			}
			
			if(running == 1) {
				break;
			}
		}

		exit(0);
	} 

	f = fork();
	if(f == -1) {
		perror("3rd fork error");
		exit(1);
	} else if(f == 0) {
			
		if(read(A2D[0], &nrA, sizeof(int)) < 0) {
			perror("A2D - read error");
			exit(1);
		}
		
		printf("D read %d from A\n", nrA);

		while(1) {

			if(read(B2D[0], &nrB, sizeof(int)) < 0) {
				perror("B2D - read error");
				exit(1);
			}

			printf("D read %d from B\n", nrB);

			if(read(C2D[0], &nrC, sizeof(int)) < 0) {
				perror("C2D - read error");
				exit(1);
			}

			printf("D read %d from C\n", nrC);

			if(abs(nrC - nrB) < nrA) {
				running = 1;
			}

			if(write(D2C[1], &running, sizeof(int)) < 0) {
				perror("D2C - write error");
				exit(1);
			}

			if(write(D2B[1], &running, sizeof(int)) < 0) {
				perror("D2B - write error");
				exit(1);
			}

			if(running == 1) {
				break;
			}
		}

		exit(0);
	}

	wait(0);
	wait(0);
}
