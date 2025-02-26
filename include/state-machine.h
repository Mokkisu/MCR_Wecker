#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

typedef enum{
  IDLE,
  RING,
  SET_CLOCK,
  SET_ALARM,
} State_t;

typedef enum{
    ALARM_ON,
    ALARM_OFF,
    CONFIG_TIME,
    CONFIG_ALARM,
    CONFIG_FINISH,
} Event_t;

extern State_t state;

void transition(Event_t event);

#endif