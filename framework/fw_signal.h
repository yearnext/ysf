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
 * @brief        framework signal component config
 *******************************************************************************
 */
#define USE_FRAMEWORK_SIGNAL_COMPONENT                                       (1)
 
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
#define Logon_Release_Event                                               (0x01)
#define Logon_PressEdge_Event                                             (0x02)
#define Logon_Press_Event                                                 (0x04)
#define Logon_LongPress_Event                                             (0x08)
#define Logon_MultiPress_Event                                            (0x10)
#define Logon_ReleaseEdge_Event                                           (0x20)
    
#define Logout_Release_Event                                              (0x01)
#define Logout_PressEdge_Event                                            (0x02)
#define Logout_Press_Event                                                (0x04)
#define Logout_LongPress_Event                                            (0x08)
#define Logout_MultiPress_Event                                           (0x10)
#define Logout_ReleaseEdge_Event                                          (0x20)

#define Logon_Edge_Signal()                                               (0x22)
#define Logon_All_Signal()                                                (0x3F)

#define IsLogonReleaseEvent(n)                   ((n) & Logon_Release_Event)
#define IsLogonPressEdgeEvent(n)                 ((n) & Logon_PressEdge_Event)
#define IsLogonPressEvent(n)                     ((n) & Logon_Press_Event)
#define IsLogonLongPressEvent(n)                 ((n) & Logon_LongPress_Event)
#define IsLogonMultiPressEvent(n)                ((n) & Logon_MultiPress_Event)
#define IsLogonReleaseEdgeEvent(n)               ((n) & Logon_ReleaseEdge_Event)

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        framework signal status config
 *******************************************************************************
 */
typedef enum
{
    SIGNAL_STATUS_INIT = 0x80,
    SIGNAL_STATUS_PRESS_FILTER_STEP,
	SIGNAL_STATUS_PRESS_EDGE,
    SIGNAL_STATUS_PRESS,
	SIGNAL_STATUS_LONG_PRESS,
	SIGNAL_STATUS_MULTI_PRESS,
    SIGNAL_STATUS_RELEASE_FILTER_STEP,
    SIGNAL_STATUS_RELEASE_EDGE,
	SIGNAL_STATUS_RELEASE,
	SIGNAL_STATUS_END,
}signal_status_t;

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_FRAMEWORK_SIGNAL_COMPONENT
extern void InitSignalComponent(void);
extern void PollSignalComponent(uint8_t);

extern fw_err_t RegisterSignal(uint8_t, uint8_t, uint8_t (*)(void), uint8_t);
extern fw_err_t LogonSignalEvent(uint8_t, uint8_t);
extern fw_err_t LogoutSignalEvent(uint8_t, uint8_t);
extern uint8_t GetSignalInfo(uint8_t);
#endif

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** framework signal component */

/**********************************END OF FILE*********************************/
