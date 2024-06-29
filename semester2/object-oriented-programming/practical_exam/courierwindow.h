//
// Created by lucac on 6/28/2024.
//

#ifndef COURIERWINDOW_H
#define COURIERWINDOW_H

#include <qlistwidget.h>
#include <QMainWindow>

#include "service.h"


QT_BEGIN_NAMESPACE
namespace Ui { class courierWindow; }
QT_END_NAMESPACE

class courierWindow : public QMainWindow, public Observer {
Q_OBJECT

public:
    explicit courierWindow(QWidget *parent = nullptr);

    courierWindow(QWidget* parent, Service* service, Courier* courier);

    void update() override;
    void populateComboBox();
    void handleComboBoxSelection();
    void handleDeliverButtonClick();
    void handleListClick(QListWidgetItem* item);

    ~courierWindow() override;

private:
    Ui::courierWindow *ui;

    QListWidgetItem* clickedItem {};

    Service* service {};
    Courier* courier {};
};


#endif //COURIERWINDOW_H
