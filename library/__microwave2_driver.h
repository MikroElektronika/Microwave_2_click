/*
    __microwave2_driver.h

-----------------------------------------------------------------------------

  This file is part of mikroSDK.
  
  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

/**
@file   __microwave2_driver.h
@brief    Microwave2 Driver
@mainpage Microwave2 Click
@{

@image html sch.jpg

@}

@defgroup   MICROWAVE2
@brief      Microwave2 Click Driver
@{

| Global Library Prefix | **MICROWAVE2** |
|:---------------------:|:-----------------:|
| Version               | **1.0.0**    |
| Date                  | **maj 2018.**      |
| Developer             | **Dusan Poluga**     |

*/
/* -------------------------------------------------------------------------- */

#include "stdint.h"

#ifndef _MICROWAVE2_H_
#define _MICROWAVE2_H_

/** 
 * @macro T_MICROWAVE2_P
 * @brief Driver Abstract type 
 */
#define T_MICROWAVE2_P    const uint8_t*

/** @defgroup MICROWAVE2_COMPILE Compilation Config */              /** @{ */

//  #define   __MICROWAVE2_DRV_SPI__                            /**<     @macro __MICROWAVE2_DRV_SPI__  @brief SPI driver selector */
//  #define   __MICROWAVE2_DRV_I2C__                            /**<     @macro __MICROWAVE2_DRV_I2C__  @brief I2C driver selector */                                          
  #define   __MICROWAVE2_DRV_UART__                           /**<     @macro __MICROWAVE2_DRV_UART__ @brief UART driver selector */ 

                                                                       /** @} */
/** @defgroup MICROWAVE2_VAR Variables */                           /** @{ */
extern uint8_t MICROWAVE2_MOVING_AWAY    ;
extern uint8_t MICROWAVE2_MOVING_CLOSER  ;
extern uint8_t MICROWAVE2_STOPPED_MOVING ;

                                                                       /** @} */
/** @defgroup MICROWAVE2_TYPES Types */                             /** @{ */



                                                                       /** @} */
#ifdef __cplusplus
extern "C"{
#endif

/** @defgroup MICROWAVE2_INIT Driver Initialization */              /** @{ */

#ifdef   __MICROWAVE2_DRV_SPI__
void microwave2_spiDriverInit(T_MICROWAVE2_P gpioObj, T_MICROWAVE2_P spiObj);
#endif
#ifdef   __MICROWAVE2_DRV_I2C__
void microwave2_i2cDriverInit(T_MICROWAVE2_P gpioObj, T_MICROWAVE2_P i2cObj, uint8_t slave);
#endif
#ifdef   __MICROWAVE2_DRV_UART__
void microwave2_uartDriverInit(T_MICROWAVE2_P gpioObj, T_MICROWAVE2_P uartObj);
#endif
                                                                       /** @} */
/** @defgroup MICROWAVE2_FUNC Driver Functions */                   /** @{ */

/**
 * @brief Write Single Byte
 *
 * @param[in] input 
 *
 * Writes sinle byte.
 */
void microwave2_writeByte(uint8_t input);

/**
 * @brief Read Single Byte
 *
 * @return received byte
 *
 * Read received byte.
 */
uint8_t microwave2_readByte();

/**
 * @brief Check for new byte received
 *
 * @retval 0 - no new data / 1 - data ready
 *
 * Checks is there a new byte received.
 */
uint8_t microwave2_byteReady();
                                                                       /** @} */
/** 
 This pin will be set to 1 if the object is aproaching.
 */
uint8_t microwave2_daState();

/** 
 This pin will be set to 1 if the object is moving away.
 */
uint8_t microwave2_dlState();

/**
 This function will handle packet's that the click board is sending when
 movement is detected.
 */
void microwave2_uartHandler(uint8_t *packegBuffer, uint8_t rData);

/**
  Function compares received packets and return's the value that 
  can be compared to the predefined one to test if the object is 
  aproaching, has stopped aproaching or moving away from the click board.
  */
uint8_t microwave2_checkTrafic();


#ifdef __cplusplus
} // extern "C"
#endif
#endif

/**
    @example Click_Microwave2_STM.c
    @example Click_Microwave2_TIVA.c
    @example Click_Microwave2_CEC.c
    @example Click_Microwave2_KINETIS.c
    @example Click_Microwave2_MSP.c
    @example Click_Microwave2_PIC.c
    @example Click_Microwave2_PIC32.c
    @example Click_Microwave2_DSPIC.c
    @example Click_Microwave2_AVR.c
    @example Click_Microwave2_FT90x.c
    @example Click_Microwave2_STM.mbas
    @example Click_Microwave2_TIVA.mbas
    @example Click_Microwave2_CEC.mbas
    @example Click_Microwave2_KINETIS.mbas
    @example Click_Microwave2_MSP.mbas
    @example Click_Microwave2_PIC.mbas
    @example Click_Microwave2_PIC32.mbas
    @example Click_Microwave2_DSPIC.mbas
    @example Click_Microwave2_AVR.mbas
    @example Click_Microwave2_FT90x.mbas
    @example Click_Microwave2_STM.mpas
    @example Click_Microwave2_TIVA.mpas
    @example Click_Microwave2_CEC.mpas
    @example Click_Microwave2_KINETIS.mpas
    @example Click_Microwave2_MSP.mpas
    @example Click_Microwave2_PIC.mpas
    @example Click_Microwave2_PIC32.mpas
    @example Click_Microwave2_DSPIC.mpas
    @example Click_Microwave2_AVR.mpas
    @example Click_Microwave2_FT90x.mpas
*/                                                                     /** @} */
/* -------------------------------------------------------------------------- */
/*
  __microwave2_driver.h

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