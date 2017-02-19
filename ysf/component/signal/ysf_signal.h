/**
  ******************************************************************************
  * @file       ysf_signal.h
  * @author     yearnext
  * @version    1.0.0
  * @date       2017-1-15
  * @brief      ynf signal head file
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
 * @defgroup ysf signal
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __YSF_SIGNAL_H__
#define __YSF_SIGNAL_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define YSF_SIGNAL_SCAN_TIME        (10)
#define YSF_SIGNAL_TIME2COUNT(n)    ((n)/YSF_SIGNAL_SCAN_TIME)

#define YSF_SIGNAL_ACTIVE_LOW       !
#define YSF_SIGNAL_ACTIVE_HIGH      !!
#define YSF_SIGNAL_ACTIVE           YSF_SIGNAL_ACTIVE_LOW

#define USE_YSF_SIGNAL_DEBUG (1)

/* Exported types ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** ysf signal */

/**********************************END OF FILE*********************************/
