#include "repository.h"

void Repository::add(Task task){
    this->tasks.push_back(task);
}

Repository::Repository() {

    Date date(1, 1, 1);

    this->tasks.push_back(Task("desc", 100, date));
    this->tasks.push_back(Task("desc2", 400, date));
    this->tasks.push_back(Task("desc3", 300, date));
    this->tasks.push_back(Task("desc4", 200, date));
}

bool Repository::isUnique(Task task) {
    for(int i = 0; i < this->tasks.size(); i++)
        if(this->tasks[i].getDescription() == task.getDescription())
            return false;

    return true;
}

/*
int Repository::getIndex(Task task) {
    auto it = find(this->tasks.begin(), this->tasks.end(), task);

    if(it != this->tasks.end())
        return distance(this->tasks.begin(), it);
    else
        return -1;
}*/