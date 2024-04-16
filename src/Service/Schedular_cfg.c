
/* Driver Libraries   */
#include "Schedular_cfg.h"

extern void LCD_Task(void);
extern void Switches(void);
extern void Sec_Increment_Task_For_Date_Time(void);
extern void Sec_Increment_Task_For_Stop_Watch(void);
extern void Write_Date_Time_Task(void);

// extern void Uart_receive_runnable();
// extern void Uart_transmit_runnable();

extern void keypad_runnable(void);

/*ARRAY FOR THE USER TO CONFIGURE THE RUNNABLES*/

runnableStr_t Loc_arrStrRunnables[MAX_SUPPORTED_TASKS] =
{

[0]=
                    {
                        .name="KEYPAD_Runnable",
                        .periodicity=6,
                        .callback=keypad_runnable,
                        .first_delayMS=0,
						.priority = 0
                    }
};

//	demo
/*
runnableStr_t Loc_arrStrRunnables[MAX_SUPPORTED_TASKS] = {
	[0] =
		{
			.name = "Keypad_Task",
			.first_delayMS = 0,
			.periodicity = 6,
			.priority = 0,
			.callback = keypad_runnable},

	[1] =
		{
			.name = "Write_Date_Time_Task",
			.first_delayMS = 50,
			.periodicity = 2,
			.priority = 0,
			.callback = Write_Date_Time_Task},

	[2] =
		{
			.name = "Sec_Increment_Task_For_Date_Time",
			.first_delayMS = 70,
			.periodicity = 1000,
			.priority = 0,
			.callback = Sec_Increment_Task_For_Date_Time},

	[3] =
		{
			.name = "Sec_Increment_Task_For_Stop_Watch",
			.first_delayMS = 350,
			.periodicity = 1000,
			.priority = 0,
			.callback = Sec_Increment_Task_For_Stop_Watch},

	[4] =
		{
			.name = "Keypad_Task",
			.first_delayMS = 90,
			.periodicity = 6,
			.priority = 0,
			.callback = keypad_runnable},
	[5] =
		{
			.name = "Switches_Task",
			.first_delayMS = 300,
			.periodicity = 120,
			.priority = 0,
			.callback = Switches},

	[6] =
		{
			.name = "UART_RECEIVE_Task",
			.first_delayMS = 230,
			.periodicity = 6,
			.priority = 0,
			.callback = Uart_receive_runnable},

	[7] =
		{
			.name = "Keypad_TRANSMIT_Task",
			.first_delayMS = 250,
			.periodicity = 6,
			.priority = 0,
			.callback = Uart_transmit_runnable}

};
*/
