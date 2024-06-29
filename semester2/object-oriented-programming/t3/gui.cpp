//
// Created by lucac on 5/28/2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_GUI.h" resolved

#include "gui.h"
#include "ui_GUI.h"
#include <algorithm>
#include <QMessageBox>

GUI::GUI(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::GUI), service() {
    ui->setupUi(this);
    this->populateInitialList();

    connect(this->ui->searchByProbButton, &QPushButton::clicked, this, handleSearchButtonClick);
    connect(this->ui->showByDescButton, &QPushButton::clicked, this, handleShowByDescButtonClick);
}

GUI::~GUI() {
    delete ui;
}

void GUI::populateInitialList() {
    vector<Weather> weathers = this->service.getAllWeather();

    sort(weathers.begin(), weathers.end(), [](Weather first, Weather second) {
       if(first.getStart() < second.getStart())
           return true;

        if(first.getStart() == second.getStart() && first.getEnd() < second.getEnd())
            return true;

        return false;
    });

    for(auto time_interval: weathers) {

        string text = std::to_string(time_interval.getStart()) + "-" + std::to_string(time_interval.getEnd()) + ", " +
                std::to_string(time_interval.getTemperature()) + " degrees, " +
                 std::to_string(time_interval.getProb()) + "%, " + time_interval.getDescription();

        this->ui->listWidget->addItem(QString::fromStdString(text));
    }
}

void GUI::handleSearchButtonClick() {

    int probability = this->ui->probLineEdit->text().toInt();

    vector<Weather> filtered = this->service.getByProb(probability);

    this->ui->listWidget->clear();

    for(auto time_interval: filtered) {

        string text = std::to_string(time_interval.getStart()) + "-" + std::to_string(time_interval.getEnd()) + ", " +
                std::to_string(time_interval.getTemperature()) + " degrees, " +
                 std::to_string(time_interval.getProb()) + "%, " + time_interval.getDescription();

        this->ui->listWidget->addItem(QString::fromStdString(text));
    }
}

void GUI::handleShowByDescButtonClick() {

    int startTime = this->ui->startTimeLineEdit->text().toInt();
    string description = this->ui->descriptionLineEdit->text().toStdString();
    vector<Weather> filtered = this->service.getByDesc(description, startTime);

    this->ui->timeIntervalsListWidget->clear();
    int totalHours = 0, newStartTime;

    for(auto time_interval: filtered) {

        string text = std::to_string(time_interval.getStart()) + "-" + std::to_string(time_interval.getEnd()) + ", " +
                std::to_string(time_interval.getTemperature()) + " degrees, " +
                 std::to_string(time_interval.getProb()) + "%, " + time_interval.getDescription();

        if(time_interval.getStart() < startTime)
            newStartTime = startTime;
        else
            newStartTime = time_interval.getStart();

        totalHours = totalHours + time_interval.getEnd() - newStartTime;

        this->ui->timeIntervalsListWidget->addItem(QString::fromStdString(text));
    }

    if(totalHours == 0) {
        this->ui->label->clear();
        this->ui->descriptionLineEdit->clear();
        this->ui->startTimeLineEdit->clear();
        QMessageBox::information(this, "Error", "No such time interval");
    } else {
        string numberOfHoursText = std::to_string(totalHours) + " hours in total.";
        this->ui->label->setText(QString::fromStdString(numberOfHoursText));
    }
}