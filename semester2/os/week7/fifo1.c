#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <fcntl.h>

int main(int argc, char** argv) {
	if(-1 == mkfifo("./fifo1", 0600)) {
		perror("Error creating fifo1");
		exit(1);
	}
	
	if(-1 == mkfifo("./fifo2", 0600)) {
		perror("Error creating fifo2");
		exit(1);
	}
	
	int p2c = open("./fifo1", O_WRONLY);
	if(-1 == p2c) { 
		perror("Error opening fifo1");
	}

	int c2p = open("./fifo2", O_RDONLY);
	if(-1 == c2p) { 
		perror("Error opening fifo2");
	}

	srandom(getpid());
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
			close(p2c);
			close(c2p);
			wait(0);
			exit(1);				
		}

		for(int i = 0; i < n; i++) { 
			if(-1 == write(p2c[1], &arr[i], sizeof(int))) {
				perror("Error writing element to child");
				free(arr);
				close(p2c);
				close(c2p);
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

