#ifndef SERVICE_SCHEDULAR_CFG_H_
#define SERVICE_SCHEDULAR_CFG_H_

/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include "Schedular.h"

/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/

#define TICK_TIME	2

//#define LED_TASKS	3

#define LCD_TASKS   3

#define KPD_TASKS   1

#define UART_TASKS  2

#define MAX_SUPPORTED_TASKS     (LCD_TASKS + KPD_TASKS + UART_TASKS)




typedef enum
{
    Sched_runnble1,
    Sched_runnble2,         
    Sched_runnble3,         
         
    __NUM_OF_RUNNABLES    /**< Total number of runnables. Do not modify.**/
} RunnableName_t;


/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/



/********************************************************************************************************/
/************************************************APIs****************************************************/
/********************************************************************************************************/














#endif // SERVICE_SCHEDULAR_CFG_H_