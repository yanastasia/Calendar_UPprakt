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
    return (startDate < rhs.startDate) || (startDate == rhs.startDate && name < rhs.name);
}

string Event::eventToString() const {
    return name + "|" + startDate.dateToString() + "|" + endDate.dateToString();
}
