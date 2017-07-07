/**
 *******************************************************************************
 * @file       ysf_event.h
 * @author     yearnext
 * @version    1.0.0
 * @date       2017-01-10
 * @brief      framework event component head files
 * @par        paltform                                  
 *                 Windows
 * @par        compiler									                         
 * 				GCC
 *******************************************************************************
 * @note
 * 1.XXXXX                  						                     
 *******************************************************************************
 */

/**
 * @defgroup framework event component
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FRAMEWORK_EVENT_H__
#define __FRAMEWORK_EVENT_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "fw_core.h"

/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_FRAMEWORK_EVENT_COMPONENT
extern void InitEventComponent(void);
extern fw_err_t RegisterEvent(uint8_t, void (*)(uint8_t));
extern inline void PostEvent(uint8_t, uint8_t);
extern inline void PollEvent(void);
#endif

/* Define to prevent recursive inclusion -------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** framework event component */

/**********************************END OF FILE*********************************/
