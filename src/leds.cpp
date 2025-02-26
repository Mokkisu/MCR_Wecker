#include "leds.h"
#include <string>
#include <rotary.h>


Adafruit_NeoPixel ring(LED_Pixel, LED_Pin, LED_Type); 
void ring_setup(){
    ring.begin();
    ring.setBrightness(75);
    ring.show();

}

void update_time(Time time)
{
    ring.setPixelColor(time.hours%12, 255,0,0);
    ring.setPixelColor((time.minutes/60)%12,0,0,255);
    ring.setPixelColor((time.seconds/60)%12,0,255,0);
    ring.show();
}

void update_alarm_time_led()
{
    for(int i = 0; i < 12; i++){
        ring.setPixelColor(12-1-i, 0, 0, 0);
        ring.show();
    }

    ring.fill(0x99CCFF, 0, configured_time);
    ring.show();
}

void alarm_lighting(){
    if (millis()%1000 > 500)
    {
        for(int i = 0; i <12; i++){
            ring.setPixelColor(12-1-i, 0, 0, 0);
            ring.show();
        }
    }
    else
    {
        for(int i = 0; i < 12;i++){
            ring.setPixelColor(i, 255, 255, 255);
            ring.show();
        }
    }
}