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
 * @file       msp_usart.h                                                     *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-04-22                                                      *
 * @brief      msp usart head files                                            *
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
 * @defgroup usart component
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F10X_MSP_USART_H__
#define __STM32F10X_MSP_USART_H__

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
#ifdef USE_MCU_USART_COMPONENT
#if USE_MCU_USART_COMPONENT
    #define USE_MSP_USART_COMPONENT                                          (1)
#else
    #define USE_MSP_USART_COMPONENT                                          (0) 
#endif
    
/**
 *******************************************************************************
 * @brief       user config flags
 * @note        1         enable
 * @note        0         disable
 *******************************************************************************
 */
#else
    #define USE_MSP_USART_COMPONENT                                          (1)
#endif
     
#define MCU_DEBUG_USART                                             MCU_USART_0

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define usart id
 *******************************************************************************
 */
enum
{
    MCU_USART_0 = 0,
    MCU_USART_1,
    MCU_USART_2,
    MCU_USART_3,
    MCU_USART_4,
    MCU_USART_5,

    MCU_USART_MAX,
};

/**
 *******************************************************************************
 * @brief       define map timer type
 *******************************************************************************
 */
struct HalTimerBlock
{
    uint8_t  ID;
    uint32_t Baud;
    void (*Handler)(void);
};

/**
 *******************************************************************************
 * @brief       define msp timer interface
 *******************************************************************************
 */
#if USE_MSP_TIMER_COMPONENT
typedef struct
{    
    hal_err_t (*Open)(uint8_t);
    hal_err_t (*Close)(uint8_t);

    struct
    {
        hal_err_t (*Base)(uint8_t, uint32_t, void(*)(void));
    }Init;
}MSP_Usart_Interface;
#endif

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_MSP_TIMER_COMPONENT
extern hal_err_t MSP_USART_Open(uint8_t);
extern hal_err_t MSP_USART_Close(uint8_t);
#endif

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
/* End include define---------------------------------------------------------*/
#endif

/** @}*/     /** usart component */

/**********************************END OF FILE*********************************/
