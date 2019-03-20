/*
Example for Microwave2 Click

    Date          : maj 2018.
    Author        : Dusan Poluga

Test configuration CEC :
    
    MCU              : CEC1702
    Dev. Board       : Clicker 2 for CEC1702
    ARM Compiler ver : v6.0.0.0

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

uint8_t tmp;

void systemInit()
{
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_AN_PIN, _GPIO_INPUT );
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_INT_PIN, _GPIO_INPUT );

    mikrobus_uartInit( _MIKROBUS1, &_MICROWAVE2_UART_CFG[0] );
    mikrobus_logInit( _MIKROBUS2, 9600 );

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
    tmp.B0 = microwave2_daState();
    tmp.B1 = microwave2_dlState();

    if( tmp.B0 )
    {
       mikrobus_logWrite("Approaching",_LOG_LINE);
       tmp.B2 = 1;
       while(microwave2_daState());
    }
    if( tmp.B1 )
    {
       mikrobus_logWrite("Moving away",_LOG_LINE);
       tmp.B3 = 1;
       while( microwave2_dlState() );
    }
    if( !tmp.B0 & tmp.B2 )
    {
       tmp.B2 = 0;
       mikrobus_logWrite("No movesment",_LOG_LINE);
    }
    if( !tmp.B1 &  tmp.B3 )
    {
       tmp.B3 = 0;
       mikrobus_logWrite("No movesment",_LOG_LINE);
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
