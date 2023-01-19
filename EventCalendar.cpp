#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

struct Date {
public:
    int day;
    int month;
    int year;

    Date() {}

    Date(string s) {

        setDate(s);
    }

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

    int getDay() {
        return day;
    }

    int getMonth() {
        return month;
    }

    int getYear() {
        return year;
    }
    string dateToString() const {
        stringstream ss;
        ss << day << '/' << month << '/' << year;
        return ss.str();
    }
};

class Event {
public:
    string name;
    Date startDate;
    Date endDate;

    Event() {}

    Event(string name, string start, string end) {
        this->name = name;
        this->startDate.setDate(start);
        this->endDate.setDate(end);
    }

    string eventToString() const {
        return name + "|" + startDate.dateToString() + "|" + endDate.dateToString();
    }
};

class Calendar {
    vector<Event> events;
public:
    Calendar() {}

    void loadEventsFile() {

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

            //cout << "You have: " << e.name << " from " << e.startDate.day << "-" << e.startDate.month << "-" << e.startDate.year << " to " << e.endDate.day << "-" << e.endDate.month << "-" << e.endDate.year << endl;
        }

        rfile.close();
    }

    void listEvents() {
        for (int i = 0; i < events.size(); ++i) {
            cout << setw(4) << i << ".";
            cout << events[i].name << '\t';
            string start = events[i].startDate.dateToString();
            string end = events[i].endDate.dateToString();

            if (start == end) {
                cout << "(" << start << ")" << '\n';
                continue;
            }
            cout << "(" << start << " - " << end << ")" << '\n';
        }
    }

    void saveEventsFile() {
        ofstream file;
        file.open("events.txt", ios::app);

        for (auto e : events) {
            file << e.eventToString() << '\n';
        }

        file.close();

        cout << "Save to file success." << endl;
    }
};


void startMessage() {
    time_t now = time(0);
    cout << "Welcome! Today is " /* << monthName(4) */ << '\n' << '\n'; //  work it out for today's date and day
    cout << "You have ____ events tomorrow" << '\n' << '\n';
    cout << " Choose an option: " << '\n';
    cout << '\t' << "1. Show calendar" << '\n';
    cout << '\t' << "2. Show schedule" << '\n';
    cout << '\t' << "3. List events" << '\n';
    cout << '\t' << "4. Add event" << '\n';
    cout << '\t' << "5. Remove event" << '\n';
    cout << '\t' << "6. Set first weekday" << '\n' << '\n';
    cout << "Enter your choice: ";
}

int main()
{
    startMessage();
    int choice = 0;
    cin >> choice;

    ifstream ifs("events.txt");
    if (!ifs.is_open()) {
        ofstream outfile("events.txt"); // create file
    }

    Calendar c;
    c.loadEventsFile();

    c.listEvents();
    return 0;
}
