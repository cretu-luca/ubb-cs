#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int f;

void child_handler(int signal) {
	printf("Child process terminating...\n");
	exit(0);
}

void parent_handler(int signal) {
	printf("Parent process terminating...\n");
	kill(f, SIGUSR1);
	wait(0);
	exit(0);
}

void zombie_handler(int signal) {
	printf("Parent waiting for child process to terminate...\n");
	wait(0);
}

int main(int argc, char* argv[]) {
	
	f = fork();

	if(f == -1) {
		perror("fork error");
		exit(1);
	} else if(f == 0) {
		
		signal(SIGUSR1, child_handler);
		printf("C - Child PID: %d Parent PID: %d\n", getpid(), getppid());

		while(1) {
			printf("Child working...\n");
			sleep(3);
		}

		exit(0);
	} else {
		
		signal(SIGUSR1, parent_handler);
		signal(SIGCHLD, zombie_handler);

		printf("P - Child PID: %d Parent PID: %d\n", f, getpid());

		while(1) {
			printf("Parent working...\n");
			sleep(3);
		}
	}

	return 0;
}
