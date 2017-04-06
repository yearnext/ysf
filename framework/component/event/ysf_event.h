/**
 ******************************************************************************
 * @file       ysf_event.h
 * @author     yearnext
 * @version    1.0.0
 * @date       2017-2-12
 * @brief      ysf event head file
 * @par        work platform
 *                 Windows
 * @par        compiler platform
 *                 GCC
 ******************************************************************************
 * @note
 * 1.XXXXX
 ******************************************************************************
 */

/**
 * @defgroup ysf event component
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __YSF_EVENT_H__
#define __YSF_EVENT_H__

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
 * @brief       ysf config
 *******************************************************************************
 */
#ifdef USE_YSF_EVENT_COMPONENT
#if USE_YSF_EVENT_COMPONENT
    #define USE_YSF_EVENT_API (1)
#else
    #define USE_YSF_EVENT_API (0)
#endif
    
/**
 *******************************************************************************
 * @brief       user config
 *******************************************************************************
 */
#else
    #define USE_YSF_EVENT_API (0)
#endif

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define event api
 *******************************************************************************
 */
#if defined(USE_YSF_EVENT_API) && USE_YSF_EVENT_API
struct YSF_EVENT_API
{
    ysf_err_t (*init)(void);
    ysf_err_t (*post)(uint16_t);
    ysf_err_t (*read)(uint16_t*);
};
#endif

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       event function interface
 *******************************************************************************
 */
#if defined(USE_YSF_EVENT_API) && USE_YSF_EVENT_API
extern ysf_err_t ysf_event_init( void );
extern ysf_err_t ysf_event_post( uint16_t );
extern ysf_err_t ysf_event_read( uint16_t* );
#endif

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** ysf event component  */

/**********************************END OF FILE*********************************/
