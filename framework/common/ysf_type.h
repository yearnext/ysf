/**
 ******************************************************************************
 * @file       ysf_type.h
 * @author     yearnext
 * @version    1.0.0
 * @date       2017-1-10
 * @brief      ysf type define head file
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
 * @defgroup ysf type
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __YSF_TYPE_H__
#define __YSF_TYPE_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "ysf_path.h"
#include YSF_COMPILER_PATH

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define ysf status type
 *******************************************************************************
 */
typedef enum
{
   ysf_disable  = 0,
   ysf_enable = !ysf_disable,
}ysf_status_t;

/**
 *******************************************************************************
 * @brief      define ysf error type
 *******************************************************************************
 */
enum
{
    YSF_ERR_NONE,
    YSF_ERR_FAIL,
    
    YSF_ERR_NOT_READY,
    YSF_ERR_NOT_SUPPORT,
    
    YSF_ERR_INVAILD_PTR,
    YSF_ERR_INVAILD_PARAM,

    YSF_ERR_IO,
    
    YSF_ERR_BUG,
    YSF_ERR_UNKNOW,
};

typedef int16_t ysf_err_t;

#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** ysf type  */

/**********************************END OF FILE*********************************/
