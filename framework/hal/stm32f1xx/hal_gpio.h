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
#include "ysf_path.h"
#include YSF_TYPE_PATH

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define gpio use status
 *******************************************************************************
 */ 
#define USE_MSP_GPIO_API (1)
#define USE_MAP_GPIO_API (1)
 
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
#define PIN_INPUT_MODE              (0x00)
                            
#define PIN_ANALOG_INPUT            (0x00)
#define PIN_FLOAT_INPUT             (0x04)
#define PIN_UP_DOWN_INPUT           (0x08)
   
#define PIN_LOW_SPEED_OUTPUT_MODE   (0x02)
#define PIN_MEDIUM_SPEED_INPUT_MODE (0x01)
#define PIN_HIGH_SPEED_INPUT_MODE   (0x03)
                               
#define PIN_PUSH_PULL_OUTPUT        (0x00)
#define PIN_OPEN_DNAIN_INPUT        (0x04)
#define PIN_AF_PUSH_PULL_INPUT      (0x08)         
#define PIN_AF_OPEN_DNAIN_INPUT     (0x0C)  

enum
{
    GPIO_PIN_INIT_MODE       = 0x04,                                                           /** ��ʼ��ģʽ */
     
    GPIO_PIN_I_A_MODE        = PIN_INPUT_MODE              | PIN_ANALOG_INPUT,                 /** ��������ģʽ */
    GPIO_PIN_I_F_MODE        = PIN_INPUT_MODE              | PIN_FLOAT_INPUT,                  /** ��������ģʽ */
    GPIO_PIN_I_UD_MODE       = PIN_INPUT_MODE              | PIN_UP_DOWN_INPUT,                /** ����/��������ģʽ */
 
    GPIO_PIN_O_PP_LS_MODE    = PIN_LOW_SPEED_OUTPUT_MODE   | PIN_PUSH_PULL_OUTPUT,             /** ����(2 Mhz)�������ģʽ */
    GPIO_PIN_O_OD_LS_MODE    = PIN_LOW_SPEED_OUTPUT_MODE   | PIN_OPEN_DNAIN_INPUT,             /** ����(2 Mhz)��©���ģʽ */
    GPIO_PIN_AF_O_PP_LS_MODE = PIN_LOW_SPEED_OUTPUT_MODE   | PIN_AF_PUSH_PULL_INPUT,           /** ����(2 Mhz)�����������ģʽ */
    GPIO_PIN_AF_O_OD_LS_MODE = PIN_LOW_SPEED_OUTPUT_MODE   | PIN_AF_OPEN_DNAIN_INPUT,          /** ����(2 Mhz)���ÿ�©���ģʽ */

    GPIO_PIN_O_PP_MS_MODE    = PIN_MEDIUM_SPEED_INPUT_MODE | PIN_PUSH_PULL_OUTPUT,             /** ����(10 Mhz)������ģʽ */
    GPIO_PIN_O_OD_MS_MODE    = PIN_MEDIUM_SPEED_INPUT_MODE | PIN_OPEN_DNAIN_INPUT,             /** ����(10 Mhz)��©���ģʽ */
    GPIO_PIN_AF_O_PP_MS_MODE = PIN_MEDIUM_SPEED_INPUT_MODE | PIN_AF_PUSH_PULL_INPUT,           /** ����(10 Mhz)�����������ģʽ */ 
    GPIO_PIN_AF_O_OD_MS_MODE = PIN_MEDIUM_SPEED_INPUT_MODE | PIN_AF_OPEN_DNAIN_INPUT,          /** ����(10 Mhz)���ÿ�©���ģʽ */
     
    GPIO_PIN_O_PP_HS_MODE    = PIN_HIGH_SPEED_INPUT_MODE   | PIN_PUSH_PULL_OUTPUT,             /** ����(50 Mhz)�������ģʽ */
    GPIO_PIN_O_OD_HS_MODE    = PIN_HIGH_SPEED_INPUT_MODE   | PIN_OPEN_DNAIN_INPUT,             /** ����(50 Mhz)��©���ģʽ */
    GPIO_PIN_AF_O_PP_HS_MODE = PIN_HIGH_SPEED_INPUT_MODE   | PIN_AF_PUSH_PULL_INPUT,           /** ����(50 Mhz)�����������ģʽ */
    GPIO_PIN_AF_O_OD_HS_MODE = PIN_HIGH_SPEED_INPUT_MODE   | PIN_AF_OPEN_DNAIN_INPUT,          /** ����(50 Mhz)���ÿ�©���ģʽ */
};
    
/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define gpio type
 *******************************************************************************
 */    
struct map_gpio_t
{
    uint8_t port;
    uint8_t pin;
};
  
/**
 *******************************************************************************
 * @brief      define msp gpio api
 *******************************************************************************
 */   
struct MSP_GPIO_API
{
    void          (*enable)(uint8_t port);
    void          (*disable)(uint8_t port);
    
	struct
	{
        void      (*init)(uint8_t port, uint8_t pin, uint8_t mode);
        
        bool      (*get)(uint8_t port, uint8_t pin);
	}input;
	
	struct
	{
        void      (*init)(uint8_t port, uint8_t pin, uint8_t mode);
        
        bool      (*get)(uint8_t port, uint8_t pin);
        void      (*set)(uint8_t port, uint8_t pin);
        void      (*clr)(uint8_t port, uint8_t pin);
	}output;
    
    struct
    {
        void (*init)(uint8_t port, uint8_t pin, uint8_t mode);
    }multi;
};
  
/**
 *******************************************************************************
 * @brief      define map gpio api
 *******************************************************************************
 */   
struct MAP_GPIO_API
{
    void          (*enable)(struct map_gpio_t*);
    void          (*disable)(struct map_gpio_t*);
    
	struct
	{
        void      (*init)(struct map_gpio_t*, uint8_t mode);
        
        bool      (*get)(struct map_gpio_t*);
	}input;
	
	struct
	{
        void      (*init)(struct map_gpio_t*, uint8_t mode);
        
        bool      (*get)(struct map_gpio_t*);
        void      (*set)(struct map_gpio_t*);
        void      (*clr)(struct map_gpio_t*);
	}output;
    
    struct
    {
        void      (*init)(struct map_gpio_t*, uint8_t mode);
    }multi;
};
    
/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      msp gpio interface
 *******************************************************************************
 */   
#if USE_MSP_GPIO_API
extern void msp_gpio_init(uint8_t);
extern void msp_gpio_fini(uint8_t);
extern void msp_gpio_config(uint8_t, uint8_t, uint8_t);
extern void msp_gpio_set(uint8_t, uint8_t);
extern void msp_gpio_clr(uint8_t, uint8_t);
extern bool msp_gpio_get_input(uint8_t, uint8_t);
extern bool msp_gpio_get_output(uint8_t, uint8_t);
#endif

  
/**
 *******************************************************************************
 * @brief      map gpio interface
 *******************************************************************************
 */   
#if USE_MAP_GPIO_API
extern void map_gpio_init(struct map_gpio_t*);
extern void map_gpio_fini(struct map_gpio_t*);
extern void map_gpio_config(struct map_gpio_t*, uint8_t);
extern void map_gpio_set(struct map_gpio_t*);
extern void map_gpio_clr(struct map_gpio_t*);
extern bool map_gpio_get_input(struct map_gpio_t*);
extern bool map_gpio_get_output(struct map_gpio_t*);
#endif

#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /* gpio component  */

/**********************************END OF FILE*********************************/
