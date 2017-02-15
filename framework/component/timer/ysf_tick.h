/**
 ******************************************************************************
  * @file       ysf_tick.h
  * @author     yearnext
  * @version    1.0.0
  * @date       2017��1��10��
  * @brief      ysf_tick ͷ�ļ�
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
 * @defgroup ysf_event����
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

/** @}*/     /* YSF_TICK ����  */

/**********************************END OF FILE*********************************/
