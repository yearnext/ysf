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
 * @file       fw_task.h                                                       *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-03-28                                                      *
 * @brief      framework task component head files                             *
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
 * @defgroup framework task component
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FRAMEWORK_TASK_COMPONENT_H__
#define __FRAMEWORK_TASK_COMPONENT_H__

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
#ifdef USE_FRAMEWORK_TASK_COMPONENT
#if USE_FRAMEWORK_TASK_COMPONENT
#define USE_FRAMEWORK_TASK_API                                               (1)
#else
#define USE_FRAMEWORK_TASK_API                                               (0)
#endif

/**
 *******************************************************************************
 * @brief       user config flags
 * @note        1         enable
 * @note        0         disable
 *******************************************************************************
 */
#else
#define USE_FRAMEWORK_TASK_API                                               (1)
#endif

/* Exported types ------------------------------------------------------------*/    
/**
 *******************************************************************************
 * @brief       task block
 *******************************************************************************
 */
struct fw_task_t
{
    struct fw_task_t *next;
    
    union
    {
        fw_err_t (*sm)(void*, uint16_t);
        fw_err_t (*evt)(uint16_t);
        fw_err_t (*cb)(void*);
    }handler;

    void *param;
    uint16_t evt;

    enum fw_task_type_t
    {
        FW_CALL_BACK_TASK,
        FW_EVENT_HANDLER_TASK,
        FW_STATE_MECHINE_TASK,
    }type;
};

/**
 *******************************************************************************
 * @brief       framework task api
 *******************************************************************************
 */
#if USE_FRAMEWORK_TASK_API
struct YSF_TASK_API
{
    fw_err_t (*Init)(void);
    fw_err_t (*Poll)(void);
    
    struct
    {
        fw_err_t (*Cb)(struct fw_task_t*, fw_err_t (*)(void*), void*);
        fw_err_t (*Evt)(struct fw_task_t*, fw_err_t (*)(uint16_t), uint16_t);
        fw_err_t (*Sm)(struct fw_task_t*, fw_err_t (*)(void*, uint16_t), void*, uint16_t);
        
        struct fw_task_t *(*CbEx)(fw_err_t (*)(void*), void*);
        struct fw_task_t *(*EvtEx)(fw_err_t (*)(uint16_t), uint16_t);
        struct fw_task_t *(*SmEx)(fw_err_t (*)(void*, uint16_t), void*, uint16_t);
    }create;
};
#endif

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_FRAMEWORK_TASK_API
extern fw_err_t fwTaskInit(void);
extern fw_err_t fwTaskPoll(void);

extern fw_err_t fw_cbTask_create(struct fw_task_t*, fw_err_t (*)(void*), void*);
extern fw_err_t fw_evtTask_create(struct fw_task_t*, fw_err_t (*)(uint16_t), uint16_t);
extern fw_err_t fw_smTask_create(struct fw_task_t*, fw_err_t (*)(void*, uint16_t), void*, uint16_t);

extern struct fw_task_t *fw_cbExTask_create(fw_err_t (*)(void*), void*);
extern struct fw_task_t *fw_evtExTask_create(fw_err_t (*)(uint16_t), uint16_t);
extern struct fw_task_t *fw_smExTask_create(fw_err_t (*)(void*, uint16_t), void*, uint16_t);
#endif    
    
/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** framework task component  */

/**********************************END OF FILE*********************************/
