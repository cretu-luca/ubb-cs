#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// Write a C program that creates a child process, which in turn creates another child 
// process, and so on until the N-th generation, where N is a command line argument. 
// Each child process will have an index (the child process will be 1, the grandchild 
// process will be 2, and so on). Each process will print its index, PID, and PPID.

int main(int argc, char* argv[]) {
	int f, count = 0, n = atoi(argv[1]);

	printf("big daddy pid - %d\n", getpid());

	for(int i = 0; i < n; i++) {
			
		f = fork();
		if(f == -1) {
			perror("fork error");
			exit(1);
		} else if(f == 0) {
			printf("index - %d, pid - %d, ppid - %d\n", count, getpid(), getppid());	
			
		} else {
			wait(0);
			exit(0);
		}
		
	}

	return 0;
}
