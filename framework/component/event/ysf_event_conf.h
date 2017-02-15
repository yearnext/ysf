/**
 ******************************************************************************
 * @file       ysf_event_conf.h
 * @author     yearnext
 * @version    1.0.0
 * @date       2017��2��12��
 * @brief      ysf_event_conf ͷ�ļ�
 * @par        ����ƽ̨                                  
 *                 Windows
 * @par        ����ƽ̨									                         
 * 				GCC
 ******************************************************************************
 * @note
 * 1.XXXXX                  						                     
 ******************************************************************************
 */

/**
 * @defgroup ysf�¼���Ϣ����
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
 * @brief       �¼���Ϣ��װ
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

/** @}*/     /* ysf_event_conf ����  */

/**********************************END OF FILE*********************************/
