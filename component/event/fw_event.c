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
#include _FW_TYPE_PATH
#include _FW_EVENT_COMPONENT_PATH
#include _FW_BUFFER_COMPONENT_PATH
#include _FW_LINK_LIST_COMPONENT_PATH
#include _FW_MEMORY_COMPONENT_PATH
#include _FW_DEBUG_COMPONENT_PATH

/* Private define ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       calculate events use memory size
 *******************************************************************************
 */
#define YSF_EVENT_SIZE_CAL(event) CalTypeByteSize(event)

/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       event component auto config
 *******************************************************************************
 */
#if USE_YSF_EVENT_API
static int16_t buffer[YSF_EVENT_MAX];
static struct  ysf_rb_t evt_queue;
#endif

/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_YSF_EVENT_API
/**
 *******************************************************************************
 * @brief       ysf event component init
 * @param       [in/out]  void
 * @return      [in/out]  FW_ERR_NONE       init finish
 * @return      [in/out]  FW_ERR_FAIL       init failed
 * @note        None
 *******************************************************************************
 */
fw_err_t ysf_event_init( void )
{
    ysf_rbInit(&evt_queue, (uint8_t *)buffer, YSF_EVENT_SIZE_CAL(buffer));
    
	return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       ysf write event to event queue
 * @param       [in/out]  event             write events
 * @return      [in/out]  FW_ERR_NONE      write success
 * @return      [in/out]  FW_ERR_FAIL      write failed
 * @note        None
 *******************************************************************************
 */
fw_err_t ysf_event_post( uint16_t event )
{
    ysf_rbWrite( &evt_queue, (uint8_t *)&event, YSF_EVENT_SIZE_CAL(int16_t) );
    
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
fw_err_t ysf_event_read( uint16_t *event )
{
    ysf_rbRead( &evt_queue, (uint8_t *)event, YSF_EVENT_SIZE_CAL(int16_t) );
	
    return FW_ERR_NONE;
}

#endif

/** @}*/     /** ysf event component  */

/**********************************END OF FILE*********************************/
