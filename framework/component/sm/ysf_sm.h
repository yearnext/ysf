/**
 ******************************************************************************
 * @file       ysf_sm.h
 * @author     yearnext
 * @version    1.0.0
 * @date       2017Äê2ÔÂ21ÈÕ
 * @brief      ysf state machine head file
 * @par        work paltform		                             
 *                 Windows
 * @par        compiler paltform									                         
 * 				   GCC
 ******************************************************************************
 * @note
 * 1.XXXXX                  						                     
 ******************************************************************************
 */

/**
 * @defgroup ysf machine component
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __YSF_MACHINE_H__
#define __YSF_MACHINE_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "ysf_path.h"
#include YSF_TYPE_PATH
    
/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define function name macro 
 *******************************************************************************
 */
enum
{
    YSF_SM_EVT_ENTER,
    YSF_SM_EVT_EXIT,
};

struct ysf_evt_t
{
    int16_t evt;    
    void *user_data;
};

/**
 *******************************************************************************
 * @brief      define function name macro 
 *******************************************************************************
 */
struct ysf_fsm_t
{
    struct ysf_evt_t evt;
    struct ysf_evt_t *(*handler)(struct ysf_fsm_t *fsm, struct ysf_evt_t *evt);
};
    
/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** ysf state machine component  */

/**********************************END OF FILE*********************************/
