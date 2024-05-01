#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]){
    
    printf("program name: %s\n", argv[0]);
    int *ptr = (int *)malloc(sizeof(int) * 100);

    free(ptr);

    for(int i = 1; i < argc; i++)
	printf("argument %d: %s\n", i, argv[i]);
	
    return 0;
}
