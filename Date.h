#ifndef DATE_H
#define DATE_H
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <ctime>
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
    void setMonthYear(string s);

    int getDay();
    int getMonth();
    int getYear();

    string dateToString() const;

    bool operator< (const Date& rhs) const;
    bool operator==(const Date& rhs) const;
};

#endif
