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
 * @file       fw_tick.h                                                       *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-01-10                                                      *
 * @brief      tick component head files                                       *
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
 * @defgroup tick component
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TICK_COMPONENT_H__
#define __TICK_COMPONENT_H__

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
#ifdef USE_FRAMEWORK_TICK_COMPONENT
#if USE_FRAMEWORK_TICK_COMPONENT
#define USE_TICK_COMPONENT                                                   (1)
#else
#define USE_TICK_COMPONENT                                                   (0)
#endif

/**
 *******************************************************************************
 * @brief       user config flags
 * @note        1         enable
 * @note        0         disable
 *******************************************************************************
 */
#else
#define USE_TICK_COMPONENT                                                   (1)
#endif

/**
 *******************************************************************************
 * @brief       define tick param
 *******************************************************************************
 */
#define TICK_PERIOD                                             CORE_TICK_PERIOD
#define TICK_VALUE_MAX                                                UINT32_MAX

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define tick function interface
 *******************************************************************************
 */
#if USE_TICK_COMPONENT
typedef struct
{
    void     (*Init)(void);
    void     (*Inc)(void*);
    uint32_t (*Read)(void);
    uint32_t (*Cal)(void);
}TickComponentInterface;
#endif

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define tick function api
 *******************************************************************************
 */
#if USE_TICK_COMPONENT
extern void     InitTickComponent(void);
extern void     IncTick(void*);
extern uint32_t GetTick(void);
extern uint32_t CalPastTick(void );
#endif

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** tick component */

/**********************************END OF FILE*********************************/
