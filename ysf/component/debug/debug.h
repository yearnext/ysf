/**
 ******************************************************************************
 * @file       debug.h
 * @author     yearnext
 * @version    1.0.0
 * @date       2017-01-10
 * @brief      ysf's debug component header files
 * @par        work platform
 *                 Windows
 * @par        compiler
 *                 GCC
 ******************************************************************************
 * @note
 * 1.XXXXX
 ******************************************************************************
 */

/**
 * @defgroup ysf's debug component
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __YSF_DEBUG_H__
#define __YSF_DEBUG_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "ysf_path.h"
#include YSF_TYPE_PATH

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       ysf tick api enable switch
 *******************************************************************************
 */
#define USE_YSF_DEBUG_API (1)
 
/**
 *******************************************************************************
 * @brief       define detecting null pointer macros
 *******************************************************************************
 */    
#define IS_PTR_NULL(ptr) ((ptr) == NULL)

/**
 *******************************************************************************
 * @brief       define assert macros
 *******************************************************************************
 */ 
#define ysf_assert(expr) ((expr) ? ysf_assert_failed((uint8_t *)__FILE__, __LINE__) :(void)0 )
                             
/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define ysf debug api
 *******************************************************************************
 */ 
#if USE_YSF_DEBUG_API
struct YSF_DEBUG_API
{
    ysf_err_t (*init)(void);
    void (*assert_failed)(uint8_t*, uint32_t);
};
#endif
      
/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define ysf debug function interface
 *******************************************************************************
 */ 
#if USE_YSF_DEBUG_API
extern ysf_err_t ysf_debug_init(void);
extern void ysf_assert_failed(uint8_t*, uint32_t);
#endif        

/**@} */

#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /* ysf's debug component  */

/**********************************END OF FILE*********************************/
