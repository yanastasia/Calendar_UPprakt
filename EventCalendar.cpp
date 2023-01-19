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

    Date() {}

    void setDate(string s) {
        vector<int> parts;
        string part;

        stringstream ss(s);
        while (getline(ss, part, '/')) {
            parts.push_back(stoi(part));
        }

        this->day = parts[0];
        this->month = parts[1];
        this->year = parts[2];
    }

    //constructor for string to Date
    Date(string s) {

        setDate(s);
    }


};

class Event {
public:

    string name;
    Date startDate;
    Date endDate;

    Event() {}


};

class Calendar {
public:

    vector<Event> events;
    Calendar() {}

    void load(string fileName) {

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
            //raboti stored in vector
                cout << "Event: " << e.name << " from " << e.startDate.day << "-" << e.startDate.month << "-" << e.startDate.year << " to " << e.endDate.day << "-" << e.endDate.month << "-" << e.endDate.year << endl;
        }

        rfile.close();
    }

};




int main() {

    Calendar c;
    c.load("events.txt");

    return 0;
}
