/**
******************************************************************************
* @file       ysf_timer.h
* @author     yearnext
* @version    1.0.0
* @date       2016年7月9日
* @brief      ysf_timer 头文件
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __YSF_TIMER_H__
#define __YSF_TIMER_H__

/* Includes ------------------------------------------------------------------*/
#include "ysf_type.h"

/* Exported macro ------------------------------------------------------------*/
/**
*******************************************************************************
* @brief       事件定时器调试开关
*******************************************************************************
*/
#define USE_EVENT_TIMER_DEBUG (1)

#define YSF_TICK_TIME         (10)

#define YSF_TIME_CAL(time)    ((time)/YSF_TICK_TIME)

/* Exported types ------------------------------------------------------------*/
/**
*******************************************************************************
* @brief       定时器相关数据结构
*******************************************************************************
*/
typedef uint16_t user_timing_t;

typedef struct _YSF_EVENT_TIMER_TYPE_
{
	/** 不需要用户配置 */
	void *next;
	/** 下列项需要用户自行配置 */
	user_timing_t time;
	uint8_t event;
}ysf_event_timer_t;

/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
extern ysf_err_t ysf_event_timer_disarm(ysf_event_timer_t*);
extern ysf_err_t ysf_event_timer_arm(ysf_event_timer_t*);
extern ysf_err_t ysf_event_timer_init(ysf_event_timer_t*, user_timing_t, uint8_t);
extern ysf_err_t ysf_event_timer_handler( void );

#endif      /* _USER_TIMER_ */
/**********************************END OF FILE*********************************/
