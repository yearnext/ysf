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

#define YSF_HEAD_PATH                        "../ysf/ysf.h"
#define YSF_EVENT_CONF_PATH                  "../ysf/ysf_event_conf.h"
    
#define YSF_COMMTOOLS_PATH                   "../ysf/common/ysf_commtools.h"	
#define YSF_OOPC_PATH          		         "../ysf/common/ysf_oopc.h"
#define YSF_TYPE_PATH         		         "../ysf/common/ysf_type.h"
	
#define YSF_COMPILER_PATH                    "../ysf/compiler/ysf_compiler.h"
#define YSF_VS_COMPILER_CONF_PATH            "../ysf/compiler/vs/ysf_compiler_conf.h"
#define YSF_ARMCC6_COMPILER_CONF_PATH        "../ysf/compiler/armcc6/ysf_compiler_conf.h"
#define YSF_ARMCC5_COMPILER_CONF_PATH        "../ysf/compiler/armcc5/ysf_compiler_conf.h"
#define YSF_GCC_COMPILER_CONF_PATH           "../ysf/compiler/gcc/ysf_compiler_conf.h"
#define YSF_SIMULATION_COMPILER_CONF_PATH    "../ysf/compiler/simulation/ysf_compiler_conf.h"
#define YSF_ICCARM_COMPILER_CONF_PATH        "../ysf/compiler/iccarm/ysf_compiler_conf.h"
#define YSF_ICC_STM8_COMPILER_CONF_PATH      "../ysf/compiler/iccstm8/ysf_compiler_conf.h"
	
#define YSF_COMPONENT_TICK_PATH              "../ysf/component/tick/ysf_tick.h"
#define YSF_COMPONENT_BUFFER_PATH            "../ysf/component/buffer/ysf_buffer.h"
#define YSF_COMPONENT_MEMORY_PATH            "../ysf/component/memory/ysf_memory.h"
#define YSF_COMPONENT_TIMER_PATH             "../ysf/component/timer/ysf_timer.h"
#define YSF_COMPONENT_EVENT_PATH             "../ysf/component/event/ysf_event.h"
#define YSF_COMPONENT_SIGNAL_PATH            "../ysf/component/signal/ysf_signal.h"
#define YSF_COMPONENT_DEBUG_PATH             "../ysf/component/debug/ysf_debug.h"
#define YSF_COMPONENT_SINGLE_LIST_PATH       "../ysf/component/list/ysf_single_list.h"

#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /* ysf path config  */

/**********************************END OF FILE*********************************/
