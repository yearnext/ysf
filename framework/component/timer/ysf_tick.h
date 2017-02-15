/**
 ******************************************************************************
  * @file       ysf_tick.h
  * @author     yearnext
  * @version    1.0.0
  * @date       2017年1月10日
  * @brief      ysf_tick 头文件
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
 * @defgroup ysf_event配置
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __YSF_TICK_H__
#define __YSF_TICK_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "ysf_type.h"

/* Exported macro ------------------------------------------------------------*/
#define YSF_TICK_MAX (0xFFFFFFFFUL)

/* Exported types ------------------------------------------------------------*/
typedef ysf_u32_t ysf_tick_t;

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
extern void ysf_tick_init( void );
extern void ysf_tick_inc( void );
extern ysf_tick_t ysf_tick_read( void );

#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /* YSF_TICK 配置  */

/**********************************END OF FILE*********************************/
