#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <string.h>

#define SIZE 128

typedef struct {
	
	int* count;
	int* pos;
	char* buffer;
	pthread_cond_t* cg;
	pthread_cond_t* cp;
	pthread_mutex_t* mtx;

} data;

void* generate(void* arg) {

	data td = *((data*) arg);
	
	while(1) {

		char ch = 'a' + rand() % ('z' - 'a' + 1);
		
		pthread_mutex_lock(td.mtx);
		
		if(*td.pos == SIZE) {
			pthread_cond_signal(td.cp);
	
			while(*td.pos == SIZE)
				pthread_cond_wait(td.cg, td.mtx);
		}

		if(*td.count == 0) {
			break;
		}

		td.buffer[*td.pos] = ch;
		(*td.pos)++;

		pthread_mutex_unlock(td.mtx);
	}

	pthread_mutex_unlock(td.mtx);
	return NULL;
}

void* print(void* arg) {

	data td = *((data*) arg);

	while(1) {
	
		pthread_mutex_lock(td.mtx);

		if(*td.pos != SIZE) {
			pthread_cond_signal(td.cg);
			while(*td.pos < SIZE) {
				pthread_cond_wait(td.cp, td.mtx);
			}
		}

		printf("%s\n", td.buffer);

		memset(td.buffer, 0, SIZE * sizeof(char));
		*td.pos = 0;
		(*td.count)--;
		pthread_cond_broadcast(td.cg);

		if(*td.count == 0)
			break;
		
		pthread_mutex_unlock(td.mtx);
	}
	
	pthread_mutex_unlock(td.mtx);
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

	int* pos = malloc(sizeof(int));
	*pos = 0;
	int count = m;
	char* buf = malloc(sizeof(char) * (SIZE + 1));
	memset(buf, 0, (SIZE + 1) * sizeof(char));
	srand(time(NULL));

	data* args = malloc(sizeof(data) * (n + 1));

	pthread_cond_t* c1 = malloc(sizeof(pthread_cond_t));
	pthread_cond_init(c1, NULL);
	
	pthread_cond_t* c2 = malloc(sizeof(pthread_cond_t));
	pthread_cond_init(c2, NULL);

	pthread_mutex_t* mtx = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(mtx, NULL);

	for(int i = 0; i < n; i++) {
		args[i].pos = pos;
		args[i].count = &count;
		args[i].buffer = buf;

		args[i].cg = c1;
		args[i].cp = c2;
		args[i].mtx = mtx;
	
		pthread_create(&tid[i], NULL, generate, &args[i]);
	}

	args[n].pos = pos;
	args[n].count = &count;
	args[n].buffer = buf;

	args[n].cg = c1;
	args[n].cp = c2;
	args[n].mtx = mtx;

	pthread_create(&tid[n], NULL, print, &args[n]);
	
	for(int i = 0; i < n + 1; i++) 
		pthread_join(tid[i], NULL);

	pthread_cond_destroy(c1);
	pthread_cond_destroy(c2);
	pthread_mutex_destroy(mtx);

	free(args);
	free(c1);
	free(c2);
	free(mtx);
	free(pos);
	free(buf);
	
	return 0;
}
