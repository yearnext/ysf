/**
  ******************************************************************************
  * @file       ysf_key.h
  * @author     yearnext
  * @version    1.0.0
  * @date       2017年1月15日
  * @brief      ysf_key 源文件
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
 * @defgroup ysf_key配置
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
#define KEY_SCAN_TIME        (10)
#define KEY_TIME2COUNT(n)    ((n)/KEY_SCAN_TIME)

/** 按键动作 */
#define KEY_ACTIVE_LOW       !
#define KEY_ACTIVE_HIGH      !!
#define KEY_ACTIVE           KEY_ACTIVE_LOW

/**
 *******************************************************************************
 * @brief       按键调试宏开关
 *******************************************************************************
 */
#define USE_YNF_KEY_DEBUG (1)

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       按键状态
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
 * @brief       按键检测函数
 *******************************************************************************
 */
typedef ysf_key_status_t(*key_detection_func)(void);

/**
 *******************************************************************************
 * @brief       按键事件列表
 *******************************************************************************
 */
typedef uint8_t key_event_list[6];

/**
 *******************************************************************************
 * @brief       按键类型
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

/** @}*/     /* ynf_key 配置  */

/**********************************END OF FILE*********************************/
