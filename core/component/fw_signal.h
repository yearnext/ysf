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
 * @file       fw_signal.h                                                     *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-01-15                                                      *
 * @brief      signal component head files                                     *
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SIGNAL_COMPONENT_H__
#define __SIGNAL_COMPONENT_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "core_path.h"
#include _FW_PATH
#include _FW_EVENT_COMPONENT_PATH
#include _FW_LINK_LIST_COMPONENT_PATH
#include _FW_TASK_COMPONENT_PATH
#include _FW_TIMER_COMPONENT_PATH

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       framework component config flags
 * @note        1                        enable
 * @note        0                        disable
 *******************************************************************************
 */
#ifdef USE_FRAMEWORK_SIGNAL_SCAN_COMPONENT
#if USE_FRAMEWORK_SIGNAL_SCAN_COMPONENT
#define USE_SIGNAL_COMPONENT                                                 (1)
#else
#define USE_SIGNAL_COMPONENT                                                 (0)
#endif

/**
 *******************************************************************************
 * @brief       user config flags
 * @note        1         enable
 * @note        0         disable
 *******************************************************************************
 */
#else
#define USE_SIGNAL_COMPONENT                                                 (1)
#endif
    
/**
 *******************************************************************************
 * @brief       config signal time
 *******************************************************************************
 */
#define SIGNAL_SCAN_TIME        (10)
#define SIGNAL_TIME2COUNT(n)    ((n)/TIME_2_TICK(SIGNAL_SCAN_TIME))
   
/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define signal status enumeration
 *******************************************************************************
 */
//#define SIGNAL_STATUS_INIT                                                   (0)  
//#define SIGNAL_STATUS_DETECT                                                 (1)
//#define SIGNAL_STATUS_HANDLER                                                (2)
//    
//#define SIGNAL_STATUS_PRESS_FILTER_STEP1                                     (3)
//#define SIGNAL_STATUS_PRESS_FILTER_STEP2                                     (4)
//#define SIGNAL_STATUS_PRESS_FILTER_STEP3                                     (5)
//#define SIGNAL_STATUS_RELEASE_FILTER_STEP1                                   (6)
//#define SIGNAL_STATUS_RELEASE_FILTER_STEP2                                   (7)
//#define SIGNAL_STATUS_RELEASE_FILTER_STEP3                                   (8)

//#define SIGNAL_STATUS_RELEASE                                                (9)
//#define SIGNAL_STATUS_PRESS_EDGE                                            (10)
//#define SIGNAL_STATUS_PRESS                                                 (11)
//#define SIGNAL_STATUS_LONG_PRESS                                            (12)
//#define SIGNAL_STATUS_MULTI_PRESS                                           (13)
//#define SIGNAL_STATUS_RELEASE_EDGE                                          (14)
enum SignalStatus
{
    SIGNAL_STATUS_INIT,
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
 * @brief       define signal info param
 *******************************************************************************
 */
#define NO_SIGNAL_INFO                                                       (0)
#define IS_NO_SIGNAL(signal)                        ((signal) == NO_SIGNAL_INFO)

#define SIGNAL_CYCLE_MODE                                       TIMER_CYCLE_MODE

/**
 *******************************************************************************
 * @brief       define signal type
 *******************************************************************************
 */
struct SignalBlock
{
    struct SignalBlock *Next;
    
    uint8_t             (*Detect)(void);
    
    union
    {
        fw_err_t        (*Simple)(uint16_t);
        fw_err_t        (*Complex)(void*, uint16_t);
    }Handle;

#if defined(USE_MEMORY_COMPONENT) && USE_MEMORY_COMPONENT
    struct TimerBlock   *Timer;
#else
    struct TimerBlock   Timer;
    struct TaskBlock    Task;
#endif
    
    uint8_t             SignalInfo;
    
    enum SignalStatus   SignalStatus;

    enum
    {
        SIMPLE_SIGNAL,
        SIMPLE_EX_SIGNAL,
        COMPLEX_SIGNAL,
        COMPLEX_EX_SIGNAL,
    }Type;
};

/**
 *******************************************************************************
 * @brief       signal component interface
 *******************************************************************************
 */
#if USE_SIGNAL_COMPONENT
typedef struct
{
    fw_err_t                (*GetInfo)(struct SignalBlock*, uint8_t*);
    
    fw_err_t                (*Arm)(struct SignalBlock*, uint32_t, int16_t);
    fw_err_t                (*Disarm)(struct SignalBlock*);
    
    struct
    {
        fw_err_t            (*Simple)(struct SignalBlock*, uint8_t (*)(void), fw_err_t (*)(uint16_t));
        fw_err_t            (*Complex)(struct SignalBlock*, uint8_t (*)(void), fw_err_t (*)(void*, uint16_t));
        
        struct SignalBlock* (*SimpleEx)(uint8_t (*)(void), fw_err_t (*)(uint16_t));
        struct SignalBlock* (*ComplexEx)(uint8_t (*)(void), fw_err_t (*)(void*, uint16_t));
    }Create;
}SignalComponentInterface;
#endif

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       signal component api
 *******************************************************************************
 */
#if USE_SIGNAL_COMPONENT
extern fw_err_t GetSignalInfo(struct SignalBlock*, uint8_t*);

extern fw_err_t ArmSignalModule(struct SignalBlock*, uint32_t, int16_t);
extern fw_err_t DisarmSignalModule(struct SignalBlock*);

extern fw_err_t InitSimpleSignalModule(struct SignalBlock*, uint8_t (*)(void), fw_err_t (*)(uint16_t));   
extern fw_err_t InitComplexSignalModule(struct SignalBlock*, uint8_t (*)(void), fw_err_t (*)(void*, uint16_t)); 

extern struct SignalBlock *InitSimpleExSignalModule(uint8_t (*)(void), fw_err_t (*)(uint16_t));                                  
extern struct SignalBlock *InitComplexExSignalModule(uint8_t (*)(void), fw_err_t (*)(void*, uint16_t));       
                                                                 
#endif
                                       
/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** signal component */

/**********************************END OF FILE*********************************/
