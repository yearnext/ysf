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
 * @file       ysf_signal.h                                                    *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-01-15                                                      *
 * @brief      ysf signal head files                                           *
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
 * @defgroup ysf signal
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __YSF_SIGNAL_H__
#define __YSF_SIGNAL_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "core_conf.h"
#include "core_path.h"
#include _COMM_TYPE_PATH
#include _FW_EVENT_COMPONENT_PATH
#include _FW_LIST_COMPONENT_PATH
#include _FW_TASK_COMPONENT_PATH

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       ysf config
 *******************************************************************************
 */
#ifdef USE_YSF_SIGNAL_SCAN_COMPONENT
#if USE_YSF_SIGNAL_SCAN_COMPONENT
#define USE_YSF_SIGNAL_API          (1)
#else
#define USE_YSF_SIGNAL_API          (0)
#endif

/**
 *******************************************************************************
 * @brief       user config
 *******************************************************************************
 */
#else
#define USE_YSF_SIGNAL_API          (1)
#endif
    
/**
 *******************************************************************************
 * @brief       config signal time
 *******************************************************************************
 */
#define YSF_SIGNAL_SCAN_TIME        YSF_TIME_2_TICK(10)
#define YSF_SIGNAL_TIME2COUNT(n)    ((n)/YSF_SIGNAL_SCAN_TIME)

#define YSF_SIGNAL_ACTIVE_LOW       !
#define YSF_SIGNAL_ACTIVE_HIGH      !!
#define YSF_SIGNAL_ACTIVE           YSF_SIGNAL_ACTIVE_LOW
   
/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define signal status enumeration
 *******************************************************************************
 */
enum ysf_signal_status_t
{
    SIGNAL_STATUS_INIT = 0,

    SIGNAL_STATUS_PRESS_FILTER_STEP1,
    SIGNAL_STATUS_PRESS_FILTER_STEP2,
    SIGNAL_STATUS_PRESS_FILTER_STEP3,
    SIGNAL_STATUS_RELEASE_FILTER_STEP1,
    SIGNAL_STATUS_RELEASE_FILTER_STEP2,
    SIGNAL_STATUS_RELEASE_FILTER_STEP3,

    SIGNAL_STATUS_RELEASE,
    SIGNAL_STATUS_PRESS_EDGE,
    SIGNAL_STATUS_PRESS,
    SIGNAL_STATUS_LONG_PRESS,
    SIGNAL_STATUS_MULTI_PRESS,
    SIGNAL_STATUS_RELEASE_EDGE,
};

/**
 *******************************************************************************
 * @brief       define signal type
 *******************************************************************************
 */
struct ysf_signal_t
{
    struct
    {
        struct ysf_signal_t *next;
        bool useStatus;
        
        enum
        {
            YSF_EVENT_HANDLER_SIGNAL,
        }type;
    };
    
    struct
    {
        enum ysf_signal_status_t (*detect)(void);
//        fw_err_t (*handler)(void *, uint16_t);
        enum ysf_signal_status_t status;
        
        struct ysf_task_t task;
    };
};

/**
 *******************************************************************************
 * @brief       ysf signal api
 *******************************************************************************
 */
#if defined(USE_YSF_SIGNAL_API) && USE_YSF_SIGNAL_API
struct YSF_SIGNAL_API
{
    fw_err_t (*init)(void);
    fw_err_t (*handler)(uint16_t);
    
    struct
    {
        fw_err_t (*arm)(struct ysf_signal_t*, enum ysf_signal_status_t (*)(void), fw_err_t (*)(uint16_t));
    };
    
    struct
    {
        struct ysf_signal_t *(*arm)(enum ysf_signal_status_t (*)(void), fw_err_t (*)(uint16_t));
    }simple;
              
    fw_err_t (*disarm)(struct ysf_signal_t*);
};
#endif

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       ysf signal api
 *******************************************************************************
 */
#if defined(USE_YSF_SIGNAL_API) && USE_YSF_SIGNAL_API
extern fw_err_t ysf_signal_init(void);

extern fw_err_t ysf_evtSignal_arm(struct ysf_signal_t*, 
                                   enum ysf_signal_status_t (*)(void), 
                                   fw_err_t (*)(uint16_t) );
                                   
extern struct ysf_signal_t *ysf_evtSimpSignal_arm(enum ysf_signal_status_t (*)(void), 
                                                  fw_err_t (*)(uint16_t) );
                                       
extern fw_err_t ysf_signal_disarm(struct ysf_signal_t*);
                                       
extern fw_err_t ysf_signal_handler(uint16_t);
#endif
                                       
/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** ysf signal */

/**********************************END OF FILE*********************************/
