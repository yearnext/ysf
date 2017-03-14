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
#include "ysf_event_conf.h"
#include "ysf_path.h"
#include YSF_TYPE_DIR

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       event component debug config
 *******************************************************************************
 */
#define USE_YSF_EVENT_API (1)

/* Exported types ------------------------------------------------------------*/
struct YSF_EVENT_API
{
    ysf_err_t (*init)(void);
    ysf_err_t (*post)(uint16_t);
    ysf_err_t (*read)(uint16_t*);
    ysf_err_t (*evt_register)(uint16_t, ysf_err_t (*handler)(uint16_t));
    ysf_err_t (*evt_writeoff)(uint16_t, ysf_err_t (*handler)(uint16_t));
    ysf_err_t (*evt_handler)(void);
};

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_YSF_EVENT_API
extern ysf_err_t ysf_event_init( void );
extern ysf_err_t ysf_event_post( uint16_t );
extern ysf_err_t ysf_event_read( uint16_t* );
extern ysf_err_t ysf_event_handler_register(uint16_t, ysf_err_t (*handler)(uint16_t));
extern ysf_err_t ysf_event_handler_writeoff(uint16_t, ysf_err_t (*handler)(uint16_t));
extern ysf_err_t ysf_event_handler( void );
#endif

#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /* ysf event component  */

/**********************************END OF FILE*********************************/
