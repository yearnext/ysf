/**
  ******************************************************************************
  * @file       ysf_key.h
  * @author     yearnext
  * @version    1.0.0
  * @date       2017-1-15
  * @brief      ynf key head file
  * @par        work platform
  *                 Windows
  * @par        compile platform
  *                 GCC
  ******************************************************************************
  * @note
  * 1.XXXXX                  						                     
  ******************************************************************************
  */

/**
 * @defgroup ysf key
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __YSF_KEY_H__
#define __YSF_KEY_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "ysf_type.h"
#include "ysf_timer.h"

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       按键模块配置层
 *******************************************************************************
 */
/** 按键扫描时间 */
#define YSF_KEY_SCAN_TIME        (10)
#define YSF_KEY_TIME2COUNT(n)    ((n)/YSF_KEY_SCAN_TIME)

/** 按键动作 */
#define YSF_KEY_ACTIVE_LOW       !
#define YSF_KEY_ACTIVE_HIGH      !!
#define YSF_KEY_ACTIVE           YSF_KEY_ACTIVE_LOW

/**
 *******************************************************************************
 * @brief       按键调试宏开关
 *******************************************************************************
 */
#define USE_YSF_KEY_DEBUG (1)

/* Exported types ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** ysf key */

/**********************************END OF FILE*********************************/
