#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
	int c2p[2], p2c[2];
	pipe(c2p);
	pipe(p2c);

	int f = fork();
	if(f == -1) {
		perror("fork error");
		exit(1);
	} else if(f == 0) {
		close(p2c[1]);
		close(c2p[0]);
		
		int n, nr;
		float rez;

		if(read(p2c[0], &n, sizeof(int)) < 0) {
			perror("error on reading number of numbers from parent");
			close(p2c[0]);
			close(c2p[1]);
			exit(1);
		}

		for(int i = 0; i < n; i++) {
			if(read(p2c[0], &nr, sizeof(int)) < 0) {
				perror("error on reading numbers from parent");
				close(p2c[0]);
				close(c2p[1]);
				exit(1);
			}
			rez += nr;
		}

		rez /= n;
		if(write(c2p[1], &rez, sizeof(float)) < 0) {
			perror("error writing to parent");
			close(p2c[0]);
			close(c2p[1]);
			exit(1);
		}

		close(p2c[0]);
		close(c2p[1]);
	} else {
		close(p2c[0]);
		close(c2p[1]);

		srand(time(0));
		int n, nr;
		float rez;
	
		n = atoi(argv[1]);
		if(write(p2c[1], &n, sizeof(int)) < 0) {
			perror("error writing to child");
			close(p2c[0]);
			close(c2p[1]);
			exit(1);
		}

		for(int i = 0; i < n; i++) {
			nr = random() % 100;
			if(write(p2c[1], &nr, sizeof(int)) < 0) {
				perror("error on writing random number to child");
				close(p2c[0]);
				close(c2p[1]);
				exit(1);
			}
			printf("parent generated %d\n", nr);
		}

		wait(0);

		if(read(c2p[0], &rez, sizeof(float)) < 0) {
			perror("error reading average from child");
			close(p2c[0]);
			close(c2p[1]);
			exit(1);
		}

		printf("average is %f", rez);	
		close(p2c[1]);
		close(c2p[0]);
	}

	return 0;
}
