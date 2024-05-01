#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char* argv[]) {
	int n = atoi(argv[1]);
	// scanf("%d", &n);

	printf("parent - %d\n", getpid());

	for(int i = 0; i < n; i++) {
		if(fork() == 0) {
			printf("%d. child - %d, parent - %d\n", i + 1, getpid(), getppid());
			exit(0);
		}
	}
}
