//
// Created by lucac on 5/28/2024.
//

#ifndef GUI_H
#define GUI_H

#include <QMainWindow>

#include "service.h"


QT_BEGIN_NAMESPACE
namespace Ui { class GUI; }
QT_END_NAMESPACE

class GUI : public QMainWindow {
Q_OBJECT

public:
    explicit GUI(QWidget *parent = nullptr);
    ~GUI() override;

    void populateInitialList();
    void handleSearchButtonClick();
    void handleShowByDescButtonClick();

private:
    Ui::GUI *ui;
    Service service;
};


#endif //GUI_H
