
#include <rtc.h>
#include <RTClib.h>

// Initialize the RTC
RTC_DS3231 rtc;

void rtc_setup() { // Initialize the RTC
    if (!rtc.begin()) {
        while (1); // Couldn't find RTC, halt the program
    }

    if (rtc.lostPower()) { // Set the RTC to the date & time this sketch was compiled
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
}

void set_time(Time time) {
    DateTime dt = DateTime(2025, 2, 26, time.hours, time.minutes, time.seconds);
    rtc.adjust(dt);
}

Time get_time() {
    DateTime now = rtc.now();
    Time time;
    time.hours = now.hour();
    time.minutes = now.minute();
    time.seconds = now.second();
    return time;
}