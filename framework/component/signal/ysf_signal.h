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
#include YSF_COMPONENT_TASK_PATH

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       config signal api switch
 *******************************************************************************
 */
#define USE_YSF_SIGNAL_API          (1)
    
/**
 *******************************************************************************
 * @brief       config signal time
 *******************************************************************************
 */
#define YSF_SIGNAL_SCAN_TIME        YSF_TIME_2_TICK(10)
#define YSF_SIGNAL_TIME2COUNT(n)    ((n)/YSF_SIGNAL_SCAN_TIME)

#define YSF_SIGNAL_ACTIVE_LOW       !
#define YSF_SIGNAL_ACTIVE_HIGH      !!
#define YSF_SIGNAL_ACTIVE           YSF_SIGNAL_ACTIVE_LOW
   
/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define signal status enumeration
 *******************************************************************************
 */
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

/**
 *******************************************************************************
 * @brief       define signal type
 *******************************************************************************
 */
struct ysf_signal_t
{
    struct
    {
        struct ysf_sList_t *next;
        ysf_status_t useStatus;
    };
    
    struct
    {
        enum ysf_signal_status_t (*detect)(void);
        
        struct ysf_task_t callback;
        uint16_t event;
    };
    
    enum ysf_signal_status_t status;
};

/**
 *******************************************************************************
 * @brief       ysf signal api
 *******************************************************************************
 */
#if defined(USE_YSF_SIGNAL_API) && USE_YSF_SIGNAL_API
struct YSF_SIGNAL_API
{
    ysf_err_t (*init)(void);
//    ysf_err_t (*handler)(void*);
    
    ysf_err_t (*cb_init)(struct ysf_signal_t*, void (*)(void*, void*), void*, void*);
    ysf_err_t (*evt_init)(struct ysf_signal_t*, uint16_t);
    ysf_err_t (*arm)(struct ysf_signal_t*, enum ysf_signal_status_t (*)(void));            
    ysf_err_t (*disarm)(struct ysf_signal_t*);
};
#endif

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       ysf signal api
 *******************************************************************************
 */
#if defined(USE_YSF_SIGNAL_API) && USE_YSF_SIGNAL_API
extern ysf_err_t ysf_signal_init(void);

extern struct ysf_signal_t *ysf_signalSimple_arm(enum ysf_signal_status_t (*detect)(void), 
                                                 void (*handler)(enum ysf_signal_status_t));

extern ysf_err_t ysf_signalEx_arm(struct ysf_signal_t*, 
                                  enum ysf_signal_status_t (*detect)(void), 
                                  void (*handler)(enum ysf_signal_status_t));
                                       
extern ysf_err_t ysf_signal_disarm(struct ysf_signal_t*);
                                       
//extern ysf_err_t ysf_signal_handler(void *);
#endif
                                       
/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** ysf signal */

/**********************************END OF FILE*********************************/
