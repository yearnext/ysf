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
#include "../ysf/component/tick/ysf_tick.h"

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       ysf tick count
 *******************************************************************************
 */
#if USE_YSF_TICK
static ysf_tick_t ysfTick = 0;
#endif

/* Exported variables --------------------------------------------------------*/
const ysf_tick_func_list ysf_tick =
{
    .init = ysf_tick_init,
    .inc  = ysf_tick_inc,
    .read = ysf_tick_read,
};

/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_YSF_TICK
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
    ysfTick = 0;
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
    ysfTick++;
}

/**
 *******************************************************************************
 * @brief       read past tick
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
ysf_tick_t ysf_tick_read( void )
{
	static ysf_tick_t lastTick = 0;
	ysf_tick_t tick = 0;
	
	if( ysfTick >= lastTick )
	{
		tick = ysfTick - lastTick;
	}
	else
	{
		tick = YSF_TICK_MAX - lastTick;
		tick = tick + ysfTick;
	}
	
	lastTick = ysfTick;
	
	return tick;
}

#endif
/** @}*/     /* ysf tick  */

/**********************************END OF FILE*********************************/
