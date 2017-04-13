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
 * @file       ysf.h                                                           *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-02-18                                                      *
 * @brief      ysf head files                                                  *
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
 * @defgroup ysf
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __YSF_H__
#define __YSF_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* YSF_API config macro ------------------------------------------------------*/   
/**
 *******************************************************************************
 * @brief      YSF API USE STATUS CONFIG
 *******************************************************************************
 */
#define USE_YSF_API (1)  
    
/* Includes ------------------------------------------------------------------*/
#include "ysf_conf.h"
#include "hal_conf.h"
#include "ysf_path.h"
#include YSF_TYPE_PATH 
#include HAL_PATH
  
/**
 *******************************************************************************
 * @brief      INCLUDE YSF COMPONENTS
 *******************************************************************************
 */
#if USE_YSF_API
#include YSF_COMPONENT_TICK_PATH
#include YSF_COMPONENT_MEMORY_PATH
#include YSF_COMPONENT_EVENT_PATH
#include YSF_COMPONENT_TIMER_PATH
#include YSF_COMPONENT_SIGNAL_PATH
#include YSF_COMPONENT_DEBUG_PATH
#include YSF_COMPONENT_PT_PATH
#include YSF_COMPONENT_TASK_PATH
#else
#warning "YSF is not use YSF_API!"
#endif

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define ysf api
 *******************************************************************************
 */
#if defined(USE_YSF_API) && USE_YSF_API   
struct YSF_API
{
    void (*init)(ysf_err_t (*user_init)(void));
    void (*start)(void);
    char *ver;
    
#if defined(USE_YSF_TICK_API)   && USE_YSF_TICK_API
    struct YSF_TICK_API tick;
#endif
        
#if defined(USE_YSF_MEMORY_API) && USE_YSF_MEMORY_API
    struct YSF_MEMORY_API memory;
#endif
    
#if defined(USE_YSF_EVENT_API)  && USE_YSF_EVENT_API
    struct YSF_EVENT_API event;
#endif
    
#if defined(USE_YSF_TIMER_API)  && USE_YSF_TIMER_API
    struct YSF_TIMER_API timer;
#endif

#if defined(USE_YSF_SIGNAL_API) && USE_YSF_SIGNAL_API
    struct YSF_SIGNAL_API signal;
#endif

#if defined(USE_YSF_DEBUG_API)  && USE_YSF_DEBUG_API
    struct YSF_DEBUG_API debug;
#endif

#if defined(USE_YSF_TASK_API)   && USE_YSF_TASK_API
    struct YSF_TASK_API task;
#endif

#if defined(USE_YSF_PT_API)     && USE_YSF_PT_API
    struct YSF_PT_API pt;
#endif
};
#endif    

/* Exported variables --------------------------------------------------------*/    
/**
 *******************************************************************************
 * @brief      define ysf api
 *******************************************************************************
 */
#if defined(USE_YSF_API) && USE_YSF_API
extern const struct YSF_API ysf;
#endif
    
/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** ysf */

/**********************************END OF FILE*********************************/