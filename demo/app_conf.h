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
 * @file       app_conf.h                                                      *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-07-10                                                      *
 * @brief      application config head files                                   *
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
 * @defgroup application config
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __APPLICATION_CONF_H__
#define __APPLICATION_CONF_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
/* Define and config ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define framework task
 *******************************************************************************
 */
enum Define_Task
{
    /** define framework task */                            /** task priority */
    FW_TICK_TASK                                                            = 0,
    FW_SIGNAL_TASK                                                          = 1,
    FW_DEBUG_TASK                                                           = 2,
    
    /** define user task begin */
	
    /** define user task end */
    FW_TASK_MAX,
};

/**
 *******************************************************************************
 * @brief      define framework event
 *******************************************************************************
 */
enum Define_Event
{
    /** define framework event */
    FW_EVENT_NONE,
    FW_TICK_EVENT,
    FW_SIGNAL_EVENT,
    FW_DELAY_EVENT,
    FW_BEGIN_EVENT,
    FW_END_EVENT,
    FW_FLOW_EVENT,
    FW_TIMEOUT_EVENT,
    FW_TRANSFER_START_EVENT,
    FW_TRANSFER_EVENT,
    FW_TRANSFER_WAIT_EVNET,
    FW_TRANSFER_COMPLET_EVENT,
    FW_SIGNAL_HANDLE_EVENT,
    
    /** define user task begin */
	
    /** define user task end */
    FW_EVENT_MAX,
};

/* Exported types ------------------------------------------------------------*/
/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** application config  */

/**********************************END OF FILE*********************************/
