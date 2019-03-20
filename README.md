![MikroE](http://www.mikroe.com/img/designs/beta/logo_small.png)

---

# Microwave2 Click

- **CIC Prefix**  : MICROWAVE2
- **Author**      : Dusan Poluga
- **Verison**     : 1.0.0
- **Date**        : maj 2018.

---

### Software Support

We provide a library for the Microwave2 Click on our [LibStock](https://libstock.mikroe.com/projects/view/2423/microwave-2-click) 
page, as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). The demo can run on all the main 
MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

**Library Description**

This library provides generic functions for communication with the click board.

Key functions :

- ``` uint8_t microwave2_readByte(); ``` - Function for reading a byte of data from the serial port.
- ``` uint8_t microwave2_byteReady(); ``` - Function for testing if a byte has been received from the click board.
- ``` void microwave2_uartHandler(uint8_t *packegBuffer, uint8_t rData); ``` - Handler function for byte's received from the click board.
- ``` uint8_t microwave2_checkTrafic(); ``` - Function will give different return values depending on the data handled in the handler function.

**Examples Description**

Description :

The application is composed of three sections :

- System Initialization - Initializes GPIO and UART structures.
- Application Initialization - Initializes the click board for communication.
- Application Task - Data sen't from the click board is captured and different 
                     actions are applied.


```.c
void applicationTask()
{
    char tmp;
    char rDat;

    if( microwave2_byteReady() )
    {
        rDat=microwave2_readByte();
        microwave2_uartHandler(&buf,rDat);
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
```

The full application code, and ready to use projects can be found on our 
[LibStock](https://libstock.mikroe.com/projects/view/2423/microwave-2-click) page.

Other mikroE Libraries used in the example:

- UART Library

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.

---
---
