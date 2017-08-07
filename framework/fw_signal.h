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
 * @file       fw_signal.h                                                     *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-01-15                                                      *
 * @brief      signal component head files                                     *
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
 * @defgroup signal component
 * @{
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SIGNAL_COMPONENT_H__
#define __SIGNAL_COMPONENT_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "fw_path.h"
#include "fw_timer.h"

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       framework component config flags
 * @note        1                        enable
 * @note        0                        disable
 *******************************************************************************
 */
#ifdef USE_FRAMEWORK_SIGNAL_SCAN_COMPONENT
#define USE_SIGNAL_COMPONENT                                                 (1)

/**
 *******************************************************************************
 * @brief       user config flags
 * @note        1         enable
 * @note        0         disable
 *******************************************************************************
 */
#else
#define USE_SIGNAL_COMPONENT                                                 (1)
#endif
    
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

/* Public typedef ------------------------------------------------------------*/
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

/**
 *******************************************************************************
 * @brief        define signal block
 *******************************************************************************
 */
struct Fw_Signal
{
    char             *String;
    
    uint8_t          (*Scan)(void);
    
    Fw_Signal_State  State;
    
    uint8_t          Filter;
    uint8_t          Value;
    
    uint8_t          TaskId;
    uint8_t          TriggerState;
    
    struct Fw_Timer  Timer;
};

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       signal component api
 *******************************************************************************
 */
#if USE_SIGNAL_COMPONENT
extern fw_err_t Fw_Signal_Init(void);
extern fw_err_t Fw_Signal_Create(struct Fw_Signal*, char*, uint8_t);
extern fw_err_t Fw_Signal_Start(struct Fw_Signal*, uint8_t, uint32_t);
extern uint8_t Fw_Signal_GetNum(void);
#endif

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** signal component */

/**********************************END OF FILE*********************************/
