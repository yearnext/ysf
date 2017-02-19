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
#include "../ysf/component/list/ysf_single_list.h"

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       None
 *******************************************************************************
 */
#define USE_TIMER_DEBUG (1)

#if USE_TIMER_DEBUG
#define USE_EVENT_TIMER_DEBUG (1)
#endif

#define YSF_TICK_TIME         (10)

#define YSF_TIME_CAL(time)    ((time)/YSF_TICK_TIME)

#define USE_YSF_VARIOUS_TIMER_TYPE (0)

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        define general timer type
 *******************************************************************************
 */
#if USE_YSF_VARIOUS_TIMER_TYPE
typedef enum
{
    YSF_EVENT_TIMER = 1,
    YSF_EVENT_CYCLE_TIMER,

    YSF_TRIGGER_TIMER,
    YSF_TRIGGER_CYCLE_TIMER,
}ysf_timer_class_t;
#endif

typedef struct
{
    ysf_s_list_t *next;
#if USE_YSF_VARIOUS_TIMER_TYPE
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
#if USE_YSF_VARIOUS_TIMER_TYPE
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
#endif

/**
 *******************************************************************************
 * @brief        define trigger timer type
 *******************************************************************************
 */
#if USE_YSF_VARIOUS_TIMER_TYPE
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
#endif

/**
 *******************************************************************************
 * @brief        define cycle trigger timer type
 *******************************************************************************
 */
#if USE_YSF_VARIOUS_TIMER_TYPE
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
#endif

/**
 *******************************************************************************
 * @brief        define cycle trigger timer type
 *******************************************************************************
 */
struct _YSF_TIMER_API_
{
    ysf_err_t (*init)(void);
    ysf_err_t (*handler)(void);

    struct
    {
        ysf_err_t (*arm)(ysf_event_timer_t*, ysf_timing_t, ysf_event_t);
        ysf_err_t (*disarm)(ysf_event_timer_t*);

#if USE_EVENT_TIMER_DEBUG
        void (*test)(void);
#endif
    }eTimer;
#if USE_YSF_VARIOUS_TIMER_TYPE
    struct
    {
        ysf_err_t (*arm)(ysf_event_timer_t*, ysf_timing_t, ysf_event_t);
        ysf_err_t (*disarm)(ysf_event_timer_t*);

#if USE_EVENT_TIMER_DEBUG
        void (*test)(void);
#endif
    }eCycleTimer;
#endif

#if USE_YSF_VARIOUS_TIMER_TYPE
    struct
    {
        ysf_err_t (*arm)(ysf_event_timer_t*, ysf_timing_t, ysf_event_t);
        ysf_err_t (*disarm)(ysf_event_timer_t*);

#if USE_EVENT_TIMER_DEBUG
        void (*test)(void);
#endif
    }tTimer;
#endif

#if USE_YSF_VARIOUS_TIMER_TYPE
    struct
    {
        ysf_err_t (*arm)(ysf_event_timer_t*, ysf_timing_t, ysf_event_t);
        ysf_err_t (*disarm)(ysf_event_timer_t*);

#if USE_EVENT_TIMER_DEBUG
        void (*test)(void);
#endif
    }tCycleTimer;
#endif
};

/* Exported constants --------------------------------------------------------*/
extern const struct _YSF_TIMER_API_ ysf_timer;

/* Exported functions --------------------------------------------------------*/
extern ysf_err_t ysf_timer_init( void );
extern ysf_err_t ysf_event_timer_arm(ysf_event_timer_t*, ysf_timing_t, ysf_event_t);
extern ysf_err_t ysf_event_timer_disarm(ysf_event_timer_t*);

#if USE_EVENT_TIMER_DEBUG
extern void ysf_event_timer_test(void);
#else
#define ysf_event_timer_test()
#endif

extern ysf_err_t ysf_timer_handler(void);

//extern ysf_err_t ysf_event_timer_disarm(ysf_event_timer_t*);
//extern ysf_err_t ysf_event_timer_arm(ysf_event_timer_t*);
//extern ysf_err_t ysf_event_timer_init(ysf_event_timer_t*, user_timing_t, uint8_t);
//extern ysf_err_t ysf_event_timer_handler( void );

#endif      /* _USER_TIMER_ */
/**********************************END OF FILE*********************************/
