/**
 ******************************************************************************
  * @file       ysf_tick.c
  * @author     yearnext
  * @version    1.0.0
  * @date       2017年1月10日
  * @brief      ysf_tick 源文件
  * @par        工作平台                                  
  *                 Windows
  * @par        编译平台									                         
  * 				GCC
 ******************************************************************************
  * @note
  * 1.XXXXX                  						                     
 ******************************************************************************
 */

/**
 * @defgroup ysf_tick配置
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "ysf_tick.h"

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       心跳计数
 *******************************************************************************
 */
static volatile ysf_tick_t sysTick = 0;

/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
void ysf_tick_init( void )
{
	sysTick = 0;
}

void ysf_tick_inc( void )
{
	sysTick++;
}

ysf_tick_t ysf_tick_read( void )
{
	static ysf_tick_t lastTick = 0;
	ysf_tick_t tick = 0;
	
	if( sysTick >= lastTick )
	{
		tick = sysTick - lastTick;
	}
	else
	{
		tick = YSF_TICK_MAX - lastTick;
		tick = tick + sysTick;
	}
	
	lastTick = sysTick;
	
	return tick;
}

/** @}*/     /* ysf_tick 配置  */

/**********************************END OF FILE*********************************/
