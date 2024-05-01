#pragma once
#include <string>

using namespace std;


class Date{
public:

    Date() {
        this->year = 0;
        this->month = 0;
        this->day = 0;
    }

    int year, month, day;

    Date(int year, int month, int day) {
        this->year = year;
        this->month = month;
        this->day = day;
    }

    bool operator==(Date other) {
        return this->day == other.day && this->month == other.month && this->year == other.year;
    }

    Date compare(Date date1, Date date2) {
        if(date1.year > date2.year)
            return date1;

        if(date1.year == date2.year && date1.month > date2.month)
            return date1;

        if(date1.year == date2.year &&  date1.month == date2.month && date1.day > date2.day)
            return date1;

        return date2;
    }
};

class Task {
private:
    string description;
    int duration;
    Date deadline;

public:
    Task(string description, int duration, Date deadline);

    bool operator==(Task other);

    string getDescription() {return this->description;}
    int getDuration() { return this->duration; }
    Date getDeadline() { return this->deadline; }
};