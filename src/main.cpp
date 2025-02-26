#include <Arduino.h>
#include <state-machine.h>
#include <rtc.h>
#include <leds.h>
#include <rotary.h>

/**
wecker
- led ring
- rotrary encoder
- rtc
*/

#define LED_Pixel 12
#define LED_Pin 25
#define LED_Type NEO_GRB + NEO_KHZ800

int incomingByte = 0; // Für eingehende serielle Daten

void setup()
{
  Serial.begin(115200);
  ring_setup();
  rotary_setup();
}

void loop()
{

  if (IDLE == state)
  {
    Serial.print("Aktuelle Zeit: ");
    Time time = get_time();
    Serial.println(time.minutes);
    update_time(time);
  }

  if (RING == state)
  {
    alarm_lighting();
  }

  if (Serial.available() > 0)
  {
    // Lies das eingehende Byte:
    incomingByte = Serial.read();

    switch (incomingByte)
    {
    case '0':
      /* code */
      Serial.print("Aktueller State: ");
      Serial.println(state);
      break;

    case '1':
      /* code */
      transition(ALARM_OFF);
      break;

    case '2':
      transition(ALARM_ON);
      alarm_lighting();
      break;

    case '3':
      /* code */
      transition(CONFIG_TIME);
      break;

    case '4':
      transition(CONFIG_ALARM);

      break;

    case '5':
      /* code */
      transition(CONFIG_FINISH);
      break;

    default:
      break;
    }
  }
}