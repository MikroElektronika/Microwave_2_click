/*
    __microwave2_driver.c

-----------------------------------------------------------------------------

  This file is part of mikroSDK.

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

#include "__microwave2_driver.h"
#include "__microwave2_hal.c"

/* ------------------------------------------------------------------- MACROS */



/* ---------------------------------------------------------------- VARIABLES */

#ifdef   __MICROWAVE2_DRV_I2C__
static uint8_t _slaveAddress;
#endif

uint8_t MICROWAVE2_MOVING_AWAY    = 1;
uint8_t MICROWAVE2_MOVING_CLOSER  = 2;
uint8_t MICROWAVE2_STOPPED_MOVING = 4;

static uint8_t _comming[6] = {'@','C',13,10,0};
static uint8_t _going[6] = {'@','L',13,10,0};
static uint8_t _nomovement[6] = {'@','N',13,10,0};

static uint8_t _internalSync; //for syncronizing the parser with the incoming data
static uint8_t _arrayCounter; //for setting of the position in the buffer
static uint8_t *_addressHolder;  
/* -------------------------------------------- PRIVATE FUNCTION DECLARATIONS */



/* --------------------------------------------- PRIVATE FUNCTION DEFINITIONS */



/* --------------------------------------------------------- PUBLIC FUNCTIONS */

#ifdef   __MICROWAVE2_DRV_SPI__

void microwave2_spiDriverInit(T_MICROWAVE2_P gpioObj, T_MICROWAVE2_P spiObj)
{
    hal_spiMap( (T_HAL_P)spiObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
}

#endif
#ifdef   __MICROWAVE2_DRV_I2C__

void microwave2_i2cDriverInit(T_MICROWAVE2_P gpioObj, T_MICROWAVE2_P i2cObj, uint8_t slave)
{
    _slaveAddress = slave;
    hal_i2cMap( (T_HAL_P)i2cObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
}

#endif
#ifdef   __MICROWAVE2_DRV_UART__

void microwave2_uartDriverInit(T_MICROWAVE2_P gpioObj, T_MICROWAVE2_P uartObj)
{
    hal_uartMap( (T_HAL_P)uartObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
    _internalSync = 0;
    _arrayCounter = 0;
    _addressHolder = 0;
}

#endif

/* ----------------------------------------------------------- IMPLEMENTATION */

void microwave2_writeByte(uint8_t input)
{
    hal_uartWrite(input);
}

uint8_t microwave2_readByte()
{
    return hal_uartRead();
}

uint8_t microwave2_byteReady()
{
    return hal_uartReady();
}

uint8_t microwave2_daState()
{
    return hal_gpio_anGet();
}

uint8_t microwave2_dlState()
{
    return hal_gpio_intGet();
}

static uint8_t _strcmp(uint8_t *str1, uint8_t *str2)
{
    while( *str1 == *str2 )
    {
      if(*str1 == '\0') 
      {
          return *str1-*str2;
      }
      str1++;
      str2++;
    }
    return 1;
}

uint8_t microwave2_checkTrafic()
{
    uint8_t *_s1;
    uint8_t *_s2;
    if(_s1);
    if(_s2);
    if( _internalSync == 1 )
    {
        _internalSync = 0;
        _s1 = _addressHolder;
        _s2 = &_going[0]; //test if comming
        if( _strcmp(_s1, _s2) == 0 )
        {
                return MICROWAVE2_MOVING_AWAY;
        }

        _s1 = _addressHolder;
        _s2 = &_comming[0]; //test if going
        if( _strcmp(_s1, _s2) == 0 )
        {
                return MICROWAVE2_MOVING_CLOSER;
        }
       
        _s1 = _addressHolder;
        _s2 = &_nomovement[0]; //test if no monvement
        if( _strcmp(_s1, _s2) == 0 )
        {
                return MICROWAVE2_STOPPED_MOVING;
        }
    }
    return 0;
}

void microwave2_uartHandler(uint8_t *packegBuffer, uint8_t rData)
{
    _addressHolder = packegBuffer;
   
    packegBuffer[_arrayCounter] = rData;
    microwave2_writeByte(rData);

    _arrayCounter++;
    if( packegBuffer[0] != '@')
    {
        _arrayCounter = 0;
    }
    if(_arrayCounter == 4  )
    {
      _arrayCounter = 0;
      _internalSync = 1;
    }

}

/* -------------------------------------------------------------------------- */
/*
  __microwave2_driver.c

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

3. All advertising materials mentioning features or use of this software
   must display the following acknowledgement:
   This product includes software developed by the MikroElektonika.

4. Neither the name of the MikroElektonika nor the
   names of its contributors may be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY MIKROELEKTRONIKA ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL MIKROELEKTRONIKA BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------------------------------------------- */