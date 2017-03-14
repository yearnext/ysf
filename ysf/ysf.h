/**
 ******************************************************************************
  * @file       ysf.h
  * @author     yearnext
  * @version    1.0.0
  * @date       2017-2-18
  * @brief      ysf head file
  * @par        work platform
  *                 Windows
  * @par        compiler platform
  * 				GCC
 ******************************************************************************
  * @note
  * 1.XXXXX                  						                     
 ******************************************************************************
 */

/**
 * @defgroup ysf
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __YSF_H__
#define __YSF_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "ysf_conf.h"

/* Exported variables --------------------------------------------------------*/    
#if USE_YSF_API
extern const struct YSF_API ysf;
#endif
    
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /* ysf */

/**********************************END OF FILE*********************************/
