#ifndef LEDS_H
#define LEDS_H
#include "rtc.h"
#include <Adafruit_NeoPixel.h>

#define LED_Pixel 12
#define LED_Pin 25
#define LED_Type NEO_GRB + NEO_KHZ800

void ring_setup();
void update_time(Time time);
void update_alarm_time_led();
void alarm_lighting();

#endif
