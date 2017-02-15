/**
 ******************************************************************************
  * @file       ysf_event.c
  * @author     yearnext
  * @version    1.0.0
  * @date       2017年1月10日
  * @brief      ysf_event 源文件
  * @par        工作平台
  *                 Windows
  * @par        编译平台
  * 				GCC
 ******************************************************************************
  * @note
  * 1.XXXXX                  						                     
 ******************************************************************************
 */

/**
 * @defgroup ysf_event配置
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "ysf_event.h"
#include "ysf_type.h"
#include "ysf_buffer.h"

/* Private define ------------------------------------------------------------*/
#define YSF_EVENT_SIZE_CAL(event) (sizeof(event)/sizeof(char))

/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       事件队列
 *******************************************************************************
 */
#if USE_YNF_EVENT_AUTO_MODE
static ysf_event_t eventQueue[YSF_EVENT_MAX];
static ysf_rb_t eventQueueCB;
#endif

/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       ysf event component init
 * @param       [in/out]  void
 * @return      [in/out]  YSF_ERR_NONE       init finish
 * @return      [in/out]  YSF_ERR_FAIL       init failed
 * @note        None
 *******************************************************************************
 */
ysf_err_t ysf_event_init( void )
{
	return ysf_rbInit(&eventQueueCB, eventQueue, sizeof(eventQueue));
}

/**
 *******************************************************************************
 * @brief       ysf write event to event queue
 * @param       [in/out]  event             write events
 * @return      [in/out]  YSF_ERR_NONE      write success
 * @return      [in/out]  YSF_ERR_FAIL      write failed
 * @note        None
 *******************************************************************************
 */
ysf_err_t ysf_event_send( ysf_event_t event )
{
	return ysf_rbWrite( &eventQueueCB, &event, YSF_EVENT_SIZE_CAL(ysf_event_t) );
}

/**
 *******************************************************************************
 * @brief       read events from event queue
 * @param       [in/out]  *event            read events
 * @return      [in/out]  YSF_ERR_NONE      read success
 * @return      [in/out]  YSF_ERR_FAIL      read failed
 * @note        None
 *******************************************************************************
 */
ysf_err_t ysf_event_read( ysf_event_t *event )
{
	return ysf_rbRead( &eventQueueCB, event, YSF_EVENT_SIZE_CAL(ysf_event_t) );
}

/** @}*/     /* ynf_event 配置  */

/**********************************END OF FILE*********************************/
