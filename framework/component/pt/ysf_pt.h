/**
 ******************************************************************************
 * @file       ysf_pt.h
 * @author     yearnext
 * @version    1.0.0
 * @date       2017Äê2ÔÂ21ÈÕ
 * @brief      ysf pt head file
 * @par        work paltform		                             
 *                 Windows
 * @par        compiler paltform									                         
 * 				   GCC
 ******************************************************************************
 * @note
 * 1.XXXXX                  						                     
 ******************************************************************************
 */

/**
 * @defgroup ysf pt component
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __YSF_PT_H__
#define __YSF_PT_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "ysf_path.h"
#include YSF_TYPE_PATH
#include YSF_COMPONENT_TIMER_PATH
    
/* Exported macro ------------------------------------------------------------*/
#define ysf_pt_init(pt)  pt->state = 0
#define ysf_pt_begin(pt) switch(pt->state){case 0:
#define ysf_pt_entry(pt) pt->state = __LINE__;case __LINE__:
//#define ysf_pt_wait(pt,state)  do
//                         {
//                             ysf_pt_entry(pt);
//                             if(  )
//                         }
//#define ysf_pt_delay(pt,tick) do
//                              {
//                                  ysf_timerSimple_cb_arm(tick,0,pt->thread,NULL);
//                              }
#define ysf_pt_end(pt)   }
    
/* Exported types ------------------------------------------------------------*/
struct ysf_pt_t
{
    int16_t state;
    ysf_err_t (*thread)(struct ysf_pt_t*, uint16_t);
};

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** ysf pt component  */

/**********************************END OF FILE*********************************/
