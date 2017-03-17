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
#include "ysf_path.h"
#include YSF_TYPE_PATH
#include YSF_COMPONENT_EVENT_PATH
#include YSF_COMPONENT_SINGLE_LIST_PATH

/* Exported macro ------------------------------------------------------------*/
#define YSF_SIGNAL_SCAN_TIME        YSF_TIME_2_TICK(10)
#define YSF_SIGNAL_TIME2COUNT(n)    ((n)/YSF_SIGNAL_SCAN_TIME)

#define YSF_SIGNAL_ACTIVE_LOW       !
#define YSF_SIGNAL_ACTIVE_HIGH      !!
#define YSF_SIGNAL_ACTIVE           YSF_SIGNAL_ACTIVE_LOW
    
#define USE_YSF_SIGNAL_API          (1)

/* Exported types ------------------------------------------------------------*/
enum ysf_signal_status_t
{
    SIGNAL_STATUS_INIT,

    SIGNAL_STATUS_PRESS_FILTER_STEP1,
    SIGNAL_STATUS_PRESS_FILTER_STEP2,
    SIGNAL_STATUS_PRESS_FILTER_STEP3,
    SIGNAL_STATUS_RELEASE_FILTER_STEP1,
    SIGNAL_STATUS_RELEASE_FILTER_STEP2,
    SIGNAL_STATUS_RELEASE_FILTER_STEP3,

    SIGNAL_STATUS_RELEASE,
    SIGNAL_STATUS_PRESS_EDGE,
    SIGNAL_STATUS_PRESS,
    SIGNAL_STATUS_LONG_PRESS,
    SIGNAL_STATUS_MULTI_PRESS,
    SIGNAL_STATUS_RELEASE_EDGE,
};

struct ysf_signal_t
{
    struct
    {
        struct ysf_sList_t *next;
        ysf_status_t status;
    }control;
    
    struct
    {
        enum ysf_signal_status_t (*detect)(void);
        void (*handler)(enum ysf_signal_status_t);
    }func;
    
    enum ysf_signal_status_t status;
};

struct YSF_SIGNAL_API
{
    ysf_err_t (*init)(void);
    ysf_err_t (*handler)(void*);
    
    struct
    {
        ysf_err_t (*arm)(enum ysf_signal_status_t (*detect)(void), void (*handler)(enum ysf_signal_status_t));
    }simple;
    
    struct
    {
        ysf_err_t (*arm)(struct ysf_signal_t *signal, 
                         enum ysf_signal_status_t (*detect)(void), 
                         void (*handler)(enum ysf_signal_status_t));
                              
        ysf_err_t (*disarm)(struct ysf_signal_t *signal);
    }ex;
};

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_YSF_SIGNAL_API
extern ysf_err_t ysf_signal_init(void);

extern ysf_err_t ysf_signalSimple_arm(enum ysf_signal_status_t (*detect)(void), 
                                      void (*handler)(enum ysf_signal_status_t));

extern ysf_err_t ysf_signalEx_arm(struct ysf_signal_t*, 
                                  enum ysf_signal_status_t (*detect)(void), 
                                  void (*handler)(enum ysf_signal_status_t));
                                       
extern ysf_err_t ysf_signalEx_disarm(struct ysf_signal_t*);
                                       
extern ysf_err_t ysf_signal_handler(void *);
#endif
                                       
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** ysf signal */

/**********************************END OF FILE*********************************/
