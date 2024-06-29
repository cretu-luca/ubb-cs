//
// Created by lucac on 6/28/2024.
//

#ifndef OBSERVER_H
#define OBSERVER_H

#include <vector>
using namespace std;

class Observer {
public:
    virtual void update() = 0;
    virtual ~Observer() = default;
};

class Subject {
public:

    vector<Observer*> observers;

    void addObserver(Observer* observer) {
        observers.push_back(observer);
    }

    void notify() {
        for(auto observer: observers) {
            observer->update();
        }
    }

};

#endif //OBSERVER_H
