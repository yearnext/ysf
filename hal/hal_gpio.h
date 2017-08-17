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
enum
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
enum
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
 * @brief      define gpio dir
 *******************************************************************************
 */ 
enum
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
enum
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
 * @brief      define gpio cmd
 *******************************************************************************
 */ 
enum
{
    HAL_GPIO_CMD_OPEN = 0,
    HAL_GPIO_CMD_CLOSE,
    HAL_GPIO_CMD_INIT,
    HAL_GPIO_CMD_FINI,
    HAL_GPIO_CMD_SET,
    HAL_GPIO_CMD_CLEAR,
    HAL_GPIO_CMD_GET_INTPUT,
    HAL_GPIO_CMD_GET_OUTPUT,
    HAL_GPIO_CMD_TOGGLE,
    HAL_GPIO_CMD_WRITE,
    HAL_GPIO_CMD_READ,
};

/**
 *******************************************************************************
 * @brief      define gpio device class
 *******************************************************************************
 */ 
struct Hal_GPIO_Opera;
struct Hal_GPIO_Device
{
    uint8_t Port;
    uint8_t Pin;
    uint8_t Dir;
    uint8_t Mode;
    
    struct Hal_GPIO_Opera *Opera;
};

/**
 *******************************************************************************
 * @brief      define gpio rw param
 *******************************************************************************
 */ 
struct Hal_GPIO_Config
{
    uint8_t Dir;
    uint8_t Mode;
    uint8_t Num;
    uint16_t RWData;
};

/**
 *******************************************************************************
 * @brief      define gpio opera interface
 *******************************************************************************
 */ 
struct Hal_GPIO_Opera
{
    void (*Open)(struct Hal_GPIO_Device*);
    void (*Close)(struct Hal_GPIO_Device*);
    
    void (*Init)(struct Hal_GPIO_Device*, void*);
    void (*Fini)(struct Hal_GPIO_Device*);
    
    void (*Set)(struct Hal_GPIO_Device*);
    void (*Clr)(struct Hal_GPIO_Device*);
    void (*Toggle)(struct Hal_GPIO_Device*);

    bool (*GetIntput)(struct Hal_GPIO_Device*);
    bool (*GetOutput)(struct Hal_GPIO_Device*);
        
    void (*Write)(struct Hal_GPIO_Device*, uint8_t*, uint8_t);
    void (*Read)(struct Hal_GPIO_Device*, uint8_t*, uint8_t);
    
    void (*Control)(struct Hal_GPIO_Device*, uint8_t, void*);
};

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
   
    void (*Write)(uint8_t, uint8_t, uint16_t, uint8_t);
    void (*Read)(uint8_t, uint8_t, uint8_t, uint16_t*, uint8_t);
};

/* Exported constants --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define hal gpio interface
 *******************************************************************************
 */
#if USE_GPIO_COMPONENT
extern __INLINE void Hal_GPIO_Module_Register(void);
extern __INLINE void Hal_GPIO_Open(struct Hal_GPIO_Device*);
extern __INLINE void Hal_GPIO_Close(struct Hal_GPIO_Device*);
extern __INLINE void Hal_GPIO_Init(struct Hal_GPIO_Device*, void*);
extern __INLINE void Hal_GPIO_Fini(struct Hal_GPIO_Device*);
extern __INLINE void Hal_GPIO_Write(struct Hal_GPIO_Device*, uint8_t*, uint8_t);
extern __INLINE void Hal_GPIO_Read(struct Hal_GPIO_Device*, uint8_t*, uint8_t);
extern __INLINE void Hal_GPIO_Set(struct Hal_GPIO_Device*);
extern __INLINE void Hal_GPIO_Clr(struct Hal_GPIO_Device*);
extern __INLINE bool Hal_GPIO_GetIntputStatus(struct Hal_GPIO_Device*);
extern __INLINE bool Hal_GPIO_GetOutputStatus(struct Hal_GPIO_Device*);
extern __INLINE void Hal_GPIO_Toggle(struct Hal_GPIO_Device*);
extern __INLINE void Hal_GPIO_Control(struct Hal_GPIO_Device*, uint8_t, void*);
#endif

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** hal component interface  */

/**********************************END OF FILE*********************************/
