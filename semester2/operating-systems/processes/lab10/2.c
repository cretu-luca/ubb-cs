#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>

// Write a C program that receives N (0 < N < 10) command line arguments. The main process
// creates N child processes. The K-th child process will count all the letters and all the digits of
// the K-th command line argument and will send the two counts to the parent. The parent will
// calculate the sum of the letter and digit counts it receives from the children and print the two
// totals.

int main(int argc, char* argv[]) {
	int c2p[10][2], f;

	for(int i = 1; i < argc; i++) {
		if(pipe(c2p[i]) == -1) {
			perror("pipe error");
			exit(1);
		}
	}

	for(int i = 1; i < argc; i++) {
		f = fork();

		if(f == -1) {
			perror("fork error");
			exit(1);
		} else if(f == 0) {
			close(c2p[i][0]);
			int letters = 0, digits = 0;
				
			for(int j = 0; j < strlen(argv[i]); j++) {
				if(isdigit(argv[i][j])) { 
					digits++;
				} else { 
					letters++;					
				}
			}
			

			if(write(c2p[i][1], &letters, sizeof(int)) < 0) {
				perror("child - write error");
				exit(1);
			}

			if(write(c2p[i][1], &digits, sizeof(int)) < 0) {
				perror("child - write error");
				exit(1);
			}

			letters = 0, digits = 0;
			
			close(c2p[i][1]);
			exit(0);
		} else {
			int letters = 0, digits = 0;
			
			if(read(c2p[i][0], &letters, sizeof(int)) < 0) {
				perror("parent - read error");
				exit(1);
			}

			if(read(c2p[i][0], &digits, sizeof(int)) < 0) { 
				perror("parent - read error");
				exit(1);
			}

			printf("argument %s has %d letters and %d digits\n", argv[i], letters, digits); 
		
			letters = 0, digits = 0;
		}
	}

	for(int i = 1; i < argc; i++) {
		close(*c2p[i]);
	}

	return 0;
}
