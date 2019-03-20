/*
Example for Microwave2 Click

    Date          : maj 2018.
    Author        : Dusan Poluga

Test configuration PIC :
    
    MCU             : P18F87K22
    Dev. Board      : EasyPIC PRO v7
    PIC Compiler ver : v7.2.0.0

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

uint8_t buf[6]={0,0,0,0,0,0};

void systemInit()
{
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_AN_PIN, _GPIO_INPUT );
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_INT_PIN, _GPIO_INPUT );

    mikrobus_uartInit( _MIKROBUS1, &_MICROWAVE2_UART_CFG[0] );
    mikrobus_logInit( _MIKROBUS3, 9600 );

    Delay_ms( 100 );
}

void applicationInit()
{
    microwave2_uartDriverInit( (T_MICROWAVE2_P)&_MIKROBUS1_GPIO, (T_MICROWAVE2_P)&_MIKROBUS1_UART );
    mikrobus_logWrite( "Initialized", _LOG_LINE );
    Delay_ms( 100 );
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
       mikrobus_logWrite("Approaching",_LOG_LINE);
    }
    if(tmp == MICROWAVE2_STOPPED_MOVING)
    {
       mikrobus_logWrite("No movesment",_LOG_LINE);
    }
    if(tmp == MICROWAVE2_MOVING_AWAY)
    {
       mikrobus_logWrite("Moving away",_LOG_LINE);
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
