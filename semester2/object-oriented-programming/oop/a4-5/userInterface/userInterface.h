#pragma once
#include "../controller/controller.h"
#include <cstdlib>
#include <windows.h>

class UserInterface{
private:
    Controller* controller;
public:
    UserInterface();

    static void printAdministratorMainMenu();
    static void printUserMainMenu();

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