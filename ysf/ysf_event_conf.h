/**
 ******************************************************************************
 * @file       ysf_event_conf.h
 * @author     yearnext
 * @version    1.0.0
 * @date       2017-2-12
 * @brief      ysf event conf head file
 * @par        work platform
 *                 Windows
 * @par        compiler platform
 * 				   GCC
 ******************************************************************************
 * @note
 * 1.XXXXX                  						                     
 ******************************************************************************
 */

/**
 * @defgroup ysf event config
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __YSF_EVENT_CONF_H__
#define __YSF_EVENT_CONF_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       EVENT MESSAGE PACKAGE
 *******************************************************************************
 */
#define RegistrarionEvent(event) event,

#define _YSF_EVENT_HEAD             enum                                       \
                                    {                                          \
                                        YSF_EVENT_NONE = 0,                    \
                                        YSF_CORE_TICK_UPDATE,                                          
                                        
#define _YSF_EVENT_END                  YSF_EVENT_MAX,                         \
                                    };

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define event message
 *******************************************************************************
 */
_YSF_EVENT_HEAD
    // user events
    RegistrarionEvent(LED1_BLINK_EVENT)
    RegistrarionEvent(LED2_BLINK_EVENT)
    RegistrarionEvent(KEY1_SCAN_EVENT)
    RegistrarionEvent(KEY2_SCAN_EVENT)
_YSF_EVENT_END

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /* ysf even config  */

/**********************************END OF FILE*********************************/
