#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

struct counts {
	int digit_count;
	int letter_count;
};

int main(int argc, char* argv[]) {
	
	int p[size][2];

	for(int i = 1; 

	for(int i = 1; i < argc; i++) {
		if(fork() == 0) {
			int digit_counter = 0, letter_counter = 0;

			for(int j = 0; j < strlen(argv[i]); j++) {
				if(isdigit(argv[i][j]))
					digit_counter += 1;
				if(isalpha(argv[i][j]))
					letter_counter += 1;
			}
			
			struct counts counters;
			counters.digit_count = digit_counter;
			counters.letter_count = letter_counter;

			if(write(c2p[1], &counters, sizeof(counters) == -1)) {
				perror("error writing to pipe");
				exit(1);
			}

			exit(0);
		} else {
			printf("parent");

			struct counts counters;
			if(read(c2p[0], &counters, sizeof(counters) == -1)) {
				perror("error reading from pipe");
				exit(1);
			}
			printf("%d %d\n", counters.digit_count, counters.letter_count);
		}
	}
}
