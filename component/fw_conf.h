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
 * @file       fw_conf.h                                                       *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-04-13                                                      *
 * @brief      framework config head files                                     *
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
 * @defgroup framework config
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FRAMEWORK_CONF_H__
#define __FRAMEWORK_CONF_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "core_conf.h"
//#include _HAL_PATH
//#include _HAL_TIMER_PATH     

/* Define and config ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define framework version
 *******************************************************************************
 */
#define _FRAMEWORK_VERSION                 "FRAMEWORK_ALPHA_0.0.3_2017040132135"

/**
 *******************************************************************************
 * @brief      define tick timer init
 *******************************************************************************
 */
//#define FwTickHardwareInit(tick, func)     msp_timer_base_init(MCU_TICK_TIMER, (tick), func)

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define framework events type
 *******************************************************************************
 */
#define FW_EVENT_NONE                                   (_EVENT_NONE)
#define FW_EVENT_DELAY                                  (_EVENT_DELAY)
#define FW_EVENT_MAX                                    (_EVENT_MAX)

typedef _evt_t                                          fw_evt_t;

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** framework config  */

/**********************************END OF FILE*********************************/
