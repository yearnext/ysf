/**
******************************************************************************
* @file       ysf_timer.h
* @author     yearnext
* @version    1.0.0
* @date       2016-7-9
* @brief      ysf timer head file
* @par        MCU paltform
*                  STM32
* @par        MCU frequency
*                  72MHz
* @par        compiler frequency
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
#include "../ysf/common/ysf_type.h"
#include "../ysf/component/event/ysf_event.h"

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       None
 *******************************************************************************
 */
#define USE_TIMER_DEBUG (1)

#define YSF_TICK_TIME         (10)

#define YSF_TIME_CAL(time)    ((time)/YSF_TICK_TIME)

#define YSF_VARIOUS_TIMER_TYPE (1)

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        define general timer type
 *******************************************************************************
 */
typedef enum
{
    YSF_GENERAL_EVENT_TIMER = 1,
    YSF_CYCLE_EVENT_TIMER,

    YSF_GENERAL_TRIGGER_TIMER,
    YSF_CYCLE_TRIGGER_TIMER,
}ysf_timer_class_t;

typedef struct
{
    void *next;
#if YSF_VARIOUS_TIMER_TYPE
    ysf_timer_class_t class;
#endif
}ysf_timer_cb_t;

typedef ysf_u16_t ysf_timing_t;

/**
 *******************************************************************************
 * @brief        define event timer type
 *******************************************************************************
 */
typedef struct
{
    ysf_timer_cb_t cb;

    struct
    {
        ysf_timing_t time;
    }config;

    struct
    {
        ysf_event_t event;
    }param;
}ysf_event_timer_t;

/**
 *******************************************************************************
 * @brief        define cycle event timer type
 *******************************************************************************
 */
typedef struct
{
    ysf_timer_cb_t cb;

    struct
    {
        ysf_timing_t setTime;
        ysf_timing_t time;
    }config;

    struct
    {
        ysf_event_t event;
    }param;
}ysf_cycle_event_timer_t;

/**
 *******************************************************************************
 * @brief        define trigger timer type
 *******************************************************************************
 */
typedef struct
{
    ysf_timer_cb_t cb;

    struct
    {
        ysf_timing_t time;
    }config;

    struct
    {
        void (*func)(void *param);
        void *param;
    }param;
}ysf_trigger_timer_t;

/**
 *******************************************************************************
 * @brief        define cycle trigger timer type
 *******************************************************************************
 */
typedef struct
{
    ysf_timer_cb_t cb;

    struct
    {
        ysf_timing_t timing;
    }config;

    struct
    {
        void (*func)(void *param);
        void *param;
    }param;
}ysf_cycle_trigger_timer_t;

/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
//extern ysf_err_t ysf_event_timer_disarm(ysf_event_timer_t*);
//extern ysf_err_t ysf_event_timer_arm(ysf_event_timer_t*);
//extern ysf_err_t ysf_event_timer_init(ysf_event_timer_t*, user_timing_t, uint8_t);
//extern ysf_err_t ysf_event_timer_handler( void );

#endif      /* _USER_TIMER_ */
/**********************************END OF FILE*********************************/
