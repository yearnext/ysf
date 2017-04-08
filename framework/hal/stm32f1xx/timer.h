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
 * @file       timer.h                                                         *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-03-04                                                      *
 * @brief      timer head files                                                *
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
#ifndef __STM32F10X_TIMER_H__
#define __STM32F10X_TIMER_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "ysf_path.h"
#include YSF_TYPE_PATH

/* Exported macro ------------------------------------------------------------*/
#define USE_MSP_TIMER_API (1)
#define USE_MAP_TIMER_API (1)  
#define USE_TICK_TIMER (1)
    
/* Exported types ------------------------------------------------------------*/
enum
{
    MCU_TIMER_0 = 0,  /** stm32 tick timer */
    MCU_TIMER_1,
    MCU_TIMER_2,
    MCU_TIMER_3,
    MCU_TIMER_4,
    MCU_TIMER_5,
    MCU_TIMER_6,
    MCU_TIMER_7,
    MCU_TIMER_8,
};
    
struct ysf_msp_timer_t
{
    uint8_t id;
};

struct MSP_TIMER_API
{    
    ysf_err_t (*enable)(uint8_t id);
    ysf_err_t (*disable)(uint8_t id);
#if USE_TICK_TIMER
    struct
    {
        ysf_err_t (*init)(void (*func)(void));
    }tick;
#endif
};
    
struct MAP_TIMER_API
{
    ysf_err_t (*enable)(struct ysf_msp_timer_t *timer);
    ysf_err_t (*disable)(struct ysf_msp_timer_t *timer);
};
    
/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
extern ysf_err_t msp_timer_init(uint8_t);
extern ysf_err_t msp_timer_fini(uint8_t);
#if USE_TICK_TIMER
extern ysf_err_t msp_tick_timer_init(void (*func)(void));
#endif

extern ysf_err_t map_timer_init(struct ysf_msp_timer_t*);
extern ysf_err_t map_timer_fini(struct ysf_msp_timer_t*);

extern void SysTick_Handler(void);

#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /* gpio component  */

/**********************************END OF FILE*********************************/
