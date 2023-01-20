#ifndef EVENT_H
#define EVENT_H
#include <string>
#include <sstream>
#include "Date.h"
using namespace std;

class Event {
public:
    string name;
    Date startDate;
    Date endDate;

    Event();

    Event(string name, string start, string end);

    bool operator<(const Event& rhs) const;

    string eventToString() const;
};

#endif
