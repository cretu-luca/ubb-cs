#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// Write a C program that creates N child processes and gives each one an index (the 
// first child will be 1, the second 2, etc.). Each child process will print its index, 
// PID and PPID (parent PID). N will be a command line argument.

int main(int argc, char* argv[]) {
	int count = 0, f, n = atoi(argv[1]);

	for(int i = 0; i < n; i++) {
	
		count++;
		f = fork();

		if(f == -1) {
			perror("fork error");
		} else if(f == 0) {
			printf("index - %d, pid - %d, ppid - %d\n", count, getpid(), getppid());
			
			exit(0);

		} else { 
			
			wait(0);
		}
	}

	return 0;
}
