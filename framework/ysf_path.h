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
 * @defgroup ysf path config
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

/* Exported macro ------------------------------------------------------------*/
#define YSF_HEAD_PATH                        "../framework/ysf.h"
#define YSF_EVENT_CONF_PATH                  "../framework/ysf_event_conf.h"
    
#define YSF_COMMTOOLS_PATH                   "../framework/common/tools.h"	
#define YSF_OOPC_PATH          		         "../framework/common/oopc.h"
#define YSF_TYPE_PATH         		         "../framework/common/type.h"
	
#define YSF_COMPILER_PATH                    "../framework/compiler/compiler.h"
#define YSF_VS_COMPILER_CONF_PATH            "../framework/compiler/vs/compiler_conf.h"
#define YSF_ARMCC6_COMPILER_CONF_PATH        "../framework/compiler/armcc6/compiler_armcc6.h"
#define YSF_ARMCC5_COMPILER_CONF_PATH        "../framework/compiler/armcc5/compiler_armcc5.h"
#define YSF_GCC_COMPILER_CONF_PATH           "../framework/compiler/gcc/compiler_conf.h"
#define YSF_SIMULATION_COMPILER_CONF_PATH    "../framework/compiler/simulation/compiler_conf.h"
#define YSF_ICCARM_COMPILER_CONF_PATH        "../framework/compiler/iccarm/compiler_iar_arm.h"
#define YSF_ICC_STM8_COMPILER_CONF_PATH      "../framework/compiler/iccstm8/compiler_conf.h"
	
#define YSF_COMPONENT_TICK_PATH              "../framework/component/tick/ysf_tick.h"
#define YSF_COMPONENT_BUFFER_PATH            "../framework/component/buffer/ysf_buffer.h"
#define YSF_COMPONENT_MEMORY_PATH            "../framework/component/memory/ysf_memory.h"
#define YSF_COMPONENT_TIMER_PATH             "../framework/component/timer/ysf_timer.h"
#define YSF_COMPONENT_EVENT_PATH             "../framework/component/event/ysf_event.h"
#define YSF_COMPONENT_SIGNAL_PATH            "../framework/component/signal/ysf_signal.h"
#define YSF_COMPONENT_DEBUG_PATH             "../framework/component/debug/ysf_debug.h"
#define YSF_COMPONENT_SINGLE_LIST_PATH       "../framework/component/list/ysf_single_list.h"

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** ysf path config  */

/**********************************END OF FILE*********************************/
