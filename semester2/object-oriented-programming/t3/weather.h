//
// Created by lucac on 5/28/2024.
//

#ifndef WEATHER_H
#define WEATHER_H

#include <iostream>
#include <string>
using namespace std;

class Weather {

private:
    int start;
    int end;
    int prob;
    int temperature;
    string description;

public:

    Weather(int start, int end, int temperature, int prob, string description) :
        start(start), end(end), prob(prob), description(description), temperature(temperature) {}

    int getStart() { return this->start; }
    int getEnd() { return this->end; }
    int getProb() { return this->prob; }
    int getTemperature() { return this->temperature; }
    string getDescription() { return this->description; }

};

#endif //WEATHER_H
