#pragma once
#include "../controller/controller.h"

typedef struct {
    Controller * controller;
} UserInterface;

UserInterface * createUserInterface();
void destroyUserInterface(UserInterface * userInterface);
void displayMenu();
void readUserInput(Material * materialPointer);
void addMaterialUI(UserInterface * userInterface);
void updateMaterialUI(UserInterface * userInterface);
void deleteMaterialUI(UserInterface * userInterface);
void displayExpiredMaterials(UserInterface * userInterface);
void mainMenu(UserInterface * userInterface);
void displayMaterial(Material * material);
void displayMaterials(UserInterface * userInterface);
void undoUI(UserInterface * userInterface);
void redoUI(UserInterface * userInterface);
typedef void (* functionality)(UserInterface * userInterface);