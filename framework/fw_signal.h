/**
 ******************************************************************************
 * @file       fw_signal.h
 * @author     yearnext
 * @version    1.0.0
 * @date       2017-01-10
 * @brief      framework signal head files
 * @par        paltform                                  
 *                 Windows
 * @par        compiler									                         
 * 				   GCC
 ******************************************************************************
 * @note
 * 1.XXXXX                  						                     
 ******************************************************************************
 */

/**
 * @defgroup framework signal component
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FRAMEWORK_SIGNAL_H__
#define __FRAMEWORK_SIGNAL_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "fw_core.h"
#include "fw_timer.h"
    
/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        framework signal component config
 *******************************************************************************
 */
#define USE_FRAMEWORK_SIGNAL_COMPONENT                                       (1)
 
/**
 *******************************************************************************
 * @brief        framework signal preiod config
 *******************************************************************************
 */
#define FW_SIGNAL_SCAN_PREIOD                                  (FW_TIME_SET(10))

/**
 *******************************************************************************
 * @brief       define signal info param
 *******************************************************************************
 */
#define NO_SIGNAL_INFO                                                       (0)
#define IS_NO_SIGNAL(signal)                        ((signal) == NO_SIGNAL_INFO)
    
/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        framework signal status config
 *******************************************************************************
 */
typedef enum
{
    SIGNAL_STATUS_INIT,
    
    SIGNAL_STATUS_DETECTION,
    
    SIGNAL_STATUS_PRESS_FILTER_STEP1,
    SIGNAL_STATUS_PRESS_FILTER_STEP2,
    SIGNAL_STATUS_PRESS_FILTER_STEP3,
    SIGNAL_STATUS_RELEASE_FILTER_STEP1,
    SIGNAL_STATUS_RELEASE_FILTER_STEP2,
    SIGNAL_STATUS_RELEASE_FILTER_STEP3,
    
	SIGNAL_STATUS_RELEASE              = 0x80,
    SIGNAL_STATUS_PRESS_EDGE           = 0x81,
    SIGNAL_STATUS_PRESS                = 0x82,
    SIGNAL_STATUS_LONG_PRESS           = 0x83,
    SIGNAL_STATUS_MULTI_PRESS          = 0x84,
    SIGNAL_STATUS_RELEASE_EDGE         = 0x85,
}signal_status_t;

/**
 *******************************************************************************
 * @brief        framework signal num config
 *******************************************************************************
 */
enum
{
	SIGNAL_KEY = 0,
	SIGNAL_MAX,
};

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_FRAMEWORK_SIGNAL_COMPONENT
extern void fw_signal_init( void );
extern void fw_signal_handler(uint8_t);

extern fw_err_t fw_signal_register(uint8_t, uint8_t, uint8_t (*)(void));
extern uint8_t fw_signal_info_get(uint8_t);
#endif

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** framework signal component */

/**********************************END OF FILE*********************************/
