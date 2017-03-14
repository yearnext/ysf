/**
 ******************************************************************************
  * @file       ysf_path.h
  * @author     yearnext
  * @version    1.0.0
  * @date       2017-2-18
  * @brief      ysf_conf head file
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
 * @defgroup ysf config
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __YSF_PATH_H__
#define __YSF_PATH_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

#define YSF_HEAD_DIR                      "../ysf/ysf.h"
#define YSF_EVENT_CONF_DIR                "../ysf/ysf_event_conf.h"
    
#define YSF_COMMTOOLS_DIR                 "../ysf/common/ysf_commtools.h"	
#define YSF_OOPC_DIR           		      "../ysf/common/ysf_oopc.h"
#define YSF_TYPE_DIR          		      "../ysf/common/ysf_type.h"
	
#define YSF_COMPILER_DIR                  "../ysf/compiler/ysf_compiler.h"
#define YSF_VS_COMPILER_CONF_DIR          "../ysf/compiler/vs/ysf_compiler_conf.h"
#define YSF_ARMCC6_COMPILER_CONF_DIR      "../ysf/compiler/armcc6/ysf_compiler_conf.h"
#define YSF_ARMCC5_COMPILER_CONF_DIR      "../ysf/compiler/armcc5/ysf_compiler_conf.h"
#define YSF_GCC_COMPILER_CONF_DIR         "../ysf/compiler/gcc/ysf_compiler_conf.h"
#define YSF_SIMULATION_COMPILER_CONF_DIR  "../ysf/compiler/simulation/ysf_compiler_conf.h"
#define YSF_ICCARM_COMPILER_CONF_DIR      "../ysf/compiler/iccarm/ysf_compiler_conf.h"
#define YSF_ICC_STM8_COMPILER_CONF_DIR    "../ysf/compiler/iccstm8/ysf_compiler_conf.h"
	
#define YSF_COMPONENT_TICK_DIR            "../ysf/component/tick/ysf_tick.h"
#define YSF_COMPONENT_BUFFER_DIR          "../ysf/component/buffer/ysf_buffer.h"
#define YSF_COMPONENT_MEMORY_DIR          "../ysf/component/memory/ysf_memory.h"
#define YSF_COMPONENT_TIMER_DIR           "../ysf/component/timer/ysf_timer.h"
#define YSF_COMPONENT_EVENT_DIR           "../ysf/component/event/ysf_event.h"
#define YSF_COMPONENT_SIGNAL_DIR          "../ysf/component/signal/ysf_signal.h"
#define YSF_COMPONENT_DEBUG_DIR           "../ysf/component/debug/ysf_debug.h"
#define YSF_COMPONENT_SINGLE_LIST_DIR     "../ysf/component/list/ysf_single_list.h"

#define YSF_HAL_DIR                       "../ysf/hal/hal.h"
#define YSF_HAL_CONF_DIR                  "../ysf/hal/hal_conf.h"

#include YSF_HAL_CONF_DIR

#if __TARGET_CHIP__ == USE_MCU_STM32F1
    #define YSF_MAL_DIR                   "../ysf/hal/msp/stm32f10x/mal/mal.h"
    #define YSF_MAL_START_UP_DIR          "../ysf/hal/msp/stm32f10x/startup/system_stm32f1xx.h"
    #define YSF_MAL_CORE_CM3_DIR          "../ysf/hal/msp/stm32f10x/mal/cmsis/core_cm3.h"
    #define YSF_MSP_GPIO_DIR              "../ysf/hal/msp/stm32f10x/gpio.h"
    #define YSF_MSP_TIMER_DIR             "../ysf/hal/msp/stm32f10x/timer.h"
#elif __TARGET_CHIP__ == USE_MCU_STM8S
    #define YSF_MAL_DIR                   "../ysf/hal/msp/stm8s/mal/mal.h"
    #define YSF_MSP_GPIO_DIR              "../ysf/hal/msp/stm8s/gpio.h"
#else
    #error not support device!
#endif

#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /* ysf path config  */

/**********************************END OF FILE*********************************/
