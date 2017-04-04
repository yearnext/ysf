/**
 ******************************************************************************
  * @file       ysf_tick.c
  * @author     yearnext
  * @version    1.0.0
  * @date       2017-1-10
  * @brief      ysf_tick source file
  * @par        work platform
  *                 Windows
  * @par        compiler platform
  * 				GCC
 ******************************************************************************
  * @note
  * 1.XXXXX                  						                     
 ******************************************************************************
 */

/**
 * @defgroup ysf tick
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "ysf_path.h"
#include YSF_COMPONENT_TICK_PATH
#include YSF_COMPONENT_EVENT_PATH
#include YSF_COMPONENT_TASK_PATH
#include YSF_COMPONENT_TIMER_PATH

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       framework tick
 *******************************************************************************
 */
#if USE_YSF_TICK_API
static ysf_tick_t tick = 0;
static struct ysf_task_t tick_task;
#endif

/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_YSF_TICK_API
/**
 *******************************************************************************
 * @brief       tick initialization
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void ysf_tick_init( void )
{
    tick = 0;
}

/**
 *******************************************************************************
 * @brief       tick value increase
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void ysf_tick_inc( void )
{
    YSF_ENTER_CRITICAL();
    tick++;
#if defined(USE_YSF_TASK_API) && USE_YSF_TASK_API
    ysf_evtTask_create(&tick_task, ysf_timer_handler, YSF_EVENT_NONE);
#endif
    YSF_EXIT_CRITICAL();
}

/**
 *******************************************************************************
 * @brief       tick value get
 * @param       [in/out]  void
 * @return      [in/out]  ysf_tick_t    now tick
 * @note        None
 *******************************************************************************
 */
ysf_tick_t ysf_tick_get( void )
{
    return tick;
}

/**
 *******************************************************************************
 * @brief       calculate the distance past the previous read tick tick
 * @param       [in/out]  void
 * @return      [in/out]  ysf_tick_t    past tick
 * @note        None
 *******************************************************************************
 */
ysf_tick_t ysf_past_tick_cal( void )
{
	static ysf_tick_t lastTick = 0;
	ysf_tick_t calTick = 0;
	
	if( tick >= lastTick )
	{
		calTick = tick - lastTick;
	}
	else
	{
		calTick = YSF_TICK_MAX - lastTick;
		calTick = calTick + tick;
	}
	
	lastTick = tick;
	
	return calTick;
}

#endif
/** @}*/     /** ysf tick component */

/**********************************END OF FILE*********************************/
