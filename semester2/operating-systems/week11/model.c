#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int isPrime(int x) {
	if(x < 2) {
		return 0;
	}
	
	if(x == 2) {
		return 1;
	}

	if(x % 2 == 0) {
		return 0;
	}

	for(int i = 3; i < x; i += 2) {
		if(x % i == 0) {
			return 0;
		}
	}

	return 1;
}

int main() {
	
	int p2c[2], c2p[2];

	if(pipe(p2c) == -1) {
		perror("1st pipe error");
		exit(1);
	}

	if(pipe(c2p) == -1) {
		perror("2nd pipe error");
		exit(1);
	}

	int f = fork();
	if(f == -1) {
		perror("fork error");
		exit(1);

	} else if(f == 0) {
		
		close(p2c[1]);
		close(c2p[0]);
		
		int x, index = 0, divisors[100];


		while(1) {
			
			index = 0;
			if(read(p2c[0], &x, sizeof(int)) < 0) {
				perror("child read error");
			}

			for(int i = 2; i < x; i++) {
				if(x % i == 0) {
					divisors[index++] = i; 
				}
			}
			
			if(write(c2p[1], &index, sizeof(int)) < 0) {
				perror("child write error");
				exit(1);
			}
	
			if(write(c2p[1], divisors, sizeof(int) * index) < 0) {
				perror("child write error");
				exit(1);
			}

			if(isPrime(x)) { 
				break;
			}
		}

		close(p2c[0]);
		close(c2p[1]);
		exit(0);

	} else {
		
		close(p2c[0]);
		close(c2p[1]);
		int length = 0, divisors[100], x;

		while(scanf("%d", &x)) {
			if(write(p2c[1], &x, sizeof(int)) < 0) {
				perror("parent write error");
				exit(1);
			}

			if(read(c2p[0], &length, sizeof(int)) < 0) {
				perror("parent write error");
				exit(1);
			}

			if(read(c2p[0], divisors, sizeof(int) * length) < 0) {
				perror("parent read error");
				exit(1);
			}

			for(int i = 0; i < length; i++) {
				printf("%d ", divisors[i]);
			}

			printf("\n");

			if(isPrime(x)) {
				wait(0);
				break;
			}

		}

		close(p2c[1]);
		close(c2p[0]);

	}
	
	return 0;

}
