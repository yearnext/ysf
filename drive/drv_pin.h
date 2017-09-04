/**
 *******************************************************************************
 *                       Copyright (C) 2017  yearnext                          *
 *                                                                             *
 *    This program is free software; you can redistribute it and/or modify     *
 *    it under the terms of the GNU General Public License as published by     *
 *    the Free Software Foundation; either version 2 of the License, or        *
 *    (at your option) any later version.                                      *
 *                                                                             *
 *    This program is distributed in the hope that it will be useful,          *
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of           *
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            *
 *    GNU General Public License for more details.                             *
 *                                                                             *
 *    You should have received a copy of the GNU General Public License along  *
 *    with this program; if not, write to the Free Software Foundation, Inc.,  *
 *    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.              *
 *******************************************************************************
 * @file       drv_pin.h                                                       *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-08-30                                                      *
 * @brief      mcu gpio pin driver software head files                         *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         * 
 *******************************************************************************
 * @note                                                                       *
 * 1.XXXXX                                                                     *
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DRIVER_PIN_H__
#define __DRIVER_PIN_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "hal_gpio.h"
#include "hal_timer.h"
#include "hal_device.h"
#include "fw_timer.h"

/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define hal pin driver
 *******************************************************************************
 */ 
struct Hal_Drv_Pin
{
    Hal_Device_t Device;

    //< about pwm param
    uint16_t Duty;
    uint16_t SetDuty;
    
    //< about blink param
    uint8_t BlinkTime;
    uint8_t BlinkTimeN;
    uint8_t BlinkCount;
    
    uint8_t Mode;

    struct Fw_Timer Timer;

    uint8_t OperaDir;
};

/**
 *******************************************************************************
 * @brief      define driver pin mode
 *******************************************************************************
 */ 
enum Drv_Pin_Mode
{
    DRV_PIN_GPIO_MODE,
    DRV_PIN_TIMER_MODE,
};

/* Exported constants --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define hal pin driver interface
 *******************************************************************************
 */ 
extern hal_err_t Drv_Pin_Init(void*);
extern hal_err_t Drv_Pin_Fini(void*);
extern hal_err_t Drv_Pin_Control(void*, uint8_t, va_list);

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif      /** prevent recursive inclusion */

/**********************************END OF FILE*********************************/
