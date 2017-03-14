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
#include YSF_COMPONENT_TICK_DIR
#include YSF_COMPONENT_EVENT_DIR

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       ysf tick count
 *******************************************************************************
 */
#if USE_YSF_TICK_API
static ysf_tick_t tick = 0;
#endif

/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_YSF_TICK_API
/**
 *******************************************************************************
 * @brief       tick value initialization
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
#if USE_YSF_EVENT_API
    ysf_event_post(YSF_CORE_TICK_UPDATE);
#endif
    YSF_EXIT_CRITICAL();
}

/**
 *******************************************************************************
 * @brief       tick value get
 * @param       [in/out]  void
 * @return      [in/out]  ysf_tick_t    tick
 * @note        None
 *******************************************************************************
 */
ysf_tick_t ysf_tick_get( void )
{
    return tick;
}

/**
 *******************************************************************************
 * @brief       read past tick
 * @param       [in/out]  void
 * @return      [in/out]  ysf_tick_t    tick
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
/** @}*/     /* ysf tick  */

/**********************************END OF FILE*********************************/
