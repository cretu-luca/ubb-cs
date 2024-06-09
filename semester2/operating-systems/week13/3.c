#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

pthread_cond_t guessed;
pthread_mutex_t mutex;

typedef struct { 
	
	
	
} data;


typedef struct {
	
	
}

int main(int argc, char* argv[]) {

	int n;
	printf("n=\n");
	scanf("%d", &n);

	srand(time(NULL));
	int randomValue = random() % 1001;

	pthread_cond_init(&

	for(int i = 0; i < n; i++) {
		
		pthread_create(&td[i], NULL, f, 

	}
}
