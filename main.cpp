#include <iostream>
#include <fstream>
#include "Calendar.h"

using namespace std;

int main()
{
    Calendar c;
    const string FILENAME = "events.txt";

    ifstream ifs(FILENAME);
    if (!ifs.is_open()) {
        ofstream outfile(FILENAME); // create file 
    }
    c.Run(FILENAME);

    return 0;
}
