/**
 ******************************************************************************
 * @file       hal.h
 * @author     yearnext
 * @version    1.0.0
 * @date       2017Äê3ÔÂ4ÈÕ
 * @brief      hal head file
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
 * @defgroup hal component
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __YSF_HAL_H__
#define __YSF_HAL_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "ysf_path.h"

#if defined(YSF_MSP_GPIO_DIR)
#include YSF_MSP_GPIO_DIR
#endif
    
#if defined(YSF_MSP_TIMER_DIR)
#include YSF_MSP_TIMER_DIR
#endif

/* Exported macro ------------------------------------------------------------*/
#define USE_HAL_API (1)
    
/* Exported types ------------------------------------------------------------*/
#if USE_HAL_API
struct HAL_API
{
#if defined(USE_MSP_GPIO_API) && USE_MSP_GPIO_API
    struct MSP_GPIO_API gpio;
#endif
    
#if defined(USE_MSP_TIMER_API) && USE_MSP_TIMER_API
    struct MSP_TIMER_API timer;
#endif
};
#endif

/* Exported variables --------------------------------------------------------*/
#if USE_HAL_API
extern const struct HAL_API hal;
#endif

/* Exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /* hal component  */

/**********************************END OF FILE*********************************/
