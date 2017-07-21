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
#include <string.h>
#include "core_path.h"
#include _FW_PATH
#include _FW_SIGNAL_COMPONENT_PATH
#include _FW_TIMER_COMPONENT_PATH
#include _FW_TASK_COMPONENT_PATH
#include _FW_LINK_LIST_COMPONENT_PATH
#include _FW_DEBUG_COMPONENT_PATH

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
#define TRANSFER_SIGNAL_STATUS(signal, status) _ST((signal)->Status = (status);)
#define UPDATE_SIGNAL_INFO(signal, info)         _ST((signal)->Filter = (info);)  

/**
 *******************************************************************************
 * @brief      update signal status
 *******************************************************************************
 */
#define SIGNAL_STATE_HANDLE(signal)                                            \
    _ST(Fw_Task_PostMessage((signal)->TaskId,                                  \
                            (void *)(signal),                                  \
                            FW_SIGNAL_HANDLE_EVENT);)

/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/   
#if USE_SIGNAL_COMPONENT
/**
 *******************************************************************************
 * @brief        Signal Init State Handle
 *******************************************************************************
 */
__STATIC_INLINE
void InitState(struct Fw_Signal *nowSignal, uint8_t nowInfo)
{
	UPDATE_SIGNAL_INFO(nowSignal, nowInfo);

	if(IS_NO_SIGNAL(nowInfo))
	{ 
		TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_RELEASE_FILTER);
	}
	else
	{
		TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_PRESS_FILTER);
	}
}

/**
 *******************************************************************************
 * @brief        Signal Press Filter State Handle
 *******************************************************************************
 */
__STATIC_INLINE
void PressFilterState(struct Fw_Signal *nowSignal, uint8_t nowInfo)
{
	if(IS_NO_SIGNAL(nowInfo))
	{
		UPDATE_SIGNAL_INFO(nowSignal, nowInfo);
		TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_RELEASE_FILTER);
	}
	else
	{
		if (!IS_SIGNAL_INFO_CHANGED(nowSignal, nowInfo))
		{
			nowSignal->Status = SIGNAL_STATUS_PRESS_EDGE;
		}
		else
		{
			UPDATE_SIGNAL_INFO(nowSignal, nowInfo);
			TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_PRESS_FILTER);
		}
	}
}

/**
 *******************************************************************************
 * @brief        Signal Release Filter State Handle
 *******************************************************************************
 */
__STATIC_INLINE
void ReleaseFilterState(struct Fw_Signal *nowSignal, uint8_t nowInfo)
{
	if(IS_NO_SIGNAL(nowInfo))
	{
		nowSignal->Status = SIGNAL_STATUS_RELEASE_EDGE;
	}
	else
	{
		UPDATE_SIGNAL_INFO(nowSignal, nowInfo);
		TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_PRESS_FILTER);
	}
}

/**
 *******************************************************************************
 * @brief        Signal Press Edge State Handle
 *******************************************************************************
 */
__STATIC_INLINE
void PressEdgeState(struct Fw_Signal *nowSignal, uint8_t nowInfo)
{
	if(IS_NO_SIGNAL(nowInfo))
	{
		UPDATE_SIGNAL_INFO(nowSignal, nowInfo);
		TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_RELEASE_FILTER);
	}
	else
	{
		if (!IS_SIGNAL_INFO_CHANGED(nowSignal, nowInfo))
		{
			if (nowSignal->Value != nowInfo                \
			    && IsLogonPressEdgeEvent(nowSignal->TriggerEvent))
			{
                nowSignal->Value = nowInfo;
				SIGNAL_STATE_HANDLE(nowSignal);
			}
			else if(nowSignal->Value == nowInfo            \
					&& IsLogonPressEvent(nowSignal->TriggerEvent))
			{
                nowSignal->Value = nowInfo;
				SIGNAL_STATE_HANDLE(nowSignal);
			}
			
			TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_PRESS);
		}
		else
		{
			UPDATE_SIGNAL_INFO(nowSignal, nowInfo);
			TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_PRESS_FILTER);
		}
	}
}

/**
 *******************************************************************************
 * @brief        Signal Release Edge State Handle
 *******************************************************************************
 */
__STATIC_INLINE
void ReleaseEdgeState(struct Fw_Signal *nowSignal, uint8_t nowInfo)
{
	if(IS_NO_SIGNAL(nowInfo))
	{
		if (nowSignal->Value != nowInfo                  \
		    && IsLogonReleaseEdgeEvent(nowSignal->TriggerEvent))
		{
            nowSignal->Value = nowInfo;
            
            SIGNAL_STATE_HANDLE(nowSignal);
		}
		
		TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_RELEASE);
	}
	else
	{
		UPDATE_SIGNAL_INFO(nowSignal, nowInfo);
		TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_PRESS_FILTER);
	}
}

/**
 *******************************************************************************
 * @brief        Signal Press State Handle
 *******************************************************************************
 */
__STATIC_INLINE
void PressState(struct Fw_Signal *nowSignal, uint8_t nowInfo)
{
	if(IS_NO_SIGNAL(nowInfo))
	{
		UPDATE_SIGNAL_INFO(nowSignal, nowInfo);
		TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_RELEASE_FILTER);
	}
	else
	{
		if (!IS_SIGNAL_INFO_CHANGED(nowSignal, nowInfo))
		{
			if (IsLogonPressEvent(nowSignal->TriggerEvent))
			{
				SIGNAL_STATE_HANDLE(nowSignal);
			}
		}
		else
		{
			UPDATE_SIGNAL_INFO(nowSignal, nowInfo);
			TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_PRESS_FILTER);
		}
	}
}

/**
 *******************************************************************************
 * @brief        Signal Release State Handle
 *******************************************************************************
 */
__STATIC_INLINE
void ReleaseState(struct Fw_Signal *nowSignal, uint8_t nowInfo)
{
	if(IS_NO_SIGNAL(nowInfo))
	{
		if (IsLogonReleaseEvent(nowSignal->TriggerEvent))
		{
			SIGNAL_STATE_HANDLE(nowSignal);
		}
	}
	else
	{
		UPDATE_SIGNAL_INFO(nowSignal, nowInfo);
		TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_PRESS_FILTER);
	}
}

//typedef void (*Signal_State)(struct Fw_Signal*, uint8_t);

//static const Signal_State StateTab[] = 
//{
//    InitState,
//    PressFilterState,
//    ReleaseFilterState,
//    PressEdgeState,
//    ReleaseEdgeState,
//    PressState,
//    ReleaseState,
//};

void SignalDetection(struct Fw_Signal *nowSignal)
{
    uint8_t nowInfo;

    nowInfo = nowSignal->Scan();
    
    switch(nowSignal->Status)
    {
		case SIGNAL_STATUS_INIT:
			InitState(nowSignal, nowInfo);
			break;
		case SIGNAL_STATUS_PRESS_FILTER:
			PressFilterState(nowSignal, nowInfo);
			break;
		case SIGNAL_STATUS_RELEASE_FILTER:
			ReleaseFilterState(nowSignal, nowInfo);
			break;
		case SIGNAL_STATUS_PRESS_EDGE:
			PressEdgeState(nowSignal, nowInfo);
			break;
		case SIGNAL_STATUS_PRESS:
			PressState(nowSignal, nowInfo);
			break;
		case SIGNAL_STATUS_RELEASE_EDGE:
			ReleaseEdgeState(nowSignal, nowInfo);
			break;
		case SIGNAL_STATUS_RELEASE:
			ReleaseState(nowSignal, nowInfo);
			break;
        default:
            break;
    }
}

void Fw_Signal_Poll(void)
{
    
}

struct _Fw_Signal_Block
{
    struct Fw_Signal *Head;
    struct Fw_Signal *Tail;
    
    uint8_t Num;
};

static struct _Fw_Signal_Block SignalBlock;

fw_err_t Fw_Signal_Init(void)
{
    memset(&SignalBlock, 0, sizeof(SignalBlock));
    
    Fw_Task_Create(FW_SIGNAL_TASK, "Framework Signal Task", (void *)Fw_Signal_Poll, FW_SIMPLE_TASK);
    
    return FW_ERR_NONE;
}

fw_err_t Fw_Signal_Create(struct Fw_Signal *signal, char *str, uint8_t taskId)
{
    Fw_Assert(IS_PTR_NUL(timer));
    
    signal->String = str;
    signal->TaskId = taskId;

    return FW_ERR_NONE;
}

fw_err_t Fw_Signal_Start(struct Fw_Signal *signal, uint8_t triggerEvent, uint32_t tick, int16_t count)
{
//    Fw_Assert(IS_PTR_NUL(timer));
//    
//    struct Fw_Signal *signalBlock = &SignalBlock;
//        
//    signal->InitTick    = tick;
//    timer->TimeOutTick = tick + Fw_GetTick();
//    timer->Cycle       = count;
//    
//    p_PushLinkListNode(timerBlock, timer);
    
    SignalBlock.Num++;
    
    return FW_ERR_NONE;
}

///**
// *******************************************************************************
// * @brief       ysf signal control block
// *******************************************************************************
// */
//static CREATE_SINGLE_LIST_FIFO_CONTROL_BLOCK(struct SignalBlock, SignalControlBlock);

///**
// *******************************************************************************
// * @brief       signal timer
// *******************************************************************************
// */
//static struct TimerBlock SignalTimer;

//struct
//{
//    struct SignalBlock *Head;
//    
//    uint8_t Flag;
//    uint8_t Count;
//}static SignalPollBlock;
//#endif

///* Exported variables --------------------------------------------------------*/
///* Private functions ---------------------------------------------------------*/
///* Exported functions --------------------------------------------------------*/
//#if USE_SIGNAL_COMPONENT
///**
// *******************************************************************************
// * @brief       detect the signal is in queue
// * @param       [in/out]  signal               will detect signal
// * @return      [in/out]  true                 the signal in the queue
// * @return      [in/out]  true                 the signal not in the queue
// * @note        this function is static inline type
// *******************************************************************************
// */
//__STATIC_INLINE
//bool signal_is_in(struct SignalBlock *signal)
//{
//    IsInSingleLinkListFifo(struct SignalBlock, SignalControlBlock, signal);
//    
//    return false;
//}

///**
// *******************************************************************************
// * @brief       pop signal to queue
// * @param       [in/out]  signal              will signal task
// * @return      [in/out]  FW_ERR_NONE         no error
// * @note        this function is static inline type
// *******************************************************************************
// */
//__STATIC_INLINE
//fw_err_t signal_push(struct SignalBlock *signal)
//{
//    PushSingleLinkListFifoNode(signal_is_in, SignalControlBlock, signal);
//    
//    return FW_ERR_NONE;
//}

///**
// *******************************************************************************
// * @brief       push signal from queue
// * @param       [in/out]  void
// * @return      [in/out]  struct SignalBlock *     push timer addr in memory
// * @note        this function is static inline type
// *******************************************************************************
// */
//__STATIC_INLINE
//struct SignalBlock *signal_pop(void)
//{
//    struct SignalBlock *signal = NULL;
//    
//    PopSingleLinkListFifoNode(SignalControlBlock, signal);
//    
//    return signal;
//}

///**
// *******************************************************************************
// * @brief       signal queue clear
// * @param       [in/out]  void
// * @return      [in/out]  FW_ERR_NONE         no error
// * @note        this function is static inline type
// *******************************************************************************
// */
//__STATIC_INLINE
//fw_err_t signal_clear(void)
//{    
//    while(signal_pop() != NULL);
//    
//    return FW_ERR_NONE;
//}

///**
// *******************************************************************************
// * @brief       signal trigger handler
// * @param       [in/out]  *signal             signal block
// * @return      [in/out]  FW_ERR_NONE         no error
// * @note        this function is static inline type
// *******************************************************************************
// */
//__STATIC_INLINE
//fw_err_t signal_trigger_handler(struct SignalBlock *signal)
//{
////    fw_assert(IS_PTR_NULL(signal));
//    signal->Task.Event = signal->Status;
//    ArmTaskModule(&signal->Task);
//    
//    return FW_ERR_NONE;
//}

///**
// *******************************************************************************
// * @brief       signal status judge
// * @param       [in/out]  *param              signal block
// * @return      [in/out]  FW_ERR_FAIL         judge failed
// * @return      [in/out]  FW_ERR_NONE         judge success
// * @note        None
// *******************************************************************************
// */
//__STATIC_INLINE
//fw_err_t signal_judge(struct SignalBlock *signal)
//{
////    fw_assert(IS_PTR_NULL(signal));
////    fw_assert(IS_PTR_NULL(signal->Detect));
//    
//    uint8_t nowInfo = signal->Detect();
//    
//    switch(signal->Status)
//    {
//        case SIGNAL_STATUS_INIT:
//            UPDATE_SIGNAL_INFO(signal, nowInfo);
//                
//            if(IS_NO_SIGNAL(nowInfo))
//            {
//                TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
//            }
//            else
//            {
//                TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
//            }
//            break;
//        case SIGNAL_STATUS_PRESS_FILTER_STEP1:
//            if(IS_SIGNAL_INFO_CHANGED(signal, nowInfo))
//            {
//                UPDATE_SIGNAL_INFO(signal, nowInfo);
//                
//                if(IS_NO_SIGNAL(nowInfo))
//                {
//                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
//                }
//                else
//                {
//                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
//                }
//            }
//            else
//            {
//                TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP2);
//            }
//            break;
//        case SIGNAL_STATUS_PRESS_FILTER_STEP2:
//            if(IS_SIGNAL_INFO_CHANGED(signal, nowInfo))
//            {
//                UPDATE_SIGNAL_INFO(signal, nowInfo);
//                
//                if(IS_NO_SIGNAL(nowInfo))
//                {
//                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
//                }
//                else
//                {
//                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
//                }
//            }
//            else
//            {
//                TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP3);
//            }
//            break;
//        case SIGNAL_STATUS_PRESS_FILTER_STEP3:
//            if(IS_SIGNAL_INFO_CHANGED(signal, nowInfo))
//            {
//                UPDATE_SIGNAL_INFO(signal, nowInfo);
//                
//                if(IS_NO_SIGNAL(nowInfo))
//                {
//                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
//                }
//                else
//                {
//                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
//                }
//            }
//            else
//            {
//                TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_EDGE);
//                signal_trigger_handler(signal);
//            }
//            break;
//        case SIGNAL_STATUS_RELEASE_FILTER_STEP1:
//            if(IS_SIGNAL_INFO_CHANGED(signal, nowInfo))
//            {
//                UPDATE_SIGNAL_INFO(signal, nowInfo);
//                
//                if(IS_NO_SIGNAL(nowInfo))
//                {
//                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
//                }
//                else
//                {
//                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
//                }
//            }
//            else
//            {
//                TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP2);
//            }
//            break;
//        case SIGNAL_STATUS_RELEASE_FILTER_STEP2:
//            if(IS_SIGNAL_INFO_CHANGED(signal, nowInfo))
//            {
//                UPDATE_SIGNAL_INFO(signal, nowInfo);
//                
//                if(IS_NO_SIGNAL(nowInfo))
//                {
//                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
//                }
//                else
//                {
//                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
//                }
//            }
//            else
//            {
//                TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP3);
//            }
//            break;
//        case SIGNAL_STATUS_RELEASE_FILTER_STEP3:
//            if(IS_SIGNAL_INFO_CHANGED(signal, nowInfo))
//            {
//                UPDATE_SIGNAL_INFO(signal, nowInfo);
//                
//                if(IS_NO_SIGNAL(nowInfo))
//                {
//                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
//                }
//                else
//                {
//                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
//                }
//            }
//            else
//            {
//                TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE);
//                signal_trigger_handler(signal);
//            }
//            break;
//        case SIGNAL_STATUS_RELEASE_EDGE:
//            if(IS_SIGNAL_INFO_CHANGED(signal, nowInfo))
//            {
//                UPDATE_SIGNAL_INFO(signal, nowInfo);
//                
//                if(IS_NO_SIGNAL(nowInfo))
//                {
//                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
//                }
//                else
//                {
//                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
//                }
//            }
//            else
//            {
//                TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
//            }
//            break;
//        case SIGNAL_STATUS_RELEASE:
//            if(IS_SIGNAL_INFO_CHANGED(signal, nowInfo))
//            {
//                UPDATE_SIGNAL_INFO(signal, nowInfo);
//                
//                if(IS_NO_SIGNAL(nowInfo))
//                {
//                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
//                }
//                else
//                {
//                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
//                }
//            }
//            else
//            {
//                TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE);
//                signal_trigger_handler(signal);
//            }
//            break;
//        case SIGNAL_STATUS_PRESS_EDGE:
//            if(IS_SIGNAL_INFO_CHANGED(signal, nowInfo))
//            {
//                UPDATE_SIGNAL_INFO(signal, nowInfo);
//                
//                if(IS_NO_SIGNAL(nowInfo))
//                {
//                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
//                }
//                else
//                {
//                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
//                }
//            }
//            else
//            {
//                TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS);
//                signal_trigger_handler(signal);
//            }
//            break;
//        case SIGNAL_STATUS_PRESS:
//            if(IS_SIGNAL_INFO_CHANGED(signal, nowInfo))
//            {
//                UPDATE_SIGNAL_INFO(signal, nowInfo);
//                
//                if(IS_NO_SIGNAL(nowInfo))
//                {
//                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_EDGE);
//                    signal_trigger_handler(signal);
//                }
//                else
//                {
//                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
//                }
//            }
//            else
//            {
//                TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS);
//                signal_trigger_handler(signal);
//            }
//            break;
//        default:
//            break;
//    }

//    return FW_ERR_NONE;
//}

///**
// *******************************************************************************
// * @brief       signal walk
// * @param       [in/out]  void
// * @return      [in/out]  void
// * @note        None
// *******************************************************************************
// */
//__STATIC_INLINE 
//void signal_walk(void)
//{
//    struct SignalBlock *now = NULL;
//    
//    // init poll process
//    if(SignalPollBlock.Flag == 0)
//    {
//        SignalPollBlock.Head = GetSingleLinkListHead(SignalControlBlock);
//        SignalPollBlock.Flag = 1;
//    }
//    else
//    {
//        // check poll is finish
//        if(IsSingleLinkListHead(SignalControlBlock, SignalPollBlock.Head))
//        {
//            if(!--SignalPollBlock.Count)
//            {
//                // exit poll
//                SignalPollBlock.Flag = 0;
//                SignalPollBlock.Head = NULL;
//                
//                return;
//            }
//        }
//    }
//    
//    // get now signal module
//    now = signal_pop();
//    
//    if(SignalPollBlock.Flag)
//    {
//        // check now signal is enable
//        if(IS_SIGNAL_ENABLE(now))
//        {
//            signal_judge(now);
//            signal_push(now); 
//        }

//        fw_task_evt_create(NULL, PoolSignalComponent, FW_EVENT_NONE);
//    }
//}

///**
// *******************************************************************************
// * @brief       signal component init
// * @param       [in/out]  void
// * @return      [in/out]  FW_ERR_NONE       init finish
// * @note        None
// *******************************************************************************
// */
//fw_err_t InitSignalComponent(void)
//{
//    signal_clear();
//    
//    SignalPollBlock.Head  = NULL;
//    SignalPollBlock.Count = 0;
//    SignalPollBlock.Flag  = 0;
//    
//    InitEventHandleTimerModule(&SignalTimer, PoolSignalComponent, FW_EVENT_DELAY);
//    StartTimerModule(&SignalTimer, SIGNAL_SCAN_TIME, TIMER_CYCLE_MODE);
//    
//    return FW_ERR_NONE;
//}

///**
// *******************************************************************************
// * @brief       signal component deinit
// * @param       [in/out]  void
// * @return      [in/out]  FW_ERR_NONE       deinit finish
// * @note        None
// *******************************************************************************
// */
//fw_err_t DeinitSignalComponent(void)
//{
//    return FW_ERR_NONE;
//}

///**
// *******************************************************************************
// * @brief       start signal scan
// * @param       [in/out]  *signal           signal block
// * @param       [in/out]  *detect           signal detect function
// * @param       [in/out]  *handler          signal handler function
// * @return      [in/out]  FW_ERR_NONE       arm success
// * @return      [in/out]  FW_ERR_FAIL       arm failed
// * @note        None
// *******************************************************************************
// */
//fw_err_t StartSignalModule(struct SignalBlock *signal, uint8_t (*detect)(void), fw_err_t (*handler)(uint16_t))
//{
//    fw_assert(IS_PTR_NULL(signal));
//    fw_assert(IS_PTR_NULL(detect));
//    fw_assert(IS_PTR_NULL(handler));
//    
//    signal->Detect = detect;
//    signal->Info   = 0;
//    signal->Status = SIGNAL_STATUS_INIT;
//    InitEventHandleTask(&signal->Task, handler, FW_EVENT_NONE);
//    signal_push(signal); 
//    
//    return FW_ERR_NONE;
//}

///**
// *******************************************************************************
// * @brief       stop signal scan
// * @param       [in/out]  *signal           signal block
// * @return      [in/out]  FW_ERR_NONE       disarm success
// * @note        None
// *******************************************************************************
// */
//fw_err_t StopSignalModule(struct SignalBlock *signal)
//{
//    fw_assert(IS_PTR_NULL(signal));
//    
//    SIGNAL_DISABLE(signal);

//    return FW_ERR_NONE;
//}

///**
// *******************************************************************************
// * @brief       add signal module
// * @param       [in/out]  *signal           signal block
// * @return      [in/out]  FW_ERR_NONE       disarm success
// * @note        None
// *******************************************************************************
// */
//fw_err_t AddSignalModuleToQueue(struct SignalBlock *signal)
//{
//    fw_assert(IS_PTR_NULL(signal));
//    
//    signal_push(signal);

//    return FW_ERR_NONE;
//}

///**
// *******************************************************************************
// * @brief       remove timer
// * @param       [in/out]  *timer            timer block
// * @return      [in/out]  FW_ERR_NONE       timer disarm success
// * @return      [in/out]  FW_ERR_FAIL       timer disarm failed
// * @note        None
// *******************************************************************************
// */
//fw_err_t RemoveSignalModuleFromQueue(struct SignalBlock *timer)
//{
//    fw_assert(IS_PTR_NULL(timer));
//    
//    struct SignalBlock *now  = GetSingleLinkListHead(SignalControlBlock);
//    struct SignalBlock *last = now;
//    
//    while(1)
//    {
//        // timer list delete
//        if(now == timer)
//        {   
//            DeleteInSignalLinkList(SignalControlBlock, last, now);
//            return FW_ERR_NONE;
//        }
//        else
//        {
//            last = now;
//            now  = now->Next;
//        }
//        
//        // break
//        if( now == NULL )
//        {
//            break;
//        }
//    }
//    
//    return FW_ERR_FAIL;
//}

///**
// *******************************************************************************
// * @brief       signal component pool
// * @param       [in/out]  event                event
// * @return      [in/out]  FW_ERR_NONE          pool not error
// * @note        None
// *******************************************************************************
// */
//fw_err_t PoolSignalComponent(uint16_t event)
//{
//    if( !IsSingleLinkListHeadEmpty(SignalControlBlock) )
//    {
//        if(event == FW_EVENT_DELAY)
//        {
//            SignalPollBlock.Count++;
//        }
//        
//        if(SignalPollBlock.Count)
//        {
//            signal_walk();
//        }
//    }
//    return FW_ERR_NONE;
//}

///**
// *******************************************************************************
// * @brief       get signal info
// * @param       [in/out]  *signal           signal block
// * @return      [in/out]  FW_ERR_NONE       get success
// * @note        None
// *******************************************************************************
// */
//inline uint8_t GetSignalModuleInfo(struct SignalBlock *signal)
//{
//    uint8_t info;
//    
//    if(IS_PTR_NULL(signal))
//    {
//        return 0;
//    }
//        
//    info = signal->Info;

//    return info;
//}

#endif

/** @}*/     /** signal component */

/**********************************END OF FILE*********************************/
