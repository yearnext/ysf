/**
  ******************************************************************************
  * @file       ysf_key.h
  * @author     yearnext
  * @version    1.0.0
  * @date       2017��1��15��
  * @brief      ysf_key Դ�ļ�
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
 * @defgroup ysf_key����
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
 * @brief       ����ģ�����ò�
 *******************************************************************************
 */
/** ����ɨ��ʱ�� */
#define KEY_SCAN_TIME        (10)
#define KEY_TIME2COUNT(n)    ((n)/KEY_SCAN_TIME)

/** �������� */
#define KEY_ACTIVE_LOW       !
#define KEY_ACTIVE_HIGH      !!
#define KEY_ACTIVE           KEY_ACTIVE_LOW

/**
 *******************************************************************************
 * @brief       �������Ժ꿪��
 *******************************************************************************
 */
#define USE_YNF_KEY_DEBUG (1)

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       ����״̬
 *******************************************************************************
 */
typedef enum _YNF_KEY_STATUS_
{
    KEY_STATUS_INIT = 0,
    
    KEY_STATUS_DETECTION,
    
    KEY_STATUS_PRESS_FILTER1,
    KEY_STATUS_PRESS_FILTER2,
    KEY_STATUS_PRESS_FILTER3,
    KEY_STATUS_RELEASE_FILTER1,
    KEY_STATUS_RELEASE_FILTER2,
    KEY_STATUS_RELEASE_FILTER3,
    
    KEY_STATUS_RELEASE,
    KEY_STATUS_PRESS_EDGE,
    KEY_STATUS_PRESS,
    KEY_STATUS_LONG_PRESS,
    KEY_STATUS_MULTI_PRESS,
    KEY_STATUS_RELEASE_EDGE,
}ysf_key_status_t;

/**
 *******************************************************************************
 * @brief       ������⺯��
 *******************************************************************************
 */
typedef ysf_key_status_t(*key_detection_func)(void);

/**
 *******************************************************************************
 * @brief       �����¼��б�
 *******************************************************************************
 */
typedef uint8_t key_event_list[6];

/**
 *******************************************************************************
 * @brief       ��������
 *******************************************************************************
 */
typedef struct
{
    key_detection_func detection;
    key_event_list event;
    ysf_key_status_t status;
}ysf_key_t;

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /* ynf_key ����  */

/**********************************END OF FILE*********************************/
