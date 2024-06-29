//
// Created by lucac on 6/28/2024.
//

#ifndef MAPWINDOW_H
#define MAPWINDOW_H

#include <QWidget>

#include "service.h"


QT_BEGIN_NAMESPACE
namespace Ui { class mapWindow; }
QT_END_NAMESPACE

class mapWindow : public QWidget, public Observer {
Q_OBJECT

public:
    explicit mapWindow(QWidget *parent = nullptr);
    mapWindow(QWidget* parent, Service* service);

    void paintEvent(QPaintEvent*) override;
    void update() override;

    ~mapWindow() override;

private:
    Ui::mapWindow *ui;

    Service* service {};
};


#endif //MAPWINDOW_H
