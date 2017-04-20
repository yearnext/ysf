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
 * @date       2017-03-04                                                      *
 * @brief      gpio head files                                                 *
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
#ifndef __STM32F1XX_GPIO_H__
#define __STM32F1XX_GPIO_H__

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
    #define USE_MSP_GPIO_COMPONENT                                           (1)
    #define USE_MAP_GPIO_COMPONENT                                           (1)  
#else
    #define USE_MSP_GPIO_COMPONENT                                           (0)
    #define USE_MAP_GPIO_COMPONENT                                           (0)  
#endif

//#if USE_HAL_DEBUG
//    #define USE_HAL_GPIO_DEBUG                                               (1)
//#else
//    #define USE_HAL_GPIO_DEBUG                                               (0)
//#endif
//    
/**
 *******************************************************************************
 * @brief       user config flags
 * @note        1         enable
 * @note        0         disable
 *******************************************************************************
 */
#else
    #define USE_MSP_GPIO_COMPONENT                                           (1)
    #define USE_MAP_GPIO_COMPONENT                                           (1)  
//    #define USE_HAL_GPIO_DEBUG                                               (1)
#endif
 
/**
 *******************************************************************************
 * @brief      define gpio port
 *******************************************************************************
 */  
enum
{    
    MCU_PORT_A = 0,
    MCU_PORT_B = 1,
    MCU_PORT_C = 2,
    MCU_PORT_D = 3,
    MCU_PORT_E = 4,
    MCU_PORT_F = 5,
    MCU_PORT_G = 6,

    MCU_PORT_0 = 0,
    MCU_PORT_1 = 1,
    MCU_PORT_2 = 2,
    MCU_PORT_3 = 3,
    MCU_PORT_4 = 4,
    MCU_PORT_5 = 5,
    MCU_PORT_6 = 6,
};

/**
 *******************************************************************************
 * @brief      define gpio pin
 *******************************************************************************
 */
enum
{    
    MCU_PIN_0  = 0,
    MCU_PIN_1  = 1,
    MCU_PIN_2  = 2,
    MCU_PIN_3  = 3,
    MCU_PIN_4  = 4,
    MCU_PIN_5  = 5,
    MCU_PIN_6  = 6,
    MCU_PIN_7  = 7,
    MCU_PIN_8  = 8,
    MCU_PIN_9  = 9,
    MCU_PIN_10 = 10,
    MCU_PIN_11 = 11,
    MCU_PIN_12 = 12,
    MCU_PIN_13 = 13,
    MCU_PIN_14 = 14,
    MCU_PIN_15 = 15,
};

/**
 *******************************************************************************
 * @brief      define gpio mode
 *******************************************************************************
 */    
#define PIN_INPUT_MODE                                                    (0x00)
                            
#define PIN_ANALOG_INPUT                                                  (0x00)
#define PIN_FLOAT_INPUT                                                   (0x04)
#define PIN_UP_DOWN_INPUT                                                 (0x08)
   
#define PIN_LOW_SPEED_OUTPUT_MODE                                         (0x02)
#define PIN_MEDIUM_SPEED_INPUT_MODE                                       (0x01)
#define PIN_HIGH_SPEED_INPUT_MODE                                         (0x03)
                               
#define PIN_PUSH_PULL_OUTPUT                                              (0x00)
#define PIN_OPEN_DNAIN_INPUT                                              (0x04)
#define PIN_AF_PUSH_PULL_INPUT                                            (0x08)         
#define PIN_AF_OPEN_DNAIN_INPUT                                           (0x0C)  

enum
{
    GPIO_PIN_INIT_MODE       = 0x04,                                                           /** 初始化模式 */
     
    GPIO_PIN_I_A_MODE        = PIN_INPUT_MODE              | PIN_ANALOG_INPUT,                 /** 浮空输入模式 */
    GPIO_PIN_I_F_MODE        = PIN_INPUT_MODE              | PIN_FLOAT_INPUT,                  /** 浮点输入模式 */
    GPIO_PIN_I_UD_MODE       = PIN_INPUT_MODE              | PIN_UP_DOWN_INPUT,                /** 上拉/下拉输入模式 */
 
    GPIO_PIN_O_PP_LS_MODE    = PIN_LOW_SPEED_OUTPUT_MODE   | PIN_PUSH_PULL_OUTPUT,             /** 低速(2 Mhz)推挽输出模式 */
    GPIO_PIN_O_OD_LS_MODE    = PIN_LOW_SPEED_OUTPUT_MODE   | PIN_OPEN_DNAIN_INPUT,             /** 低速(2 Mhz)开漏输出模式 */
    GPIO_PIN_AF_O_PP_LS_MODE = PIN_LOW_SPEED_OUTPUT_MODE   | PIN_AF_PUSH_PULL_INPUT,           /** 低速(2 Mhz)复用推挽输出模式 */
    GPIO_PIN_AF_O_OD_LS_MODE = PIN_LOW_SPEED_OUTPUT_MODE   | PIN_AF_OPEN_DNAIN_INPUT,          /** 低速(2 Mhz)复用开漏输出模式 */

    GPIO_PIN_O_PP_MS_MODE    = PIN_MEDIUM_SPEED_INPUT_MODE | PIN_PUSH_PULL_OUTPUT,             /** 中速(10 Mhz)推挽输模式 */
    GPIO_PIN_O_OD_MS_MODE    = PIN_MEDIUM_SPEED_INPUT_MODE | PIN_OPEN_DNAIN_INPUT,             /** 中速(10 Mhz)开漏输出模式 */
    GPIO_PIN_AF_O_PP_MS_MODE = PIN_MEDIUM_SPEED_INPUT_MODE | PIN_AF_PUSH_PULL_INPUT,           /** 中速(10 Mhz)复用推挽输出模式 */ 
    GPIO_PIN_AF_O_OD_MS_MODE = PIN_MEDIUM_SPEED_INPUT_MODE | PIN_AF_OPEN_DNAIN_INPUT,          /** 中速(10 Mhz)复用开漏输出模式 */
     
    GPIO_PIN_O_PP_HS_MODE    = PIN_HIGH_SPEED_INPUT_MODE   | PIN_PUSH_PULL_OUTPUT,             /** 高速(50 Mhz)推挽输出模式 */
    GPIO_PIN_O_OD_HS_MODE    = PIN_HIGH_SPEED_INPUT_MODE   | PIN_OPEN_DNAIN_INPUT,             /** 高速(50 Mhz)开漏输出模式 */
    GPIO_PIN_AF_O_PP_HS_MODE = PIN_HIGH_SPEED_INPUT_MODE   | PIN_AF_PUSH_PULL_INPUT,           /** 高速(50 Mhz)复用推挽输出模式 */
    GPIO_PIN_AF_O_OD_HS_MODE = PIN_HIGH_SPEED_INPUT_MODE   | PIN_AF_OPEN_DNAIN_INPUT,          /** 高速(50 Mhz)复用开漏输出模式 */
};
    
/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define msp gpio interface
 *******************************************************************************
 */
#if USE_MSP_GPIO_COMPONENT
typedef struct
{
    hal_err_t          (*Enable)(uint8_t);
    hal_err_t          (*Disable)(uint8_t);
    
	struct
	{
        hal_err_t      (*Init)(uint8_t, uint8_t, uint8_t);
        hal_err_t      (*Fini)(uint8_t, uint8_t);
        
        hal_err_t      (*Get)(uint8_t, uint8_t, uint8_t*);
	}Input;
	
	struct
	{
        hal_err_t      (*Init)(uint8_t, uint8_t, uint8_t);
        hal_err_t      (*Fini)(uint8_t, uint8_t);
        
        hal_err_t      (*Get)(uint8_t, uint8_t, uint8_t*);
        hal_err_t      (*Set)(uint8_t, uint8_t);
        hal_err_t      (*Clr)(uint8_t, uint8_t);
	}Output;
    
    struct
    {
        hal_err_t      (*Init)(uint8_t, uint8_t, uint8_t);
        hal_err_t      (*Fini)(uint8_t, uint8_t);
    }Multi;
}MspGPIOInterface;
#endif

/**
 *******************************************************************************
 * @brief      define map gpio
 *******************************************************************************
 */    
struct HalGPIOBlock
{
    uint8_t Port;
    uint8_t Pin;
    uint8_t Mode;
};
  
/**
 *******************************************************************************
 * @brief      define map gpio interface
 *******************************************************************************
 */ 
#if USE_MAP_GPIO_COMPONENT
typedef struct
{
    hal_err_t          (*Enable)(struct HalGPIOBlock*);
    hal_err_t          (*Disable)(struct HalGPIOBlock*);
    
	struct
	{
        hal_err_t      (*Init)(struct HalGPIOBlock*);
        hal_err_t      (*Fini)(struct HalGPIOBlock*);
        
        hal_err_t      (*Get)(struct HalGPIOBlock*, uint8_t*);
	}Input;
	
	struct
	{
        hal_err_t      (*Init)(struct HalGPIOBlock*);
        hal_err_t      (*Fini)(struct HalGPIOBlock*);
        
        hal_err_t      (*Get)(struct HalGPIOBlock*, uint8_t*);
        hal_err_t      (*Set)(struct HalGPIOBlock*);
        hal_err_t      (*Clr)(struct HalGPIOBlock*);
        hal_err_t      (*Toggle)(struct HalGPIOBlock*);
	}Output;
    
    struct
    {
        hal_err_t      (*Init)(struct HalGPIOBlock*);
        hal_err_t      (*Fini)(struct HalGPIOBlock*);
    }Multi;
}HalGPIOInterface;
#endif  

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/*
 *******************************************************************************
 * @brief      define msp gpio api
 *******************************************************************************
 */   
#if USE_MSP_GPIO_COMPONENT
extern hal_err_t MspEnableGPIO(uint8_t);
extern hal_err_t MspDisableGPIO(uint8_t);
extern hal_err_t MspInitGPIO(uint8_t, uint8_t, uint8_t);
extern hal_err_t MspDeinitGPIO(uint8_t, uint8_t);
extern hal_err_t MspSetGPIO(uint8_t, uint8_t);
extern hal_err_t MspClrGPIO(uint8_t, uint8_t);
extern hal_err_t MspGetGPIOInputStatus(uint8_t, uint8_t, uint8_t*);
extern hal_err_t MspGetGPIOOutputStatus(uint8_t, uint8_t, uint8_t*);
#endif

  
/**
 *******************************************************************************
 * @brief      define map gpio api
 *******************************************************************************
 */   
#if USE_MAP_GPIO_COMPONENT
extern hal_err_t HalEnableGPIO(struct HalGPIOBlock*);
extern hal_err_t HalDisableGPIO(struct HalGPIOBlock*);
extern hal_err_t HalInitGPIO(struct HalGPIOBlock*);
extern hal_err_t HalDeinitGPIO(struct HalGPIOBlock*);
extern hal_err_t HalSetGPIO(struct HalGPIOBlock*);
extern hal_err_t HalClrGPIO(struct HalGPIOBlock*);
extern hal_err_t HalToggleGPIO(struct HalGPIOBlock*);
extern hal_err_t HalGetGPIOInputStatus(struct HalGPIOBlock*, uint8_t*);
extern hal_err_t HalGetGPIOOutputStatus(struct HalGPIOBlock*, uint8_t*);
#endif

#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** gpio component */

/**********************************END OF FILE*********************************/
