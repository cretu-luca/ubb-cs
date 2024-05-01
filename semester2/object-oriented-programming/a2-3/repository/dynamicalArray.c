#include <stdlib.h>
#include "../repository//dynamicalArray.h"

DynamicalArray * createArray(int totalCapacity){
    DynamicalArray * array = (DynamicalArray *) malloc(sizeof(DynamicalArray));
    array->elements = (void **) malloc(sizeof(void *) * totalCapacity);
    array->totalCapacity = totalCapacity;
    array->size = 0;

    return array;
}

void destroyArray(DynamicalArray *array){
    for(int i = 0; i < array->size; i++){
        free((*(Material *)array->elements[i]).name);
        free((*(Material *)array->elements[i]).supplier);
        free((Material *)array->elements[i]);
    }

    free(array->elements);
    free(array);
}


void destroyStack(DynamicalArray *stack){
    for(int i = 0; i < stack->size; i++) {
        destroyArray(stack->elements[i]);
    }
    free(stack->elements);
    free(stack);
}

void resize(DynamicalArray *array){
    array->totalCapacity *= 2;
    array->elements = realloc(array->elements,sizeof(void *) * array->totalCapacity);
}

int getArraySize(DynamicalArray *array){
    return array->size;
}

int getArrayCapacity(DynamicalArray *array){
    return array->totalCapacity;
}

int getAndDecrementArraySize(DynamicalArray *array){
    array->size--;
    return array->size;
}