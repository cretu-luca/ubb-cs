#pragma once
#include "../controller/controller.h"
#include <iostream>

class UserInterface {
private:
    Controller controller;

public:

    void printMenu();
    void getOption();
    void addUI();
    void displayAll();
    void displayByDate();
};