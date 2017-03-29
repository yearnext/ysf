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

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "ysf_path.h"
#include YSF_TYPE_PATH
#include YSF_COMPONENT_TASK_PATH
#include YSF_COMPONENT_TICK_PATH
#include YSF_COMPONENT_SINGLE_LIST_PATH

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        config timer api switch
 *******************************************************************************
 */
#define USE_YSF_TIMER_API        (1)

/**
 *******************************************************************************
 * @brief       ysf timer tick config
 *******************************************************************************
 */
#define YSF_TIMER_PERIOD         YSF_TICK_TIME
#define YSF_TIME_2_TICK(time)    ((time)/YSF_TIMER_PERIOD)

#define YSF_TIMER_CYCLE_PARAM    (0)

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        ysf timer type
 *******************************************************************************
 */
struct ysf_timer_t
{
    struct
    {
        struct ysf_timer_t *next;
        ysf_status_t  status;
    }control;
    
    struct
    {
        struct ysf_task_t callback;

        uint16_t event;
    }handler;

    struct
    {
        ysf_tick_t ticks;
        ysf_tick_t loadTicks;
        
        uint8_t cycle;
    }config;
};

/**
 *******************************************************************************
 * @brief      interface function defineitions 
 *******************************************************************************
 */
#if defined(USE_YSF_TIMER_API) && USE_YSF_TIMER_API
struct YSF_TIMER_API
{
    ysf_err_t (*init)(void);
    ysf_err_t (*handler)(uint16_t);
    
    struct
    {
        ysf_err_t (*cb_init)(struct ysf_timer_t*, ysf_err_t (*func)(void*, void*), void*, void*);
        ysf_err_t (*evt_init)(struct ysf_timer_t*, uint16_t);
        ysf_err_t (*arm)(struct ysf_timer_t*,uint32_t,uint16_t);
        ysf_err_t (*disarm)(struct ysf_timer_t*);
    };
};
#endif

/* Exported constants --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      defineitions interface function 
 *******************************************************************************
 */
#if defined(USE_YSF_TIMER_API) && USE_YSF_TIMER_API
extern ysf_err_t ysf_timer_init(void);
//extern struct ysf_timer_t *ysf_timerSimple_cb_arm(uint32_t, uint8_t, ysf_err_t (*func)(void*), void*);                                         
//extern struct ysf_timer_t *ysf_timerSimple_evt_arm(uint32_t, uint8_t, uint16_t);                                             
//extern ysf_err_t ysf_timerEx_cb_init(struct ysf_timer_t*, ysf_err_t (*func)(void*), void*);                                          
//extern ysf_err_t ysf_timerEx_evt_init(struct ysf_timer_t*, uint16_t);                                          
//extern ysf_err_t ysf_timerEx_arm(struct ysf_timer_t*, uint32_t, uint8_t);                                          
//extern ysf_err_t ysf_timer_disarm(struct ysf_timer_t*);                                          
//extern ysf_err_t ysf_timer_handler(uint16_t);
#endif

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif      /** timer */
/**********************************END OF FILE*********************************/
