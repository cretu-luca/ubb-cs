#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]) {

	if(argc != 2) {
		perror("Please provide exactly one argument!");
		exit(1);
	}

	int n = atoi(argv[1]);
	for(int i = 0; i < n; i++) {
		int f = fork();
		if(f == -1) {
			perror("Error on fork!");
		} else if (f == 0) {
			printf("%d. PID: %d - PPID: %d\n", i, getpid(), getppid());
			exit(0);
		} else {
			printf("Parent %d - Child: %d\n", getpid(), f);
		}
	}

	for(int i = 0; i < n; i++) {
		wait(0);
	}

	return 0;
}
