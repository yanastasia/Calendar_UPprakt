#include "Calendar.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <ctime>
#include<windows.h>
#include<map>
#include "Date.h"
#include "Event.h"

using namespace std;

Calendar::Calendar() {}

const string Calendar::MONTHNAMES[12] = {
    "January",
    "February",
    "March",
    "April",
    "May",
    "June",
    "July",
    "August",
    "September",
    "October",
    "November",
    "December"
};

const string Calendar::DAYNAMES[7] = {
    "Mo",
    "Tu",
    "We",
    "Th",
    "Fr",
    "Sa",
    "Su"
};

const string Calendar::DAYNAMESFULL[7] = {
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday",
    "Sunday"
};

int Calendar::monthDays(int month, int year) {
    switch (month)
    {
    case 1:
        return 31;
        break;
    case 2:
        if (year % 4 != 0)
            return 28;
        else
            return 29;
        break;
    case 3:
        return 31;
        break;
    case 4:
        return 30;
        break;
    case 5:
        return 31;
        break;
    case 6:
        return 30;
        break;
    case 7:
        return 31;
        break;
    case 8:
        return 31;
        break;
    case 9:
        return 30;
        break;
    case 10:
        return 31;
        break;
    case 11:
        return 30;
        break;
    case 12:
        return 31;
        break;
    default:
        cout << "The month entered is invalid.\n";
        return -1;
    }
}

Date Calendar::getCurrDate() {
    return currDate;
}

string Calendar::getStartDay() {
    if (startMonday) {
        return "Monday";
    }
    return "Sunday";
}

void Calendar::setStartDay(string day) {
    if (day == "Mon" || day == "Monday") {
        startMonday = true;
    }
    else if (day == "Sun" || day == "Sunday") {
        startMonday = false;
    }
}
void Calendar::loadEventsFile() {

    events.clear();

    string line, part, junk;

    ifstream rfile("events.txt");

    while (!rfile.eof()) {
        Event e;
        string row[3];

        getline(rfile, line);
        stringstream ss(line);
        int i = 0;
        while (getline(ss, part, '|')) {
            row[i] = part;
            i++;
        }

        e.name = row[0];

        e.startDate.setDate(row[1]);
        e.endDate.setDate(row[2]);
        if (validateDate(e.startDate) && validateDate(e.endDate) && validateEventLength(e.startDate, e.endDate)) {
            events.push_back(e);
        }
    }

    rfile.close();
    //cout << "File loaded successfuly!\n\n";
}
void Calendar::sortEvents() {
    sort(events.begin(), events.end());
}

void Calendar::ListEvents() {

    if (events.empty()) {
        cout << "There are currently no events.\n\n";
        return;
    }

    //sortEvents();
    cout << "You have the following events:\n";
    for (int i = 0; i < events.size(); ++i) {
        cout << i + 1 << ".";
        cout << events[i].name << '\t';

        if (events[i].startDate.dateToString() == events[i].endDate.dateToString()) {
            cout << "(" << events[i].startDate.dateToString() << ")" << '\n';
            continue;
        }
        cout << "(" << events[i].startDate.dateToString() << " - " << events[i].endDate.dateToString() << ")" << '\n';
    }
    cout << "\n\n";
    return;
}

bool Calendar::validateDate(Date d) {
    if (d.getMonth() >= 1 && d.getMonth() <= 12) {
        if (d.getDay() >= 1 && d.getDay() <= monthDays(d.getMonth(), d.getYear())) {
            return true;
        }
    }

    return false;
}

bool Calendar::validateEventLength(Date d1, Date d2) {

    if (d1.getYear() > d2.getYear()) {
        return false;
    }
    if (d1.getMonth() > d2.getMonth()) {
        return false;
    }
    if (d1.getDay() > d2.getDay()) {
        return false;
    }

    return true;
}

struct Calendar::hasName {
    string& e_name;
    hasName(string& name) : e_name(name) {}
    bool operator() (const Event& e) const {
        return (e.name) == e_name;
    }
};

Date Calendar::inputMonthYear() {
    string iDate;
    Date inputDate;
    while (true) {
        cout << "Enter month (MM/YYYY): ";

        cin >> iDate;
        cout << '\n';
        if (iDate.length() != 7) {
            cout << "Invalid format! Try again.\n";
            continue;
        }

        inputDate.setMonthYear(iDate);

        if (validateDate(inputDate)) {
            break;
        }
        else {
            cout << "Invalid input! Try again.\n";
        }
    }

    return inputDate;
}

multimap<int, Event> Calendar::vecToMM_MonthYear(int y, int m) {
    int year = y;
    int month = m;

    multimap<int, Event> eventsMap;
    for (int j = 1; j < monthDays(month, year); ++j) {
        Date targetDate(j, month, year);
        for (int i = 0; i < events.size(); ++i) {
            if ((events[i].startDate <= targetDate) && (events[i].endDate >= targetDate)) {
                eventsMap.insert(pair<int, Event>(j, events[i]));
            }
        }
    }

    return eventsMap;
}

int Calendar::eventsOnDate(Date d) {
    int eventCount = 0;
    for (int i = 0; i < events.size(); ++i) {
        if ((events[i].startDate <= d) && (events[i].endDate >= d)) {
            ++eventCount;
        }
    }
    
    return eventCount;
}

void Calendar::ShowSchedule() {
    Date inputDate = inputMonthYear();
    int year = inputDate.getYear();
    int month = inputDate.getMonth();

    multimap<int, Event> eventsOTM = vecToMM_MonthYear(year, month);

    cout << MONTHNAMES[month - 1] << " " << year << '\n';
    cout << "----------\n";

    for (int j = 1; j < monthDays(month, year); ++j) {
        if (eventsOTM.count(j)) {
            string day;
            if (FirstDayOfMonth_Sunday(year, month, j) == 0) {
                day = "Su";
            }
            else {
                day = DAYNAMES[FirstDayOfMonth_Sunday(year, month, j)-1];
            }
            

            cout << day << ", " << j << '\t';
            auto itr1 = eventsOTM.lower_bound(j);
            auto itr2 = eventsOTM.upper_bound(j);
            while (itr1 != itr2) {
                
                if ((itr1->first == j) && (itr1 == eventsOTM.lower_bound(j))) { 
                    cout << "  " << itr1->second.name << endl;
                }
                else if (itr1->first == j) { 
                    cout << setw(14) << itr1->second.name << endl;
                }
                itr1++;
            }
        }
    }

}

void Calendar::CreateEventW() {
    string name, sDate, eDate;
    Date testSDate, testEDate;

    //User input with validation
    cin.ignore();

    while (true) {
        cout << "Enter name: ";

        getline(cin, name);
        cout << '\n';

        vector<Event>::iterator it;
        it = find_if(events.begin(), events.end(), hasName(name));

        if (it != events.end()) {

            cout << "An event with that name already exists. Try again. \n";
            continue;
        }
        else {
            break;
        }
    }

    while (true) {

        while (true) {

            cout << "Enter start date (DD/MM/YYYY): ";
            cin >> sDate;
            cout << '\n';

            if (sDate.length() != 10) {
                cout << "Invalid format! Try again.\n";
                continue;
            }

            testSDate.setDate(sDate);

            if (validateDate(testSDate)) {
                break;
            }
            else {
                cout << "Invalid input! Try again.\n";
            }
        }

        while (true) {
            cout << "Enter end date (DD/MM/YYYY): ";
            cin >> eDate;
            cout << '\n';

            if (eDate.length() != 10) {
                cout << "Invalid format! Try again.\n";
                continue;
            }

            testEDate.setDate(eDate);

            if (validateDate(testEDate)) {
                break;
            }
            else {
                cout << "Invalid input! Try again.\n";
            }
        }

        if (validateEventLength(testSDate, testEDate)) {

            Event e(name, sDate, eDate);
            events.push_back(e);

            cout << "Event added successfuly!\n\n";
            return;
        }

        cout << "End date is before start date! Try again.\n";
    }
}

void Calendar::DeleteEvent() {
    string n;
    cout << "Enter name: ";
    cin.ignore();
    getline(cin, n);

    vector<Event>::iterator it;
    it = find_if(events.begin(), events.end(), hasName(n));
    if (it != events.end())
    {
        __int64 pos = distance(events.begin(), it);
        events.erase(events.begin() + pos);
        cout << "Event deleted successfuly!\n\n";
        return;
    }
    else {
        cout << "Element not found.\n\n";
    }
}

int Calendar::FirstDayOfMonth_Monday(int year, int month)
{
    int t[12] = { 0,3,2,5,0,3,5,1,4,6,2,4 };
    int y = year - (month < 3);
    y = (y + y / 4 - y / 100 + y / 400 + t[month - 1]) % 7;
    // y = 0 for Sunday, 1 for Monday.. etc.
    return y;
}

int Calendar::FirstDayOfMonth_Sunday(int year, int month, int day)
{
    int t[12] = { 0,3,2,5,0,3,5,1,4,6,2,4 };
    int y = year - (month < 3);
    y = (y + y / 4 - y / 100 + y / 400 + t[month - 1] + day) % 7;
    // y = 0 for Sunday, 1 for Monday.. etc.
    return y;
}

void Calendar::generateCalendar() {
    Date cDate = inputMonthYear();
    int year = cDate.getYear();
    int month = cDate.getMonth();
    int day = 1;

    cout << setw(28) << MONTHNAMES[month - 1] << " " << year << '\n';

    int startingDay;
    int dayCount = monthDays(month, year);

    const int W = 9;

    if (getStartDay() == "Monday") {
        startingDay = FirstDayOfMonth_Monday(year, month);

        //Print all the startingDay days Mon-Sun 
        for (int i = 0; i < 7; ++i) {
            cout << DAYNAMES[i] << setw(W);
        }
        cout << '\n';

        //Print and empty space if the day doesn't have a corresponding day 
        for (int x = 0; x < startingDay; ++x) {
            cout << setw(2 * W + 1);
        }
    }

    else if (getStartDay() == "Sunday") {
        startingDay = FirstDayOfMonth_Sunday(year, month, day);

        //Print all the startingDay days Sun-Sat
        cout << DAYNAMES[6] << setw(W);
        for (int i = 0; i < 6; ++i) {
            cout << DAYNAMES[i] << setw(W);
        }
        cout << '\n';

        //Print and empty space if the day doesn't have a corresponding day 
        for (int x = 0; x < startingDay; ++x) {
            cout << "         ";
        }
    }

    //Print the date corresponding with the day 
    for (int d = 0; d < dayCount; ++d) {
        Date sample(d, month, year);
        if (d < 8) {
            cout << "0" << d + 1;
            if (eventsOnDate(sample)) {
                cout << " (" << eventsOnDate(sample) << ")";
                cout << setw(4);
            }
            else {
                cout << setw(8);
            }
        }
        else if (d == 8) { //aesthetic purposes
            cout << "0" << d + 1;
            if (eventsOnDate(sample)) {
                cout << " (" << eventsOnDate(sample) << ")";
                cout << setw(5);
            }
            else {
                cout << setw(9);
            }
        }
        else {
            cout << d + 1;
            if (eventsOnDate(sample)) {
                cout << " (" << eventsOnDate(sample) << ")";
                cout << setw(5);
            }
            else {
                cout << setw(9);
            }
        }
        ++startingDay;
        if (startingDay == 7) {
            startingDay = 0;
            cout << '\n';
        }
    }

    cout << '\n';
}

void Calendar::ChangeFirstWeekDay() {
    cout << "The first day of the week is currently: ";
    if (getStartDay() == "Monday") {
        cout << "Monday.\n\n";
    }
    else if (getStartDay() == "Sunday") {
        cout << "Sunday.\n\n";
    }

    cout << "Enter new (Mon/Sun): ";
    string nw;
    cin >> nw;

    setStartDay(nw);

    cout << "\n\n";

    cout << "Saved!\n\n";
}

void Calendar::saveEventsFile(string filename) {
    ofstream file;
    file.open(filename, ios::trunc);

    for (auto e : events) {
        file << e.eventToString() << '\n';
    }

    file.close();

    //cout << "Save to file successful.\n";
}

Date Calendar::getTomorrow(Date today) {
    int dayT = 0, monthT = 0, yearT = 0;

    dayT = today.getDay() + 1;
    monthT = today.getMonth();
    yearT = today.getYear();
    Date tomorrow(dayT, monthT, yearT);

    if (!validateDate(tomorrow)) {
        tomorrow.setDate(1, monthT + 1, yearT);
    }

    if (!validateDate(tomorrow)) {
        //Happy NYE
        tomorrow.setDate(1, 1, yearT + 1);
    }

    return tomorrow;
}

void Calendar::startMessage() {
    string day = DAYNAMESFULL[FirstDayOfMonth_Sunday(currDate.getYear(), currDate.getMonth(), currDate.getDay())-1];

    cout << "Welcome! Today is " << day<<", "<< currDate.getDay() << " " << MONTHNAMES[currDate.getMonth() - 1] << " " << currDate.getYear() << "\n\n";

    if (eventsOnDate(currDate)) {
        cout << "You have "<< eventsOnDate(currDate)<<" events today.\n\n";
    }
    else {
        Date tomDate = getTomorrow(currDate);
        cout << "You have " << eventsOnDate(tomDate) << " events tomorrow.\n\n";
    }


}

void Calendar::StartMenu() {
    cout << " Choose an option: \n";
    cout << '\t' << "1. Show calendar\n";
    cout << '\t' << "2. Show schedule\n";
    cout << '\t' << "3. List events\n";
    cout << '\t' << "4. Add event\n";
    cout << '\t' << "5. Remove event\n";
    cout << '\t' << "6. Set first weekday\n\n";
    cout << "Enter your choice: ";
}

void Calendar::separator() {
    cout << "-----------------------------------------------------------------------------------------------------------\n";
    return;
}

void Calendar::Run(string FILENAME) {
    startMessage();
    while (true) {

        StartMenu();
        int choice = 0;
        cin >> choice;
        cout << "\n\n";

        switch (choice) {
        case 1:
            generateCalendar();
            break;
        case 2:
            ShowSchedule();
            break;
        case 3:
            ListEvents();
            break;
        case 4:
            CreateEvent();
            break;
        case 5:
            DeleteEvent();
            break;
        case 6:
            ChangeFirstWeekDay();
            break;
        default:
            cout << "Invalid input!";
            return;
            break;
        }

        separator();
        Sleep(500);

        cout << "\n";

        cout << "To continue enter 0. To quit enter any other character.\n";
        cout << "Your choice: ";
        cin >> choice;
        cout << "\n";

        if (choice != 0) {
            
            return;
        }

        separator();
        Sleep(500);
        cout << "\n";
    }
    return;
}
