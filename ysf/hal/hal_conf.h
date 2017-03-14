/**
 ******************************************************************************
 * @file       hal_conf.h
 * @author     yearnext
 * @version    1.0.0
 * @date       2017Äê3ÔÂ4ÈÕ
 * @brief      hal config head file
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
#ifndef __YSF_HAL_CONF_H__
#define __YSF_HAL_CONF_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define USE_MCU_STM32F1 (1)
#define USE_MCU_STM8S   (2)
#define __TARGET_CHIP__ USE_MCU_STM32F1
    
#define MCU_CLOCK_FREQ ((uint32_t)72000000) 
#define MCU_HSE_FREQ   ((uint32_t)8000000)    
    
#if __TARGET_CHIP__ == USE_MCU_STM32F1
    #define STM32F103xE

#elif __TARGET_CHIP__ == USE_MCU_STM8S
    #define STM8S003
#else
#endif
    
/* Exported types ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/ 
/* Exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /* hal config component  */

/**********************************END OF FILE*********************************/
