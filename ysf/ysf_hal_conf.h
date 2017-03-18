/**
 ******************************************************************************
  * @file       ysf_hal_conf.h
  * @author     yearnext
  * @version    1.0.0
  * @date       2017-2-18
  * @brief      hal_conf head file
  * @par        work platform
  *                 Windows
  * @par        compiler platform
  *                 GCC
 ******************************************************************************
  * @note
  * 1.XXXXX                  						                     
 ******************************************************************************
 */

/**
 * @defgroup ysf hal config
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __YSF_HAL_CONF_H__
#define __YSF_HAL_CONF_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "ysf_conf.h"

#ifndef __TARGET_CHIP__
    #error "The use chip is not config, please config in ysf_conf.h file!"
#endif
    
#if __TARGET_CHIP__ == USE_MCU_STM32F1xx
    #include "../ysf/hal/stm32f1xx/hal.h"
#elif __TARGET_CHIP__ == USE_MCU_STM8S
    #include "../ysf/hal/stm8s/hal.h"
#else
#endif

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** ysf hal config  */

/**********************************END OF FILE*********************************/
