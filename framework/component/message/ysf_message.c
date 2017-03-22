/**
 ******************************************************************************
  * @file       ysf_message.c
  * @author     yearnext
  * @version    1.0.0
  * @date       2017-1-10
  * @brief      ysf message source file
  * @par        work platform
  *                 Windows
  * @par        compiler platform
  * 				GCC
 ******************************************************************************
  * @note
  * 1.XXXXX                  						                     
 ******************************************************************************
 */

/**
 * @defgroup ysf message component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "ysf_path.h"
#include YSF_COMPONENT_MESSAGE_PATH

/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_YSF_MESSAGE_API
/**
 *******************************************************************************
 * @brief       ysf message component init
 * @param       [in/out]  void
 * @return      [in/out]  YSF_ERR_NONE       init finish
 * @return      [in/out]  YSF_ERR_FAIL       init failed
 * @note        None
 *******************************************************************************
 */
ysf_err_t ysf_message_init( void )
{
	return YSF_ERR_NONE;
}

#endif

/** @}*/     /** ysf message component  */

/**********************************END OF FILE*********************************/
