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
#include "../ysf/component/buffer/ysf_buffer.h"

/* Exported macro ------------------------------------------------------------*/
#define USE_YSF_MEMORY_COMPONENT (1)

#define USE_YSF_MEMORY_SIZE      (4096)

/* Exported types ------------------------------------------------------------*/
struct _YSF_MEMORY_API_
{
    void (*init)(void);
    void* (*malloc)(ysf_memSize_t);
    void (*free)(void*);
};

/* Exported variables --------------------------------------------------------*/
extern const struct _YSF_MEMORY_API_ ysf_memory;

/* Exported functions --------------------------------------------------------*/
extern void ysf_memory_init( void );
extern void *ysf_malloc(ysf_memSize_t);
extern void ysf_free(void*);


#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /* ysf memory component  */

/**********************************END OF FILE*********************************/
