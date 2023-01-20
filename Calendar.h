#ifndef CALENDAR_H
#define CALENDAR_H

#include <vector>
#include <iostream>
#include "Date.h"
#include "Event.h"
using namespace std;

class Calendar {
    Date currDate;
    vector<Event> events;
    bool startMonday = true;
public:

    Calendar();
    
    static const string MONTHNAMES[12];
    static const string DAYNAMES[7];
    int monthDays(int month, int year);

    Date getCurrDate();
    string getStartDay();

    void setStartDay(string day);

    void loadEventsFile();

    void sortEvents(); //Sort events by date or name

    void ListEvents(); //List all events, inputed and from file

    bool validateDate(Date d); //Date validation
    bool validateEventLength(Date d1, Date d2); //interval between dates validation

    struct hasName; //helper for searching

    void CreateEventW(); //User creating an event
    void DeleteEvent(); //User deleting and event

    void InputDate();
    int FirstDayOfMonth_Monday(int year, int month);
    int FirstDayOfMonth_Sunday(int year, int month, int day);
    void generateCalendar(Date cDate);

    void ChangeFirstWeekDay();

    void saveEventsFile(string filename); //Save events to file

    Date getTomorrow(Date today); //calculating tomorrow's date

    void startMessage(); // at start

    void StartMenu(); //menu
    void separator();
    void Run(string FILENAME); //for running the program
};

#endif
