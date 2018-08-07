#ifndef TIME_H
#define TIME_H

#include <virtuabotixRTC.h>

class Time {
    public:
        Time();
        void add_sec(int sec);
        void set(virtuabotixRTC time);
        double getInt();
        int h;
        int m;
        int s;
};

#endif
