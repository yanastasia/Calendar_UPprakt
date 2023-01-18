#include <iostream>
#include <string>


using namespace std;

//class Event {
//    string name;
//
//
//};

string monthName(int n) {
    switch (n) {
        case 1:
            return "January";
            break;
        case 2:
            return "February";
            break;
        case 3:
            return "March";
            break;
        case 4:
            return "April";
            break;
        case 5:
            return "May";
            break;
        case 6:
            return "June";
            break;
        case 7:
            return "July";
            break;
        case 8:
            return "August";
            break;
        case 9:
            return "September";
            break;
        case 10:
            return "October";
            break;
        case 11:
            return "November";
            break;
        case 12:
            return "December";
            break;
        default:
            return "Invalid";
    }
}
void startMessage() {
    time_t now = time(0);
    cout << "Welcome! Today is " << monthName(4)<<'\n'<<'\n'; // dosredi dnshanj datum i dn 
    cout << "You have ____ events tomorrow" << '\n' << '\n';
    cout << " Choose an option: " << '\n';
    cout << '\t' << "1. Show calendar" << '\n';
    cout << '\t' << "2. Show schedule" << '\n';
    cout << '\t' << "3. List events" << '\n';
    cout << '\t' << "4. Add event" << '\n';
    cout << '\t' << "5. Remove event" << '\n';
    cout << '\t' << "1. Set first weekday" << '\n' << '\n';
    cout << "Enter your choice: ";
}
int main()
{
    startMessage();
    return 0;
}
