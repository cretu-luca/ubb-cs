//
// Created by lucac on 6/28/2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_companyWindow.h" resolved

#include "companywindow.h"
#include "ui_companyWindow.h"
#include <iostream>

companyWindow::companyWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::companyWindow) {
    ui->setupUi(this);
}

companyWindow::companyWindow(QWidget* parent, Service* service):
    QMainWindow(parent), ui(new Ui::companyWindow), service(service) {
    ui->setupUi(this);

    for(auto package: service->getAllPackages()) {

        auto item = new QListWidgetItem(QString::fromStdString(package->recipient + " " + package->street + " "
                + std::to_string(package->number) + " " + std::to_string(package->xLocation) + " " + to_string(package->status)));

        if(package->status == true)
            item->setBackground(Qt::green);

        ui->allPackagesList->addItem(item);
    }

    connect(ui->addPackageButton, &QPushButton::clicked, this, handleAddPackageButton);
}

void companyWindow::update() {
    ui->allPackagesList->clear();

    for(auto package: service->getAllPackages()) {

        auto item = new QListWidgetItem(QString::fromStdString(package->recipient + " " + package->street + " "
                + std::to_string(package->number) + " " + std::to_string(package->xLocation) + " " + to_string(package->status)));

        if(package->status == true)
            item->setBackground(Qt::green);

        ui->allPackagesList->addItem(item);
    }
}

void companyWindow::handleAddPackageButton() {
    string recipient = ui->recipientLineEdit->text().toStdString();
    string street = ui->streetLineEdit->text().toStdString();
    string number = ui->numberLineEdit->text().toStdString();
    int x = ui->xLineEdit->text().toInt();
    int y = ui->yLineEdit->text().toInt();

    ui->recipientLineEdit->clear();
    ui->streetLineEdit->clear();
    ui->numberLineEdit->clear();
    ui->xLineEdit->clear();
    ui->yLineEdit->clear();

    auto package = new Package(recipient, street, stoi(number), x, y, false);
    service->addPackage(package);
}

companyWindow::~companyWindow() {
    delete ui;
}
