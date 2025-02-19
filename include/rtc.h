#ifndef RTC_H
#define RTC_H

struct Time
{
    int hours;
    int minutes;
    int seconds;
};

void set_time(Time time);
Time get_time();

#endif
