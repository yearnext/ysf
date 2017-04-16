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
 * @file       fw_event.c                                                      *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-01-10                                                      *
 * @brief      event component source files                                    *
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
 * @defgroup event component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "core_path.h"
#include _FW_PATH
#include _FW_EVENT_COMPONENT_PATH
#include _FW_BUFFER_COMPONENT_PATH
#include _FW_DEBUG_COMPONENT_PATH

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       event component auto config
 *******************************************************************************
 */
#if USE_FRAMEWORK_EVENT_API
static uint16_t            EventQueue[FW_EVENT_MAX];
static struct fw_buffer_t EventControlBlock;
#endif

/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_EVENT_COMPONENT
/**
 *******************************************************************************
 * @brief       event component init
 * @param       [in/out]  void
 * @return      [in/out]  FW_ERR_NONE       init finish
 * @return      [in/out]  FW_ERR_FAIL       init failed
 * @note        None
 *******************************************************************************
 */
fw_err_t EventInit(void)
{
    RingBufferInit(&EventControlBlock, EventQueue, CalTypeByteSize(EventQueue));
    
	return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       write event to event queue
 * @param       [in/out]  event             write events
 * @return      [in/out]  FW_ERR_NONE      write success
 * @return      [in/out]  FW_ERR_FAIL      write failed
 * @note        None
 *******************************************************************************
 */
fw_err_t EventPost(uint16_t event)
{
    RingBufferWrite(&EventControlBlock, &event, CalTypeByteSize(event));
    
	return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       read events from event queue
 * @param       [in/out]  *event            read events
 * @return      [in/out]  FW_ERR_NONE      read success
 * @return      [in/out]  FW_ERR_FAIL      read failed
 * @note        None
 *******************************************************************************
 */
fw_err_t EventRead(uint16_t *event)
{
    RingBufferRead(&EventControlBlock, event, CalTypeByteSize(uint16_t));
	
    return FW_ERR_NONE;
}

#endif

/** @}*/     /** event component  */

/**********************************END OF FILE*********************************/
