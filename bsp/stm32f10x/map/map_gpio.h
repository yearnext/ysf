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
 * @date       2017-08-07                                                      *
 * @brief      mcu application gpio component head files                       *
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
 * @defgroup map gpio component
 * @{
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAP_GPIO_H__
#define __MAP_GPIO_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/  
#include "hal_path.h"
    
/* Exported macro ------------------------------------------------------------*/ 
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

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define gpio mode
 *******************************************************************************
 */ 
enum Define_GPIO_Mode
{
	GPIO_INIT_MODE          = 0x04,
	GPIO_INTPUT_MODE        = 0x00,
	GPIO_OUTPUT_LS_MODE     = 0x01,
	GPIO_OUTPUT_MS_MODE     = 0x02,
	GPIO_OUTPUT_HS_MODE     = 0x03,
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
struct HalGPIODevice
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
struct MspGPIOParam
{
    uint8_t Pos;
    uint8_t Num;
    uint16_t RWData;
};

/* Exported constants --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define map api
 *******************************************************************************
 */ 
extern hal_err_t Map_GPIO_Open(uint8_t);
extern hal_err_t Map_GPIO_Close(uint8_t);
extern hal_err_t Map_GPIO_Init(uint8_t, uint8_t, uint8_t, uint8_t);
extern hal_err_t Map_GPIO_Fini(uint8_t, uint8_t);
extern hal_err_t Map_GPIO_Set(uint8_t, uint8_t);
extern hal_err_t Map_GPIO_Clear(uint8_t, uint8_t);
extern hal_err_t Map_GPIO_GetIntputStatus(uint8_t, uint8_t, uint16_t*);
extern hal_err_t Map_GPIO_GetOutputStatus(uint8_t, uint8_t, uint16_t*);
extern hal_err_t Map_GPIO_Toggle(uint8_t, uint8_t);
extern hal_err_t Map_GPIO_Write(uint8_t, uint8_t, uint16_t, uint8_t);
extern hal_err_t Map_GPIO_Read(uint8_t, uint8_t, uint16_t*, uint8_t);
extern hal_err_t Map_GPIO_Control(struct HalGPIODevice*, uint8_t, void*);

/**
 *******************************************************************************
 * @brief      define hal api
 *******************************************************************************
 */ 
extern __INLINE hal_err_t Hal_GPIO_Open(struct HalGPIODevice*);
extern __INLINE hal_err_t Hal_GPIO_Close(struct HalGPIODevice*);
extern __INLINE hal_err_t Hal_GPIO_Init(struct HalGPIODevice*);
extern __INLINE hal_err_t Hal_GPIO_Fini(struct HalGPIODevice*);
extern __INLINE hal_err_t Hal_GPIO_Set(struct HalGPIODevice*);
extern __INLINE hal_err_t Hal_GPIO_Clear(struct HalGPIODevice*);
extern __INLINE hal_err_t Hal_GPIO_GetIntputStatus(struct HalGPIODevice*, uint16_t*);
extern __INLINE hal_err_t Hal_GPIO_GetOutputStatus(struct HalGPIODevice*, uint16_t*);
extern __INLINE hal_err_t Hal_GPIO_Toggle(struct HalGPIODevice*);
extern __INLINE hal_err_t Hal_GPIO_Write(struct HalGPIODevice*, struct MspGPIOParam*);
extern __INLINE hal_err_t Hal_GPIO_Read(struct HalGPIODevice*, struct MspGPIOParam*);
extern __INLINE hal_err_t Hal_GPIO_Control(struct HalGPIODevice*, uint8_t, void*);

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** map gpio component */

/**********************************END OF FILE*********************************/
