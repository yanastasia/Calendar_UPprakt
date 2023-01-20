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
public:

    Calendar();
    
    static const string MONTHNAMES[12];
    static const string DAYNAMES[7];
    static const int MONTHDAYS[12];

    void LoadEventsFile(); //Load events from event file
    void LoadEventsFile(string fileName);

    void sortEvents(); //Sort events by date or name

    void ListEvents(); //List all events, inputed and from file

    bool validateDate(Date d); //Date validation
    bool validateEventLength(Date d1, Date d2); //interval between dates validation

    struct hasName; //helper for searching

    void CreateEvent(); //User creating an event
    void DeleteEvent(); //User deleting and event

    void saveEventsFile(string filename); //Save events to file

    Date getTomorrow(Date today); //calculating tomorrow's date

    void startMessage(); //start menu
    void separator();
    void Run(string FILENAME); //for running the program
};

#endif