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
 * @file       fw_signal.c
 * @author     yearnext
 * @version    1.0.0
 * @date       2017-01-10
 * @brief      framework signal source files
 * @par        paltform                                  
 *                 Windows
 * @par        compiler									                         
 * 				   GCC
 *******************************************************************************
 * @note
 * 1.XXXXX                  						                     
 *******************************************************************************
 */

/**
 * @defgroup framework signal component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "fw_signal.h"
#include "fw_event.h"
#include "fw_debug.h"

/* Private define ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      detect signal status
 *******************************************************************************
 */
#define IS_SIGNAL_INFO_CHANGED(signal, nowInfo)  ((signal)->Filter != (nowInfo))
/**
 *******************************************************************************
 * @brief      update signal status
 *******************************************************************************
 */
#define TRANSFER_SIGNAL_STATUS(signal, state)    _ST((signal)->State = (state);)
#define UPDATE_SIGNAL_INFO(signal, info)         _ST((signal)->Filter = (info);)  
/**
 *******************************************************************************
 * @brief      update signal status
 *******************************************************************************
 */
#define SIGNAL_STATE_HANDLE(signal) \
                          _ST(Fw_Event_Post((signal)->TaskId, (signal)->State);)
        
/* Private typedef -----------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        defien signal block type
 *******************************************************************************
 */
struct Fw_Signal
{
    uint8_t         (*Scan)(void);
    Fw_Signal_State State;
    uint8_t         Filter;
    uint8_t         Value;
    uint8_t         TaskId;
    uint8_t         TriggerState;
};

/* Private variables ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        defien signal block
 *******************************************************************************
 */
#if USE_FRAMEWORK_SIGNAL_COMPONENT
static struct Fw_Signal Signal[SIGNAL_MAX];
#endif

/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
#if USE_FRAMEWORK_SIGNAL_COMPONENT
/**
 *******************************************************************************
 * @brief       signal init state handle
 * @param       [in/out]  nowSignal             signal block
 * @param       [in/out]  nowInfo               signal info
 * @return      [in/out]  void
 * @note        this function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
void InitState(struct Fw_Signal *nowSignal, uint8_t nowInfo)
{
    UPDATE_SIGNAL_INFO(nowSignal, nowInfo);
    if(IS_NO_SIGNAL(nowInfo))
    { 
        TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_RELEASE_FILTER_STATE);
    }
    else
    {
        TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_PRESS_STATE);
    }
}
/**
 *******************************************************************************
 * @brief       signal press filter state handle
 * @param       [in/out]  nowSignal             signal block
 * @param       [in/out]  nowInfo               signal info
 * @return      [in/out]  void
 * @note        this function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
void PressFilterState(struct Fw_Signal *nowSignal, uint8_t nowInfo)
{
    if(IS_NO_SIGNAL(nowInfo))
    {
        UPDATE_SIGNAL_INFO(nowSignal, nowInfo);
        TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_RELEASE_FILTER_STATE);
    }
    else
    {
        if (!IS_SIGNAL_INFO_CHANGED(nowSignal, nowInfo))
        {
            nowSignal->State = SIGNAL_PRESS_EDGE_STATE;
        }
        else
        {
            UPDATE_SIGNAL_INFO(nowSignal, nowInfo);
            TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_PRESS_STATE);
        }
    }
}
/**
 *******************************************************************************
 * @brief       signal release filter state handle
 * @param       [in/out]  nowSignal             signal block
 * @param       [in/out]  nowInfo               signal info
 * @return      [in/out]  void
 * @note        this function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
void ReleaseFilterState(struct Fw_Signal *nowSignal, uint8_t nowInfo)
{
    if(IS_NO_SIGNAL(nowInfo))
    {
        nowSignal->State = SIGNAL_RELEASE_EDGE_STATE;
    }
    else
    {
        UPDATE_SIGNAL_INFO(nowSignal, nowInfo);
        TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_PRESS_STATE);
    }
}
/**
 *******************************************************************************
 * @brief       signal press edge state handle
 * @param       [in/out]  nowSignal             signal block
 * @param       [in/out]  nowInfo               signal info
 * @return      [in/out]  void
 * @note        this function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
void PressEdgeState(struct Fw_Signal *nowSignal, uint8_t nowInfo)
{
    if(IS_NO_SIGNAL(nowInfo))
    {
        UPDATE_SIGNAL_INFO(nowSignal, nowInfo);
        TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_RELEASE_FILTER_STATE);
    }
    else
    {
        if (!IS_SIGNAL_INFO_CHANGED(nowSignal, nowInfo))
        {
            if (nowSignal->Value != nowInfo                \
                && IsRegPressEdgeState(nowSignal->TriggerState))
            {
                nowSignal->Value = nowInfo;
                SIGNAL_STATE_HANDLE(nowSignal);
            }
            else if(nowSignal->Value == nowInfo            \
                    && IsRegPressState(nowSignal->TriggerState))
            {
                nowSignal->Value = nowInfo;
                SIGNAL_STATE_HANDLE(nowSignal);
            }
            
            TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_PRESS_STATE);
        }
        else
        {
            UPDATE_SIGNAL_INFO(nowSignal, nowInfo);
            TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_PRESS_STATE);
        }
    }
}
/**
 *******************************************************************************
 * @brief       signal release edge state handle
 * @param       [in/out]  nowSignal             signal block
 * @param       [in/out]  nowInfo               signal info
 * @return      [in/out]  void
 * @note        this function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
void ReleaseEdgeState(struct Fw_Signal *nowSignal, uint8_t nowInfo)
{
    if(IS_NO_SIGNAL(nowInfo))
    {
        if (nowSignal->Value != nowInfo                  \
            && IsRegReleaseEdgeState(nowSignal->TriggerState))
        {
            nowSignal->Value = nowInfo;
            
            SIGNAL_STATE_HANDLE(nowSignal);
        }
        
        TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_RELEASE_STATE);
    }
    else
    {
        UPDATE_SIGNAL_INFO(nowSignal, nowInfo);
        TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_PRESS_STATE);
    }
}
/**
 *******************************************************************************
 * @brief       signal press state handle
 * @param       [in/out]  nowSignal             signal block
 * @param       [in/out]  nowInfo               signal info
 * @return      [in/out]  void
 * @note        this function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
void PressState(struct Fw_Signal *nowSignal, uint8_t nowInfo)
{
    if(IS_NO_SIGNAL(nowInfo))
    {
        UPDATE_SIGNAL_INFO(nowSignal, nowInfo);
        TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_RELEASE_FILTER_STATE);
    }
    else
    {
        if (!IS_SIGNAL_INFO_CHANGED(nowSignal, nowInfo))
        {
            if (IsRegPressState(nowSignal->TriggerState))
            {
                SIGNAL_STATE_HANDLE(nowSignal);
            }
        }
        else
        {
            UPDATE_SIGNAL_INFO(nowSignal, nowInfo);
            TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_PRESS_STATE);
        }
    }
}
/**
 *******************************************************************************
 * @brief       signal release state handle
 * @param       [in/out]  nowSignal             signal block
 * @param       [in/out]  nowInfo               signal info
 * @return      [in/out]  void
 * @note        this function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
void ReleaseState(struct Fw_Signal *nowSignal, uint8_t nowInfo)
{
    if(IS_NO_SIGNAL(nowInfo))
    {
        if (IsRegReleaseState(nowSignal->TriggerState))
        {
            SIGNAL_STATE_HANDLE(nowSignal);
        }
    }
    else
    {
        UPDATE_SIGNAL_INFO(nowSignal, nowInfo);
        TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_PRESS_STATE);
    }
}

/**
 *******************************************************************************
 * @brief       signal detection functon
 * @param       [in/out]  signal         signal
 * @param       [in/out]  nowSignal->Status        signal status
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
static inline
void Fw_Signal_Detection(struct Fw_Signal *nowSignal)
{
    uint8_t nowInfo;

    nowInfo = nowSignal->Scan();
    
    switch(nowSignal->State)
    {
        case SIGNAL_INIT_STATE:
            InitState(nowSignal, nowInfo);
            break;
        case SIGNAL_PRESS_FILTER_STATE:
            PressFilterState(nowSignal, nowInfo);
            break;
        case SIGNAL_RELEASE_FILTER_STATE:
            ReleaseFilterState(nowSignal, nowInfo);
            break;
        case SIGNAL_PRESS_EDGE_STATE:
            PressEdgeState(nowSignal, nowInfo);
            break;
        case SIGNAL_PRESS_STATE:
            PressState(nowSignal, nowInfo);
            break;
        case SIGNAL_RELEASE_EDGE_STATE:
            ReleaseEdgeState(nowSignal, nowInfo);
            break;
        case SIGNAL_RELEASE_STATE:
            ReleaseState(nowSignal, nowInfo);
            break;
        default:
            break;
    }
}

/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       signal component init
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Fw_Signal_InitComponent(void)
{
    uint8_t i = 0;

    for( i=0; i<SIGNAL_MAX; i++ )
    {
        Signal[i].Scan   = NULL;
        Signal[i].TaskId = 0;
        Signal[i].State  = SIGNAL_INIT_STATE;
        Signal[i].Value  = 0xFF;
        Signal[i].Filter = 0xFF;
    }
    
    Fw_Event_Register(FW_SIGNAL_TASK, Fw_Signal_Poll);
    Fw_Timer_Init(SIGNAL_SCAN_TIMER, FW_SIGNAL_TASK, FW_DELAY_EVENT, NULL);
    Fw_Timer_Start(SIGNAL_SCAN_TIMER, FW_TIMER_PERIOD_MODE, FW_SIGNAL_SCAN_PREIOD);
    Fw_Event_Post(FW_SIGNAL_TASK, FW_SIGNAL_EVENT);
}

/**
 *******************************************************************************
 * @brief       signal component register
 * @param       [in/out]  task                     task id
 * @param       [in/out]  signal                   signal id
 * @param       [in/out]  *scan                    signal scan function
 * @return      [in/out]  fw_err_t                 register status
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Signal_Init(uint8_t signalId, uint8_t taskId, uint8_t (*scan)(void), uint8_t registerState)
{
    if( signalId > SIGNAL_MAX )
    {
        return FW_ERR_FAIL;
    }
    
    if( taskId > FW_TASK_MAX )
    {
        return FW_ERR_FAIL;
    }
    
    if(scan == NULL)
    {
        return FW_ERR_FAIL;
    }

    Signal[signalId].Scan         = scan;
    Signal[signalId].TaskId       = taskId;
    Signal[signalId].TriggerState = registerState;
    Signal[signalId].State        = SIGNAL_INIT_STATE;
    Signal[signalId].Value        = 0;
    Signal[signalId].Filter       = 0;

    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       signal component event logon
 * @param       [in/out]  signalId                   signal id
 * @param       [in/out]  logonEvent               logon event
 * @return      [in/out]  fw_err_t                 register status
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Signal_RegisterState(uint8_t signalId, uint8_t logonEvent)
{
    if (signalId > SIGNAL_MAX)
    {
        return FW_ERR_FAIL;
    }
    
    Signal[signalId].TriggerState |= logonEvent;
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       signal component event logout
 * @param       [in/out]  signalId                 signal id
 * @param       [in/out]  logoutEvent              logout event
 * @return      [in/out]  fw_err_t                 register status
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Signal_UnregisterState(uint8_t signalId, uint8_t logoutEvent)
{
    if (signalId > SIGNAL_MAX)
    {
        return FW_ERR_FAIL;
    }
    
    Signal[signalId].TriggerState &= ~logoutEvent;
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       get signal info
 * @param       [in/out]  signalId    signal id
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
uint8_t Fw_Signal_GetInfo(uint8_t signalId)
{
    if (signalId > SIGNAL_MAX)
    {
        return 0;
    }

    return Signal[signalId].Value;
}

/**
 *******************************************************************************
 * @brief       signal handler
 * @param       [in/out]  event         trigger events
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Fw_Signal_Poll(uint8_t event)
{
    uint8_t i = 0;

    for( i=0; i<SIGNAL_MAX; i++ )
    {
        if( !IS_PTR_NULL(Signal[i].Scan) )
        {
            Fw_Signal_Detection(&Signal[i]);
        }
    }
}
#endif

/** @}*/     /** framework signal component  */

/**********************************END OF FILE*********************************/
