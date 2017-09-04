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
 * @file       hal_gpio.h                                                      *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-08-07                                                      *
 * @brief      hal gpio component head files                                   *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         * 
 *******************************************************************************
 * @note                                                                       *
 * 1.XXXXX                                                                     *
 *******************************************************************************
 */
 
/**
 * @defgroup hal gpio component
 * @{
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HAL_GPIO_COMPONENT_H__
#define __HAL_GPIO_COMPONENT_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/  
#include "hal_path.h"
#include "hal_device.h"

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       framework component config flags
 * @note        1                        enable
 * @note        0                        disable
 *******************************************************************************
 */
#ifdef USE_HAL_GPIO_COMPONENT
    #define USE_GPIO_COMPONENT                                               (1)
  
/**
 *******************************************************************************
 * @brief       user config flags
 * @note        1         enable
 * @note        0         disable
 *******************************************************************************
 */
#else
    #define USE_GPIO_COMPONENT                                               (1)
#endif

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define gpio port
 *******************************************************************************
 */  
enum _Hal_GPIO_Port
{
	MCU_PORT_A,
	MCU_PORT_B,
	MCU_PORT_C,
	MCU_PORT_D,
	MCU_PORT_E,
	MCU_PORT_F,
	MCU_PORT_G,
};

/**
 *******************************************************************************
 * @brief      define gpio pin
 *******************************************************************************
 */
enum _Hal_GPIO_Pin
{
	MCU_PIN_0 = 0,
	MCU_PIN_1,
	MCU_PIN_2,
	MCU_PIN_3,
	MCU_PIN_4,
	MCU_PIN_5,
	MCU_PIN_6,
	MCU_PIN_7,
	MCU_PIN_8,
	MCU_PIN_9,
	MCU_PIN_10,
	MCU_PIN_11,
	MCU_PIN_12,
	MCU_PIN_13,
	MCU_PIN_14,
	MCU_PIN_15,
};

/**
 *******************************************************************************
 * @brief      define gpio dir
 *******************************************************************************
 */ 
enum _Hal_GPIO_Dir
{
    GPIO_DIR_INTPUT = 0,
    GPIO_DIR_OUTPUT,
	GPIO_DIR_LS_OUTPUT,
	GPIO_DIR_MS_OUTPUT,
	GPIO_DIR_HS_OUTPUT,
};
     
/**
 *******************************************************************************
 * @brief      define gpio mode
 *******************************************************************************
 */ 
enum _Hal_GPIO_Mode
{
	GPIO_INIT_MODE = 0,
	GPIO_ANALOG_MODE,
	GPIO_FLOAT_MODE,
	GPIO_PULL_UP_DOWN_MODE,
	GPIO_PUSH_PULL_MODE,
	GPIO_OPEN_DRAIN_MODE,
	GPIO_AF_PUSH_PULL_MODE,
	GPIO_AF_OPEN_DRAIN_MODE,
};

/**
 *******************************************************************************
 * @brief      define gpio device class
 *******************************************************************************
 */ 
typedef struct
{
    uint8_t Port;
    uint8_t Pin;
    uint8_t Dir;
    uint8_t Mode;
}Hal_Device_GPIO;

/**
 *******************************************************************************
 * @brief      define mcu application pack gpio opera interface
 *******************************************************************************
 */ 
struct Map_GPIO_Opera
{
    void (*Open)(uint8_t);
    void (*Close)(uint8_t);
    
    void (*Init)(uint8_t, uint8_t, uint8_t, uint8_t);
    void (*Fini)(uint8_t, uint8_t);
   
    hal_err_t (*Write)(uint8_t, uint8_t, uint16_t, uint8_t);
    hal_err_t (*Read)(uint8_t, uint8_t, uint8_t, uint16_t*, uint8_t);
    
    void (*Toggle)(uint8_t, uint8_t);
};

/* Exported constants --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define hal gpio interface
 *******************************************************************************
 */ 
#ifdef USE_HAL_DEVICE_COMPONENT
extern const struct Hal_Interface Hal_GPIO_Interface;
#endif

/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define hal gpio interface
 *******************************************************************************
 */
#if USE_GPIO_COMPONENT
extern hal_err_t Hal_GPIO_Interface_Init(void*);
extern hal_err_t Hal_GPIO_Interface_Fini(void*);
extern hal_err_t Hal_GPIO_Interface_Control(void*, uint8_t, va_list);
#endif

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** hal component interface  */

/**********************************END OF FILE*********************************/
