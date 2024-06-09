#include <stdio.h>
#include <pthread.h>

struct arg_t {
	char* name;
	int count;
};

void* f(void* arg) {
	
	struct arg_t* s = (struct arg_t*) arg; 
	for(int i = 0; i < s->count; i++) {
		sleep(1);
		printf("%s\n", s->name); 
	}

	return NULL;
}

int main(int argc, char* argv[]) {
	pthread_t ta, tb;
	struct arg_t aa, bb;

	aa.name = "salut";
	aa.count = 5;
	bb.name = "pa";
	bb.count = 3;

	pthread_create(&ta, NULL, f, &aa);
	pthread_create(&tb, NULL, f, &bb);

	pthread_join(ta, NULL);
	pthread_join(tb, NULL);
}
