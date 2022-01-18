#include <string>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <list>
using namespace std;

class Time {

    int hour;
    int min;

public:
    Time();
    //post: default constructor.

    Time(int hour, int min);
    //pre: valid hour and time input 
    // post: copy constructor

    static int elapsedMin(Time t1, Time t2);
    //post: difference between the two given times in minutes.

    string toString() const;
    //post: creates a string of the time.
    
    Time& operator=(const Time& t);
    // post: assignment operator.

};

Time::Time() {
    hour = 0;
    min = 0;
}

Time::Time(int hour, int min) {
    if ((hour < 0 || hour > 23) || (min < 0 || min > 59)) {
        throw logic_error("Incorrect time");
    }

    this->hour = hour;
    this->min = min;
}

int Time::elapsedMin(Time t1, Time t2) {
    return ((t2.hour - t1.hour)*60)  + (t2.min - t1.min);
}

string Time::toString() const {

    string minutes;
    string hours;

    if (min < 10) {
        minutes = "0" + to_string(min);
    }
    else {
        minutes = to_string(min);
    }
    if (hour < 10) {
        hours = "0" + to_string(hour);
    }
    else {
        hours = to_string(hour);
    }

    string timeOutput = hours + ":" + minutes;

    return timeOutput;
}

Time& Time:: operator=(const Time& t) = default;



