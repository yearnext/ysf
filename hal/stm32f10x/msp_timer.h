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
 * @file       msp_timer.h                                                     *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-03-04                                                      *
 * @brief      msp timer head files                                            *
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
 * @defgroup timer component
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F10X_HAL_MSP_TIMER_H__
#define __STM32F10X_HAL_MSP_TIMER_H__

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
#ifdef USE_MCU_TIMER_COMPONENT
#if USE_MCU_TIMER_COMPONENT
    #define USE_MSP_TIMER_COMPONENT                                          (1)
#else
    #define USE_MSP_TIMER_COMPONENT                                          (0)
#endif
    
/**
 *******************************************************************************
 * @brief       user config flags
 * @note        1         enable
 * @note        0         disable
 *******************************************************************************
 */
#else
    #define USE_MSP_TIMER_COMPONENT                                          (1)
#endif
 
/**
 *******************************************************************************
 * @brief       define tick timer symbol
 *******************************************************************************
 */
#define MCU_TICK_TIMER                                               MCU_TIMER_0
    
/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define timer id
 *******************************************************************************
 */
enum
{
    MCU_TIMER_0 = 0,
    MCU_TIMER_1,
    MCU_TIMER_2,
    MCU_TIMER_3,
    MCU_TIMER_4,
    MCU_TIMER_5,
    MCU_TIMER_6,
    MCU_TIMER_7,
    MCU_TIMER_8,
    
    MCU_TIMER_MAX,
};

/**
 *******************************************************************************
 * @brief       define map timer type
 *******************************************************************************
 */
struct Hal_Timer_Block
{
    uint8_t ID;
    uint32_t Period;
};

/**
 *******************************************************************************
 * @brief       define msp timer interface
 *******************************************************************************
 */
typedef struct
{    
    hal_err_t (*Open)(uint8_t);
    hal_err_t (*Close)(uint8_t);
    
    hal_err_t (*Start)(uint8_t);
    hal_err_t (*Stop)(uint8_t);
    
    struct
    {
        hal_err_t (*Init)(uint8_t, uint32_t);
        hal_err_t (*HandleRegister)(uint8_t, void (*)(void *), void*);
        hal_err_t (*Arm)(uint8_t, uint32_t, void (*)(void *), void*);
    }Base;
}MSP_Timer_Interface;

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define msp timer api
 *******************************************************************************
 */
#if USE_MSP_TIMER_COMPONENT
extern hal_err_t MSP_Timer_Open(uint8_t);
extern hal_err_t MSP_Timer_Close(uint8_t);
extern hal_err_t MSP_Timer_Start(uint8_t);
extern hal_err_t MSP_Timer_Stop(uint8_t);
extern hal_err_t MSP_TimerBase_Init(uint8_t, uint32_t);
extern hal_err_t MSP_TimerBaseHandle_Register(uint8_t, void (*)(void *), void*);
extern hal_err_t MSP_TimerBase_Arm(uint8_t, uint32_t, void (*)(void *), void*);
#endif

/**
 *******************************************************************************
 * @brief      define hal timer interrupt server function
 *******************************************************************************
 */   
extern void SysTick_Handler(void);

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
/* End include define---------------------------------------------------------*/
#endif

/** @}*/     /** timer component */

/**********************************END OF FILE*********************************/
