
#include "Keypad.h"

#define NOT_INIT_State 0
#define OPERATIONAL_STATE 1

#define BTN_NOT_PRESSED 0
#define BTN_PRESSED 1

#define DATE_TIME_MODE 0
#define EDIT_MODE 1
#define STOP_WATCH_MODE 2

#define IDLE_MESSAGE 0X01

static uint8_t input = 0;
static uint8_t *PTR_TO_Input = &input;
static uint8_t Keypadstate = NOT_INIT_State;
static uint8_t KeypadCurrentMode = DATE_TIME_MODE;
static uint8_t BTN_state[No_of_Desired_Rows][No_of_Desired_Columns] = {0};

static Keypad_Errorstates_t Keypad_init();
static Keypad_Errorstates_t Keypad_get_value();
static Keypad_Errorstates_t IsPressed(uint8_t Row_No, uint8_t Column_No, uint8_t *switch_current_state);

/*
 * array of two first byte start second byte input from get value send to uart
 *
 */
volatile uint8_t UARTFARME[2] = {0x55, 0};
//uint8_t UARTFARME[1] = &UARTFARME[1];

static const uint8_t keypad_values[No_of_Desired_Rows][No_of_Desired_Columns] = {
    {0x10, 0x70, 0x20},
    {0x50, 0x90, 0x60},
    {0x30, 0x80, 0x40}};
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
        Keypadstate = OPERATIONAL_STATE;
        break;
    case OPERATIONAL_STATE:
        switch (KeypadCurrentMode)
        {
        case DATE_TIME_MODE:
            // LED_SetStatus(LED_1,LED_ON);
            Keypad_get_value();
            if (*PTR_TO_Input == 0x10)
            {
                KeypadCurrentMode = STOP_WATCH_MODE;
                UARTFARME[1] = *PTR_TO_Input;
                // send UARTFRAME
            }
            else if (*PTR_TO_Input == 0x20)
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
            // LED_SetStatus(LED_2,LED_ON);
            Keypad_get_value();
            if (*PTR_TO_Input == 0x10)
            {
                KeypadCurrentMode = DATE_TIME_MODE;
                UARTFARME[1] = *PTR_TO_Input;
            }
            else if (*PTR_TO_Input == 0x30 || *PTR_TO_Input == 0x40)
            {
                UARTFARME[1] = *PTR_TO_Input;
            }
            else
            {
                UARTFARME[1] = IDLE_MESSAGE;
            }
            break;
        case EDIT_MODE:
            // LED_SetStatus(LED_3,LED_ON);
            Keypad_get_value();
            if (*PTR_TO_Input == 0x90)
            {
                UARTFARME[1] = *PTR_TO_Input;
                KeypadCurrentMode = DATE_TIME_MODE;
            }
            else if (*PTR_TO_Input == 0x50 || *PTR_TO_Input == 0x60 || *PTR_TO_Input == 0x70 || *PTR_TO_Input == 0x80)
            {
                UARTFARME[1] = *PTR_TO_Input;
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

extern GPIO_StrCfg_t Keypad_row_pins[__NUM_OF_PINS_KPD_ROWS];
extern GPIO_StrCfg_t Keypad_Column_pins[__NUM_OF_PINS_KPD_COLS];

Keypad_Errorstates_t Keypad_init()
{

    Keypad_Errorstates_t ret_Errorstate = KEYPAD_OK;

    GPIO_Init(&Keypad_row_pins, __NUM_OF_PINS_KPD_ROWS);
    GPIO_Init(&Keypad_Column_pins, __NUM_OF_PINS_KPD_COLS);

    // GPIO_StrCfg_t Keypad_row_pins;
    // GPIO_StrCfg_t Keypad_Column_pins;
    // Keypad_row_pins.speed = GPIO_SPEED_High;
    // Keypad_Column_pins.speed = GPIO_SPEED_High;
    // for (uint8_t LOC_iterartor = 0; LOC_iterartor < NO_OF_KEYPADS; LOC_iterartor++)
    // {
    //     for (uint8_t Nested_LOC_iterartor = 0; Nested_LOC_iterartor < No_of_Desired_Rows; Nested_LOC_iterartor++)
    //     {
    //         Keypad_row_pins.port = KeyPad_CFG[LOC_iterartor].KeyPad_Rows_Connection_CFG[Nested_LOC_iterartor].PORT;
    //         Keypad_row_pins.pin = KeyPad_CFG[LOC_iterartor].KeyPad_Rows_Connection_CFG[Nested_LOC_iterartor].PIN;
    //         Keypad_row_pins.mode = KeyPad_CFG[LOC_iterartor].ROWS_Default_state;
    //         Keypad_Column_pins.port = KeyPad_CFG[LOC_iterartor].KeyPad_Columns_Connection_CFG[Nested_LOC_iterartor].PORT;
    //         Keypad_Column_pins.pin = KeyPad_CFG[LOC_iterartor].KeyPad_Columns_Connection_CFG[Nested_LOC_iterartor].PIN;
    //         Keypad_Column_pins.mode = KeyPad_CFG[LOC_iterartor].Columns_Default_state;
    //     }

    //     if (Keypad_row_pins.mode == GPIO_MODE_Output)
    //     {
    //         GPIO_Init(&Keypad_row_pins, __NUM_OF_PINS_KPD/2);
    //     }
    //     else
    //     {
    //         GPIO_Init(&Keypad_Column_pins, __NUM_OF_PINS_KPD/2);
    //     }
    // }

    return ret_Errorstate;
}
Keypad_Errorstates_t Keypad_get_value()
{

    Keypad_Errorstates_t ret_Errorstate = KEYPAD_OK;
    uint8_t LOC_TEMP = 0;
    uint8_t *ptr_to_local_value = &LOC_TEMP;
    for (uint8_t LOC_iterartor = 0; LOC_iterartor < NO_OF_KEYPADS; LOC_iterartor++)
    {

        for (uint8_t Nested_LOC_iterartor_1 = 0; Nested_LOC_iterartor_1 < No_of_Desired_Rows; Nested_LOC_iterartor_1++)
        {
            for (uint8_t Nested_LOC_iterartor = 0; Nested_LOC_iterartor < No_of_Desired_Rows; Nested_LOC_iterartor++)
            {
                GPIO_SetPinState(KeyPad_CFG[LOC_iterartor].KeyPad_Rows_Connection_CFG[Nested_LOC_iterartor].PORT, KeyPad_CFG[LOC_iterartor].KeyPad_Rows_Connection_CFG[Nested_LOC_iterartor].PIN, GPIO_PINSTATE_LOW);
            }
            GPIO_SetPinState(KeyPad_CFG[LOC_iterartor].KeyPad_Rows_Connection_CFG[Nested_LOC_iterartor_1].PORT, KeyPad_CFG[LOC_iterartor].KeyPad_Rows_Connection_CFG[Nested_LOC_iterartor_1].PIN, GPIO_PINSTATE_HIGH);
            for (uint8_t Nested_LOC_iterartor_2 = 0; Nested_LOC_iterartor_2 < No_of_Desired_Columns; Nested_LOC_iterartor_2++)
            {

                GPIO_GetPinState(KeyPad_CFG[LOC_iterartor].KeyPad_Rows_Connection_CFG[Nested_LOC_iterartor_2].PORT, KeyPad_CFG[LOC_iterartor].KeyPad_Columns_Connection_CFG[Nested_LOC_iterartor_2].PIN, ptr_to_local_value);
                IsPressed(Nested_LOC_iterartor_1, Nested_LOC_iterartor_2, ptr_to_local_value);
            }
        }
    }
    return ret_Errorstate;
}
static Keypad_Errorstates_t IsPressed(uint8_t Row_No, uint8_t Column_No, uint8_t *switch_current_state)
{
    Keypad_Errorstates_t ret_Errorstate = KEYPAD_OK;
    static uint8_t count[No_of_Desired_Rows][No_of_Desired_Columns] = {0};
    static uint8_t past_value[No_of_Desired_Rows][No_of_Desired_Columns] = {0};
    if (*switch_current_state == past_value[Row_No][Column_No])
    {
        count[Row_No][Column_No] = (count[Row_No][Column_No]) + 1;
        BTN_state[Row_No][Column_No] = *switch_current_state;
    }
    else
    {
        count[Row_No][Column_No] = 0;
    }
    if ((count[Row_No][Column_No]) % 5 == 0 && BTN_state[Row_No][Column_No])
    {
        *PTR_TO_Input = keypad_values[Row_No][Column_No];
    }
    past_value[Row_No][Column_No] = *switch_current_state;

    return ret_Errorstate;
}
