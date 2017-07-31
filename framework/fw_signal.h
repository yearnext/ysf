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
 * @file       fw_signal.h
 * @author     yearnext
 * @version    1.0.0
 * @date       2017-01-10
 * @brief      framework signal head files
 * @par        paltform                                  
 *                 Windows
 * @par        compiler									                         
 * 				   GCC
 *******************************************************************************
 * @note
 * 1.XXXXX                  						                     
 *******************************************************************************
 */

/**
 * @defgroup framework signal component
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FRAMEWORK_SIGNAL_H__
#define __FRAMEWORK_SIGNAL_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "fw_core.h"
#include "fw_timer.h"
    
/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        framework signal preiod config
 *******************************************************************************
 */
#define FW_SIGNAL_SCAN_PREIOD                                  (FW_TIME_SET(10))
/**
 *******************************************************************************
 * @brief       define signal info param
 *******************************************************************************
 */
#define NO_SIGNAL_INFO                                                       (0)
#define IS_NO_SIGNAL(signal)                        ((signal) == NO_SIGNAL_INFO)
    
/**
 *******************************************************************************
 * @brief       define signal event
 *******************************************************************************
 */
#define REG_RELEASE_STATE                                                (0x01)
#define REG_PRESS_EDGE_STATE                                             (0x02)
#define REG_PRESS_STATE                                                  (0x04)
#define REG_LONG_PRESS_STATE                                             (0x08)
#define REG_MULTI_PRESS_STATE                                            (0x10)
#define REG_RELEASE_EDGE_STATE                                           (0x20)
#define REG_DOUBLE_EDGE_STATE                                            (0x22)
#define REG_ALL_STATE                                                    (0x3F)
#define IsRegReleaseState(n)                      ((n) & REG_RELEASE_STATE)
#define IsRegPressEdgeState(n)                    ((n) & REG_PRESS_EDGE_STATE)
#define IsRegPressState(n)                        ((n) & REG_PRESS_STATE)
#define IsRegLongPressState(n)                    ((n) & REG_LONG_PRESS_STATE)
#define IsRegMultiPressState(n)                   ((n) & REG_MULTI_PRESS_STATE)
#define IsRegReleaseEdgeState(n)                  ((n) & REG_RELEASE_EDGE_STATE)

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        define signal status
 *******************************************************************************
 */
typedef enum FW_SIGNAL_STATE
{
    SIGNAL_INIT_STATE = 0x80,
    SIGNAL_PRESS_FILTER_STATE,
    SIGNAL_PRESS_EDGE_STATE,
    SIGNAL_PRESS_STATE,
    SIGNAL_LONG_PRESS_STATE,
    SIGNAL_MULTI_PRESS_STATE,
    SIGNAL_RELEASE_FILTER_STATE,
    SIGNAL_RELEASE_EDGE_STATE,
    SIGNAL_RELEASE_STATE,
    SIGNAL_END_STATE,
}Fw_Signal_State;

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_FRAMEWORK_SIGNAL_COMPONENT
extern void Fw_Signal_InitComponent(void);
extern void Fw_Signal_Poll(uint8_t);

extern fw_err_t Fw_Signal_Init(uint8_t, uint8_t, uint8_t (*)(void), uint8_t);
extern fw_err_t Fw_Signal_RegisterState(uint8_t, uint8_t);
extern fw_err_t Fw_Signal_UnregisterState(uint8_t, uint8_t);
extern uint8_t Fw_Signal_GetInfo(uint8_t);
#endif

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** framework signal component */

/**********************************END OF FILE*********************************/
