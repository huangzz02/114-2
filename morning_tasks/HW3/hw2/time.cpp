#include "time.h"
#include <iostream>
#include <sstream>
#include <iomanip>

void Time::setTime(int h, int m, int s) {
    hour = h;
    minute = m;
    second = s;
    if (h < 12) {
        is_AM = true;
    } else {
        is_AM = false;
    }

    if (h >= 12) {
        hour = (h == 12) ? 12 : h - 12;
    } else {
        hour = (h == 0) ? 12 : h;
    }
}

void Time::setTime(int s) {
    hour = s / 3600;
    minute = (s % 3600) / 60;
    second = s % 60;
    if (hour < 12) {
        is_AM = true;
    } else {
        is_AM = false;
    }

    if (hour >= 12) {
        hour = (hour == 12) ? 12 : hour - 12;
    } else {
        hour = (hour == 0) ? 12 : hour;
    }
}

std::string Time::showTime() {
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << hour << ":"
        << std::setw(2) << std::setfill('0') << minute << ":"
        << std::setw(2) << std::setfill('0') << second
        << (is_AM ? " AM" : " PM");
    return oss.str();
}