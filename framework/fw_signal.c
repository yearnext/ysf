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
#include "fw_signal.h"
#include "fw_task.h"
#include "fw_linklist.h"
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
#define SIGNAL_STATE_HANDLE(signal)                                            \
    _ST(Fw_Task_PostMessage((signal)->Task,                                    \
                            FW_SIGNAL_HANDLE_EVENT,                            \
                            (void *)(signal));)

/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/   
#if USE_SIGNAL_COMPONENT
/**
 *******************************************************************************
 * @brief        signal block
 *******************************************************************************
 */
struct Fw_Signal_Block
{
	uint8_t Num;
};

static struct Fw_Signal_Block SignalBlock;
static struct Fw_Task Fw_Signal_Task;
#endif

/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
#if USE_SIGNAL_COMPONENT
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
 * @brief       signal task handle
 * @param       [in/out]  nowSignal             signal block
 * @param       [in/out]  nowInfo               signal info
 * @return      [in/out]  void
 * @note        this function is static type
 *******************************************************************************
 */
static void Fw_Signal_Task_Handle(void *param)
{
	_FW_ASSERT(IS_PTR_NULL(param));

    uint8_t nowInfo;
	struct Fw_Signal *nowSignal = (struct Fw_Signal *)param;

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
 * @return      [in/out]  FW_ERR_NONE       init finish
 * @note        NONE
 *******************************************************************************
 */
fw_err_t Fw_Signal_InitComponent(void)
{    
	SignalBlock.Num = 0;

	Fw_Task_Init(&Fw_Signal_Task, "Framework Signal Handle Task", 1, (void *)Fw_Signal_Task_Handle, FW_CALL_BACK_TYPE_TASK);
	
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       create new signal
 * @param       [in/out]  *signal           signal block
 * @param       [in/out]  *str              signal name
 * @param       [in/out]  taskId            post task id 
 * @param       [in/out]  triggerEvent      register trigger signal event
 * @return      [in/out]  FW_ERR_NONE       create success
 * @return      [in/out]  FW_ERR_FAIL       create failed
 * @note        NONE
 *******************************************************************************
 */
fw_err_t Fw_Signal_Init(struct Fw_Signal *signal, char *str, struct Fw_Task *task, uint8_t (*scan)(void))
{
    _FW_ASSERT(IS_PTR_NULL(signal));
	_FW_ASSERT(IS_PTR_NULL(str));
    _FW_ASSERT(IS_PTR_NULL(task));

    signal->Str  = str;
    signal->Task = task;
    signal->Scan = scan;
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       start signal
 * @param       [in/out]  *signal           signal block
 * @param       [in/out]  tick              signal scan period
 * @return      [in/out]  FW_ERR_NONE       start success
 * @return      [in/out]  FW_ERR_FAIL       start failed
 * @note        NONE
 *******************************************************************************
 */
fw_err_t Fw_Signal_Open(struct Fw_Signal *signal, uint8_t triggerState, uint32_t tick)
{
	_FW_ASSERT(IS_PTR_NULL(signal));

	signal->TriggerState = triggerState;
	
	Fw_Timer_Init(&signal->Timer, signal->Str);
    Fw_Timer_SetCallback(&signal->Timer, Fw_Signal_Task_Handle, (void *)signal);
	Fw_Timer_Start(&signal->Timer, tick, FW_TIMER_CYCLE_MODE);
    
    SignalBlock.Num++;
	
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       get now signal num
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        NONE
 *******************************************************************************
 */
uint8_t Fw_Signal_GetNum(void)
{
	return SignalBlock.Num;
}

#endif

/** @}*/     /** framework signal component */

/**********************************END OF FILE*********************************/
