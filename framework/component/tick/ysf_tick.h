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
#include "ysf_conf.h"
#include "ysf_path.h"
#include YSF_TYPE_PATH

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       ysf tick api enable switch
 *******************************************************************************
 */
#if defined(USE_YSF_TICK_COMPONENT) &&USE_YSF_TICK_COMPONENT
#define USE_YSF_TICK_API (1)
#else
#define USE_YSF_TICK_API (0)
#endif

/**
 *******************************************************************************
 * @brief       ysf tick time(unit: ms)
 *******************************************************************************
 */
#define YSF_TICK_TIME    (1)
    
/**
 *******************************************************************************
 * @brief       ysf tick max value
 *******************************************************************************
 */
#define YSF_TICK_MAX UINT32_MAX

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       ysf tick type
 *******************************************************************************
 */
#if USE_YSF_TICK_API
typedef uint32_t ysf_tick_t;
#endif

/**
 *******************************************************************************
 * @brief       ysf tick func list
 *******************************************************************************
 */
#if USE_YSF_TICK_API
struct YSF_TICK_API
{
    void (*init)(void);
    void (*inc)(void);
    ysf_tick_t (*read)(void);
    ysf_tick_t (*cal)(void);
};
#endif

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_YSF_TICK_API
extern void ysf_tick_init( void );
extern void ysf_tick_inc( void );
extern ysf_tick_t ysf_tick_get( void );
extern ysf_tick_t ysf_past_tick_cal( void );
#endif

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** ysf tick component  */

/**********************************END OF FILE*********************************/
