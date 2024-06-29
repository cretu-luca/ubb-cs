//
// Created by lucac on 5/28/2024.
//

#ifndef SERVICE_H
#define SERVICE_H
#include "repository.h"

class Service {

private:

    Repository repository;

public:

    Service() : repository() {}
    vector<Weather> getAllWeather() { return repository.getAll(); }

    vector<Weather> getByProb(int probability) {

        vector<Weather> all = this->getAllWeather();
        vector<Weather> filtered;

        for(auto elem: all) {

            if(elem.getProb() < probability)
                filtered.emplace_back(elem);
        }

        return filtered;
    }

    vector<Weather> getByDesc(string description, int startTime) {
        vector<Weather> all = this->getAllWeather();
        vector<Weather> filtered;

        for(auto elem: all) {

            if(elem.getEnd() > startTime && elem.getDescription() == description) {
                filtered.emplace_back(elem);
            }
        }

        return filtered;
    }
};

#endif //SERVICE_H
