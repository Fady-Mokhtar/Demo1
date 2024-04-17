
/* Driver Libraries   */
#include "Schedular_cfg.h"

extern void LCD_Task(void);
extern void Switches_Of_Keypad(void);
extern void Sec_Increment_Task_For_Date_Time(void);
extern void Sec_Increment_Task_For_Stop_Watch(void);
extern void Write_Date_Time_Task(void);
extern void LCD_Test(void);
extern void keypad_runnable(void);
// extern void Uart_receive_runnable();
// extern void Uart_transmit_runnable();

//	demo

runnableStr_t Loc_arrStrRunnables[MAX_SUPPORTED_TASKS] = {
	[0] =
		{
			.name = "LCD_Task",
			.first_delayMS = 0,
			.periodicity = 2,
			.priority = 0,
			.callback = LCD_Task},

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
			.first_delayMS = 54,
			.periodicity = 1000,
			.priority = 0,
			.callback = Sec_Increment_Task_For_Date_Time},

	[3] =
		{
			.name = "Sec_Increment_Task_For_Stop_Watch",
			.first_delayMS = 56,
			.periodicity = 1000,
			.priority = 0,
			.callback = Sec_Increment_Task_For_Stop_Watch},

	[4] =
		{
			.name = "LCD_Test",
			.first_delayMS = 52,
			.periodicity = 200,
			.priority = 0,
			.callback = LCD_Test},
	[5] =
		{
			.name = "Switches_Task",
			.first_delayMS = 60,
			.periodicity = 150,
			.priority = 0,
			.callback = Switches_Of_Keypad},

	// [6] =
	// 	{
	// 		.name = "UART_RECEIVE_Task",
	// 		.first_delayMS = 230,
	// 		.periodicity = 6,
	// 		.priority = 0,
	// 		.callback = Uart_receive_runnable},

	// [7] =
	// 	{
	// 		.name = "Keypad_TRANSMIT_Task",
	// 		.first_delayMS = 250,
	// 		.periodicity = 6,
	// 		.priority = 0,
	// 		.callback = Uart_transmit_runnable}

};

