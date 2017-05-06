/**
 ******************************************************************************
 * @file       fw_debug.h
 * @author     yearnext
 * @version    1.0.0
 * @date       2017-01-10
 * @brief      framework debug head files
 * @par        paltform
 *                 Windows
 * @par        compiler
 *                 GCC
 ******************************************************************************
 * @note
 * 1.XXXXX
 ******************************************************************************
 */

/**
 * @defgroup framework debug component
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FRAMEWORK_DEBUG_H__
#define __FRAMEWORK_DEBUG_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "fw_core.h"

/* Framework debug -----------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      debug config
 *******************************************************************************
 */    
#if USE_GLOBAL_DEBUG
#include "bsp_uart.h"

#define log(a)     bsp_uart_tx_config(a, sizeof(a))
#else
#define log(a)
#endif
                             
/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** framework debug */

/**********************************END OF FILE*********************************/
