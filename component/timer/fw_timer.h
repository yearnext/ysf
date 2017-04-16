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
 * @file       fw_timer.h                                                      *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-07-09                                                      *
 * @brief      framework timer component head files                            *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         * 
 *******************************************************************************
 * @note                                                                       *
 * 1.XXXXX                                                                     *
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FRAMEWORK_TIMER_COMPONENT_H__
#define __FRAMEWORK_TIMER_COMPONENT_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "core_path.h"
#include _FW_PATH
#include _FW_TASK_COMPONENT_PATH
#include _FW_TICK_COMPONENT_PATH
#include _FW_LINK_LIST_COMPONENT_PATH

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       framework component config flags
 * @note        1                        enable
 * @note        0                        disable
 *******************************************************************************
 */
#ifdef USE_FRAMEWORK_TIMER_COMPONENT
#if USE_FRAMEWORK_TIMER_COMPONENT
#define USE_FRAMEWORK_TIMER_API                                              (1)
#else
#define USE_FRAMEWORK_TIMER_API                                              (0)
#endif

/**
 *******************************************************************************
 * @brief       user config flags
 * @note        1         enable
 * @note        0         disable
 *******************************************************************************
 */
#else
#define USE_FRAMEWORK_TIMER_API                                              (1)
#endif

/**
 *******************************************************************************
 * @brief       ysf timer tick config
 *******************************************************************************
 */
#define FW_TIMER_PERIOD         FW_TICK_PERIOD
#define FW_TIME_2_TICK(time)    ((time)/FW_TIMER_PERIOD)

#define FW_TIMER_CYCLE_MODE     (-1)

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        ysf timer type
 *******************************************************************************
 */
struct ysf_timer_t
{
    struct
    {
        struct ysf_timer_t *next;

        enum
        {
            YSF_CALL_BACK_TIMER,
            YSF_EVENT_HANDLER_TIMER,
            YSF_STATE_MACHINE_TIMER,
        }type;
    };

    struct
    {
        struct ysf_task_t task;
    };
    
    struct
    {
        fw_tick_t ticks;
        fw_tick_t loadTicks;
        
        int16_t    cycle;
    };
};

/**
 *******************************************************************************
 * @brief      interface function defineitions 
 *******************************************************************************
 */
#if USE_FRAMEWORK_TIMER_API
struct YSF_TIMER_API
{
    fw_err_t (*init)(void);
    fw_err_t (*handler)(uint16_t);

    fw_err_t (*arm)(struct ysf_timer_t*, uint32_t, int16_t);
    fw_err_t (*disarm)(struct ysf_timer_t*);
    
    bool (*getStatus)(struct ysf_timer_t*);
    
    struct
    {
        fw_err_t (*cb_init)(struct ysf_timer_t*, fw_err_t (*)(void*), void*);
        fw_err_t (*evt_init)(struct ysf_timer_t*, fw_err_t (*)(uint16_t), uint16_t);
        fw_err_t (*sm_init)(struct ysf_timer_t*, fw_err_t (*)(void*, uint16_t), void*, uint16_t);
    };
    
    struct
    {
        struct ysf_timer_t *(*cb_init)(fw_err_t (*)(void*), void*);
        struct ysf_timer_t *(*evt_init)(fw_err_t (*)(uint16_t), uint16_t);
        struct ysf_timer_t *(*sm_init)(fw_err_t (*)(void*, uint16_t), void*, uint16_t);
    }simple;
};
#endif

/* Exported constants --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      defineitions interface function 
 *******************************************************************************
 */
#if USE_FRAMEWORK_TIMER_API
extern fw_err_t ysf_timer_init(void);

extern fw_err_t ysf_timer_handler(uint16_t);

extern bool ysf_timerGetStatus(struct ysf_timer_t*);

extern fw_err_t ysf_timer_arm(struct ysf_timer_t*, uint32_t, int16_t);                                          
extern fw_err_t ysf_timer_disarm(struct ysf_timer_t*); 

extern fw_err_t ysf_cbTimer_init(struct ysf_timer_t*, fw_err_t (*)(void*), void*); 
extern fw_err_t ysf_evtTimer_init(struct ysf_timer_t*, fw_err_t (*)(uint16_t), uint16_t);
extern fw_err_t ysf_smTimer_init(struct ysf_timer_t*, fw_err_t (*)(void*, uint16_t), void*, uint16_t);

extern struct ysf_timer_t *ysf_cbSimpTimer_init(fw_err_t (*)(void*), void*);
extern struct ysf_timer_t *ysf_evtSimpTimer_init(fw_err_t (*)(uint16_t), uint16_t);
extern struct ysf_timer_t *ysf_smSimpTimer_init(fw_err_t (*)(void*, uint16_t), void*, uint16_t);
#endif

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif      /** framework timer component */

/**********************************END OF FILE*********************************/
