#pragma once
#include "../repository/dynamicalArray.h"
#include "../repository/repository.h"
#include "../domain/material.h"

typedef struct {
    Repository * repository;
} Controller;
/*
 * creates a struct of type Controller *, by allocating memory dynamically for it
 * param: None
 * return: Controller *
*/
Controller * createController();
/*
 * returns the array containing the materials
 * param: Controller *controller
 * return: DynamicalArray *
*/
DynamicalArray * getArrayController(Controller * controller);
/*
 * destroys the controller, by deallocating the memory for it
 * param: Controller *service (controller)
 * return: None
*/
void destroyController(Controller * service);
/*
 * adds a given Material* struct to the repository administered by the given controller
 * param: Controller *controller - accesses repository in order to perform certain operations on it
 * Material *material - material to be added
 * return: None
*/
void addMaterialController(Controller * controller, Material * material);
/*
 * deletes a given Material* struct from the repository administered by the given controller
 * param: Controller *controller - accesses repository in order to perform certain operations on it
 * param: Material *material - material to be deleted
 * return: None
*/
void deleteMaterialController(Controller * controller, Material * material);
/*
 * generates numberOfMaterials number of Material objects and adds them to repository administered by given controller
 * param: Controller *controller - accesses repository in order to perform certain operations on it
 * param: numberOfMaterials - number of materials to be generated
 * return: None
*/
void generateMaterials(Controller * controller, int numberOfMaterials);
/*
 * adds current Material* array to the target stack from the repository
 * param: Controller* controller - accesses repository in order to perform certain options on it
 * param: DynamicalArray *targetStack - field of repository in which current Material array is added (Undo/Redo Stack)
 * return: None
*/
void saveCurrentStateController(Controller * controller, DynamicalArray *targetStack);
/*
 * undo's the last operation that modified the Material repository (add/delete/update)
 * param: Controller *controller - accesses repository in order to perform certain options on it
 * return: None
*/
void undo(Controller * controller);
/*
 * redo's the last operation that was undone
 * param: Controller *controller - accesses repository in order to perform certain operation on it
 * return: None
*/
void redo(Controller * controller);
/*
 * compares to dates
 * param: Date date1, Date date2
 * return: int {-1: "date1 < date2", 0: "date1 == date2", 1: "date1 > date2"}
*/
int compareDates(Date date1, Date date2);
/*
 * looks for Material passed by address in the repository administered by given controller
 * param: Controller *controller - accesses the repository in order to perform certain operations on it
 * param: Material *material - Material pointer to which method looks for in controller->repository->array
 * return: int - position of Material in controller->repository->array, -1 - if there isn't any
*/
int positionInArray(Controller * controller, Material * material);

Repository *getRepository(Controller *controller);