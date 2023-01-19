#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

class Date {
public:
    int day;
    int month;
    int year;

    Date(){}
};

class Event {
public:

    string name;
    Date startDate;
    Date endDate;

    Event(){}
};

class Calendar {
public:

    vector<Event> events;

    Calendar(){}

};

Date stringToDate(string s) {
    Date date;

    vector<int> parts;
    string part;

    stringstream ss(s);
    while(getline(ss, part, '/')) {
        parts.push_back(stoi(part));
    }

    date.day = parts[0];
    date.month = parts[1];
    date.year = parts[2];

    return date;
}


int main() {

    vector<string> row;
    string line, part;

    ifstream rfile("events.txt");

    Calendar cal;

    while (!rfile.eof()) {
        Event e;
        row.clear();

        getline(rfile, line);
        stringstream ss(line);

        while (getline(ss, part, '|')) {
            row.push_back(part);
        }
        
        e.name = row[0];
        e.startDate = stringToDate(row[1]);
        e.endDate = stringToDate(row[2]);

        cal.events.push_back(e);

        //cout << "Event: " << e.name << " from " << e.startDate.day<<"-"<<e.startDate.month<<"-"<<e.startDate.year << " to " << e.endDate.day<<"-"<<e.endDate.month<<"-"<<e.endDate.year<<endl;
    }

    
    rfile.close();

    return 0;
}
