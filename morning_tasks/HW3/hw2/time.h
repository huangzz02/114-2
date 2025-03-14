#ifndef TIME_H
#define TIME_H

#include <string>

class Time {
    private:
        int hour;
        int minute;
        int second;
        bool is_AM;
    public:
        Time() : hour(0), minute(0), second(0) {}
        void setTime(int h, int m, int sec);
        void setTime(int s);
        std::string showTime();
};

#endif