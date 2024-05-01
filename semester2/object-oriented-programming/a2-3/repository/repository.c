#include <stdlib.h>
#include <string.h>
#include "repository.h"

Repository *createRepository(){
    Repository *repository = (Repository *) malloc(sizeof(Repository));
    repository->array = createArray(10);
    repository->undoStack = createArray(10);
    repository->redoStack = createArray(10);

    return repository;
}


void destroyRepository(Repository * repository){
    destroyArray(repository->array);
    destroyStack(repository->undoStack);
    destroyStack(repository->redoStack);
    free(repository);
}

DynamicalArray *getArray(Repository * repository){
    return repository->array;
}

void add(Repository * repository, void *element) {
    if (getRepoArraySize(repository) + 1 == getRepoArrayCapacity(repository)) {
        resize(repository->array);
    }
    repository->array->elements[getRepoArraySize(repository)] = element;
    repository->array->size += 1;
}

DynamicalArray *cloneArray(DynamicalArray *array) {
    DynamicalArray *newArray = createArray(array->totalCapacity);
    for (int i = 0; i < array->size; i++) {
        Material *original = (Material *)array->elements[i];
        Material *copy = malloc(sizeof(Material));

        copy->name = strdup(original->name);
        copy->supplier = strdup(original->supplier);
        copy->quantity = original->quantity;
        copy->expirationDate.year = original->expirationDate.year;
        copy->expirationDate.month = original->expirationDate.month;
        copy->expirationDate.day = original->expirationDate.day;

        newArray->elements[i] = copy;
    }
    newArray->size = array->size;
    return newArray;
}

void saveCurrentState(Repository *repository, DynamicalArray *targetStack){
    DynamicalArray *arrayCopy = cloneArray(repository->array);
    if (targetStack->size + 1 == targetStack->totalCapacity) {
        targetStack->totalCapacity *= 2;
        targetStack->elements = realloc(targetStack->elements, sizeof(void *) * targetStack->totalCapacity);
    }
    targetStack->elements[targetStack->size++] = arrayCopy;
}

int getRepoArraySize(Repository *repository){
    return getArraySize(repository->array);
}

int getRepoArrayCapacity(Repository *repository){
    return getArrayCapacity(repository->array);
}

DynamicalArray *getUndoStack(Repository *repository){
    return repository->undoStack;
}

DynamicalArray *getRedoStack(Repository *repository){
    return repository->redoStack;
}

void assignNewState(Repository *repository, DynamicalArray *arrayToAssign){
    repository->array = arrayToAssign;
}