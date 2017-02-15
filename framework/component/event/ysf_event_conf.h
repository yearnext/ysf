/**
 ******************************************************************************
 * @file       ysf_event_conf.h
 * @author     yearnext
 * @version    1.0.0
 * @date       2017年2月12日
 * @brief      ysf_event_conf 头文件
 * @par        工作平台                                  
 *                 Windows
 * @par        编译平台									                         
 * 				GCC
 ******************************************************************************
 * @note
 * 1.XXXXX                  						                     
 ******************************************************************************
 */

/**
 * @defgroup ysf事件信息配置
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
 * @brief       事件信息封装
 *******************************************************************************
 */
#define RegistrarionEvent(event) event,

#define _YSF_EVENT_HEAD(name)       typedef enum _YSF_##name##_TYPE            \
                                    {                                          \
                                        YSF_EVENT_NONE = 0,

#define _YSF_EVENT_END(name)            YSF_EVENT_MAX,                         \
                                    }ysf_event_t;

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define event message
 *******************************************************************************
 */
_YSF_EVENT_HEAD(EVENT)
// YSF core events
    RegistrarionEvent(YSF_CORE_INIT)
    RegistrarionEvent(YSF_CORE_REBOOT)
    RegistrarionEvent(YSF_CORE_RESET)
    RegistrarionEvent(YSF_CORE_TICK_UPDATE)
// user events

_YSF_EVENT_END(EVENT)

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /* ysf_event_conf 配置  */

/**********************************END OF FILE*********************************/
