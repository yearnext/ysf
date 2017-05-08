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
 * @file       map_gpio.h                                                      *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-04-21                                                      *
 * @brief      map gpio head files                                             *
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
 * @defgroup gpio component
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F1XX_MAP_GPIO_H__
#define __STM32F1XX_MAP_GPIO_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "core_path.h"
#include _HAL_PATH
    
/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       framework component config flags
 * @note        1                        enable
 * @note        0                        disable
 *******************************************************************************
 */
#ifdef USE_MCU_GPIO_COMPONENT
#if USE_MCU_GPIO_COMPONENT
    #define USE_MAP_GPIO_COMPONENT                                           (1) 
#else
    #define USE_MAP_GPIO_COMPONENT                                           (0)
#endif

/**
 *******************************************************************************
 * @brief       user config flags
 * @note        1         enable
 * @note        0         disable
 *******************************************************************************
 */
#else
    #define USE_MAP_GPIO_COMPONENT                                           (1)
#endif
 
/**
 *******************************************************************************
 * @brief      define gpio port
 *******************************************************************************
 */  

#define  MCU_PORT_A                                                          (0)
#define  MCU_PORT_B                                                          (1)
#define  MCU_PORT_C                                                          (2)
#define  MCU_PORT_D                                                          (3)
#define  MCU_PORT_E                                                          (4)
#define  MCU_PORT_F                                                          (5)
#define  MCU_PORT_G                                                          (6)

/**
 *******************************************************************************
 * @brief      define gpio pin
 *******************************************************************************
 */
#define  MCU_PIN_0                                                           (0)
#define  MCU_PIN_1                                                           (1)
#define  MCU_PIN_2                                                           (2)
#define  MCU_PIN_3                                                           (3)
#define  MCU_PIN_4                                                           (4)
#define  MCU_PIN_5                                                           (5)
#define  MCU_PIN_6                                                           (6)
#define  MCU_PIN_7                                                           (7)
#define  MCU_PIN_8                                                           (8)
#define  MCU_PIN_9                                                           (9)
#define  MCU_PIN_10                                                         (10)
#define  MCU_PIN_11                                                         (11)
#define  MCU_PIN_12                                                         (12)
#define  MCU_PIN_13                                                         (13)
#define  MCU_PIN_14                                                         (14)
#define  MCU_PIN_15                                                         (15)

/**
 *******************************************************************************
 * @brief      define gpio mode
 *******************************************************************************
 */ 
/** gpio mode param dir */
#define GPIO_INPUT                                                        (0x00)
#define GPIO_LOW_SPEED_OUTPUT                                             (0x01)
#define GPIO_MEDIUM_SPEED_OUTPUT                                          (0x02)
#define GPIO_HIGH_SPEED_OUTPUT                                            (0x03)

/** gpio mode param mode */
#define GPIO_INIT_MODE                                                    (0x00)
#define GPIO_IN_ANALOG_MODE                                               (0x40)
#define GPIO_IN_FLOAT_MODE                                                (0x44)
#define GPIO_IN_PULL_DOWN_MODE                                            (0x48)
#define GPIO_IN_PULL_UP_MODE                                              (0x88)
#define GPIO_OUT_PUSH_PULL_MODE                                           (0x40)
#define GPIO_OUT_OPEN_DRAIN_MODE                                          (0x44)
#define GPIO_AF_OUT_PUSH_PULL_MODE                                        (0x48)
#define GPIO_AF_OUT_OPEN_DRAIN_MODE                                       (0x4C)

/** gpio mode param */
#define GPIO_MODE_PARAM(dir, mode)                   ((uint8_t)((dir) | (mode)))

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define map gpio
 *******************************************************************************
 */    
struct Hal_GPIO_Block
{
    uint8_t Port;
    uint8_t Pin;
    uint8_t Mode;
};

/**
 *******************************************************************************
 * @brief      define msp gpio interface
 *******************************************************************************
 */
#if USE_MAP_GPIO_COMPONENT
typedef struct
{
    hal_err_t          (*Open)(uint8_t);
    hal_err_t          (*Close)(uint8_t);
    hal_err_t          (*Init)(uint8_t, uint8_t, uint8_t);
    hal_err_t          (*Fini)(uint8_t, uint8_t);
    
	struct
	{
        hal_err_t      (*Get)(uint8_t, uint8_t, uint8_t*);
	}Input;
	
	struct
	{
        hal_err_t      (*Get)(uint8_t, uint8_t, uint8_t*);
        hal_err_t      (*Set)(uint8_t, uint8_t);
        hal_err_t      (*Clr)(uint8_t, uint8_t);
        hal_err_t      (*Toggle)(uint8_t, uint8_t);
        hal_err_t      (*Cmd)(uint8_t, uint8_t, uint8_t);
	}Output;
}MAP_GPIO_Interface;
#endif

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/*
 *******************************************************************************
 * @brief      define msp gpio api
 *******************************************************************************
 */   
#if USE_MAP_GPIO_COMPONENT
extern hal_err_t MAP_GPIO_Open(uint8_t);
extern hal_err_t MAP_GPIO_Close(uint8_t);
extern hal_err_t MAP_GPIO_Init(uint8_t, uint8_t, uint8_t);
extern hal_err_t MAP_GPIO_Deinit(uint8_t, uint8_t);
extern hal_err_t MAP_GPIO_Set(uint8_t, uint8_t);
extern hal_err_t MAP_GPIO_Clr(uint8_t, uint8_t);
extern hal_err_t MAP_GPIO_GetInputStatus(uint8_t, uint8_t, uint8_t*);
extern hal_err_t MAP_GPIO_GetOutputStatus(uint8_t, uint8_t, uint8_t*);
extern hal_err_t MAP_GPIO_Toggle(uint8_t, uint8_t);
extern hal_err_t MAP_GPIO_OutputCmd(uint8_t, uint8_t, uint8_t);
#endif

#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** gpio component */

/**********************************END OF FILE*********************************/
