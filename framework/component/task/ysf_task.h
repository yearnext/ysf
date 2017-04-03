/**
 ******************************************************************************
  * @file       ysf_task.h
  * @author     yearnext
  * @version    1.0.0
  * @date       2017-1-10
  * @brief      ysf task head file
  * @par        work platform
  *                 Windows
  * @par        compiler platform
  * 				GCC
 ******************************************************************************
  * @note
  * 1.XXXXX                  						                     
 ******************************************************************************
 */

/**
 * @defgroup ysf task
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __YSF_TASK_H__
#define __YSF_TASK_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "ysf_path.h"
#include YSF_TYPE_PATH

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       ysf task api enable switch
 *******************************************************************************
 */
#define USE_YSF_TASK_API (1)

/* Exported types ------------------------------------------------------------*/    
/**
 *******************************************************************************
 * @brief       ysf task block
 *******************************************************************************
 */
struct ysf_task_t
{
    struct
    {
        struct ysf_task_t    *next;
        
        enum ysf_task_type_t
        {
            YSF_CALL_BACK_TASK,
            YSF_EVENT_TRIGGER_TASK,
            YSF_EVENT_HANDLER_TASK,
        }type;
    };
    
    struct
    {                
        union
        {
            ysf_err_t (*evt_trigger)(void*, uint16_t);
            ysf_err_t (*evt_handler)(uint16_t);
            ysf_err_t (*cb)(void*);
        };

        void *param;
        uint16_t event;
    };
};

/**
 *******************************************************************************
 * @brief       ysf task api
 *******************************************************************************
 */
#if defined(USE_YSF_TASK_API) && USE_YSF_TASK_API
struct YSF_TASK_API
{
    ysf_err_t (*init)(void);
    ysf_err_t (*poll)(void);
    
    struct
    {
        ysf_err_t (*evt_trigger)(struct ysf_task_t*, ysf_err_t (*)(void*, uint16_t), void*, uint16_t);
        ysf_err_t (*evt_handler)(struct ysf_task_t*, ysf_err_t (*)(uint16_t), uint16_t);
        ysf_err_t (*call_back)(struct ysf_task_t*, ysf_err_t (*)(void*), void*);
    }create;
};
#endif

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if defined(USE_YSF_TASK_API) && USE_YSF_TASK_API
extern ysf_err_t ysf_task_init(void);
extern ysf_err_t ysf_task_poll(void);
extern ysf_err_t ysf_evtTriggerTask_create(struct ysf_task_t*, ysf_err_t (*)(void*, uint16_t), void*, uint16_t);
extern ysf_err_t ysf_evtHandlerTask_create(struct ysf_task_t*, ysf_err_t (*)(uint16_t), uint16_t);
extern ysf_err_t ysf_cbTask_create(struct ysf_task_t*, ysf_err_t (*)(void*), void*);
#endif    
    
/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** ysf task component  */

/**********************************END OF FILE*********************************/
