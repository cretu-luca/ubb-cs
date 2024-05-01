#include <stdlib.h>
#include <stdio.h>

int main(){

	int *** m;

	m = (int***) malloc(sizeof(int **) * 9);
	for(int i = 0; i < 9; i++){
		m[i] = (int **)malloc(sizeof(int *) * 9);
		for(int j = 0; j < 9; j++)
			m[i][j] = (int *) malloc(sizeof(int) * 9);
	}


	for(int i = 0; i < 9; i++){
		for(int j = 0; j < 9; j++)
			free(m[i][j]);
		free(m[i]);
	}

	free(m);
	return 0;
}
