#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

// Write a C program that creates n child processes. Each child process will print its PID and its parent PID. The parent process will print its PID and the PID of each of the child processes.

int main(int argc, char* argv[]) {
	
	if(argc != 2) {
		perror("invalid arguments");
	}

	int n = atoi(argv[1]);

	for(int i = 0; i < n; i++) {
	
		int p = fork();

		if(p == -1) {
			perror("error in fork");
		} else if(p == 0) {
			printf("child, i = %d, pid = %d, ppid = %d\n", i, getpid(), getppid());
			exit(0);
		} else {
			printf("parent, pid = %d, ppid = %d\n", getpid(), getppid());
			wait(0);
		}
	
	}

	for(int	i = 0; i < n; i++) {
		wait(NULL);
	}

	return 0;
}
