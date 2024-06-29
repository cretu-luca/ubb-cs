//
// Created by lucac on 6/28/2024.
//

#ifndef GUI_H
#define GUI_H

#include <QObject>
#include "courierwindow.h"
#include "companywindow.h"
#include "mapwindow.h"
#include "service.h"

class GUI {
public:

    Service* service;
    vector<courierWindow*> courierWindows;
    companyWindow* THEcompanyWindow;
    mapWindow* map;

    GUI() {

        this->service = new Service();
        this->THEcompanyWindow = new companyWindow(nullptr, service);
        this->map = new mapWindow(nullptr, service);

        // this->service->repository->addObserver(THEcompanyWindow);
        this->service->addObserver(THEcompanyWindow);
        this->service->addObserver(map);

        createWindows();
        displayWindows();
    }

    void createWindows() {
        vector<Courier*> allCouriers = service->getAllCouriers();

        for(auto courier: allCouriers) {

            auto window = new courierWindow(nullptr, service, courier);
            window->setWindowTitle(QString::fromStdString(courier->name));
            this->courierWindows.push_back(window);
            // this->service->repository->addObserver(window);
            this->service->addObserver(window);
        }
    }

    void displayWindows() {
        for(auto window: courierWindows) {
            window->show();
        }

        THEcompanyWindow->show();
        map->show();
    }

};

#endif //GUI_H
