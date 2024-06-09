#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

typedef struct {

	char* buf;
    int* fr;
    pthread_mutex_t* mutex;

} data;

void* f(void* arg) {
	
	data* d = (data*) arg;

	for(int i = 0; i < strlen(d->buf); i++) {

		char c = d->buf[i];

		if('a' <= c && c <= 'z') {
			pthread_mutex_lock(&d->mutex[(int) c - 'a']);
			d->fr[(int) c - 'a']++;
			pthread_mutex_unlock(&d->mutex[(int) c - 'a']);
		}
	}

	return NULL;
}

int main(int argc, char* argv[]) {

	pthread_t td[argc];
    data arg[argc];

    pthread_mutex_t* mutex = malloc(sizeof(pthread_mutex_t) * 26);
	for(int i = 0; i < 26; i++) {
    	pthread_mutex_init(&mutex[i], NULL);
	}

    int* fr = malloc(sizeof(int) * 26);

    for(int i = 1; i < argc; i++) {

		arg[i].buf = argv[i];
        arg[i].fr = fr;
        arg[i].mutex = mutex;
        pthread_create(&td[i], NULL, f, &arg[i]);
	}

    for(int i = 1; i < argc; i++) {
		pthread_join(td[i], NULL);
    }

	for(int i = 0; i < 26; i++) {
		if(fr[i] > 0) {
			printf("%c appears %d times\n", i + 'a', fr[i]);
		}
	}

	free(fr);
}
