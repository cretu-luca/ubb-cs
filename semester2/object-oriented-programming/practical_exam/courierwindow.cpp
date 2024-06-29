#include "courierwindow.h"
#include "ui_courierWindow.h"
#include <iostream>
#include <cstring>
#include <set>

courierWindow::courierWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::courierWindow) {
    ui->setupUi(this);
}

courierWindow::courierWindow(QWidget* parent, Service* service, Courier* courier):
    QMainWindow(parent), ui(new Ui::courierWindow), service(service), courier(courier) {
    ui->setupUi(this);

    ui->streetsLabel->setText(QString::fromStdString("Streets: " + courier->streets));

    ui->zoneLabel->setText(QString::fromStdString("Zone: (" + std::to_string(courier->xCenter) + ", " +
        std::to_string(courier->yCenter) + "), r = " + std::to_string(courier->radius)));

    for(auto package: service->getAllPackages()) {
        if(package->status == false && (strstr(courier->streets.c_str(), package->street.c_str())) ||
            service->isInCircle(package, courier)) {
            ui->undeliveredList->addItem(QString::fromStdString(package->recipient + " " + package->street + " "
                + std::to_string(package->number) + " " + std::to_string(package->xLocation) + " " + to_string(package->status)));
        }
    }

    connect(ui->streetComboBox, &QComboBox::currentIndexChanged, this, handleComboBoxSelection);
    connect(ui->deliverButton, &QPushButton::clicked, this, handleDeliverButtonClick);
    connect(ui->undeliveredList, &QListWidget::itemClicked, this, handleListClick);

    populateComboBox();
}

void courierWindow::handleListClick(QListWidgetItem* item) {
    clickedItem = item;
}

void courierWindow::handleDeliverButtonClick() {
    service->changePackageStatus(clickedItem->text().toStdString());
}

void courierWindow::handleComboBoxSelection() {
    string street = ui->streetComboBox->currentText().toStdString();
    vector<Package*> packages;

    ui->undeliveredList->clear();

    if(street == "All") {
        packages = service->getAllPackages();
    } else {
        packages = service->getPackagesByStreet(street);
    }

    for(auto package: packages) {
        if(package->status == false && (strstr(courier->streets.c_str(), package->street.c_str())) ||
            service->isInCircle(package, courier)) {
            ui->undeliveredList->addItem(QString::fromStdString(package->recipient + " " + package->street + " "
                + std::to_string(package->number) + " " + std::to_string(package->xLocation) + " " + to_string(package->status)));
            }
    }
}

void courierWindow::populateComboBox() {
    set<string> streets = service->getStreets();

    ui->streetComboBox->clear();

    ui->streetComboBox->addItem("All");

    for(auto street: streets) {
        if(strstr(courier->streets.c_str(), street.c_str())) {
            ui->streetComboBox->addItem(QString::fromStdString(street));
        }
    }
}

void courierWindow::update() {
    ui->undeliveredList->clear();

    for(auto package: service->getAllPackages()) {
        if(package->status == false && (strstr(courier->streets.c_str(), package->street.c_str())) ||
            service->isInCircle(package, courier)) {
            ui->undeliveredList->addItem(QString::fromStdString(package->recipient + " " + package->street + " "
                + std::to_string(package->number) + " " + std::to_string(package->xLocation) + " " + to_string(package->status)));
            }
    }
}

courierWindow::~courierWindow() {
    delete ui;
}
