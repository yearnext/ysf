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
#define YSF_MAL_PATH          "../ysf/hal/stm32f1xx/mal/mal.h"
#define YSF_MSP_GPIO_PATH     "../ysf/hal/stm32f1xx/gpio.h"
#define YSF_MSP_TIMER_PATH    "../ysf/hal/stm32f1xx/timer.h"
#define YSF_MAL_CORE_CM3_PATH "../ysf/hal/stm32f1xx/mal/cmsis/core_cm3.h"
#define YSF_MAL_START_UP_PATH "../ysf/hal/stm32f1xx/startup/system_stm32f1xx.h"
   
/* Includes ------------------------------------------------------------------*/  
#include YSF_MAL_PATH
#include YSF_MSP_GPIO_PATH
#include YSF_MSP_TIMER_PATH

/* Exported macro ------------------------------------------------------------*/
#define USE_HAL_API (1)
    
/* Exported types ------------------------------------------------------------*/
#if USE_HAL_API
struct HAL_API
{
    struct
    {
#if defined(USE_MSP_GPIO_API) && USE_MSP_GPIO_API
        struct MSP_GPIO_API gpio;
#endif
        
#if defined(USE_MSP_TIMER_API) && USE_MSP_TIMER_API
    struct MSP_TIMER_API timer;
#endif
    }msp;
    
    struct
    {
#if defined(USE_MAP_GPIO_API) && USE_MAP_GPIO_API
    struct MAP_GPIO_API gpio;
#endif
        
#if defined(USE_MAP_TIMER_API) && USE_MAP_TIMER_API
        struct MAP_TIMER_API timer;
#endif
    }map;
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
