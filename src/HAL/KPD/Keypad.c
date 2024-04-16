
#include"port.h"
#include"Keypad_cfg.h"
#include"Keypad.h"
#include"led.h"

#define NOT_INIT_State 0
#define OPERATIONAL_STATE 1

#define BTN_NOT_PRESSED 0
#define BTN_PRESSED 1

#define DATE_TIME_MODE 0
#define STOP_WATCH_MODE 3




static u8 input = 0;
static u8 *PTR_TO_Input = &input;
static u8 Keypadstate = NOT_INIT_State;
static u8 KeypadCurrentMode = DATE_TIME_MODE;
static u8 BTN_state[No_of_Desired_Rows][No_of_Desired_Columns] = {0};

static Keypad_Errorstates_t Keypad_init();
static Keypad_Errorstates_t Keypad_get_value();
static Keypad_Errorstates_t IsPressed(u8 keypad_num,u8 Row_No,u8 Column_No,u32 *switch_current_state);

/*
 * array of two first byte start second byte input from get value send to uart
 *
 */
volatile u8 UARTFARME[2] = {START_OF_FRAME, IDLE_MESSAGE};
//uint8_t UARTFARME[1] = &UARTFARME[1];

static const u8 keypad_values[No_of_Desired_Rows][No_of_Desired_Columns] = {
    {CHANGE_MODE, INCREMENT, EDIT_MODE},
    {RIGHT, OK, LEFT},
    {START, DECREMENT, STOP}};
/*
        btns layout={MODE,INCREMENT,EDIT},
                    {RIGHT,OK,LEFT},
                    {BEGIN,DECREMENT,STOP}
*/
extern KeyPad_CFG_t KeyPad_CFG[NO_OF_KEYPADS];
void keypad_runnable(void)
{
    switch (Keypadstate)
    {
    case NOT_INIT_State:
        Keypad_init();
        LED_Init();
        Keypadstate = OPERATIONAL_STATE;
        break;
    case OPERATIONAL_STATE:
   
        switch (KeypadCurrentMode)
        {
        case DATE_TIME_MODE:
            LED_SetStatus(LED_1, LED_ON);
              LED_SetStatus(LED_2, LED_OFF);
             LED_SetStatus(LED_3, LED_OFF);
              LED_SetStatus(LED_4, LED_OFF);
            Keypad_get_value();
            if (*PTR_TO_Input == CHANGE_MODE)
            {
                KeypadCurrentMode = STOP_WATCH_MODE;
                UARTFARME[1] = *PTR_TO_Input;
                // send UARTFRAME
            }
            else if (*PTR_TO_Input == EDIT_MODE)
            {
                KeypadCurrentMode = EDIT_MODE;
                UARTFARME[1] = *PTR_TO_Input;
            }
            else
            {
                UARTFARME[1] = IDLE_MESSAGE;
            }
            break;
        case STOP_WATCH_MODE:
            LED_SetStatus(LED_1, LED_OFF);
              LED_SetStatus(LED_2, LED_ON);
             LED_SetStatus(LED_3, LED_OFF);
              LED_SetStatus(LED_4, LED_OFF);
            Keypad_get_value();
            if (*PTR_TO_Input == CHANGE_MODE)
            {
                KeypadCurrentMode = DATE_TIME_MODE;
                UARTFARME[1] = *PTR_TO_Input;
            }
            else if (*PTR_TO_Input == START || *PTR_TO_Input == STOP)
            {
                UARTFARME[1] = *PTR_TO_Input;
            }
            else
            {
                UARTFARME[1] = IDLE_MESSAGE;
            }
            break;
        case EDIT_MODE:
            LED_SetStatus(LED_1, LED_OFF);
            LED_SetStatus(LED_2, LED_OFF);
            LED_SetStatus(LED_3, LED_ON);
            LED_SetStatus(LED_4, LED_OFF);
            // LED_SetStatus(LED_3,LED_ON);
            Keypad_get_value();
            if (*PTR_TO_Input == OK)
            {
                UARTFARME[1] = *PTR_TO_Input;
                KeypadCurrentMode = DATE_TIME_MODE;
            }
            else if (*PTR_TO_Input == LEFT || *PTR_TO_Input == RIGHT || *PTR_TO_Input == INCREMENT || *PTR_TO_Input == DECREMENT)
            {
                UARTFARME[1] = *PTR_TO_Input;
                LED_SetStatus(LED_4, LED_ON);
            }
            else
            {
                UARTFARME[1] = IDLE_MESSAGE;
            }
            break;
        default:
            UARTFARME[1] = IDLE_MESSAGE;
            break;
        }

    default:
        break;
    }
}

Keypad_Errorstates_t Keypad_init()
{
    
    Keypad_Errorstates_t ret_Errorstate=KEYPAD_OK;
    GPIO_PinConfig_t Keypad_row_pins;
    GPIO_PinConfig_t Keypad_Column_pins; 
    Keypad_row_pins.Speed=GPIO_HIGH_SPEED;
    Keypad_Column_pins.Speed=GPIO_HIGH_SPEED; 
    for(u8 LOC_iterartor=0;LOC_iterartor<NO_OF_KEYPADS;LOC_iterartor++)
    {
        for(u8 Nested_LOC_iterartor=0;Nested_LOC_iterartor<No_of_Desired_Rows;Nested_LOC_iterartor++)
        {
           Keypad_row_pins.Port=KeyPad_CFG[LOC_iterartor].KeyPad_Rows_Connection_CFG[Nested_LOC_iterartor].PORT;
           Keypad_row_pins.Pin=KeyPad_CFG[LOC_iterartor].KeyPad_Rows_Connection_CFG[Nested_LOC_iterartor].PIN;
           Keypad_row_pins.Mode=KeyPad_CFG[LOC_iterartor].ROWS_Default_state;
           Keypad_Column_pins.Port=KeyPad_CFG[LOC_iterartor].KeyPad_Columns_Connection_CFG[Nested_LOC_iterartor].PORT;
           Keypad_Column_pins.Pin=KeyPad_CFG[LOC_iterartor].KeyPad_Columns_Connection_CFG[Nested_LOC_iterartor].PIN;
           Keypad_Column_pins.Mode=KeyPad_CFG[LOC_iterartor].Columns_Default_state;
           if(Keypad_row_pins.Mode==GPIO_OUTPUT_PP)
           {
            GPIO_InitPin(&Keypad_row_pins);
            GPIO_Set_PinValue(Keypad_row_pins.Port,Keypad_row_pins.Pin,KeyPad_CFG[LOC_iterartor].ROWS_Column_Output_state);
           }
           else
           {
            GPIO_InitPin(&Keypad_row_pins);
           }
            if(Keypad_Column_pins.Mode==GPIO_OUTPUT_PP)
           {
            GPIO_InitPin(&Keypad_Column_pins);
            GPIO_Set_PinValue(Keypad_Column_pins.Port,Keypad_Column_pins.Pin,KeyPad_CFG[LOC_iterartor].ROWS_Column_Output_state);
           }
           else
           {
            GPIO_InitPin(&Keypad_Column_pins);
           }

        }

    }
    
    return ret_Errorstate;
}
Keypad_Errorstates_t Keypad_get_value()
{
  
    Keypad_Errorstates_t ret_Errorstate=KEYPAD_OK; 
    u32 LOC_TEMP=0;
    u32 *ptr_to_local_value=&LOC_TEMP;
    for(u8 LOC_iterartor=0;LOC_iterartor<NO_OF_KEYPADS;LOC_iterartor++)
    {
        
        for(u8 Nested_LOC_iterartor_1=0;Nested_LOC_iterartor_1<No_of_Desired_Rows;Nested_LOC_iterartor_1++)
        {
            for(u8 Nested_LOC_iterartor=0;Nested_LOC_iterartor<No_of_Desired_Rows;Nested_LOC_iterartor++)
            {
                GPIO_Set_PinValue(KeyPad_CFG[LOC_iterartor].KeyPad_Rows_Connection_CFG[Nested_LOC_iterartor].PORT,KeyPad_CFG[LOC_iterartor].KeyPad_Rows_Connection_CFG[Nested_LOC_iterartor].PIN,GPIO_LOW);
            }
            GPIO_Set_PinValue(KeyPad_CFG[LOC_iterartor].KeyPad_Rows_Connection_CFG[Nested_LOC_iterartor_1].PORT,KeyPad_CFG[LOC_iterartor].KeyPad_Rows_Connection_CFG[Nested_LOC_iterartor_1].PIN,GPIO_HIGH);
            for ( u8 Nested_LOC_iterartor_2=0; Nested_LOC_iterartor_2<No_of_Desired_Columns;Nested_LOC_iterartor_2++)
            {

                GPIO_GetPinValue(KeyPad_CFG[LOC_iterartor].KeyPad_Rows_Connection_CFG[Nested_LOC_iterartor_2].PORT,KeyPad_CFG[LOC_iterartor].KeyPad_Columns_Connection_CFG[Nested_LOC_iterartor_2].PIN,ptr_to_local_value);
                IsPressed(LOC_iterartor,Nested_LOC_iterartor_1,Nested_LOC_iterartor_2,ptr_to_local_value);
            }
         }
    }
    return ret_Errorstate;
}
static Keypad_Errorstates_t IsPressed(u8 keypad_num,u8 Row_No,u8 Column_No,u32 *switch_current_state)
{
    Keypad_Errorstates_t ret_Errorstate=KEYPAD_OK;
    static u8 count[No_of_Desired_Rows][No_of_Desired_Columns]={0};
    static u8 past_value[No_of_Desired_Rows][No_of_Desired_Columns]={0};
    if(*switch_current_state==past_value[Row_No][Column_No])
    {
        count[Row_No][Column_No]=(count[Row_No][Column_No])+1;
        BTN_state[Row_No][Column_No]=*switch_current_state;
    }
    else
    {
       count[Row_No][Column_No]=0;
       *PTR_TO_Input=IDLE_MESSAGE;
    }
    if((count[Row_No][Column_No])%5==0&&BTN_state[Row_No][Column_No])
    {
        *PTR_TO_Input=keypad_values[Row_No][Column_No];
    }
    past_value[Row_No][Column_No]=*switch_current_state;

    return ret_Errorstate;
}


