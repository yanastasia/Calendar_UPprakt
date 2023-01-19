#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <ctime>

using namespace std;

const string MONTHNAMES[12] = {
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

const string DAYNAMES[7] = {
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday",
    "Sunday"
};

const int MONTHDAYS[12] = {
    31, 28, 31, 30, 31, 30,
    31, 31, 30, 31, 30, 31,
};

struct Date {
public:
    int day;
    int month;
    int year;

    Date() {

        struct tm currtime;
        time_t now = time(0);
        localtime_s(&currtime, &now);

        year = currtime.tm_year + 1900; 
        month = currtime.tm_mon + 1;
        day = currtime.tm_mday;

    }

    Date(string s) {

        setDate(s);
    }

    Date(int d, int m, int y) {
        setDate(d, m, y);
    }

    void setDate(int d, int m, int y) {
        this->day = d;
        this->month = m;
        this->year = y;
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

    bool operator< (const Date& rhs) const {
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

    bool operator==(const Date& rhs) const {
        return year == rhs.year && month == rhs.month && day == rhs.day;
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

    bool operator<(const Event& rhs) const {
        if (startDate < rhs.startDate) {
            return true;
        }
        else if (startDate == rhs.startDate) {
            return name < rhs.name;
        }

        return false;
    }

    string eventToString() const {
        return name + "|" + startDate.dateToString() + "|" + endDate.dateToString();
    }
};

class Calendar {
public:
    Date currDate;
    vector<Event> events;
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
        }

        rfile.close();
        return;
    }

    void sortEvents() {
        sort(events.begin(), events.end());
    }


    void ListEvents() {

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

    bool validateDate(Date d) {
        if (d.month >= 1 && d.month <= 12) {
            if (d.day >= 1 && d.day <= MONTHDAYS[d.month - 1]) {
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

    struct hasName {
        string& e_name;
        hasName(string& name) : e_name(name) {}
        bool operator() (const Event& e) const {
            return (e.name) == e_name;
        }
    };

    void CreateEvent() {
        string name, sDate, eDate;
        Date testSDate, testEDate;

        //User input with validation
        while (true) {
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
            cout << "Element not found.\n\n";
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

    Date getTomorrow(Date today) {
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

    void startMessage() {
        
        cout << "Welcome! Today is "<<currDate.getDay()<<" "<<MONTHNAMES[currDate.getMonth()-1]<<" "<<currDate.getYear()<< "\n\n"; // dosredi dnshanj datum i dn 
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
};

void separator() {
    cout << "-----------------------------------------------------------------------------------------------------------\n";
    return;
}

int main()
{
    Calendar c;
    while (true) {

        c.startMessage();
        int choice = 0;
        cin >> choice;
        cout << '\n\n';

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
