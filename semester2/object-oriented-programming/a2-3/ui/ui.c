#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ui.h"

UserInterface * createUserInterface(){
    UserInterface * userInterface = (UserInterface *) malloc(sizeof(UserInterface));
    userInterface->controller = createController();

    return userInterface;
}

void destroyUserInterface(UserInterface * userInterface){
    destroyController(userInterface->controller);
    free(userInterface);
}

int readInteger(){
    char input[50];
    scanf("%s", input);
    int result = 0;

    for(int i = 0; i < strlen(input); i++){
        if(!(input[i] >= '0' && input[i] <= '9'))
            return -1;

        result = result * 10 + (input[i] - '0');
    }
    return result;
}

void displayMenu(){
    printf("1. Add material\n"
                  "2. Delete material\n"
                  "3. Update material\n"
                  "4. Display materials\n"
                  "5. Expired materials\n"
                  "6. Display materials in short supply\n"
                  "7. Undo\n"
                  "8. Redo\n"
                  "0. Exit\n\n");
}

void readUserInput(Material * materialPointer){
    int invalidInput = 1;
    printf("Material:");
    scanf("%s", materialPointer->name);

    printf("Supplier:");
    scanf("%s", materialPointer->supplier);
    while(invalidInput) {
        printf("Quantity:");
        materialPointer->quantity = readInteger();

        if(materialPointer->quantity == -1)
            printf("Invalid input!\n");
        else
            invalidInput = 0;
    }
    invalidInput = 1;
    printf("Date:\n");
    while(invalidInput) {
        printf("Day:");
        materialPointer->expirationDate.day = readInteger();

        if (materialPointer->expirationDate.day == -1)
            printf("Invalid input!\n");
        else
            invalidInput = 0;
    }
    invalidInput = 1;
    while(invalidInput) {
        printf("Month:");
        materialPointer->expirationDate.month = readInteger();

        if(materialPointer->expirationDate.month == -1)
            printf("Invalid input!\n");
        else
            invalidInput = 0;
    }
    invalidInput = 1;
    while(invalidInput) {
        printf("Year:");
        materialPointer->expirationDate.year = readInteger();

        if(materialPointer->expirationDate.year == -1)
            printf("Invalid input!\n");
        else
            invalidInput = 0;
    }
}

void addMaterialUI(UserInterface * userInterface){
    Material * materialPointer = malloc(sizeof(Material));
    materialPointer->name = malloc(sizeof(char) * 100);
    materialPointer->supplier = malloc(sizeof(char) * 100);

    readUserInput(materialPointer);

    saveCurrentStateController(userInterface->controller, getUndoStack(getRepository(userInterface->controller)));
    addMaterialController(userInterface->controller, materialPointer);
}

void updateMaterialUI(UserInterface * userInterface){
    Material * materialPointer = malloc(sizeof(Material));
    materialPointer->name = malloc(sizeof(char) * 100);
    materialPointer->supplier = malloc(sizeof(char) * 100);

    readUserInput(materialPointer);
    int position = positionInArray(userInterface->controller, materialPointer);
    if(position != -1) {
        saveCurrentStateController(userInterface->controller, getUndoStack(getRepository(userInterface->controller)));
        free(materialPointer->name);
        free(materialPointer->supplier);
        free(materialPointer);
        materialPointer = (Material *)getArrayController(userInterface->controller)->elements[position];

        readUserInput(materialPointer);
    }
    else {
        free(materialPointer->name);
        free(materialPointer->supplier);
        free(materialPointer);
        printf("No such element was found\n");
    }
}

void deleteMaterialUI(UserInterface * userInterface){
    Material * material = malloc(sizeof(Material));
    material->name = malloc(sizeof(char) * 50);
    material->supplier = malloc(sizeof(char) * 50);

    readUserInput(material);

    int index = positionInArray(userInterface->controller, material);
    if(index == -1)
        printf("No such element was found\n");
    else {
        saveCurrentStateController(userInterface->controller, getUndoStack(getRepository(userInterface->controller)));
        deleteMaterialController(userInterface->controller, material);
    }

    free(material->name);
    free(material->supplier);
    free(material);
}

void displayMaterial(Material * material){
    printf("Material: %s\n", material->name);
    printf("Supplier: %s\n", material->supplier);
    printf("Quantity: %d\n", material->quantity);
    printf("Expiration date: %d/%d/%d\n\n", material->expirationDate.day,
           material->expirationDate.month, material->expirationDate.year);
}

void displayMaterials(UserInterface * userInterface){
    DynamicalArray *array = getArrayController(userInterface->controller);
    for(int i = 0; i < array->size; i++) {
        printf("%d.\n", i + 1);
        displayMaterial((Material *)array->elements[i]);
    }
}

void displayExpiredMaterials(UserInterface * userInterface){
    printf("Filter by:\n"
                  "1. Materials validity, containing given string\n"
                  "2. Materials that expire in a given year\n");
    int option, invalidInput = 1;
    while(invalidInput){
        option = readInteger();
        if(option == -1 || option < 1 || option > 2)
            printf("Invalid input!\n");
        else
            invalidInput = 0;
    }
    if(option == 1) {
        char name[50];
        Date currentDate = createDate(2024, 3, 10);
        DynamicalArray *array = getArrayController(userInterface->controller);

        printf("Name:");
        fgets(name, 49, stdin);
        fgets(name, 49, stdin);

        if (strcmp(name, "\n") == 0) {
            for (int i = 0; i < array->size; i++)
                if (compareDates((*(Material *) array->elements[i]).expirationDate, currentDate) == 1)
                    displayMaterial((Material *) array->elements[i]);
        } else {
            for (int i = 0; i < array->size; i++)
                if (strstr(name, (*(Material *) array->elements[i]).name)) {
                    if (compareDates((*(Material *) array->elements[i]).expirationDate, currentDate) == 1)
                        displayMaterial((Material *) array->elements[i]);
                }
        }
    }
    else {
        int year;
        invalidInput = 1;
        printf("Year:\n");
        while(invalidInput){
            year = readInteger();
            if(year < 0)
                printf("Invalid input!\n");
            else
                invalidInput = 0;
        }
        DynamicalArray *array = getArrayController(userInterface->controller);
        for(int i = 0; i < array->size; i++)
            if(((Material *)array->elements[i])->expirationDate.year == year)
                displayMaterial((Material *) array->elements[i]);
    }
}

void displayMaterialsInShortSupply(UserInterface * userInterface){
    printf("Choose the type of sorting\n"
                  "1. Ascending by quantity\n"
                  "2. Descending by quantity\n");

    int invalidInput = 1, sortingOption;
    while(invalidInput){
        sortingOption = readInteger();
        if(sortingOption < 1 || sortingOption > 2)
            printf("Invalid input!\n");
        else
            invalidInput = 0;
    }

    char supplier[50];
    int quantity;

    printf("Enter supplier:");
    scanf("%s", supplier);

    printf("Enter maximum quantity:");
    scanf("%d", &quantity);

    DynamicalArray * array = getArrayController(userInterface->controller);

    int indices[100];
    for(int i = 0; i < array->size; i++)
        indices[i] = i;

    if(sortingOption == 1) {
        for(int i = 0; i < array->size - 1; i++) {
            for(int j = i + 1; j < array->size; j++) {
                if(((Material *)array->elements[indices[i]])->quantity > ((Material *)array->elements[indices[j]])->quantity) {
                    int t = indices[i];
                    indices[i] = indices[j];
                    indices[j] = t;
                }
            }
        }
    }
    else
        for(int i = 0; i < array->size - 1; i++)
            for(int j = i + 1; j < array->size; j++)
                if(((Material *)array->elements[indices[i]])->quantity < ((Material *)array->elements[indices[j]])->quantity){
                    int t = indices[i];
                    indices[i] = indices[j];
                    indices[j] = t;
                }

    for(int i = 0; i < array->size; i++)
        if(strcmp((*(Material *)array->elements[indices[i]]).supplier, supplier) == 0 && (*(Material *)array->elements[indices[i]]).quantity < quantity)
            displayMaterial((Material *) array->elements[indices[i]]);
}

void undoUI(UserInterface * userInterface){
    if(getArraySize(getUndoStack(getRepository(userInterface->controller))) == 0) {
        printf("No more undo's!\n");
        return;
    }
    else
        undo(userInterface->controller);
}

void redoUI(UserInterface * userInterface){
    if(getArraySize(getRedoStack(getRepository(userInterface->controller))) == 0) {
        printf("No more redo's!\n");
        return;
    }
    else
        redo(userInterface->controller);
}

void mainMenu(UserInterface * userInterface) {
    int option, running = 1;
    functionality func[] = {addMaterialUI, deleteMaterialUI, updateMaterialUI,
                            displayMaterials, displayExpiredMaterials, displayMaterialsInShortSupply,
                            undoUI, redoUI};

    generateMaterials(userInterface->controller, 20);
    while (running) {
        displayMenu();

        int invalidInput = 1;
        while (invalidInput) {
            printf("Enter option: \n>");
            option = readInteger();

            if(option == -1 || !(option >= 0 && option <= 8))
                printf("Invalid input!");
            else
                invalidInput = 0;
        }

        if (option == 0)
            running = 0;
        else
            func[option - 1](userInterface);

    }
}