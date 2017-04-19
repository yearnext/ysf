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
 * @file       fw_event.h                                                      *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-02-12                                                      *
 * @brief      event component head files                                      *
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __EVENT_COMPONENT_H__
#define __EVENT_COMPONENT_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "core_path.h"
#include _FW_PATH

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       framework component config flags
 * @note        1                        enable
 * @note        0                        disable
 *******************************************************************************
 */
#ifdef USE_FRAMEWORK_EVENT_COMPONENT
#if USE_FRAMEWORK_EVENT_COMPONENT
    #define USE_EVENT_COMPONENT                                              (1)
#else
    #define USE_EVENT_COMPONENT                                              (0)
#endif

/**
 *******************************************************************************
 * @brief       user config flags
 * @note        1         enable
 * @note        0         disable
 *******************************************************************************
 */
#else
    #define USE_EVENT_COMPONENT                                              (1)
#endif

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define event interface
 *******************************************************************************
 */
#if USE_EVENT_COMPONENT
typedef struct
{
    fw_err_t (*Init)(void);
    fw_err_t (*Post)(uint16_t);
    fw_err_t (*Read)(uint16_t*);
}EventComponentInterface;
#endif

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       event function interface
 *******************************************************************************
 */
#if USE_EVENT_COMPONENT
extern fw_err_t InitEventComponent(void);
extern fw_err_t PostEvent(uint16_t);
extern fw_err_t GetEvent(uint16_t*);
#endif

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** event component */

/**********************************END OF FILE*********************************/
