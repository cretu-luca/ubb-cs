#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <string.h>

#define SIZE 128

int count, pos;
char buffer[SIZE + 1];

pthread_cond_t cg = PTHREAD_COND_INITIALIZER;
pthread_cond_t cp = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mx = PTHREAD_MUTEX_INITIALIZER;

void* generate(void* arg) {
	
	while(1) {

		char ch = 'a' + rand() % ('z' - 'a' + 1);
		
		pthread_mutex_lock(&mx);
		
		if(pos == SIZE) {
			pthread_cond_signal(&cp);
	
			while(pos == SIZE)
				pthread_cond_wait(&cg, &mx);
		}

		if(count == 0) {
			break;
		}

		buffer[pos] = ch;
		pos++;

		pthread_mutex_unlock(&mx);
	}

	pthread_mutex_unlock(&mx);
	return NULL;
}

void* print(void* arg) {

	while(1) {
	
		pthread_mutex_lock(&mx);

		if(pos != SIZE) {
			pthread_cond_signal(&cg);
			while(pos < SIZE) {
				pthread_cond_wait(&cp, &mx);
			}
		}

		printf("%s\n", buffer);

		memset(buffer, 0, SIZE * sizeof(char));
		pos = 0;
		count--;
		pthread_cond_broadcast(&cg);

		if(count == 0)
			break;
		
		pthread_mutex_unlock(&mx);
	}
	
	pthread_mutex_unlock(&mx);
	return NULL;
}

int main(int argc, char* argv[]) {

	if(argc < 3) {
		printf("prea putine argumente");
		exit(EXIT_FAILURE);
	}

	int n = atoi(argv[1]);
	int m = atoi(argv[2]);

	pthread_t tid[n + 1];

	pos = 0;
	count = m;
	memset(buffer, 0, (SIZE + 1) * sizeof(char));
	srand(time(NULL));

	for(int i = 0; i < n; i++) {
		pthread_create(&tid[i], NULL, generate, NULL);
	}

	pthread_create(&tid[n], NULL, print, NULL);
	
	for(int i = 0; i < n + 1; i++) {
		pthread_join(tid[i], NULL);
	}
	
	return 0;
}
