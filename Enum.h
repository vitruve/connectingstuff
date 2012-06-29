/*
Output.h - Library for domotic ouput management
  Created by Lebrun Olivier 05/08/2010
*/
#ifndef Enum_h
#define Enum_h

typedef enum SwitchState_t {RELEASE = 0, PRESS = 1, LONGPRESS = 2, PRESSRELEASE = 3} SwitchState;
typedef enum Statut_t {OFF = 0, ON = 1, ONOFF = 2} Statut;

extern uint8_t SwitchState_t;
extern uint8_t Statut_t;

#endif
