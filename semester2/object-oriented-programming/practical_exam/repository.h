//
// Created by lucac on 6/28/2024.
//

#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <vector>
#include "domain.h"
#include "observer.h"
#include <fstream>
#include <sstream>

class Repository {
public:
    vector<Package*> packages;
    vector<Courier*> couriers;

    Repository() {

        loadPackages();
        loadCouriers();
    }

    vector<Package*> getPackages() {
        return this->packages;
    }

    vector<Courier*> getCouriers() {
        return this->couriers;
    }

    void loadPackages() {
        ifstream fin(R"(C:\Users\lucac\CLionProjects\practical_exam\packages.txt)");
        string line, recipient, street, number, x, y, status;
        char sep = ';';

        while(getline(fin, line)) {
            stringstream ss(line);

            getline(ss, recipient, sep);
            getline(ss, street, sep);
            getline(ss, number, sep);
            getline(ss, x, sep);
            getline(ss, y, sep);
            getline(ss, status, sep);

            auto package = new Package(recipient, street, stoi(number), stoi(x), stoi(y), stoi(status));
            this->packages.push_back(package);
        }
    }

    void writePackages() {
        ofstream fout(R"(C:\Users\lucac\CLionProjects\practical_exam\packages.txt)");

        for(auto package: packages) {
            fout << package->recipient + ";" + package->street + ";" + std::to_string(package->number) + ";" +
                std::to_string(package->xLocation) + ";" + std::to_string(package->yLocation) + ";" + to_string(package->status) + "\n";
        }
    }

    void loadCouriers() {
        ifstream fin(R"(C:\Users\lucac\CLionProjects\practical_exam\couriers.txt)");
        string line, name, streets, x, y, radius;
        char sep = ';';

        while(getline(fin, line)) {
            stringstream ss(line);

            getline(ss, name, sep);
            getline(ss, streets, sep);
            getline(ss, x, sep);
            getline(ss, y, sep);
            getline(ss, radius, sep);

            auto courier = new Courier(name, streets, stoi(x), stoi(y), stoi(radius));
            this->couriers.push_back(courier);
        }
    }

    void writeCouriers() {
        ofstream fout(R"(C:\Users\lucac\CLionProjects\practical_exam\couriers.txt)");

        for(auto courier: couriers) {
            fout << courier->name + ";" + courier->streets + ";" + std::to_string(courier->xCenter) + ";" +
                std::to_string(courier->yCenter) + ";" + std::to_string(courier->radius) + "\n";
        }
    }

    void addPackageRepo(Package* package) {
        this->packages.push_back(package);
        writeCouriers();
        writePackages();
    }
};

#endif //REPOSITORY_H
