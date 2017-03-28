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
        struct ysf_task_t *next;
    }control;
    
    struct
    {
        ysf_err_t (*handler)(void*, void*);
        void *param;
        void *expand;
    }func;
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
        
    struct
    {
        ysf_err_t (*add)(struct ysf_task_t*, void*, void*, void*);
    }ex;
    
    struct
    {
        ysf_err_t (*add)(void*, void*, void*);
    }simple;
};
#endif

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if defined(USE_YSF_TASK_API) && USE_YSF_TASK_API
extern ysf_err_t ysf_task_init(void);
extern ysf_err_t ysf_taskEx_add(struct ysf_task_t*, void*, void*, void*);
extern ysf_err_t ysf_taskSimple_add(void*, void*, void*);
#endif    
    
/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** ysf task component  */

/**********************************END OF FILE*********************************/
