#include"Keypad.h"

KeyPad_CFG_t KeyPad_CFG[NO_OF_KEYPADS]=
{
    [FIRST_KEYPAD]=
    {
        .KeyPad_Rows_Connection_CFG[Row0]=
        {
            .PORT=GPIO_PORTB,
            .PIN=GPIO_PIN0,
        },
        .KeyPad_Rows_Connection_CFG[Row1]=
        {
            .PORT=GPIO_PORTB,
            .PIN=GPIO_PIN1,
        },
        .KeyPad_Rows_Connection_CFG[Row2]=
        {
            .PORT=GPIO_PORTB,
            .PIN=GPIO_PIN2,
        },
        .KeyPad_Columns_Connection_CFG[Column0]=
        {
            .PORT=GPIO_PORTB,
            .PIN=GPIO_PIN3,
        },
        .KeyPad_Columns_Connection_CFG[Column1]=
        {
            .PORT=GPIO_PORTB,
            .PIN=GPIO_PIN4,
        },
        .KeyPad_Columns_Connection_CFG[Column2]=
        {
            .PORT=GPIO_PORTB,
            .PIN=GPIO_PIN5,
        },
        .ROWS_Default_state=GPIO_MODE_Output,
        .Columns_Default_state=GPIO_MODE_Input,
        .ROWS_Column_Output_state=GPIO_PINSTATE_HIGH
    }

};

