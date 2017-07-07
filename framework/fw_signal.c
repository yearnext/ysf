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
#include "fw_timer.h"
#include "fw_event.h"
#include "fw_debug.h"

/* Private define ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      detect signal status
 *******************************************************************************
 */
#define IS_SIGNAL_INFO_CHANGED(signal, nowInfo) ((signal)->FilterSignal != (nowInfo))

/**
 *******************************************************************************
 * @brief      update signal status
 *******************************************************************************
 */
#define TRANSFER_SIGNAL_STATUS(signal, status) ((signal)->Status = (status))
#define UPDATE_SIGNAL_INFO(signal, info)       ((signal)->FilterSignal = (info))

/* Private typedef -----------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        defien signal block type
 *******************************************************************************
 */
struct fw_signal
{
    uint8_t         (*Scan)(void);
    signal_status_t Status;
    uint8_t         FilterSignal;
    uint8_t         ValidSignal;
    uint8_t         TaskId;
    uint8_t         TriggerEvent;
};

/* Private variables ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        defien signal block
 *******************************************************************************
 */
#if USE_FRAMEWORK_SIGNAL_COMPONENT
static struct fw_signal Signal[SIGNAL_MAX];
#endif

/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
#if USE_FRAMEWORK_SIGNAL_COMPONENT
/**
 *******************************************************************************
 * @brief        Signal Init State Handle
 *******************************************************************************
 */
#define Signal_Init_State_Handle()                                               \
{                                                                                \
	UPDATE_SIGNAL_INFO(nowSignal, nowInfo);                                      \
                                                                                 \
	if(IS_NO_SIGNAL(nowInfo))                                                    \
	{                             										         \
		TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_RELEASE_FILTER_STEP);    \
	}																	         \
	else																	     \
	{																	         \
		TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_PRESS_FILTER_STEP);      \
	}																		     \
}

/**
 *******************************************************************************
 * @brief        Signal Press Filter State Handle
 *******************************************************************************
 */
#define Signal_Press_Filter_State_Handle()                                       \
{                                                                                \
	if(IS_NO_SIGNAL(nowInfo))                                                    \
	{                                                                            \
		UPDATE_SIGNAL_INFO(nowSignal, nowInfo);                                  \
		TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_RELEASE_FILTER_STEP);    \
	}                                                                            \
	else                                                                         \
	{                                                                            \
		if (!IS_SIGNAL_INFO_CHANGED(nowSignal, nowInfo))                         \
		{                                                                        \
			nowSignal->Status = SIGNAL_STATUS_PRESS_EDGE;                        \
		}                                                                        \
		else                                                                     \
		{                                                                        \
			UPDATE_SIGNAL_INFO(nowSignal, nowInfo);                              \
			TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_PRESS_FILTER_STEP);  \
		}                                                                        \
	}        																	 \
}

/**
 *******************************************************************************
 * @brief        Signal Release Filter State Handle
 *******************************************************************************
 */
#define Signal_Release_Filter_State_Handle()                                     \
{                                                                                \
	if(IS_NO_SIGNAL(nowInfo))                                                    \
	{                                                                            \
		nowSignal->Status = SIGNAL_STATUS_RELEASE_EDGE;                          \
	}                                                                            \
	else                                                                         \
	{                                                                            \
		UPDATE_SIGNAL_INFO(nowSignal, nowInfo);                                  \
		TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_PRESS_FILTER_STEP);      \
	}        																	 \
}

/**
 *******************************************************************************
 * @brief        Signal Press Edge State Handle
 *******************************************************************************
 */
#define Signal_PressEdge_State_Handle()                                          \
{																				 \
	if(IS_NO_SIGNAL(nowInfo))												     \
	{																		     \
		UPDATE_SIGNAL_INFO(nowSignal, nowInfo);									 \
		TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_RELEASE_FILTER_STEP);    \
	}																			 \
	else																		 \
	{																			 \
		if (!IS_SIGNAL_INFO_CHANGED(nowSignal, nowInfo))					     \
		{																		 \
			if (nowSignal->ValidSignal != nowInfo                                \
			    && IsLogonPressEdgeEvent(nowSignal->TriggerEvent))               \
			{																	 \
				PostEvent(nowSignal->TaskId, nowSignal->Status);		         \
			}																	 \
			else if(nowSignal->ValidSignal == nowInfo                            \
					&& IsLogonPressEvent(nowSignal->TriggerEvent))               \
			{                                                                    \
				PostEvent(nowSignal->TaskId, nowSignal->Status);		         \
			}                                                                    \
			nowSignal->ValidSignal = nowInfo;   								 \
			TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_PRESS);	         	 \
		}																		 \
		else																	 \
		{																		 \
			UPDATE_SIGNAL_INFO(nowSignal, nowInfo);								 \
			TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_PRESS_FILTER_STEP);  \
		}																		 \
	}																			 \
}

/**
 *******************************************************************************
 * @brief        Signal Release Edge State Handle
 *******************************************************************************
 */
#define Signal_ReleaseEdge_State_Handle()                                        \
{																				 \
	if(IS_NO_SIGNAL(nowInfo))												     \
	{																		     \
		if (nowSignal->ValidSignal != nowInfo                                    \
		    && IsLogonReleaseEdgeEvent(nowSignal->TriggerEvent))                 \
		{																	     \
			PostEvent(nowSignal->TaskId, nowSignal->Status);		         	 \
		}																	     \
		nowSignal->ValidSignal = nowInfo;   								     \
		TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_RELEASE);	         	 \
	}																			 \
	else																		 \
	{																			 \
		UPDATE_SIGNAL_INFO(nowSignal, nowInfo);								     \
		TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_PRESS_FILTER_STEP);      \
	}																			 \
}

/**
 *******************************************************************************
 * @brief        Signal Press State Handle
 *******************************************************************************
 */
#define Signal_Press_State_Handle()                                              \
{																				 \
	if(IS_NO_SIGNAL(nowInfo))												     \
	{																		     \
		UPDATE_SIGNAL_INFO(nowSignal, nowInfo);									 \
		TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_RELEASE_FILTER_STEP);    \
	}																			 \
	else																		 \
	{																			 \
		if (!IS_SIGNAL_INFO_CHANGED(nowSignal, nowInfo))					     \
		{																		 \
			if (IsLogonPressEvent(nowSignal->TriggerEvent))                      \
			{																	 \
				PostEvent(nowSignal->TaskId, nowSignal->Status);		         \
			}																	 \
		}																		 \
		else																	 \
		{																		 \
			UPDATE_SIGNAL_INFO(nowSignal, nowInfo);								 \
			TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_PRESS_FILTER_STEP);  \
		}																		 \
	}																			 \
}

/**
 *******************************************************************************
 * @brief        Signal Release State Handle
 *******************************************************************************
 */
#define Signal_Release_State_Handle()                                            \
{																				 \
	if(IS_NO_SIGNAL(nowInfo))												     \
	{																		     \
		if (IsLogonReleaseEvent(nowSignal->TriggerEvent))                        \
		{																	     \
			PostEvent(nowSignal->TaskId, nowSignal->Status);		         	 \
		}																	     \
	}																			 \
	else																		 \
	{												                             \
		UPDATE_SIGNAL_INFO(nowSignal, nowInfo);								     \
		TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_PRESS_FILTER_STEP);	     \
	}																		     \
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
void SignalDetection(struct fw_signal *nowSignal)
{
    uint8_t nowInfo;

    nowInfo = nowSignal->Scan();
    
    switch(nowSignal->Status)
    {
		case SIGNAL_STATUS_INIT:
			Signal_Init_State_Handle();
			break;
		case SIGNAL_STATUS_PRESS_FILTER_STEP:
			Signal_Press_Filter_State_Handle();
			break;
		case SIGNAL_STATUS_RELEASE_FILTER_STEP:
			Signal_Release_Filter_State_Handle();
			break;
		case SIGNAL_STATUS_PRESS_EDGE:
			Signal_PressEdge_State_Handle();
			break;
		case SIGNAL_STATUS_PRESS:
			Signal_Press_State_Handle();
			break;
		case SIGNAL_STATUS_RELEASE_EDGE:
			Signal_ReleaseEdge_State_Handle();
			break;
		case SIGNAL_STATUS_RELEASE:
			Signal_Release_State_Handle();
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
void InitSignalComponent(void)
{
    uint8_t i = 0;

    for( i=0; i<SIGNAL_MAX; i++ )
    {
        Signal[i].Scan         = NULL;
        Signal[i].TaskId       = 0;
        Signal[i].Status       = SIGNAL_STATUS_INIT;
        Signal[i].ValidSignal  = 0xFF;
        Signal[i].FilterSignal = 0xFF;
    }
    
    RegisterEvent(FW_SIGNAL_TASK, PollSignalComponent);
    Fw_Timer_Init(SIGNAL_SCAN_TIMER, FW_SIGNAL_TASK, FW_DELAY_EVENT, NULL);
    Fw_Timer_Start(SIGNAL_SCAN_TIMER, FW_TIMER_PERIOD_MODE, FW_SIGNAL_SCAN_PREIOD);
    PostEvent(FW_SIGNAL_TASK, FW_SIGNAL_EVENT);
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
fw_err_t RegisterSignal(uint8_t taskId, uint8_t signalId, uint8_t (*scan)(void), uint8_t registerEvent)
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
    Signal[signalId].TriggerEvent = registerEvent;
    Signal[signalId].Status       = SIGNAL_STATUS_INIT;
    Signal[signalId].ValidSignal  = 0;
    Signal[signalId].FilterSignal = 0;

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
fw_err_t LogonSignalEvent(uint8_t signalId, uint8_t logonEvent)
{
    if (signalId > SIGNAL_MAX)
    {
        return FW_ERR_FAIL;
    }
    
    Signal[signalId].TriggerEvent |= logonEvent;
    
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
fw_err_t LogoutSignalEvent(uint8_t signalId, uint8_t logoutEvent)
{
    if (signalId > SIGNAL_MAX)
    {
        return FW_ERR_FAIL;
    }
    
    Signal[signalId].TriggerEvent &= ~logoutEvent;
    
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
uint8_t GetSignalInfo(uint8_t signalId)
{
    if (signalId > SIGNAL_MAX)
    {
        return 0;
    }

    return Signal[signalId].ValidSignal;
}

/**
 *******************************************************************************
 * @brief       signal handler
 * @param       [in/out]  event         trigger events
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void PollSignalComponent(uint8_t event)
{
    uint8_t i = 0;

    for( i=0; i<SIGNAL_MAX; i++ )
    {
        if( !IS_PTR_NULL(Signal[i].Scan) )
        {
            SignalDetection(&Signal[i]);
        }
    }
}
#endif

/** @}*/     /** framework signal component  */

/**********************************END OF FILE*********************************/
