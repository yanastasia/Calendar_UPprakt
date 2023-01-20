#include "Calendar.h"
#include <ctime>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Date.h"
#include "Event.h"

Calendar::Calendar() {
    /*Date now;
    currDate = now;*/
}

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
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday",
    "Sunday"
};

const int Calendar:: MONTHDAYS[12] = {
    31, 28, 31, 30, 31, 30,
    31, 31, 30, 31, 30, 31,
};
/*
void Calendar::LoadEventsFile() {

    events.clear();

    vector<string> row;
    string line, part;

    ifstream rfile("events.txt");

    while (!rfile.eof()) {
        Event e;
        row.clear();

        getline(rfile, line);
        stringstream ss(line);

        while (getline(ss, part, '|')) {
            row.push_back(part);
        }

        e.name = row[0];

        e.startDate.setDate(row[1]);
        e.endDate.setDate(row[2]);

        events.push_back(e);
    }

    rfile.close();
}

void Calendar::LoadEventsFile(string fileName) {

    vector<string> row;
    string line, part;

    ifstream rfile(fileName);

    //Calendar cal;

    while (!rfile.eof()) {
        Event e;
        row.clear();

        getline(rfile, line);
        stringstream ss(line);

        while (getline(ss, part, '|')) {
            row.push_back(part);
        }

        e.name = row[0];

        e.startDate.setDate(row[1]);
        e.endDate.setDate(row[2]);

        events.push_back(e);
    }

    rfile.close();
    return;
}
*/

void Calendar::sortEvents() {
    sort(events.begin(), events.end());
}

void Calendar::ListEvents() {

    if (events.empty()) {
        cout << "There are currently no events.\n\n";
        return;
    }

    sortEvents();
    cout << "You have the following events:\n";
    for (int i = 0; i < events.size(); ++i) {
        cout << i + 1 << ".";
        cout << events[i].name << '\t';

        string start = events[i].startDate.dateToString();
        string end = events[i].endDate.dateToString();

        if (start == end) {
            cout << "(" << start << ")" << '\n';
            continue;
        }
        cout << "(" << start << " - " << end << ")" << '\n';
    }
    cout << "\n\n";
    return;
}

bool Calendar::validateDate(Date d) {
    if (d.getMonth() >= 1 && d.getMonth() <= 12) {
        if (d.getDay() >= 1 && d.getDay() <= MONTHDAYS[d.getMonth() - 1]) {
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

void Calendar::CreateEvent() {
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
        cout << pos << endl; // !! figure it out
    }
    else
        cout << "Element not found.\n\n";
}

void Calendar::saveEventsFile(string filename) {
    ofstream file;
    file.open(filename, ios::app);

    for (auto e : events) {
        file << e.eventToString() << '\n';
    }

    file.close();

    cout << "Save to file successful.\n";
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

    cout << "Welcome! Today is " << currDate.getDay() << " " << MONTHNAMES[currDate.getMonth() - 1] << " " << currDate.getYear() << "\n\n"; // dosredi dnshanj datum i dn 
    Date tomDate = getTomorrow(currDate);

    cout << "You have ____ events tomorrow\n\n";
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
    while (true) {

        startMessage();
        int choice = 0;
        cin >> choice;
        cout << "\n\n";

        switch (choice) {
        case 3:
            ListEvents();
            break;
        case 4:
            CreateEvent();
            break;
        case 5:
            DeleteEvent();
            break;

        default:
            saveEventsFile(FILENAME);
            break;
        }

        separator();
    }
    return;
}