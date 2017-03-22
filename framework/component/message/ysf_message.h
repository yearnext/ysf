/**
 ******************************************************************************
 * @file       ysf_message.h
 * @author     yearnext
 * @version    1.0.0
 * @date       2017-2-12
 * @brief      ysf message head file
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
 * @defgroup ysf message component
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __YSF_MESSAGE_H__
#define __YSF_MESSAGE_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "ysf_conf.h"
#include "ysf_path.h"
#include YSF_TYPE_PATH

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       message component debug config
 *******************************************************************************
 */
#define USE_YSF_MESSAGE_API (1)

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define message api
 *******************************************************************************
 */
#if defined(USE_YSF_MESSAGE_API) && USE_YSF_MESSAGE_API
#endif

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       message function interface
 *******************************************************************************
 */
#if defined(USE_YSF_MESSAGE_API) && USE_YSF_MESSAGE_API
extern ysf_err_t ysf_message_init(void);
#endif

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** ysf message component  */

/**********************************END OF FILE*********************************/
