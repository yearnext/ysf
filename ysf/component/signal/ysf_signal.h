/**
  ******************************************************************************
  * @file       ysf_signal.h
  * @author     yearnext
  * @version    1.0.0
  * @date       2017-1-15
  * @brief      ynf signal head file
  * @par        work platform
  *                 Windows
  * @par        compile platform
  *                 GCC
  ******************************************************************************
  * @note
  * 1.XXXXX                  						                     
  ******************************************************************************
  */

/**
 * @defgroup ysf signal
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __YSF_SIGNAL_H__
#define __YSF_SIGNAL_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "../ysf/common/ysf_type.h"
#include "../ysf/component/event/ysf_event.h"

/* Exported macro ------------------------------------------------------------*/
#define YSF_SIGNAL_SCAN_TIME        (10)
#define YSF_SIGNAL_TIME2COUNT(n)    ((n)/YSF_SIGNAL_SCAN_TIME)

#define YSF_SIGNAL_ACTIVE_LOW       !
#define YSF_SIGNAL_ACTIVE_HIGH      !!
#define YSF_SIGNAL_ACTIVE           YSF_SIGNAL_ACTIVE_LOW

#define USE_YSF_SIGNAL_DEBUG (1)

#define USE_GENRAL_SIGNAL_
#define USE_FULL_SIGNAL (0)

#define USE_SINGAL_EVENT_NUM (4)

/* Exported types ------------------------------------------------------------*/
typedef enum signal_status
{
    SIGNAL_STATUS_INIT                 = 10,

    SIGNAL_STATUS_DETECT               = 20,

    SIGNAL_STATUS_PRESS_FILTER_STEP1   = 30,
    SIGNAL_STATUS_PRESS_FILTER_STEP2   = 31,
    SIGNAL_STATUS_PRESS_FILTER_STEP3   = 32,
    SIGNAL_STATUS_RELEASE_FILTER_STEP1 = 40,
    SIGNAL_STATUS_RELEASE_FILTER_STEP2 = 41,
    SIGNAL_STATUS_RELEASE_FILTER_STEP3 = 42,

    SIGNAL_STATUS_RELEASE              = 0,
    SIGNAL_STATUS_PRESS_EDGE           = 1,
    SIGNAL_STATUS_PRESS                = 2,
    SIGNAL_STATUS_LONG_PRESS           = 4,
    SIGNAL_STATUS_MULTI_PRESS          = 5,
    SIGNAL_STATUS_RELEASE_EDGE         = 3,
}signal_status_t;

typedef enum
{
    YSF_EVENT_SIGNAL,
    YSF_TRIGGER_SIGNAL,
}singal_class_t;

typedef struct
{
    void *next;
    singal_class_t class;
}ysf_signal_cb_t;

typedef ysf_event_t ysf_singal_event_t[USE_SINGAL_EVENT_NUM];

typedef struct
{
    ysf_signal_cb_t cb;

    struct
    {
        signal_status_t status;
        ysf_singal_event_t event;
        signal_status_t (*detect)(void);

    }param;
}ysf_event_signal_t;

typedef struct
{
    ysf_signal_cb_t cb;

    struct
    {
        signal_status_t status;
        signal_status_t (*detect)(void);
        ysf_err_t (*handler)(signal_status_t);
    }param;
}ysf_trigger_signal_t;

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** ysf signal */

/**********************************END OF FILE*********************************/
