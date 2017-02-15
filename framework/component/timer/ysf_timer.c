/**
******************************************************************************
* @file       ysf_timer.c
* @author     yearnext
* @version    1.0.0
* @date       2016年7月9日
* @brief      ysf_timer 源文件
* @par        工作平台
*                  STM32
* @par        工作频率
*                  72MHz
* @par        编译平台
*                  Keil
******************************************************************************
* @note
* 1.XXXXX
******************************************************************************
*/

/**
* @defgroup user_timer 模块
* @{
*/

/* Includes ------------------------------------------------------------------*/
#include "ysf_timer.h"
#include "ysf_type.h"
#include "ysf_event.h"
#include "ysf_tick.h"

/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/**
*******************************************************************************
* @brief       定时器链表头指针
*******************************************************************************
*/
static void *head = NULL;

/* Exported functions --------------------------------------------------------*/
ysf_err_t ysf_event_timer_disarm(ysf_event_timer_t *timer)
{
	ysf_event_timer_t *temp = (ysf_event_timer_t *)head;

#if USE_EVENT_TIMER_DEBUG
	if (head == NULL)
	{
		return YSF_ERR_INVAILD_PTR;
	}
#endif
	if (head == timer)
	{
		head = timer->next;
		timer->next = NULL;
	}
	else
	{
		while (temp->next != timer)
		{
			if (temp->next == NULL)
			{
				return YSF_ERR_NONE;
			}

			temp = temp->next;
		}

		temp->next = timer->next;
	}
	
	return YSF_ERR_NONE;
}

ysf_err_t ysf_event_timer_arm(ysf_event_timer_t *timer)
{
	ysf_event_timer_t *temp = (ysf_event_timer_t *)head;
	
#if USE_EVENT_TIMER_DEBUG
	if (timer == NULL)
	{
		return YSF_ERR_INVAILD_PTR;
	}
#endif

	if (head == NULL)
	{
		head = timer;
	}
	else
	{
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = timer;
	}
	
	return YSF_ERR_NONE;
}

ysf_err_t ysf_event_timer_init(ysf_event_timer_t *timer, user_timing_t time, uint8_t event)
{
#if USE_EVENT_TIMER_DEBUG
	if(timer == NULL )
	{
		return YSF_ERR_INVAILD_PTR;
	}
	
	if(time == 0 )
	{
		return YSF_ERR_INVAILD_PARAM;
	}
#endif
	ysf_event_timer_disarm(timer);

	timer->time  = time;
	timer->event = event;

	timer->next = NULL;
	
	return YSF_ERR_NONE;
}

ysf_err_t ysf_event_timer_handler( void )
{
	ysf_event_timer_t *temp = (ysf_event_timer_t *)head;
	ysf_tick_t tick = ysf_tick_read();
    
	while (1)
	{
		if (temp != NULL)
		{
			if (temp->time > tick)
			{
				temp->time = temp->time - tick;
			}
			else
			{
				ysf_event_write(temp->event);
				ysf_event_timer_disarm(temp);
			}
			
			temp = temp->next;
		}
		else
		{
			return YSF_ERR_NONE;
		}
	}
}

/** @}*/     /* timer */
 /**********************************END OF FILE*********************************/
