#include "task.h"

Task::Task(string description, int duration, Date deadline) {
    this->deadline = deadline;
    this->description = description;
    this->duration = duration;
}

bool Task::operator==(Task other) {
    this->deadline = other.deadline;
    this->duration = other.duration;
    this->description = other.description;
}