#include "Event.h"
#include <string>
#include <sstream>
Event::Event() { }

Event::Event(string name, string start, string end) {
    this->name = name;
    this->startDate.setDate(start);
    this->endDate.setDate(end);
}

bool Event::operator<(const Event& rhs) const {
    if (startDate < rhs.startDate) {
        return true;
    }
    else if (startDate == rhs.startDate) {
        return name < rhs.name;
    }

    return false;
}

string Event::eventToString() const {
    return name + "|" + startDate.dateToString() + "|" + endDate.dateToString();
}
