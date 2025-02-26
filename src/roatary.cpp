#include <Arduino.h>
#include <state-machine.h>
#include <leds.h>

// Definition of the input pins
const int PIN_CLK = 34;
const int PIN_DT = 35;
const int PIN_BTN = 32;

// Initialization of required variables
bool initialisation_complete = false;

void transiton_btn_pressed()
{
    switch (state)
    {
    case RING:
        transition(ALARM_OFF);

        break;
    case IDLE:
        transition(CONFIG_ALARM);

        break;
    case SET_ALARM:
        transition(SET_ALARM);

        break;
    }
}

#define DEBOUNCE_DELAY 300

typedef enum
{
    NONE = 0,
    CLOCKWISE = 1,
    COUNTERCLOCKWISE = -1,
    INVALID = 2
} RotationDirection;

// https://daniellethurow.com/blog/2021/8/30/how-to-use-quadrature-rotary-encoders
// lookup table, first index is previous value
// second index is current value
// says if it's part of the sequence when moving
// clockwise (1) or counterclockwise (-1)
// didn't move (0) or skipped a value (2)
int lookupTable[4][4] = {{NONE, COUNTERCLOCKWISE, CLOCKWISE, INVALID},
                         {CLOCKWISE, NONE, INVALID, COUNTERCLOCKWISE},
                         {COUNTERCLOCKWISE, INVALID, NONE, CLOCKWISE},
                         {INVALID, CLOCKWISE, COUNTERCLOCKWISE, NONE}};

void readEncoderSave()
{
    static unsigned int clockState = 0;
    static unsigned int counterClockState = 0;
    static int prevVal = 3;

    int newVal = (digitalRead(PIN_CLK) << 1) + digitalRead(PIN_DT);

    int info = lookupTable[prevVal][newVal];
    if (info == CLOCKWISE)
    {
        clockState |= (1 << newVal);
    }
    else if (info == COUNTERCLOCKWISE)
    {
        counterClockState |= (1 << newVal);
    }
    else if (info == INVALID)
    {
        Serial.println("skipped a value");
    }

    if (prevVal != newVal && newVal == 3)
    {
        // changed to the non moving state, lets figure out what direction we went!

        // for each clockwise and counterclockwise, the encoder state goes through 4 distinct states
        // make sure it's gone through at least 3 of those (and assume if one is missing it's because I didn't read fast enough)
        if (clockState == 0b1011 || clockState == 0b1101 || clockState == 0b1110 || clockState == 0b1111)
        {
            set_alarm_time_led(1);
        }
        if (counterClockState == 0b1011 || counterClockState == 0b1101 || counterClockState == 0b1110 || counterClockState == 0b1111)
        {
            set_alarm_time_led(-1);
        }

        clockState = 0;
        counterClockState = 0;
    }

    prevVal = newVal;
}

void readButton()
{
    unsigned long static last_interrupt = 0;
    if (initialisation_complete && millis() - last_interrupt > DEBOUNCE_DELAY)
    {
        transiton_btn_pressed();
        last_interrupt = millis();
    }
}

void setup()
{
    pinMode(PIN_CLK, INPUT_PULLUP);
    pinMode(PIN_DT, INPUT_PULLUP);
    pinMode(PIN_BTN, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(PIN_CLK), readEncoderSave, CHANGE);
    attachInterrupt(digitalPinToInterrupt(PIN_DT), readEncoderSave, CHANGE);

    attachInterrupt(digitalPinToInterrupt(PIN_BTN), readButton, RISING);
    initialisation_complete = true;
}
