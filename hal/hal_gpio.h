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
#include "hal_core.h"

/* Exported macro ------------------------------------------------------------*/ \
/**
 *******************************************************************************
 * @brief       framework component config flags
 * @note        1                        enable
 * @note        0                        disable
 *******************************************************************************
 */
#ifdef USE_MCU_GPIO_COMPONENT
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
enum Define_GPIO_Port
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
enum Define_GPIO_Pin
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

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define gpio mode
 *******************************************************************************
 */ 
enum Define_GPIO_Mode
{
	GPIO_INIT_MODE          = 0x04,
	GPIO_INTPUT             = 0x00,
	GPIO_LS_OUTPUT          = 0x01,
	GPIO_MS_OUTPUT          = 0x02,
	GPIO_HS_OUTPUT          = 0x03,
	GPIO_ANALOG_MODE        = 0x00,
	GPIO_FLOAT_MODE         = 0x04,
	GPIO_PULL_UP_DOWN_MODE  = 0x08,
	GPIO_PUSH_PULL_MODE     = 0x00,
	GPIO_OPEN_DRAIN_MODE    = 0x04,
	GPIO_AF_PUSH_PULL_MODE  = 0x08,
	GPIO_AF_OPEN_DRAIN_MODE = 0x0C,
};

/** gpio mode param */ 
#define GPIO_MODE(dir, mode)                         ((uint8_t)((dir) | (mode)))

/**
 *******************************************************************************
 * @brief      define gpio cmd
 *******************************************************************************
 */ 
enum Define_GPIO_Cmd
{
    GPIO_CMD_OPEN,
    GPIO_CMD_CLOSE,
    GPIO_CMD_INIT,
    GPIO_CMD_FINI,
    GPIO_CMD_SET,
    GPIO_CMD_RESET,
    GPIO_CMD_GET_INPUT,
    GPIO_CMD_GET_OUTPUT,
    GPIO_CMD_TOGGLE,
    GPIO_CMD_WRITE,
    GPIO_CMD_READ,
};

/**
 *******************************************************************************
 * @brief      define gpio device class
 *******************************************************************************
 */ 
struct Hal_GPIO_Device
{
    uint8_t Port;
    uint8_t Pin;
	uint8_t IO;
    uint8_t Mode;
};

/**
 *******************************************************************************
 * @brief      define gpio rw param
 *******************************************************************************
 */ 
struct Hal_GPIO_Param
{
    uint8_t Pos;
    uint8_t Num;
    uint16_t RWData;
};

/* Exported constants --------------------------------------------------------*/
/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** hal component interface  */

/**********************************END OF FILE*********************************/
