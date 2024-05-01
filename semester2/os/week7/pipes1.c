#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <fcntl.h>

int main(int argc, char** argv) {
	srandom(getpid());

	int p2c[2];
	int c2p[2];
	if(-1 == pipe(p2c)) { 
		perror("Error on pipe");
		exit(1);
	}

	if(-1 == pipe(c2p)) {
		perror("Error on pipe");
		exit(1);
	}

	int f = fork();
	if(0 > f) {
		perror("Cannot create child process");
		exit(1);
	} else if(0 == f) { // child
		close(p2c[1]); // 
		close(c2p[0]);		
		
		int size;
		if(-1 == read(p2c[0], &size, sizeof(int))) {
			perror("Error reading array size from parent");
			close(p2c[0]);
			close(c2p[1]);
			exit(1);
		}

		int nr, sum = 0;
	
		for(int i = 0; i < size; i++) { 
			if(-1 == read(p2c[0], &nr, sizeof(int))) { 
				perror("Error reading element from parent");
				close(p2c[0]);
				close(c2p[1]);
				exit(1);
			}
			sum += nr;
		}

		if(-1 == write(c2p[1], &sum, sizeof(int))) {
			perror("Error writing array size from parent");
			close(p2c[0]);
			close(c2p[1]);
			exit(1);
		}
	
		close(p2c[0]);
		close(c2p[1]);
		exit(0);
	} else { // parent
		close(p2c[0]); // parent doesn't read from p2c (0 is used for reading)
		close(c2p[1]); // parent doesn't write to c2p (1 is used for writing)

		int n;
		printf("n=");
		scanf("%d", &n);

		if(n > 0) {
			int* arr = malloc(sizeof(int) * n);

			for(int i = 0; i < n; i++) {
				arr[i] = random() % 100;
				printf("a[%d] = %d\n", i, arr[i]);
			}

			if(-1 == write(p2c[1], &n, sizeof(int))) {
				perror("Error writing element to child");
				free(arr);
				close(p2c[0]);
				close(p2c[1]);
				wait(0);
				exit(1);				
			}

			for(int i = 0; i < n; i++) { 
				if(-1 == write(p2c[1], &arr[i], sizeof(int))) {
					perror("Error writing element to child");
					free(arr);
					close(p2c[0]);
					close(p2c[1]);
					wait(0);
					exit(1);
				}
			}
			
			free(arr);

			int sum = 0;
			if(-1 == read(p2c[0], &sum, sizeof(int))) {
				perror("Error reading sum from child");
				close(p2c[1]);
				wait(0);
				exit(1); 
			}

			printf("sum = %d\n", sum);
		}
		wait(NULL);
		close(p2c[1]);
		close(p2c[0]);
	}
}

