#ifndef _KEYPAD_H_
#define _KEYPAD_H_

#include "std_types.h"
#include "GPIO.h"
#include "Keypad_cfg.h"


typedef enum
{
    KEYPAD_OK,
    KEYPAD_NOK,
    KEYPAD_NULLPTR
}Keypad_Errorstates_t;

void keypad_runnable(void);


#endif