/**
 ******************************************************************************
 * @file       ysf_debug.c
 * @author     yearnext
 * @version    1.0.0
 * @date       2017-01-10
 * @brief      ysf's debug component source files
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
 * @defgroup ysf debug
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "../ysf/component/debug/ysf_debug.h"
#include "../ysf/common/ysf_type.h"

#if USE_STD_LIB_IN_YSF_DEBUG
#include <stdarg.h>
#include <stdio.h>
#else
    
#endif

/* Private define ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       ysf put log message
 * @param       [in/out]  log*              put message
 * @param       [in/out]  ...               message param
 * @return      [in/out]  YSF_ERR_NONE      put finish
 * @note        None
 *******************************************************************************
 */
#if USE_STD_LIB_IN_YSF_DEBUG
ysf_err_t ysf_log(const char *log, ...)
{
#if USE_YSF_DBBUG_MODULE_DEBUG
    if( log == NULL )
    {
        return YSF_ERR_INVAILD_PTR;
    }
#endif
    va_list arg;
    
    va_start(arg,log);
    vprintf(log, arg);
    va_end(arg);
    
    return YSF_ERR_NONE;
}

#else
ysf_err_t ysf_log(const char *log, ...)
{
#if USE_YSF_DBBUG_MODULE_DEBUG
    if( log == NULL )
    {
        return YSF_ERR_INVAILD_PTR;
    }
#endif

    return YSF_ERR_NONE;
}
#endif

/** @}*/     /* ysf debug component */

/**********************************END OF FILE*********************************/
