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
#include "../ysf/common/ysf_type.h"
#include "../ysf/component/event/ysf_event_conf.h"

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       event component debug config
 *******************************************************************************
 */
#define USE_YNF_EVENT_DEBUG (0)

/**
 *******************************************************************************
 * @brief       event component auto config
 *******************************************************************************
 */
#define USE_YNF_EVENT_AUTO_MODE (1)

/* Exported types ------------------------------------------------------------*/
typedef struct
{
    ysf_err_t (*init)(void);
    ysf_err_t (*send)(ysf_event_t);
    ysf_err_t (*read)(ysf_event_t*);
}ysf_event_func_list_t;

/* Exported variables --------------------------------------------------------*/
extern const ysf_event_func_list_t ysf_event;

/* Exported functions --------------------------------------------------------*/
extern ysf_err_t ysf_event_init( void );
extern ysf_err_t ysf_event_send( ysf_event_t );
extern ysf_err_t ysf_event_read( ysf_event_t* );

#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /* ysf event component  */

/**********************************END OF FILE*********************************/
