#include "Date.h"
#include <ctime>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

Date::Date() {

    struct tm currtime;
    time_t now = time(0);
    localtime_s(&currtime, &now);

    year = currtime.tm_year + 1900;
    month = currtime.tm_mon + 1;
    day = currtime.tm_mday;

}

Date::Date(string s) {

    setDate(s);
}

Date::Date(int d, int m, int y) {
    setDate(d, m, y);
}

void Date::setDate(int d, int m, int y) {
    this->day = d;
    this->month = m;
    this->year = y;
}

void Date::setDate(string s) {

    int parts[3];
    string p;

    stringstream ss(s);
    int i = 0;
    while (getline(ss, p, '/')) {
        parts[i] = stoi(p);
        i++;
    }

    this->day = parts[0];
    this->month = parts[1];
    this->year = parts[2];
}

void Date::setMonthYear(string s) {
    int parts[2];
    string p;

    stringstream ss(s);
    int i = 0;
    while (getline(ss, p, '/')) {
        parts[i] = stoi(p);
        i++;
    }

    this->day = 1;
    this->month = parts[0];
    this->year = parts[1];
}

int Date::getDay() {
    return day;
}

int Date::getMonth() {
    return month;
}

int Date::getYear() {
    return year;
}
string Date::dateToString() const {
    stringstream ss;
    ss << day << '/' << month << '/' << year;
    return ss.str();
}

bool Date::operator< (const Date& rhs) const {
    if (year < rhs.year) {
        return true;
    }
    else if (month < rhs.month) {
        return true;
    }
    else if (day < rhs.day) {
        return true;
    }

    return false;
}

bool Date::operator==(const Date& rhs) const {
    return year == rhs.year && month == rhs.month && day == rhs.day;
}

bool Date::operator> (const Date& rhs) const {
    if (year > rhs.year) {
        return true;
    }
    else if (month > rhs.month) {
        return true;
    }
    else if (day > rhs.day) {
        return true;
    }

    return false;
}

bool Date::operator<=(const Date& rhs) const {
    if (year <= rhs.year) {
        if (month <= rhs.month) {
            if (day <= rhs.day) {
                return true;
            }
        }
    }
    return false;
}

bool Date::operator>=(const Date& rhs) const{
    if (year >= rhs.year) {
        if (month >= rhs.month) {
            if (day >= rhs.day) {
                return true;
            }
        }
    }

    return false;
}
