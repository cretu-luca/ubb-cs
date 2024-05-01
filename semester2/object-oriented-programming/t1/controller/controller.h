#pragma once
#include "../repository/repository.h"
#include <iostream>

using namespace std;

class Controller {
private:
    Repository repository;

public:

    bool addTaskController(Task task) {
        // checks whether given task with same description exist
        // if that's the case, return false;
        // otherwise, add it and return true

        if (this->repository.isUnique(task) == false)
            return false;
        else {
            this->repository.add(task);
            return true;
        }
    }

    vector<Task> getALLController() {
        return this->repository.getAll();
    }

};