/**
 ******************************************************************************
  * @file       ysf_tick.h
  * @author     yearnext
  * @version    1.0.0
  * @date       2017-1-10
  * @brief      ysf tick head file
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
 * @defgroup ysf tick
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
#include "../ysf/common/ysf_type.h"

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       ysf tick component enable configuration
 *******************************************************************************
 */
#define USE_YSF_TICK (1)

/**
 *******************************************************************************
 * @brief       ysf tick max value
 *******************************************************************************
 */
#define YSF_TICK_MAX YSF_UINT32_MAX

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       ysf tick type
 *******************************************************************************
 */
typedef ysf_vu32_t ysf_tick_t;

/**
 *******************************************************************************
 * @brief       ysf tick func list
 *******************************************************************************
 */
struct _YSF_TICK_API_
{
    void (*init)(void);
    void (*inc)(void);
    ysf_tick_t (*read)(void);
    ysf_tick_t (*cal)(void);
};

/* Exported variables --------------------------------------------------------*/
extern const struct _YSF_TICK_API_ ysf_tick;

/* Exported functions --------------------------------------------------------*/
#if USE_YSF_TICK
extern void ysf_tick_init( void );
extern void ysf_tick_inc( void );
extern ysf_tick_t ysf_tick_get( void );
extern ysf_tick_t ysf_past_tick_cal( void );

#else
#define ysf_tick_init()
#define ysf_tick_inc()
#define ysf_tick_read() (0)

#endif

#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /* ysf tick component  */

/**********************************END OF FILE*********************************/
