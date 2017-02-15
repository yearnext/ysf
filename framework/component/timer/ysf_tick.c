/**
 ******************************************************************************
  * @file       ysf_tick.c
  * @author     yearnext
  * @version    1.0.0
  * @date       2017��1��10��
  * @brief      ysf_tick Դ�ļ�
  * @par        ����ƽ̨                                  
  *                 Windows
  * @par        ����ƽ̨									                         
  * 				GCC
 ******************************************************************************
  * @note
  * 1.XXXXX                  						                     
 ******************************************************************************
 */

/**
 * @defgroup ysf_tick����
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "ysf_tick.h"

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       ��������
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

/** @}*/     /* ysf_tick ����  */

/**********************************END OF FILE*********************************/
