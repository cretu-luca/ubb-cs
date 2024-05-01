#include "../repository/dynamicalArray.h"

typedef struct {
    DynamicalArray *array;
    DynamicalArray *undoStack, *redoStack;
} Repository;

Repository * createRepository();
DynamicalArray * getArray(Repository * repository);
DynamicalArray *getUndoStack(Repository *repository);
DynamicalArray *getRedoStack(Repository *repository);
void destroyRepository(Repository * repository);
void add(Repository * repository, void *element);
void saveCurrentState(Repository *repository, DynamicalArray *targetStack);
int getRepoArraySize(Repository *repository);
int getRepoArrayCapacity(Repository *repository);
void assignNewState(Repository *repository, DynamicalArray *arrayToAssign);