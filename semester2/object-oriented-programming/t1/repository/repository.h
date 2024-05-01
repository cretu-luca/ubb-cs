#pragma once
#include <vector>
#include <algorithm>
#include "../domain/task.h"

using namespace std;

class Repository{
private:
    vector<Task> tasks;

public:

    Repository();

    void add(Task task);

    vector<Task> getAll() { return this->tasks; }

    /*
    int getIndex(Task task) {
        auto it = find(this->tasks.begin(), this->tasks.end(), task);

        if(it != this->tasks.end())
            return distance(this->tasks.begin(), it);
        else
            return -1;
    }*/

    bool isUnique(Task task);

};