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
#define YSF_HEAD_PATH                        "../ysf/ysf.h"
#define YSF_EVENT_CONF_PATH                  "../ysf/ysf_event_conf.h"
    
#define YSF_COMMTOOLS_PATH                   "../ysf/common/tools.h"	
#define YSF_OOPC_PATH          		         "../ysf/common/oopc.h"
#define YSF_TYPE_PATH         		         "../ysf/common/type.h"
	
#define YSF_COMPILER_PATH                    "../ysf/compiler/compiler.h"
#define YSF_VS_COMPILER_CONF_PATH            "../ysf/compiler/vs/compiler_conf.h"
#define YSF_ARMCC6_COMPILER_CONF_PATH        "../ysf/compiler/armcc6/compiler_armcc6.h"
#define YSF_ARMCC5_COMPILER_CONF_PATH        "../ysf/compiler/armcc5/compiler_armcc5.h"
#define YSF_GCC_COMPILER_CONF_PATH           "../ysf/compiler/gcc/compiler_conf.h"
#define YSF_SIMULATION_COMPILER_CONF_PATH    "../ysf/compiler/simulation/compiler_conf.h"
#define YSF_ICCARM_COMPILER_CONF_PATH        "../ysf/compiler/iccarm/compiler_iar_arm.h"
#define YSF_ICC_STM8_COMPILER_CONF_PATH      "../ysf/compiler/iccstm8/compiler_conf.h"
	
#define YSF_COMPONENT_TICK_PATH              "../ysf/component/tick/tick.h"
#define YSF_COMPONENT_BUFFER_PATH            "../ysf/component/buffer/buffer.h"
#define YSF_COMPONENT_MEMORY_PATH            "../ysf/component/memory/memory.h"
#define YSF_COMPONENT_TIMER_PATH             "../ysf/component/timer/timer.h"
#define YSF_COMPONENT_EVENT_PATH             "../ysf/component/event/event.h"
#define YSF_COMPONENT_SIGNAL_PATH            "../ysf/component/signal/signal.h"
#define YSF_COMPONENT_DEBUG_PATH             "../ysf/component/debug/debug.h"
#define YSF_COMPONENT_SINGLE_LIST_PATH       "../ysf/component/list/single_list.h"

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** ysf path config  */

/**********************************END OF FILE*********************************/
