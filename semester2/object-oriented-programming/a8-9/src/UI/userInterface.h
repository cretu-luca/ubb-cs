#pragma once
#include "../controller/controller.h"

class UserInterface{
private:
    Controller* controller;
public:
    UserInterface();

    static void printAdministratorMainMenu();
    static void printUserMainMenu();

    int getIntegerInput();

    void displayWatchlist();
    void printMenu();
    void displayMoviesByGenre();
    void chooseProfileMenu();
    void selectOptionAdministratorMenu();
    void selectOptionUserMenu();
    void addUI();
    void removeByNameUI();
    void updateMovieUI();
    void listMoviesUI();
    void getFile();
};