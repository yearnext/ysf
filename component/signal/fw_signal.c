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
 * @file       fw_signal.c                                                     *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-01-15                                                      *
 * @brief      signal component source files                                   *
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
 * @defgroup signal component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "core_path.h"
#include _FW_PATH
#include _FW_SIGNAL_COMPONENT_PATH
#include _FW_TIMER_COMPONENT_PATH
#include _FW_MEMORY_COMPONENT_PATH
#include _FW_TASK_COMPONENT_PATH
#include _FW_DEBUG_COMPONENT_PATH

/* Private define ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      detect signal status
 *******************************************************************************
 */
#define IS_SIGNAL_INFO_CHANGED(signal, nowInfo) ((signal)->SignalInfo != (nowInfo))

/**
 *******************************************************************************
 * @brief      update signal status
 *******************************************************************************
 */
#define TRANSFER_SIGNAL_STATUS(signal, status)  ((signal)->SignalStatus = (status))
#define UPDATE_SIGNAL_INFO(signal, info)        ((signal)->SignalInfo = (info))   

/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/                     
/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_SIGNAL_COMPONENT
/**
 *******************************************************************************
 * @brief       signal trigger handler
 * @param       [in/out]  *signal             signal block
 * @return      [in/out]  FW_ERR_NONE         no error
 * @note        this function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
fw_err_t signal_trigger_handler(struct SignalBlock *signal)
{
//    fw_assert(IS_PTR_NULL(signal));

#if defined(USE_MEMORY_COMPONENT) && USE_MEMORY_COMPONENT
    switch(signal->Type)
    {
        case SIMPLE_SIGNAL:
        case SIMPLE_EX_SIGNAL:
            CreateEventHandleExTask(signal->Handle.Simple, signal->SignalStatus);
            break;
        case COMPLEX_SIGNAL:
        case COMPLEX_EX_SIGNAL:
            CreateMessageHandleExTask(signal->Handle.Complex, (void*)signal, (uint16_t)signal->SignalStatus);
            break;
        default:
            break;
    }
#else
    switch(signal->Type)
    {
        case SIMPLE_SIGNAL:
        case SIMPLE_EX_SIGNAL:
            CreateEventHandleTask(&signal->Task, signal->Handle.Simple, signal->SignalStatus);
            break;
        case COMPLEX_SIGNAL:
        case COMPLEX_EX_SIGNAL:
            CreateMessageHandleTask(&signal->Task, signal->Handle.Complex, (void*)signal, (uint16_t)signal->SignalStatus);
            break;
        default:
            break;
    }
#endif    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       signal status judge
 * @param       [in/out]  *param              signal block
 * @param       [in/out]  event               signal status event
 * @return      [in/out]  FW_ERR_FAIL         judge failed
 * @return      [in/out]  FW_ERR_NONE         judge success
 * @note        None
 *******************************************************************************
 */
__STATIC_INLINE
fw_err_t signal_judge(void *param)
{
    fw_assert(IS_PTR_NULL(param));
    
    struct SignalBlock *signal = (struct SignalBlock *)param;
    
    fw_assert(IS_PTR_NULL(signal->Detect));
    
    uint8_t nowInfo = signal->Detect();
    
    switch( signal->SignalStatus )
    {
        case SIGNAL_STATUS_INIT:
            if(IS_SIGNAL_INFO_CHANGED(signal, nowInfo))
            {
                UPDATE_SIGNAL_INFO(signal, nowInfo);
                
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
                }
            }
            else
            {
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
                }
            }
            break;
        case SIGNAL_STATUS_PRESS_FILTER_STEP1:
            if(IS_SIGNAL_INFO_CHANGED(signal, nowInfo))
            {
                UPDATE_SIGNAL_INFO(signal, nowInfo);
                
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
                }
            }
            else
            {
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP2);
                }
            }
            break;
        case SIGNAL_STATUS_PRESS_FILTER_STEP2:
            if(IS_SIGNAL_INFO_CHANGED(signal, nowInfo))
            {
                UPDATE_SIGNAL_INFO(signal, nowInfo);
                
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
                }
            }
            else
            {
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP3);
                }
            }
            break;
        case SIGNAL_STATUS_PRESS_FILTER_STEP3:
            if(IS_SIGNAL_INFO_CHANGED(signal, nowInfo))
            {
                UPDATE_SIGNAL_INFO(signal, nowInfo);
                
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
                }
            }
            else
            {
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_EDGE);
                    signal_trigger_handler(signal);
                }
            }
            break;
        case SIGNAL_STATUS_RELEASE_FILTER_STEP1:
            if(IS_SIGNAL_INFO_CHANGED(signal, nowInfo))
            {
                UPDATE_SIGNAL_INFO(signal, nowInfo);
                
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
                }
            }
            else
            {
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP2);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
                }
            }
            break;
        case SIGNAL_STATUS_RELEASE_FILTER_STEP2:
            if(IS_SIGNAL_INFO_CHANGED(signal, nowInfo))
            {
                UPDATE_SIGNAL_INFO(signal, nowInfo);
                
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
                }
            }
            else
            {
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP3);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
                }
            }
            break;
        case SIGNAL_STATUS_RELEASE_FILTER_STEP3:
            if(IS_SIGNAL_INFO_CHANGED(signal, nowInfo))
            {
                UPDATE_SIGNAL_INFO(signal, nowInfo);
                
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
                }
            }
            else
            {
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_EDGE);
                    signal_trigger_handler(signal);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
                }
            }
            break;
        case SIGNAL_STATUS_RELEASE_EDGE:
            if(IS_SIGNAL_INFO_CHANGED(signal, nowInfo))
            {
                UPDATE_SIGNAL_INFO(signal, nowInfo);
                
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
                }
            }
            else
            {
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE);
                    signal_trigger_handler(signal);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
                }
            }
            break;
        case SIGNAL_STATUS_RELEASE:
            if(IS_SIGNAL_INFO_CHANGED(signal, nowInfo))
            {
                UPDATE_SIGNAL_INFO(signal, nowInfo);
                
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
                }
            }
            else
            {
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE);
                    signal_trigger_handler(signal);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
                }
            }
            break;
        case SIGNAL_STATUS_PRESS_EDGE:
            if(IS_SIGNAL_INFO_CHANGED(signal, nowInfo))
            {
                UPDATE_SIGNAL_INFO(signal, nowInfo);
                
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
                }
            }
            else
            {
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS);
                    signal_trigger_handler(signal);
                }
            }
            break;
        case SIGNAL_STATUS_PRESS:
            if(IS_SIGNAL_INFO_CHANGED(signal, nowInfo))
            {
                UPDATE_SIGNAL_INFO(signal, nowInfo);
                
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
                }
            }
            else
            {
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS);
                    signal_trigger_handler(signal);
                }
            }
            break;
        default:
            break;
    }

    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       signal component arm
 * @param       [in/out]  *signal           signal block
 * @param       [in/out]  *detect           signal detect function
 * @param       [in/out]  *handler          signal handler function
 * @return      [in/out]  FW_ERR_NONE       arm success
 * @return      [in/out]  FW_ERR_FAIL       arm failed
 * @note        None
 *******************************************************************************
 */
fw_err_t InitSimpleSignalModule(struct SignalBlock *signal, uint8_t (*detect)(void), fw_err_t (*handler)(uint16_t))
{
    fw_assert(IS_PTR_NULL(signal));
    fw_assert(IS_PTR_NULL(detect));
    fw_assert(IS_PTR_NULL(handler));
    
    signal->Detect            = detect;
    signal->Handle.Simple     = handler;
    signal->Type              = SIMPLE_SIGNAL;

    return FW_ERR_NONE;
}


/**
 *******************************************************************************
 * @brief       signal ex component arm
 * @param       [in/out]  *detect           signal detect function
 * @param       [in/out]  *handler          signal handler function
 * @return      [in/out]  NOT NULL          arm success
 * @return      [in/out]  NULL              arm failed
 * @note        None
 *******************************************************************************
 */
fw_err_t InitComplexSignalModule(struct SignalBlock* signal, uint8_t (*detect)(void), fw_err_t (*handler)(void*, uint16_t))
{
    fw_assert(IS_PTR_NULL(signal));
    fw_assert(IS_PTR_NULL(detect));
    fw_assert(IS_PTR_NULL(handler));

    signal->Detect            = detect;
    signal->Handle.Complex    = handler;
    signal->Type              = COMPLEX_SIGNAL;

    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       signal component arm
 * @param       [in/out]  *signal           signal block
 * @param       [in/out]  *detect           signal detect function
 * @param       [in/out]  *handler          signal handler function
 * @return      [in/out]  FW_ERR_NONE       arm success
 * @return      [in/out]  FW_ERR_FAIL       arm failed
 * @note        None
 *******************************************************************************
 */
struct SignalBlock *InitSimpleExSignalModule(uint8_t (*detect)(void), fw_err_t (*handler)(uint16_t))
{
#if defined(USE_MEMORY_COMPONENT) && USE_MEMORY_COMPONENT
    fw_assert(IS_PTR_NULL(detect));
    fw_assert(IS_PTR_NULL(handler));
    
    struct SignalBlock *signal = (struct SignalBlock *)MallocMemory(sizeof(struct SignalBlock *));
    fw_assert(IS_PTR_NULL(signal));
    
    signal->Detect            = detect;
    signal->Handle.Simple     = handler;
    signal->Type              = SIMPLE_EX_SIGNAL;

    return signal;
#else
    return NULL;
#endif
}

/**
 *******************************************************************************
 * @brief       signal ex component arm
 * @param       [in/out]  *detect           signal detect function
 * @param       [in/out]  *handler          signal handler function
 * @return      [in/out]  NOT NULL          arm success
 * @return      [in/out]  NULL              arm failed
 * @note        None
 *******************************************************************************
 */
struct SignalBlock *InitComplexExSignalModule(uint8_t (*detect)(void), fw_err_t (*handle)(void*, uint16_t))
{
#if defined(USE_MEMORY_COMPONENT) && USE_MEMORY_COMPONENT
    fw_assert(IS_PTR_NULL(detect));
    fw_assert(IS_PTR_NULL(handle));
    
    struct SignalBlock *signal = (struct SignalBlock *)MallocMemory(sizeof(struct SignalBlock));
    
    fw_assert(IS_PTR_NULL(signal));

    signal->Detect            = detect;
    signal->Handle.Complex    = handle;
    signal->Type              = COMPLEX_EX_SIGNAL;
    
    return signal;
#else
    return NULL;
#endif
}

/**
 *******************************************************************************
 * @brief       signal component arm
 * @param       [in/out]  *signal           signal block
 * @param       [in/out]  *detect           signal detect function
 * @param       [in/out]  *handler          signal handler function
 * @return      [in/out]  FW_ERR_NONE       arm success
 * @return      [in/out]  FW_ERR_FAIL       arm failed
 * @note        None
 *******************************************************************************
 */
fw_err_t ArmSignalModule(struct SignalBlock *signal, uint32_t scanTime, int16_t scanCount)
{
    fw_assert(IS_PTR_NULL(signal));
    
#if defined(USE_MEMORY_COMPONENT) && USE_MEMORY_COMPONENT
    signal->Timer = InitCallBackExTimer(signal_judge, (void *)signal);
    ArmTimerModule(signal->Timer, scanTime, scanCount);
#else
    InitCallBackExTimer(&signal->Timer, signal_judge, (void *)signal);
    ArmTimerModule(&signal->Timer, scanTime, scanCount);
#endif    
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       signal disarm
 * @param       [in/out]  *signal           signal block
 * @return      [in/out]  FW_ERR_NONE       disarm success
 * @note        None
 *******************************************************************************
 */
fw_err_t DisarmSignalModule(struct SignalBlock *signal)
{
    fw_assert(IS_PTR_NULL(signal));
    
#if defined(USE_MEMORY_COMPONENT) && USE_MEMORY_COMPONENT
    DisarmTimerModule(signal->Timer);
#else
    DisarmTimerModule(&signal->Timer);
#endif    

    return FW_ERR_NONE;
}

#endif

/** @}*/     /** signal component */

/**********************************END OF FILE*********************************/
