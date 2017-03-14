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
#include "ysf_path.h"
#include YSF_COMPONENT_DEBUG_DIR
#include YSF_TYPE_DIR

/* Private define ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
ysf_err_t ysf_debug_init( void )
{
    return YSF_ERR_NONE;
}

void ysf_assert_failed(uint8_t* file, uint32_t line)
{
    YSF_ENTER_CRITICAL();
    YSF_EXIT_CRITICAL();
}

/** @}*/     /* ysf debug component */

/**********************************END OF FILE*********************************/
