#include <rtc.h>

void set_time(Time time){}
Time get_time(){
    Time time;
    time.hours = 4;
    time.minutes = 25;
    time.seconds = 5;

    return time;
}