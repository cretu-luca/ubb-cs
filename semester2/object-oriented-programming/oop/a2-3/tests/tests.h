#pragma once
#include "../ui/ui.h"
#include <assert.h>
#include <string.h>

void testAdd(UserInterface * userInterface, Material *material);
void testDelete(UserInterface * userInterface, Material *material);
void testGenerate(UserInterface * userInterface, int numberOfMaterials);
void testIndexInArray(UserInterface * userInterface, Material *material);
void testCompareDates();
void testUndoRedo(UserInterface * userInterface, Material *material);