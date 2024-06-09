#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

// Write a C program that takes two numbers, N and M, as arguments from the command line. The program creates N "generator" threads that generate random lowercase letters and append them to a string with 128 positions. The program will create an additional "printer" thread that that waits until all the positions of the string are filled, at which point it prints the string and clears it. The N "generator" threads must generate a total of M such strings and the "printer" thread prints each one as soon as it gets to length 128.

typedef struct {

	int id;
	int maxSize;
	int* repeats;
	int* pos;
	char* buf;
	pthread_mutex_t* m;
	pthread_cond_t* c;
} data;

void* gen(void* arg) {
	data* d = (data*) arg;
		
	while(1) {
	
		pthread_mutex_lock(d->m);
		if(*(d->repeats) == 0) {
			pthread_mutex_unlock(d->m);
			break;
		}
		
		while(*d->pos == d->maxSize) {
			pthread_cond_broadcast(d->c);
			pthread_cond_wait(d->c, d->m);
		}

		char c = rand() % 26 + 'a';
		d->buf[*d->pos] = c;
		(*(d->pos))++;

		if(*d->pos == d->maxSize) {
			pthread_cond_signal(d->c);
		}
	
		pthread_mutex_unlock(d->m);
	}
	
	return NULL;
}

void* printer(void* arg) {
	
	data* d = (data*) arg;

	while(1) {
	
		pthread_mutex_lock(d->m);
		if(*(d->repeats) == 0) {

			pthread_cond_signal(d->c);
			pthread_mutex_unlock(d->m);
			break;
		}

		while(*d->pos < d->maxSize) {
			pthread_cond_broadcast(d->c);
			pthread_cond_wait(d->c, d->m);
		}

		printf("%s\n", d->buf);

		memset(d->buf, 0, sizeof(char) * d->maxSize);
		*d->pos = 0;
		(*d->repeats)--;
		
		pthread_cond_signal(d->c);
		pthread_mutex_unlock(d->m);
	}

	return NULL;
} 

int main(int argc, char* argv[]) {
	
	int n = atoi(argv[1]);
	int m = atoi(argv[2]);
	int pos = 0;
	
	pthread_mutex_t mtx;
	pthread_cond_t cond;

	pthread_mutex_init(&mtx, NULL);
	pthread_cond_init(&cond, NULL);

	char* buf = malloc(sizeof(char) * 128);
	memset(buf, 0, sizeof(char) * 128);

	pthread_t th[n + 1];
	data args[n + 1];
	for(int i = 0; i < n; i++) { 
	
		args[i].id = i;
		args[i].maxSize = 128;
		args[i].m = &mtx;
		args[i].c = &cond;
		args[i].repeats = &m;
		args[i].pos = &pos;
		args[i].buf = buf;

		if(pthread_create(&th[i], NULL,  gen, &args[i]) != 0) {
			perror("thread failed to start");
			exit(1);
		}
	}

	args[n].id = n;
	args[n].maxSize = 128;
	args[n].m = &mtx;
	args[n].c = &cond;
	args[n].repeats = &m;
	args[n].pos = &pos;
	args[n].buf = buf;

	if(pthread_create(&th[n], NULL, printer, &args[n]) != 0) { 
		perror("thread failed to start");
		exit(1);
	}

	for(int i = 0; i < n + 1; i++) {
		pthread_join(th[i], NULL);
	}

	free(buf);
	pthread_cond_destroy(&cond);
	pthread_mutex_destroy(&mtx);
}
