#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
	if(argc != 2) {
		perror("invalid number of arguments");
		exit(0);
	}

	int n = atoi(argv[1]);

	for(int i = 0; i < n; i++) {
		int f = fork();

		if(f == -1) {
			perror("fork error");
		} else if(f == 0) {
			printf("child, i = %d, pid = %d, ppid = %d\n", i, getpid(), getppid());
		} else {
			printf("parent %d - child %d\n", getpid(), f);
			wait(0);
			exit(0);
		}
	}

	printf("we so done");

	return 0;
}
