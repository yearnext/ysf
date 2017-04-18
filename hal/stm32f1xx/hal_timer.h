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
 * @file       hal_timer.h                                                     *
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
#include "core_path.h"

/* Exported macro ------------------------------------------------------------*/
#define USE_MSP_TIMER_API  (1)
#define USE_MAP_TIMER_API  (1)  
 
#define MCU_TICK_TIMER     MCU_TIMER_0
    
/* Exported types ------------------------------------------------------------*/
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
    
struct map_timer_t
{
    uint8_t id;
};

struct MSP_TIMER_API
{    
    void (*enable)(uint8_t);
    void (*disable)(uint8_t);
    
    void (*start)(uint8_t);
    void (*stop)(uint8_t);
    
    struct
    {
        void (*base)(uint8_t, uint32_t, void(*)(void));
    }init;
};
    
struct MAP_TIMER_API
{
    void (*enable)(struct map_timer_t *timer);
    void (*disable)(struct map_timer_t *timer);
};
    
/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
extern void msp_timer_init(uint8_t);
extern void msp_timer_fini(uint8_t);
extern void msp_timer_base_init(uint8_t, uint32_t, void (*)(void));

//extern void map_timer_init(struct ysf_msp_timer_t*);
//extern void map_timer_fini(struct ysf_msp_timer_t*);

//extern void SysTick_Handler(void);

#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /* gpio component  */

/**********************************END OF FILE*********************************/
