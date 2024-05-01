#pragma once
#include "stdio.h"
#include "../domain/material.h"

typedef struct {
    void ** elements;
    int size, totalCapacity;
} DynamicalArray;
/*
 * creates a dynamically allocated array
 * param: totalCapacity - number of void * we reserve space for
 * return: returns the dynamically allocated array
*/
DynamicalArray * createArray(int totalCapacity);
/*
 * deallocates memory reserved for given array
 * param: DynamicalArray *Array - array to be destroyed (memory reserved for it will be deallocated)
 * return: None
*/
void destroyArray(DynamicalArray * array);
/*
 * deallocates memory reserved for given stack (dynamically array containing repositories)
 * param: DynamicalArray *stack - stack for which the memory we deallocate was allocated for
 * return: None
*/
void destroyStack(DynamicalArray * stack);

void resize(DynamicalArray *array);

int getArraySize(DynamicalArray *array);
int getArrayCapacity(DynamicalArray *array);
int getAndDecrementArraySize(DynamicalArray *array);