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
 * @brief      framework tick component head files                             *
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
 * @defgroup framework tick component
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FRAMEWORK_TICK_H__
#define __FRAMEWORK_TICK_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "core_conf.h"
#include "core_path.h"
#include _COMM_TYPE_PATH

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       ysf config
 *******************************************************************************
 */
#ifdef USE_YSF_TICK_COMPONENT
#if USE_YSF_TICK_COMPONENT
#define USE_YSF_TICK_API (1)
#else
#define USE_YSF_TICK_API (0)
#endif

/**
 *******************************************************************************
 * @brief       user config
 *******************************************************************************
 */
#else
#define USE_YSF_TICK_API (1)
#endif

/**
 *******************************************************************************
 * @brief       ysf tick time(unit: ms)
 *******************************************************************************
 */
#define YSF_TICK_TIME    (10)
    
/**
 *******************************************************************************
 * @brief       ysf tick max value
 *******************************************************************************
 */
#define YSF_TICK_MAX UINT32_MAX

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       ysf tick type
 *******************************************************************************
 */
#if USE_YSF_TICK_API
typedef uint32_t ysf_tick_t;
#endif

/**
 *******************************************************************************
 * @brief       ysf tick func list
 *******************************************************************************
 */
#if USE_YSF_TICK_API
struct YSF_TICK_API
{
    void (*init)(void);
    void (*inc)(void);
    ysf_tick_t (*read)(void);
    ysf_tick_t (*cal)(void);
};
#endif

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_YSF_TICK_API
extern void ysf_tick_init( void );
extern void ysf_tick_inc( void );
extern ysf_tick_t ysf_tick_get( void );
extern ysf_tick_t ysf_past_tick_cal( void );
#endif

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** framework tick component  */

/**********************************END OF FILE*********************************/
