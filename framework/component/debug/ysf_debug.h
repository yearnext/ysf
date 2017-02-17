/**
 ******************************************************************************
 * @file       ysf_debug.h
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
#include "..\framework\common\ysf_commtools.h"
#include "..\framework\compiler\ysf_compiler.h"
#include "..\framework\common\ysf_type.h"
#include <stdarg.h>

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       ysf's debug component configuration
 *******************************************************************************
 */
#define USE_STD_LIB_IN_YSF_DEBUG     (1)
#define USE_YSF_DBBUG_MODULE_DEBUG   (1)
#define USE_GLOBAL_ASSERT            (1)

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       ysf's function parameter error
 *******************************************************************************
 */
#if USE_GLOBAL_DEBUG
#define ysf_param_err_log(param) ysf_log("%s func param %s is invaild! \n"     \
                                         ,__YSF_FUNCNAME__                     \
                                         ,Name2String(errorParam))
#else
#define ysf_param_err_log(param)
#endif

/**
 *******************************************************************************
 * @brief       ysf's assert function
 *******************************************************************************
 */
#define ysf_assert_failed(c,...) ysf_log(c,##__VA_ARGS__)

#if USE_GLOBAL_ASSERT
#define ysf_assert(c)   {                                                 \
                            if((c) == 1)                                  \
                            {                                             \
                                ysf_assert_failed(__FILE__,__LINE__);     \
                                while(1);                                 \
                            }                                             \
                        }

#else
#define ysf_assert(c)            (0)
#endif

/**
 *******************************************************************************
 * @brief       detect whether the points is invaild pointer
 * @note        if the test results is 1, then the pointer is invaild
 * @note        if the test results is 0, the pointer is vaild
 *******************************************************************************
 */
#define IS_PTR_NULL(ptr)         ((ptr) == YSF_NULL)

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
extern ysf_err_t ysf_log(const char *log, ...);

/**@} */

#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /* ysf's debug component  */

/**********************************END OF FILE*********************************/
