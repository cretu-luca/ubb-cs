//
// Created by lucac on 6/28/2024.
//

#ifndef DOMAIN_H
#define DOMAIN_H

#include <string>
using namespace std;

class Courier {
public:
    string name;
    string streets;
    int xCenter;
    int yCenter;
    int radius;

    Courier(string name, string streets, int x, int y, int radius) {
        this->name = name;
        this->streets = streets;
        this->xCenter = x;
        this->yCenter = y;
        this->radius = radius;
    }
};

class Package {
public:
    string recipient;
    string street;
    int number;
    int xLocation;
    int yLocation;
    bool status;

    Package(string recipient, string street, int number, int x, int y, bool status) {
        this->recipient = recipient;
        this->street = street;
        this->number = number;
        this->xLocation = x;
        this->yLocation = y;
        this->status = status;
    }
};

#endif //DOMAIN_H
