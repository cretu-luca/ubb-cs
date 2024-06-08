#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

// parent reads from standard input until X and sends to child 1
// child 1 populates letter frequency array for received words
// child 1 sends the array to child 2, which does the printing

int f, p;

void handle_child1(int sig) {
	printf("terminating child 1...\n");
	kill(f, SIGTERM); 
}

void handle_child2(int sig) {
	printf("terminating child 2...\n");
	kill(p, SIGTERM);
}

int main() {
	
	int length;
	int p2c[2], c2c2[2];

	pipe(p2c);
	pipe(c2c2);

	f = fork();
	if(f == -1) {
		printf("fork failed");
		exit(1);
	} else if(f == 0) {
		
		close(p2c[1]);
		close(c2c2[0]);

		while(1) { 

			char word[100];
			int frequency[300] = {0};

			if(read(p2c[0], &length, sizeof(int)) < 0) {
				perror("child 1 read length error");
				exit(1);
			}

			if(read(p2c[0], word, sizeof(char) * (length + 1)) < 0) {
				perror("child 1 read word error");
				exit(1);
			}
			
			for(int i = 0; i < length; i++) {
				frequency[word[i]]++;
			}

			if(write(c2c2[1], frequency, sizeof(int) * 300) < 0) {
				perror("child 1 write error"); 
				exit(1);
			}
		}
	} 

	p = fork();

	if(p == -1) {
		printf("fork failed");
		exit(1);
	} else if(p == 0) { 
		
		close(c2c2[1]);
		close(p2c[0]);
		close(p2c[1]);

		while(1) {
			int frequency[300] = {0};
			if(read(c2c2[0], frequency, sizeof(int) * 300) < 0) {
				perror("child 2 read error");
				exit(1);
			}

			for(int i = 0; i < 300; i++) {
				if(frequency[i] > 0) {
					printf("%c has frequency %d\n", (char) i, frequency[i]);
				}
			}
		}
	} else {

		signal(SIGUSR1, handle_child1);
		signal(SIGUSR2, handle_child2);

		char word[100];
		printf("Enter word:\n");
        while (scanf("%s", word) && strcmp(word, "X") != 0) {
            int length = strlen(word);

            if (write(p2c[1], &length, sizeof(int)) <= 0) {
                perror("parent write length error");
                break;
            }

            if (write(p2c[1], word, length) <= 0) {
                perror("parent write word error");
                break;
            }
		
			sleep(1);
            printf("Enter word:\n");
        }


		kill(f, SIGUSR1);
		kill(p, SIGUSR2);

	}
}
