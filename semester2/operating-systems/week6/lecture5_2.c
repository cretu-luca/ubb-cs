#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv){
	// int a[4] = {1, 2, 3, 4};

	if(fork() == 0){
		if(execlp("echo", "echo", "asdf", NULL) != -1){
			perror("something went bad");
			exit(0);
		}
	}
	printf("we echoed!\n");
	return 0;
}
