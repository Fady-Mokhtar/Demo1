/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/

/* Include Libraries  */

/* Driver Libraries   */
#include "Schedular_cfg.h"

/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/



/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/
/*
extern void Traffic_Green(void);
extern void Traffic_Yellow(void);
extern void Traffic_Red(void);
*/
// extern void LCD_Runnable();
// extern void LCD_Write();
extern void	LCD_Task(void);
extern void Sec_Increment_Task(void);
extern void Write_Date_Time_Task(void);
extern void keypad_runnable(void);

/********************************************************************************************************/
/************************************************Variables***********************************************/
/********************************************************************************************************/
//	LCD
runnableStr_t Loc_arrStrRunnables[MAX_SUPPORTED_TASKS] = {
        [0] = 
        {
            .name = "LCD_Task",
			.first_delayMS = 0,
			.periodicity = 2,
			.priority = 0,
			.callback = LCD_Task
        },

        [1] = 
        {
			.name = "Write_Date_Time_Task",
			.first_delayMS = 50,
			.periodicity = 2,
			.priority = 0,
			.callback = Write_Date_Time_Task
        },

		[2] = 
        {
            .name = "Sec_Increment_Task",
			.first_delayMS = 100,
			.periodicity = 1000,
			.priority = 0,
			.callback = Sec_Increment_Task
        },

		[3] = 
        {
            .name = "Keypad_Task",
			.first_delayMS = 60,
			.periodicity = 6,
			.priority = 0,
			.callback = keypad_runnable
        },

		[4] =
		{
			.name = "UART_RECEIVE_Task",
			.first_delayMS = 60,
			.periodicity = 6,
			.priority = 0,
			.callback = Uart_receive_runnable
		},

		[5] = 
		{
			.name = "Keypad_TRANSMIT_Task",
			.first_delayMS = 60,
			.periodicity = 6,
			.priority = 0,
			.callback = Uart_transmit_runnable
		}

};

//	Traffic_Lights
/*
runnableStr_t Loc_arrStrRunnables[LED_TASKS] = {
        [0] = 
        {
            .name = "green_runnable_1",
			.first_delayMS = 0,
			.periodicity = 500,
			.priority = 0,
			.callback = Traffic_Green
        }

        [1] = 
        {
            .name = "yellow_runnable_2",
			.first_delayMS = 0,
			.periodicity = 1000,
			.priority = 0,
			.callback = Traffic_Yellow
        },
		[2] =
		{
			.name = "red_runnable_3",
			.first_delayMS = 0,
			.periodicity = 3000,
			.priority = 0,
			.callback = Traffic_Red
		}

};
*/


