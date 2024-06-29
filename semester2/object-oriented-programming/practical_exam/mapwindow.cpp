//
// Created by lucac on 6/28/2024.
//
#include "mapwindow.h"
#include "ui_mapWindow.h"
#include <QPainter>
#include <iostream>

mapWindow::mapWindow(QWidget *parent) :
    QWidget(parent), ui(new Ui::mapWindow) {
    ui->setupUi(this);
}

mapWindow::mapWindow(QWidget* parent, Service* service):
    QWidget(parent), ui(new Ui::mapWindow), service(service) {
    ui->setupUi(this);
}

void mapWindow::paintEvent(QPaintEvent*) {
    QPainter painter(this);

    for(auto package: service->getAllPackages()) {
        if(package->status == false) {
            painter.drawEllipse(package->xLocation * 10, package->yLocation * 10, 20, 20);
        }
    }
}

void mapWindow::update() {
    repaint();
}

mapWindow::~mapWindow() {
    delete ui;
}
