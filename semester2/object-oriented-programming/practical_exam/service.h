//
// Created by lucac on 6/28/2024.
//

#ifndef SERVICE_H
#define SERVICE_H
#include "repository.h"
#include <set>
#include <string>

class Service: public Subject {
public:
    Repository* repository;

    Service() {
        this->repository = new Repository;
    }

    vector<Package*> getAllPackages() {
        return this->repository->getPackages();
    }

    vector<Courier*> getAllCouriers() {
        return this->repository->getCouriers();
    }

    void addPackage(Package* package) {
        this->repository->addPackageRepo(package);
        notify();
    }

    set<string> getStreets() {
        set<string> streets;

        for(auto package: getAllPackages()) {
            streets.insert(package->street);
        }

        return streets;
    }

    vector<Package*> getPackagesByStreet(string street) {
        vector<Package*> packages;

        for(auto package: getAllPackages()) {
            if(package->street == street) {
                packages.push_back(package);
            }
        }

        return packages;
    }

    void changePackageStatus(string packageString) {
        for(auto package: getAllPackages()) {
            if(package->recipient + " " + package->street + " " + std::to_string(package->number) + " " +
                std::to_string(package->xLocation) + " " + to_string(package->status) == packageString) {
                package->status = true;
            }
        }

        notify();
        repository->writeCouriers();
        repository->writePackages();
    }

    bool isInCircle(Package* package, Courier* courier) {
        return false;
    }
};


#endif //SERVICE_H
