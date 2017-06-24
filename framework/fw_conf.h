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
 * @file       fw_conf.h
 * @author     yearnext
 * @version    1.0.0
 * @date       2017-01-10
 * @brief      framework config component head files
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
 * @defgroup framework config component
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FRAMEWORK_CONFIG_H__
#define __FRAMEWORK_CONFIG_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       API config
 *******************************************************************************
 */
#define USE_FRAMEWORK_EVENT_COMPONENT                                        (1)

/**
 *******************************************************************************
 * @brief       queue compoent config flag
 *******************************************************************************
 */
#define USE_FRAMEWORK_QUEUE_COMPONENT                                        (0)

/**
 *******************************************************************************
 * @brief        framework signal component config
 *******************************************************************************
 */
#define USE_FRAMEWORK_SIGNAL_COMPONENT                                       (0)
    
/**
 *******************************************************************************
 * @brief       timer compoent config flag
 *******************************************************************************
 */
#define USE_FRAMEWORK_TIMER_COMPONENT                                        (1)

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define event class
 * @note        event value can not be greater than FW_EVENT_MAX(127)
 *******************************************************************************
 */
enum define_fw_event
{
    /** framework event */
    FW_EVENT_NONE,
    FW_TICK_EVENT,
    FW_SIGNAL_EVENT,
	FW_DELAY_EVENT,
	FW_BEGIN_EVENT,
	FW_END_EVENT,
	FW_FLOW_EVENT,
	FW_TIMEOUT_EVENT,
    
    /** user define begin */

    /** user define end */
    FW_EVENT_MAX,
};

/**
 *******************************************************************************
 * @brief       framework task config
 *******************************************************************************
 */
enum define_fw_task
{
    /** framework task */
    FW_TICK_TASK = 0,
 	FW_SIGNAL_TASK,
    
	/** user define begin */

	/** user define end */
    FW_TASK_MAX,
};

/**
 *******************************************************************************
 * @brief       framework queue config
 *******************************************************************************
 */
enum define_fw_queue
{
	/** framework queue */
	FW_TICK_QUEUE,

	/** user define begin */

	/** user define end */
	FW_QUEUE_MAX,
};

/**
 *******************************************************************************
 * @brief        framework signal config
 *******************************************************************************
 */
enum define_fw_signal
{
	/** framework signal */

	/** user define begin */

	/** user define end */
	SIGNAL_MAX,
};

/**
 *******************************************************************************
 * @brief       framework timer config
 *******************************************************************************
 */
enum define_fw_timer
{
	/** framework timer */
    SIGNAL_SCAN_TIMER,
    
	/** user define begin */
    
	/** user define end */
    Timer_Max,
};

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** framework event component */

/**********************************END OF FILE*********************************/
