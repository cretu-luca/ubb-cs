#include <stdlib.h>
#include <string.h>
#include "../controller/controller.h"

Controller * createController(){
    Controller *controller = (Controller *) malloc(sizeof(Controller));
    controller->repository = createRepository();

    return controller;
}

void destroyController(Controller * controller){
    destroyRepository(controller->repository);
    free(controller);
}

DynamicalArray * getArrayController(Controller * controller){
    return getArray(controller->repository);
}

void addMaterialController(Controller * controller, Material * material){
    int newQuantity = material->quantity, position = positionInArray(controller, material), isNewMaterial = 1;
    DynamicalArray *array = getArrayController(controller);

    if(position != -1)
        material = (Material *)&array->elements[position],
                isNewMaterial = 0;

    if(!isNewMaterial) {
        material->quantity += newQuantity;
    }
    else
        add(controller->repository, material);

}

void deleteMaterialController(Controller * controller, Material * material){
    int index = positionInArray(controller, material);
    DynamicalArray * array = getArrayController(controller);

    for (int i = index; i < array->size - 1; i++)
        array->elements[i] = array->elements[i + 1];

    free(((Material *)array->elements[getArraySize(array) - 1])->name);
    free(((Material *)array->elements[getArraySize(array) - 1])->supplier);
    free((Material *)array->elements[getArraySize(array) - 1]);

    array->size -= 1;
}

int positionInArray(Controller * controller, Material * material){
    DynamicalArray * array = getArray(controller->repository);

    for(int i = 0; i < array->size; i++)
        if(strcmp((*(Material *)array->elements[i]).name, material->name) == 0 &&
           strcmp((*(Material *)array->elements[i]).supplier, material->supplier) == 0 &&
                (*(Material *)array->elements[i]).expirationDate.year == material->expirationDate.year &&
                (*(Material *)array->elements[i]).expirationDate.month == material->expirationDate.month &&
                (*(Material *)array->elements[i]).expirationDate.day == material->expirationDate.day)
            return i;

    return -1;
}


int compareDates(Date date1, Date date2){
    if(date1.year > date2.year)
        return -1;
    else
    if(date1.year == date2.year && date1.month > date2.month)
        return -1;
    else
    if(date1.year == date2.year && date1.month == date2.month && date1.day > date2.day)
        return -1;
    else
    if(date1.year == date2.year && date1.month == date2.month && date1.day == date2.day)
        return 0;

    return 1;
}

void generateMaterials(Controller * controller, int numberOfMaterials){
    int nameChoice, supplierChoice, year, month, day;

    char materialsNames[100][100] = {"Flour", "Sugars", "Eggs", "Chocolate",
                                     "Powder", "Nuts", "Vanilla",
                                     "Milk", "Water", "Salt", "Fruits",
                                     "Vegetables", "Spices", "Cheese",
                                     "Cream", "Butter", "Oil"};

    char suppliers[100][100] = {"SBS", "NBS","WBS", "EBS","CBS"};

    for(int i = 0; i < numberOfMaterials; i++){
        Material  * randomMaterial = malloc(sizeof(Material));

        randomMaterial->name = (char *) malloc(25);
        randomMaterial->supplier = (char *) malloc(25);

        nameChoice = rand() % 17;
        strcpy(randomMaterial->name, materialsNames[nameChoice]);
        supplierChoice = rand() % 5;
        strcpy(randomMaterial->supplier, suppliers[supplierChoice]);
        randomMaterial->quantity = rand() % 100;
        year = 2020 + rand() % 10;
        month = 1 + rand() % 12;
        day = 1 + rand() % 29;
        randomMaterial->expirationDate = createDate(year, month, day);

        while(positionInArray(controller, randomMaterial) != -1) {
            nameChoice = rand() % 17;
            strcpy(randomMaterial->name, materialsNames[nameChoice]);
            supplierChoice = rand() % 5;
            strcpy(randomMaterial->supplier, suppliers[supplierChoice]);
            randomMaterial->quantity = rand() % 100;
            year = 2020 + rand() % 10;
            month = 1 + rand() % 12;
            day = 1 + rand() % 29;
            randomMaterial->expirationDate = createDate(year, month, day);
        }

        addMaterialController(controller, randomMaterial);
    }
}

void undo(Controller *controller){
    DynamicalArray *lastState = getUndoStack(controller->repository)->elements[getAndDecrementArraySize(getUndoStack(controller->repository))];
    saveCurrentState(controller->repository, getRedoStack(controller->repository));
    destroyArray(getArray(controller->repository));
    assignNewState(controller->repository, lastState);
}

void redo(Controller *controller){
    DynamicalArray *nextState = getRedoStack(controller->repository)->elements[getAndDecrementArraySize(getRedoStack(controller->repository))];
    saveCurrentState(controller->repository, getUndoStack(controller->repository));
    destroyArray(getArray(controller->repository));
    assignNewState(controller->repository, nextState);
}

void saveCurrentStateController(Controller *controller, DynamicalArray *targetStack){
    saveCurrentState(controller->repository, targetStack);
}

Repository *getRepository(Controller *controller){
    return controller->repository;
}