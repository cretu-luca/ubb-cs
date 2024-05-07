#pragma once
#include <QApplication>
#include <QPushButton>
#include <QMessageBox>
#include <QLineEdit>
#include <QFormLayout>
#include <QGroupBox>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QTableWidget>
#include <QHeaderView>
#include "controller/controller.h"
#include <QCheckBox>


// SELECT PROFILE WIDGET
class MainWidget: public QWidget {
    Q_OBJECT
protected:
    Controller* controller;

public:
    explicit MainWidget(QWidget* parent = nullptr);

    void selectProfile();
    void setUpController();

    QPushButton* selectUserButton;
    QPushButton* selectAdminButton;
    QPushButton* HTMLButton;
    QPushButton* CSVButton;

    QVBoxLayout* mainLayout;

    const QSize buttonSize = QSize(200, 100);

public slots:
    void selectUser();
    void selectAdmin();

    void setUpHTMLController();
    void setUpCSVController();
};