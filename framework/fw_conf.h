/**
 *******************************************************************************
 * @file       fw_conf.h
 * @author     yearnext
 * @version    1.0.0
 * @date       2017-01-10
 * @brief      framework config component head files
 * @par        paltform                                  
 *                 Windows
 * @par        compiler									                         
 * 				   GCC
 *******************************************************************************
 * @note
 * 1.XXXXX                  						                     
 *******************************************************************************
 */

/**
 * @defgroup framework config component
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FRAMEWORK_CONFIG_H__
#define __FRAMEWORK_CONFIG_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       API config
 *******************************************************************************
 */
#define USE_FRAMEWORK_EVENT_COMPONENT                                        (1)

/**
 *******************************************************************************
 * @brief       queue compoent config flag
 *******************************************************************************
 */
#define USE_FRAMEWORK_QUEUE_COMPONENT                                        (1)

/**
 *******************************************************************************
 * @brief       timer compoent config flag
 *******************************************************************************
 */
#define USE_FRAMEWORK_TIMER_COMPONENT                                        (1)

/**
 *******************************************************************************
 * @brief       debug compoent config flag
 *******************************************************************************
 */
#define USE_FRAMEWORK_DEBUG_COMPONENT                                        (1)
    
/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define event class
 * @note        event value can not be greater than FW_EVENT_MAX(127)
 *******************************************************************************
 */
enum define_fw_event
{
    /** framework event */
    FW_EVENT_NONE,
    FW_TICK_EVENT,
    FW_SIGNAL_EVENT,
	FW_DELAY_EVENT,
	FW_BEGIN_EVENT,
	FW_END_EVENT,
	FW_FLOW_EVENT,
	FW_TIMEOUT_EVENT,
    FW_TRANSFER_START_EVENT,
    FW_TRANSFER_EVENT,
    FW_TRANSFER_WAIT_EVNET,
    FW_TRANSFER_COMPLET_EVENT,
    
    /** user define begin */

    /** user define end */
    FW_EVENT_MAX,
};

/**
 *******************************************************************************
 * @brief       framework task config
 *******************************************************************************
 */
enum define_fw_task
{
    /** framework task */
    FW_TICK_TASK = 0,
 	FW_SIGNAL_TASK,
 	FW_DEBUG_TASK,
    
	/** user define begin */

	/** user define end */
    FW_TASK_MAX,
};

/**
 *******************************************************************************
 * @brief       framework queue config
 *******************************************************************************
 */
enum define_fw_queue
{
	/** framework queue */
	FW_TICK_QUEUE,

	/** user define begin */

	/** user define end */
	FW_QUEUE_MAX,
};

/**
 *******************************************************************************
 * @brief        framework signal config
 *******************************************************************************
 */
enum define_fw_signal
{
	/** framework signal */

	/** user define begin */
	SIGNAL_MouseKey,
    SIGNAL_SetKey,
    SIGNAL_LedSetKey,
    SIGNAL_SoundSetKey,
    SIGNAL_SleepLedSetKey,
    SIGNAL_BackLightSetKey,
    SIGNAL_ShockSwitch,

	/** user define end */
	SIGNAL_MAX,
};

/**
 *******************************************************************************
 * @brief       framework timer config
 *******************************************************************************
 */
enum define_fw_timer
{
	/** framework timer */
    SIGNAL_SCAN_TIMER,
    FW_DEBUG_TIMER,
    
	/** user define begin */

	/** user define end */
    Timer_Max,
};

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** framework event component */

/**********************************END OF FILE*********************************/
