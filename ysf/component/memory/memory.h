/**
 ******************************************************************************
 * @file       ysf_memory.h
 * @author     yearnext
 * @version    1.0.0
 * @date       2017Äê2ÔÂ20ÈÕ
 * @brief      ysf_memory head file
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
 * @defgroup ysf_memory component
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __YSF_MEMORY_H__
#define __YSF_MEMORY_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "ysf_path.h"
#include YSF_COMPONENT_BUFFER_PATH

/* Exported macro ------------------------------------------------------------*/
#define USE_YSF_MEMORY_API  (1)

#define USE_YSF_MEMORY_SIZE (4096)

/* Exported types ------------------------------------------------------------*/
struct YSF_MEMORY_API
{
    void (*init)(void);
    void *(*malloc)(ysf_mem_size_t);
    void (*free)(void*);
    ysf_mem_size_t (*len)(void);
    ysf_mem_size_t (*alignment)(void);
    ysf_mem_size_t (*useRate)(void);
    bool (*isIn)(void *);
};

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_YSF_MEMORY_API
extern void ysf_memory_init( void );
extern void *ysf_memory_malloc(ysf_mem_size_t);
extern void ysf_memory_free(void*);
extern ysf_mem_size_t ysf_memory_get_len(void);
extern ysf_mem_size_t ysf_memory_get_alignment(void);
extern ysf_mem_size_t ysf_memory_cal_use_rate(void);
extern bool ysf_memory_is_in(void*);
#endif

#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /* ysf memory component  */

/**********************************END OF FILE*********************************/
