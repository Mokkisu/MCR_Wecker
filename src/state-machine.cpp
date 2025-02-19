#include "state-machine.h"

// globale Variable
State_t state = IDLE;

void transition(Event_t event)
{
    switch (state)
    {
    case IDLE:
        if (ALARM_ON == event){
            state = RING;
        } else if (CONFIG_ALARM == event){
            state = SET_ALARM;
        } else if (CONFIG_TIME == event){
            state = SET_CLOCK;
        }
        break;
    case RING:
        if (ALARM_OFF == event){
            state = IDLE;
        }
        break;
    case SET_ALARM:
        if (CONFIG_FINISH == event){
            state = IDLE;
        }
        break;
    case SET_CLOCK:
        if (CONFIG_FINISH == event){
            state = IDLE;
        }
        break;
    default:
        break;
    }
}