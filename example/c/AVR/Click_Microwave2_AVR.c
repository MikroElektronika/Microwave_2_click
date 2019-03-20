/*
Example for Microwave2 Click

    Date          : maj 2018.
    Author        : Dusan Poluga

Test configuration AVR :
    
    MCU              : ATMEGA32
    Dev. Board       : EasyAVR v7 
    AVR Compiler ver : v7.0.1.0

---

Description :

The application is composed of three sections :

- System Initialization - Initializes GPIO and UART structures.
- Application Initialization - Initializes the click board for communication.
- Application Task - Data sen't from the click board is captured and different 
                     actions are applied.

*/

#include "Click_Microwave2_types.h"
#include "Click_Microwave2_config.h"

char buf[6]={0,0,0,0,0,0};

void systemInit()
{
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_AN_PIN, _GPIO_INPUT );
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_INT_PIN, _GPIO_INPUT );

    mikrobus_uartInit( _MIKROBUS1, &_MICROWAVE2_UART_CFG[0] );
    Delay_ms( 100 );
}

void applicationInit()
{
    microwave2_uartDriverInit( (T_MICROWAVE2_P)&_MIKROBUS1_GPIO, (T_MICROWAVE2_P)&_MIKROBUS1_UART );
    Delay_ms( 100 );
    Lcd_Init();
    Lcd_Cmd(_LCD_CLEAR);
    Lcd_Cmd(_LCD_CURSOR_OFF);
    Lcd_Out(1,1,"Text");
}

void applicationTask()
{   
    char tmp;
    char rDat=0;

    if( microwave2_byteReady() )
    {
        rDat = microwave2_readByte();
        microwave2_uartHandler(&buf[0],rDat);
    }

    tmp = microwave2_checkTrafic();

    if(tmp == MICROWAVE2_MOVING_CLOSER)
    {
         Lcd_Out(2,1,"Approaching ");
    }
    if(tmp == MICROWAVE2_STOPPED_MOVING)
    {
       Lcd_Out(2,1,"No movesment");
    }
    if(tmp == MICROWAVE2_MOVING_AWAY)
    {
       Lcd_Out(2,1,"Moving away ");
    }
}

void main()
{
    systemInit();
    applicationInit();

    while (1)
    {
            applicationTask();
    }
}
