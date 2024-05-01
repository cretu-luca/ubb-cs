#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
	int c1_2p[2], c2_2p[2];
	int p2_c1[2], p2_c2[2];	

	int nr1, nr2;
	
	if(pipe(c1_2p) == -1){ 
		perror("error creating pipe from parent to child 1");
		exit(1);
	}

	if(pipe(c2_2p) == -1) {
		perror("error creating pipe from parent to child 2");
		exit(1);
	}

	if(pipe(p2_c1) == -1) {
		perror("error creating pipe from child 1 to parent");
		exit(1);
	}

	if(pipe(p2_c2) == -1) {
		perror("error creating pipe from child 2 to parent");
		exit(1);
	}

	int f1 = fork();
	if(-1 == f1) {
		perror("forking error 1");
		exit(1);
	} else if (f1 == 0) {
		close(c1_2p[0]);
		close(c2_2p[0]);
		close(c2_2p[1]);

		srand(getpid());
		int nr = rand() % 1000;
		printf("Child 1 generated %d\n", nr);

		if(write(c1_2p[1], &nr, sizeof(int)) == -1) {
			perror("Horror has occurred");
			exit(1);
		}

		if(-1 == read(p2_c1[0], &nr, sizeof(int))) {
			perror("cannot read response in child 1");
			exit(1);
		}

		if(nr == 1) {
			printf("child 1 has won!\n");
		} else if (nr == 0) {
			printf("draw!\n");
		} else {
			printf("child 1 has lost!\n");
		}

		exit(0);
	}

	int f2 = fork();
	if(f2 == -1) {
		perror("forking error 2");
		wait(0);
		exit(1);
	} else if (f2 == 0) {
		close(c2_2p[0]);
		close(c1_2p[0]);
		close(c1_2p[1]);

		srand(getpid());
		int nr = rand() % 1000;
		printf("Child 2 generated %d\n", nr);
		
		if(write(c2_2p[1], &nr, sizeof(int)) == -1) {
			perror("Horror has occurred");
			exit(1);
		}

		exit(0);
	}
	close(c1_2p[1]);
	close(c2_2p[1]);
	
	if(read(c1_2p[0], &nr1, sizeof(int)) == -1) {
		perror("cannot read number from child 1");
		close(c1_2p[0]);
		close(c2_2p[0]);
		exit(1);
	}	

	if(read(c2_2p[0], &nr2, sizeof(int)) == -1) {
		perror("cannot read from child 2");
		close(c1_2p[0]);
		close(c2_2p[0]);
		exit(1);
	}

	printf("parent read number 1: %d\nParent read number 2: %d\n", nr1, nr2);
	
	if(nr1 > nr2) {
		nr1 = 1;
		nr2 = -1;
	} else if(nr1 == nr2) {
		nr1 = 0;
		nr2 = 0;
	} else {
		nr1 = -1;
		nr2 = 1;
	}

	close(c1_2p[0]);
	close(c2_2p[0]);
	wait(0);
	wait(0);
	return 0;
}
