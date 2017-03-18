/**
 ******************************************************************************
 * @file       debug.c
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
#include "ysf_path.h"
#include YSF_COMPONENT_DEBUG_PATH
#include YSF_TYPE_PATH

/* Private define ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_YSF_DEBUG_API
/**
 *******************************************************************************
 * @brief       ysf debug component initialization
 * @param       [in/out]  void
 * @return      [in/out]  YSF_ERR_NONE    without exception
 * @note        None
 *******************************************************************************
 */
ysf_err_t ysf_debug_init( void )
{
    return YSF_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       ysf assert failed handler
 * @param       [in/out]  *file           assertion failed file name
 * @param       [in/out]  line            assertion failed file line
 * @return      [in/out]  none
 * @note        None
 *******************************************************************************
 */
void ysf_assert_failed(uint8_t* file, uint32_t line)
{
    YSF_ENTER_CRITICAL();
    YSF_EXIT_CRITICAL();
}
#endif

/** @}*/     /* ysf debug component */

/**********************************END OF FILE*********************************/
