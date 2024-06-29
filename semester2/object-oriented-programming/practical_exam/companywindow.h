//
// Created by lucac on 6/28/2024.
//

#ifndef COMPANYWINDOW_H
#define COMPANYWINDOW_H

#include <QMainWindow>

#include "service.h"


QT_BEGIN_NAMESPACE
namespace Ui { class companyWindow; }
QT_END_NAMESPACE

class companyWindow : public QMainWindow, public Observer {
Q_OBJECT

public:
    explicit companyWindow(QWidget *parent = nullptr);

    companyWindow(QWidget* parent, Service* service);

    void handleAddPackageButton();
    void update() override;

    ~companyWindow() override;

private:
    Ui::companyWindow *ui;

    Service* service {};
};


#endif //COMPANYWINDOW_H
