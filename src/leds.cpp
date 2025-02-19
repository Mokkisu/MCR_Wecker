#include "leds.h"



void update_time(Time time, Adafruit_NeoPixel *ring)
{
    ring->setPixelColor(time.hours%12, 255,0,0);
    ring->setPixelColor((time.minutes/60)%12,0,0,255);
    ring->setPixelColor((time.seconds/60)%12,0,255,0);
}