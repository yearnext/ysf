/**
 *******************************************************************************
 * @file       fw_tick.h
 * @author     yearnext
 * @version    1.0.0
 * @date       2017-01-10
 * @brief      framework tick component head files
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
 * @defgroup framework tick component
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FRAMEWORK_TICK_H__
#define __FRAMEWORK_TICK_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "fw_core.h"

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @note        framework tick component config
 *******************************************************************************
 */
#define USE_FRAMEWORK_TICK_COMPONENT                                         (1)
    
/**
 *******************************************************************************
 * @note        define tick max value
 *******************************************************************************
 */
#define FW_TICK_MAX                                               (0xFFFFFFFFUL)
    
/**
 *******************************************************************************
 * @note        define tick preiod
 *******************************************************************************
 */
#define FW_TICK_PREIOD                                                      (10)

/* Exported types ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_FRAMEWORK_TICK_COMPONENT
extern void InitTickComponent(void);
extern inline void IncTick(void);
extern inline uint32_t GetTick(void);
#endif

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** framework tick component */

/**********************************END OF FILE*********************************/
