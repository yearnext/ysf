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
 * @file       ysf_task.h                                                      *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-03-28                                                      *
 * @brief      ysf task head files                                             *
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
 * @defgroup ysf task
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __YSF_TASK_H__
#define __YSF_TASK_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "ysf_conf.h"
#include "ysf_path.h"
#include YSF_TYPE_PATH

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       ysf config
 *******************************************************************************
 */
#ifdef USE_YSF_TASK_COMPONENT
#if USE_YSF_TASK_COMPONENT
#define USE_YSF_TASK_API (1)
#else
#define USE_YSF_TASK_API (0)
#endif

/**
 *******************************************************************************
 * @brief       user config
 *******************************************************************************
 */
#else
#define USE_YSF_TASK_API (1)
#endif

/* Exported types ------------------------------------------------------------*/    
/**
 *******************************************************************************
 * @brief       ysf task block
 *******************************************************************************
 */
struct ysf_task_t
{
    struct
    {
        struct ysf_task_t    *next;
        
        enum ysf_task_type_t
        {
            YSF_CALL_BACK_TASK,
            YSF_EVENT_HANDLER_TASK,
            YSF_STATE_MECHINE_TASK,
        }type;
    };
    
    struct
    {                
        union
        {
            ysf_err_t (*sm)(void*, uint16_t);
            ysf_err_t (*evt)(uint16_t);
            ysf_err_t (*cb)(void*);
        }handler;

        void *param;
        uint16_t evt;
    };
};

/**
 *******************************************************************************
 * @brief       ysf task api
 *******************************************************************************
 */
#if defined(USE_YSF_TASK_API) && USE_YSF_TASK_API
struct YSF_TASK_API
{
    ysf_err_t (*init)(void);
    ysf_err_t (*poll)(void);
    
    struct
    {
        ysf_err_t (*cb)(struct ysf_task_t*, ysf_err_t (*)(void*), void*);
        ysf_err_t (*evt)(struct ysf_task_t*, ysf_err_t (*)(uint16_t), uint16_t);
        ysf_err_t (*sm)(struct ysf_task_t*, ysf_err_t (*)(void*, uint16_t), void*, uint16_t);
        
        struct
        {
            struct ysf_task_t *(*cb)(ysf_err_t (*)(void*), void*);
            struct ysf_task_t *(*evt)(ysf_err_t (*)(uint16_t), uint16_t);
            struct ysf_task_t *(*sm)(ysf_err_t (*)(void*, uint16_t), void*, uint16_t);
        }simple;
    }create;
};
#endif

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if defined(USE_YSF_TASK_API) && USE_YSF_TASK_API
extern ysf_err_t ysf_task_init(void);
extern ysf_err_t ysf_task_poll(void);

extern ysf_err_t ysf_cbTask_create(struct ysf_task_t*, ysf_err_t (*)(void*), void*);
extern ysf_err_t ysf_evtTask_create(struct ysf_task_t*, ysf_err_t (*)(uint16_t), uint16_t);
extern ysf_err_t ysf_smTask_create(struct ysf_task_t*, ysf_err_t (*)(void*, uint16_t), void*, uint16_t);

extern struct ysf_task_t *ysf_cbSimpTask_create(ysf_err_t (*)(void*), void*);
extern struct ysf_task_t *ysf_evtSimpTask_create(ysf_err_t (*)(uint16_t), uint16_t);
extern struct ysf_task_t *ysf_smSimpTask_create(ysf_err_t (*)(void*, uint16_t), void*, uint16_t);
#endif    
    
/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** ysf task component  */

/**********************************END OF FILE*********************************/
