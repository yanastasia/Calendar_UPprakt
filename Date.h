#ifndef DATE_H
#define DATE_H
#include <ctime>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

class Date {
    int day;
    int month;
    int year;

public:

    Date(); //default constructor for current date
    Date(string s); //constructor with setter string->date
    Date(int d, int m, int y); //constructor with setter int, int, int->date

    void setDate(int d, int m, int y);
    void setDate(string s);

    int getDay();
    int getMonth();
    int getYear();

    string dateToString() const;

    bool operator< (const Date& rhs) const;
    bool operator==(const Date& rhs) const;
};

#endif