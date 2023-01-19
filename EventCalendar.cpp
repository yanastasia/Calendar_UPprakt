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

    const int monthDays[12] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31,
    };
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


    void LoadEventsFile() {

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

    void ListEvents() {

        if (events.empty()) {
            cout << "There are currently no events.\n\n";
            return;
        }

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

    bool validateDate(Date d) {
        if (d.month >= 1 && d.month <= 12) {
            if (d.day >= 1 && d.day <= d.monthDays[d.month - 1]) {
                return true;
            }
        }

        return false;
    }

    bool validateEventLength(Date d1, Date d2) {

        if (d1.year > d2.year) {
            return false;
        }
        if (d1.month > d2.month) {
            return false;
        }
        if (d1.day > d2.day) {
            return false;
        }

        return true;
    }

    void CreateEvent() {
        string name, sDate, eDate;
        Date testSDate, testEDate;

        cout << "Enter name: ";

        cin.ignore();
        getline(cin, name);
        cout << '\n';

        //User input with validation
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

    struct hasName {
        string& e_name;
        hasName(string& name) : e_name(name) {}
        bool operator() (const Event& e) const {
            return (e.name) == e_name;
        }
    };

    void DeleteEvent() {
        string n;
        cout << "Enter name: ";
        cin.ignore();
        getline(cin, n);

        vector<Event>::iterator it;
        it = find_if(events.begin(), events.end(), hasName(n));
        if (it != events.end())
        {
            int pos = distance(events.begin(), it);
            cout << pos << endl; // !! figure it out
        }
        else
            cout << "Event not found.\n\n";
    }

    void saveEventsFile(string filename) {
        ofstream file;
        file.open(filename, ios::app);

        for (auto e : events) {
            file << e.eventToString() << '\n';
        }

        file.close();

        cout << "Save to file successful.\n";
    }
};


void startMessage() {
    time_t now = time(0);
    cout << "Welcome! Today is " /* << monthName(4) */ << '\n' << '\n'; // dosredi dnshanj datum i dn 
    cout << "You have ____ events tomorrow\n";
    cout << " Choose an option: \n";
    cout << '\t' << "1. Show calendar\n";
    cout << '\t' << "2. Show schedule\n";
    cout << '\t' << "3. List events\n";
    cout << '\t' << "4. Add event\n";
    cout << '\t' << "5. Remove event\n";
    cout << '\t' << "6. Set first weekday\n\n";
    cout << "Enter your choice: ";
}

void separator() {
    cout << "-----------------------------------------------------------------------------------------------------------\n";
    return;
}

int main()
{
    Calendar c;
    while (true) {

        startMessage();
        int choice = 0;
        cin >> choice;
        cout << "\n\n";

        const string FILENAME = "events.txt";

        ifstream ifs(FILENAME);
        if (!ifs.is_open()) {
            ofstream outfile(FILENAME); // create file 
        }

        switch (choice) {
        case 3:
            c.ListEvents();
            break;
        case 4:
            c.CreateEvent();
            break;
        case 5:
            c.DeleteEvent();
            break;
        default:
            c.saveEventsFile(FILENAME);
            break;
        }

        separator();
    }

    return 0;
}
