#include <stdlib.h>
#include "tests.h"

int main(){
    printf("Testing...\n");
    UserInterface * userInterface = createUserInterface();

    Material * materialPointer = malloc(sizeof(Material));
    materialPointer->name = malloc(sizeof(char) * 100);
    materialPointer->supplier = malloc(sizeof(char) * 100);

    materialPointer->name = strdup("material");
    materialPointer->supplier = strdup("NBS");
    materialPointer->quantity = 100;
    materialPointer->expirationDate.year = 2025;
    materialPointer->expirationDate.month = 2;
    materialPointer->expirationDate.day = 10;

    testAdd(userInterface, materialPointer);
    testDelete(userInterface, materialPointer);
    testGenerate(userInterface, 15);
    testIndexInArray(userInterface, materialPointer);
    testCompareDates();

    printf("All tests passed! :)\n");
}

void testAdd(UserInterface * userInterface, Material *material){
    addMaterialController(userInterface->controller, material);

    int found = 0;
    DynamicalArray * array = getArrayController(userInterface->controller);
    for(int i = 0; i < array->size; i++)
        if(strcmp((*(Material *)array->elements[i]).name, material->name) == 0 &&
           strcmp((*(Material *)array->elements[i]).supplier, material->supplier) == 0 &&
                (*(Material *)array->elements[i]).quantity == material->quantity &&
                (*(Material *)array->elements[i]).expirationDate.day == material->expirationDate.day &&
                (*(Material *)array->elements[i]).expirationDate.month == material->expirationDate.month &&
                (*(Material *)array->elements[i]).expirationDate.year == material->expirationDate.year)
            found = 1;

    assert(found == 1);
    printf("Adding works fine...\n");
}

void testDelete(UserInterface * userInterface, Material *material){
    deleteMaterialController(userInterface->controller, material);

    int found = 0;
    DynamicalArray * array = getArrayController(userInterface->controller);
    for(int i = 0; i < array->size; i++)
        if(strcmp((*(Material *)array->elements[i]).name, material->name) == 0 &&
           strcmp((*(Material *)array->elements[i]).supplier, material->supplier) == 0 &&
           (*(Material *)array->elements[i]).quantity == material->quantity &&
           (*(Material *)array->elements[i]).expirationDate.day == material->expirationDate.day &&
           (*(Material *)array->elements[i]).expirationDate.month == material->expirationDate.month &&
           (*(Material *)array->elements[i]).expirationDate.year == material->expirationDate.year)
            found = 1;

    assert(found == 0);
    printf("Deleting works fine...\n");
}

void testGenerate(UserInterface * userInterface, int numberOfMaterials){
    generateMaterials(userInterface->controller, numberOfMaterials);

    assert(userInterface->controller->repository->array->size == numberOfMaterials);
    printf("Generating works fine...\n");
}

void testIndexInArray(UserInterface * userInterface, Material *material){
    add(userInterface->controller->repository, material);
    int index = positionInArray(userInterface->controller, material);

    assert(index == 0);
    printf("Searching works fine...\n");
}

void testCompareDates() {
    Date date1 = createDate(2025, 10, 16);
    Date date2 = createDate(2024, 2, 24);
    Date date3 = createDate(2026, 5, 3);

    assert(compareDates(date1, date2) == -1);
    assert(compareDates(date2, date3) == 1);
    printf("Comparing works fine...\n");
}