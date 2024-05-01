#include "date.h"

Date createDate(int year, int month, int day){
    Date date;
    date.year = year;
    date.month = month;
    date.day = day;

    return date;
}