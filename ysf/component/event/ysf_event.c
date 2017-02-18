/**
 ******************************************************************************
  * @file       ysf_event.c
  * @author     yearnext
  * @version    1.0.0
  * @date       2017-1-10
  * @brief      ysf event source file
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
 * @defgroup ysf event component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "../ysf/component/event/ysf_event.h"
#include "../ysf/common/ysf_type.h"
#include "../ysf/component/buffer/ysf_buffer.h"

/* Private define ------------------------------------------------------------*/
#define YSF_EVENT_SIZE_CAL(event) (sizeof(event)/sizeof(char))

/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       event component auto config
 *******************************************************************************
 */
#if USE_YNF_EVENT_AUTO_MODE
static volatile ysf_event_t eventQueue[YSF_EVENT_MAX];
static volatile ysf_rb_t eventQueueCB;
#endif

/* Exported variables --------------------------------------------------------*/
const ysf_event_func_list_t ysf_event =
{
    .init = ysf_event_init,
    .send = ysf_event_send,
    .read = ysf_event_read,
};

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
	return ysf_rbInit( &eventQueueCB,
	                   (ysf_u8_t *)&eventQueue,
	                   YSF_EVENT_SIZE_CAL(eventQueue));
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
	return ysf_rbWrite( &eventQueueCB,
	                    (ysf_u8_t *)&event,
	                    YSF_EVENT_SIZE_CAL(ysf_event_t) );
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
	return ysf_rbRead( &eventQueueCB,
	                   (ysf_u8_t *)event,
	                   YSF_EVENT_SIZE_CAL(ysf_event_t) );
}

/** @}*/     /* ynf_event component  */

/**********************************END OF FILE*********************************/
