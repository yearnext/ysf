/**
 ******************************************************************************
  * @file       ysf_buffer.c
  * @author     yearnext
  * @version    1.0.0
  * @date       2017骞�1鏈�6鏃�
  * @brief      ysf 缂撳啿鍖� 婧愭枃浠�
  * @par        宸ヤ綔骞冲彴
  *                 Windows
  * @par        缂栬瘧骞冲彴
  * 				GCC
 ******************************************************************************
  * @note
  * 1.瀹氫箟浜嗛槦鍒椼�佺幆褰㈢紦鍐插尯銆丗IFO鐨勫姛鑳藉嚱鏁般��
 ******************************************************************************
 */

/**
 * @defgroup ysf 閰嶇疆
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "ysf_debug.h"
#include "ysf_type.h"

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
 * @brief       杈撳嚭鏃ュ織鍑芥暟
 * @param       [in/out]  log*              杈撳嚭鏃ュ織淇℃伅
 * @param       [in/out]  ...               鏃ュ織鍙傛暟
 * @return      [in/out]  YSF_ERR_NONE      杈撳嚭鎴愬姛
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

/** @}*/     /* ynf_ringbuff 閰嶇疆  */

/**********************************END OF FILE*********************************/
