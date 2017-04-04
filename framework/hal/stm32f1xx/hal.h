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

/* Hal path macro ------------------------------------------------------------*/
#define YSF_MAL_PATH          "../framework/hal/stm32f1xx/mal/stm32f1xx.h"
#define YSF_MSP_GPIO_PATH     "../framework/hal/stm32f1xx/gpio.h"
#define YSF_MSP_TIMER_PATH    "../framework/hal/stm32f1xx/timer.h"
#define YSF_MAL_CORE_CM3_PATH "../framework/hal/stm32f1xx/mal/cmsis/core_cm3.h"
#define YSF_MAL_START_UP_PATH "../framework/hal/stm32f1xx/startup/system_stm32f1xx.h"
   
/* Includes ------------------------------------------------------------------*/  
#include YSF_MAL_PATH
#include YSF_MSP_GPIO_PATH
#include YSF_MSP_TIMER_PATH

/* Exported macro ------------------------------------------------------------*/
#define USE_HAL_API (1)
    
/* Exported types ------------------------------------------------------------*/
#if USE_HAL_API
struct YSF_MSP_API
{
#if defined(USE_MSP_GPIO_API) && USE_MSP_GPIO_API
    struct MSP_GPIO_API gpio;
#endif
        
#if defined(USE_MSP_TIMER_API) && USE_MSP_TIMER_API
    struct MSP_TIMER_API timer;
#endif
};
    
struct YSF_MAP_API
{
#if defined(USE_MAP_GPIO_API) && USE_MAP_GPIO_API
    struct MAP_GPIO_API gpio;
#endif
        
#if defined(USE_MAP_TIMER_API) && USE_MAP_TIMER_API
    struct MAP_TIMER_API timer;
#endif
};
#endif

/* Exported variables --------------------------------------------------------*/
#if USE_HAL_API
extern const struct YSF_MSP_API msp;
extern const struct YSF_MAP_API map;
#endif

/* Exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /* hal component  */

/**********************************END OF FILE*********************************/
