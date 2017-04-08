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
 * @file       ysf_timer.h                                                     *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-07-09                                                      *
 * @brief      ysf timer head files                                            *
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
#ifndef __YSF_TIMER_H__
#define __YSF_TIMER_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "ysf_conf.h"
#include "ysf_path.h"
#include YSF_TYPE_PATH
#include YSF_COMPONENT_TASK_PATH
#include YSF_COMPONENT_TICK_PATH
#include YSF_COMPONENT_SINGLE_LIST_PATH

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        ysf config
 *******************************************************************************
 */
#ifdef USE_YSF_TIMER_COMPONENT
#if USE_YSF_TIMER_COMPONENT
#define USE_YSF_TIMER_API        (1)
#else
#define USE_YSF_TIMER_API        (0)
#endif

/**
 *******************************************************************************
 * @brief        user config
 *******************************************************************************
 */
#else
#define USE_YSF_TIMER_API        (1)
#endif

/**
 *******************************************************************************
 * @brief       ysf timer tick config
 *******************************************************************************
 */
#define YSF_TIMER_PERIOD         YSF_TICK_TIME
#define YSF_TIME_2_TICK(time)    ((time)/YSF_TIMER_PERIOD)

#define YSF_TIMER_CYCLE_PARAM    (-1)

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
        ysf_tick_t ticks;
        ysf_tick_t loadTicks;
        
        int16_t    cycle;
    };
};

/**
 *******************************************************************************
 * @brief      interface function defineitions 
 *******************************************************************************
 */
#if defined(USE_YSF_TIMER_API) && USE_YSF_TIMER_API
struct YSF_TIMER_API
{
    ysf_err_t (*init)(void);
    ysf_err_t (*handler)(uint16_t);

    ysf_err_t (*arm)(struct ysf_timer_t*, uint32_t, int16_t);
    ysf_err_t (*disarm)(struct ysf_timer_t*);
    
    bool (*getStatus)(struct ysf_timer_t*);
    
    struct
    {
        ysf_err_t (*cb_init)(struct ysf_timer_t*, ysf_err_t (*)(void*), void*);
        ysf_err_t (*evt_init)(struct ysf_timer_t*, ysf_err_t (*)(uint16_t), uint16_t);
        ysf_err_t (*sm_init)(struct ysf_timer_t*, ysf_err_t (*)(void*, uint16_t), void*, uint16_t);
    };
    
    struct
    {
        struct ysf_timer_t *(*cb_init)(ysf_err_t (*)(void*), void*);
        struct ysf_timer_t *(*evt_init)(ysf_err_t (*)(uint16_t), uint16_t);
        struct ysf_timer_t *(*sm_init)(ysf_err_t (*)(void*, uint16_t), void*, uint16_t);
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
#if defined(USE_YSF_TIMER_API) && USE_YSF_TIMER_API
extern ysf_err_t ysf_timer_init(void);

extern ysf_err_t ysf_timer_handler(uint16_t);

extern bool ysf_timerGetStatus(struct ysf_timer_t*);

extern ysf_err_t ysf_timer_arm(struct ysf_timer_t*, uint32_t, int16_t);                                          
extern ysf_err_t ysf_timer_disarm(struct ysf_timer_t*); 

extern ysf_err_t ysf_cbTimer_init(struct ysf_timer_t*, ysf_err_t (*)(void*), void*); 
extern ysf_err_t ysf_evtTimer_init(struct ysf_timer_t*, ysf_err_t (*)(uint16_t), uint16_t);
extern ysf_err_t ysf_smTimer_init(struct ysf_timer_t*, ysf_err_t (*)(void*, uint16_t), void*, uint16_t);

extern struct ysf_timer_t *ysf_cbSimpTimer_init(ysf_err_t (*)(void*), void*);
extern struct ysf_timer_t *ysf_evtSimpTimer_init(ysf_err_t (*)(uint16_t), uint16_t);
extern struct ysf_timer_t *ysf_smSimpTimer_init(ysf_err_t (*)(void*, uint16_t), void*, uint16_t);
#endif

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif      /** timer */
/**********************************END OF FILE*********************************/
