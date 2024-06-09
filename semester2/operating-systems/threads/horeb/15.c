#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <ctype.h>

// Write a program that receives strings of characters as command line arguments. For each string the program creates a thread which calculates the number of digits, the number of letters and the number of special characters (anything other than a letter or digit). The main program waits for the threads to terminate and prints the total results (total number of digits, letters and special characters across all the received command line arguments) and terminates. Use efficient synchronization. Do not use global variables


struct arg_t {
	
	int* digits;
	int* letters;
	int* special;

	pthread_mutex_t* mtx;

	char* string;
};

void* f(void* arg) {

	int letters = 0, digits = 0, special = 0;
	struct arg_t* data = (struct arg_t*) arg;
	for(int i = 0; i < strlen(data->string); i++) {
		if(isalpha(data->string[i])) {
			letters += 1;
		} else if(isdigit(data->string[i])) {
			digits += 1;
		} else {
			special += 1;
		}
	}
	
	if(letters > 0) {
		// printf("%s has %d letters\n", data->string, letters);
		pthread_mutex_lock(&data->mtx[0]);
		(*data->letters) += letters;
		pthread_mutex_unlock(&data->mtx[0]);
	}

	if(digits > 0) {
		// printf("%s has %d digits\n", data->string, digits);
		pthread_mutex_lock(&data->mtx[1]);
		(*data->digits) += digits;
		pthread_mutex_unlock(&data->mtx[1]);
	}

	if(special > 0) {
		// printf("%s has %d special\n", data->string, special);
		pthread_mutex_lock(&data->mtx[2]);
		(*data->special) += special;
		pthread_mutex_unlock(&data->mtx[2]);
	}
}

int main(int argc, char* argv[]) {
	
	int letters = 0, digits = 0, special = 0;

	pthread_t td[argc];
	pthread_mutex_t mtx[3];

	struct arg_t args[argc];
	
	for(int i = 0; i < 3; i++) {
		pthread_mutex_init(&mtx[i], NULL);
	}

	for(int i = 0; i < argc - 1; i++) {
		args[i].letters = &letters;
		args[i].digits = &digits;
		args[i].special = &special;
		args[i].mtx = mtx;
		args[i].string = argv[i + 1];

		pthread_create(&td[i], NULL, f, &args[i]); 
	}

	for(int i = 0; i < argc - 1; i++) {
		pthread_join(td[i], NULL);
	}

	printf("letters - %d\ndigits - %d\nspecial - %d", letters, digits, special);

}
