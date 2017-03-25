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
struct ysf_fsm_t
{
    uint16_t state;
};
    
/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** ysf state machine component  */

/**********************************END OF FILE*********************************/
