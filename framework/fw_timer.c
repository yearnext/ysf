/**
 *******************************************************************************
 * @file       fw_timer.c
 * @author     yearnext
 * @version    1.0.0
 * @date       2016-07-09
 * @brief      framework timer component source files
 * @par        paltform
 *                  Windows
 * @par        compiler
 *                  GCC
 *******************************************************************************
 * @note
 * 1.XXXXX
 *******************************************************************************
 */

/**
 * @defgroup framework timer component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "fw_timer.h"
#include "fw_queue.h"
#include "fw_debug.h"

/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       MACRO
 *******************************************************************************
 */
#define IsTimerEnable(timer)                                ((timer).Count != 0)

/**
 *******************************************************************************
 * @brief       MACRO
 *******************************************************************************
 */
#define DisableTimer(timer)                               _ST((timer).Count = 0;)

/* Private typedef -----------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       framework timer structure
 *******************************************************************************
 */
#if USE_FRAMEWORK_TIMER_COMPONENT
struct Timer_Block
{
	void     (*Hook)(uint8_t);
    uint32_t TimeOutTick;
    uint32_t Tick;
	int16_t  Count;
    uint8_t  TaskId;
    uint8_t  TaskEvent;
}static Timer[Timer_Max];
#endif

/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_FRAMEWORK_TIMER_COMPONENT
/**
 *******************************************************************************
 * @brief       timer component init
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void InitTimerComponent(void)
{
    uint8_t i;
    
    for( i=0; i<Timer_Max; i++ )
    {
    	Timer[i].Hook        = NULL;
        Timer[i].TaskId      = 0;
        Timer[i].TimeOutTick = 0;
        Timer[i].Tick        = 0;
        Timer[i].Count       = 0;
        Timer[i].TaskEvent   = FW_EVENT_NONE;
    }
    
    RegisterEvent(FW_TICK_TASK, PollTimerComponent);
}

/**
 *******************************************************************************
 * @brief       init timer
 * @param       [in/out]  timerId     timer id
 * @param       [in/out]  taskId      task id
 * @param       [in/out]  taskEvent   task event
 * @param       [in/out]  hook        hook function
 * @return      [in/out]  fw_err_t    init status
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Timer_Init(uint8_t timerId, uint8_t taskId, uint8_t taskEvent, void (*hook)(uint8_t))
{
    if(timerId >= Timer_Max)
    {
        return FW_ERR_FAIL;
    }

    if(taskId >= FW_TASK_MAX)
    {
        return FW_ERR_FAIL;
    }

    if(taskEvent >= FW_EVENT_MAX)
    {
        return FW_ERR_FAIL;
    }

    Timer[timerId].Hook      = hook;
    Timer[timerId].TaskEvent = taskEvent;
    Timer[timerId].TaskId    = taskId;

    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       start timer
 * @param       [in/out]  timerId     timer id
 * @param       [in/out]  count       work count
 * @param       [in/out]  tick        set time
 * @return      [in/out]  fw_err_t    return start status
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Timer_Start(uint8_t timerId, int16_t count, uint32_t tick)
{
    if(timerId >= Timer_Max)
    {
        return FW_ERR_FAIL;
    }
    
//    _ATOM_ACTIVE_BEGIN();   
    
    if(!IsTimerEnable(Timer[timerId]))
    {
        Timer[timerId].Count = count;
        Timer[timerId].Tick  = tick;
        Timer[timerId].TimeOutTick = Timer[timerId].Tick;

        if(!IS_PTR_NULL(Timer[timerId].Hook))
        {
        	Timer[timerId].Hook(FW_BEGIN_EVENT);
        }
    }
    
//    _ATOM_ACTIVE_END();
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       force start timer
 * @param       [in/out]  timerId     timer id
 * @param       [in/out]  count       work count
 * @param       [in/out]  tick        set time
 * @return      [in/out]  fw_err_t    return start status
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Timer_ForceStart(uint8_t timerId, int16_t count, uint32_t tick)
{
    if(timerId >= Timer_Max)
    {
        return FW_ERR_FAIL;
    }

//    _ATOM_ACTIVE_BEGIN();    
    
    Timer[timerId].Count       = count;
    Timer[timerId].Tick        = tick;
    Timer[timerId].TimeOutTick = Timer[timerId].Tick;
    
    if(!IS_PTR_NULL(Timer[timerId].Hook))
    {
    	Timer[timerId].Hook(FW_BEGIN_EVENT);
    }

//    _ATOM_ACTIVE_END();
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       stop timer
 * @param       [in/out]  timerId     timer id
 * @return      [in/out]  fw_err_t    opera status
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Timer_Stop(uint8_t timerId)
{
    if(timerId >= Timer_Max)
    {
        return FW_ERR_FAIL;
    }
    
//    _ATOM_ACTIVE_BEGIN();
    
    DisableTimer(Timer[timerId]);
    
//    _ATOM_ACTIVE_END();  
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       get timer status
 * @param       [in/out]  timerId      timer id
 * @param       [in/out]  *status      now timer status
 * @return      [in/out]  fw_err_t     return flags
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Timer_GetStatus(uint8_t timerId, int16_t *status)
{
    if(timerId >= Timer_Max)
    {
        return FW_ERR_FAIL;
    }

	*status = Timer[timerId].Count;

	return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       timer component handler
 * @param       [in/out]  event    trigger event
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void PollTimerComponent(uint8_t event)
{
    static uint32_t lastTick = 0;
    uint32_t nowTick = GetTick();
    uint32_t tick = CalPastTick(lastTick, nowTick);
    uint8_t i;

    lastTick = nowTick;
    
    for(i=0; i<Timer_Max; i++)
    {        
        if(IsTimerEnable(Timer[i]))
        {
            if( Timer[i].TimeOutTick <= tick )
            {
            	if(Timer[i].Count > 0)
                {
                    --Timer[i].Count;
                }

                if(Timer[i].Count == 0 && !IS_PTR_NULL(Timer[i].Hook))
                {
                    Timer[i].Hook(FW_END_EVENT);
                }

                Timer[i].TimeOutTick = Timer[i].Tick;
                
                PostEvent(Timer[i].TaskId, Timer[i].TaskEvent); 
            }
            else
            {
                Timer[i].TimeOutTick -= tick;
            }
        }
    }
}
#endif

/** @}*/    /** framework event component */

/**********************************END OF FILE*********************************/
