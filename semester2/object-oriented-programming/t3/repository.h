//
// Created by lucac on 5/28/2024.
//

#ifndef REPOSITORY_H
#define REPOSITORY_H
#include "weather.h"
#include <sstream>
#include <vector>
#include <fstream>

class Repository {

private:

    vector<Weather> forecast;

public:

    Repository() {

        ifstream fin(R"(C:\Users\lucac\CLionProjects\test3\forecast.txt)");
        string start, end, prob, temperature, description, line;
        char sep = ';';

        while(getline(fin, line)) {

            stringstream ss(line);

            getline(ss, start, sep);
            getline(ss, end, sep);
            getline(ss, temperature, sep);
            getline(ss, prob, sep);
            getline(ss, description, sep);

            forecast.emplace_back(Weather(stoi(start), stoi(end), stoi(temperature), stoi(prob), description));
        }
    }

    vector<Weather> getAll() { return this->forecast; }
};

#endif //REPOSITORY_H
