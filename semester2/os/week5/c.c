#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>

int main(int argc, char *argv[]){
	struct timeval start, stop;
	gettimeofday(&start, NULL);
	gettimeofday(&stop, NULL);
	sleep(2);
	printf("Time = %lf millis\n", ((stop.tv_sec - start.tv_sec) * 1000.0 + 
		(stop.tv_usec - start.tv_usec) / 1000.0));
	
	return 0;
}
