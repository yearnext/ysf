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
#include "ysf_path.h"
#include YSF_COMMTOOLS_PATH
#include YSF_COMPONENT_EVENT_PATH
#include YSF_TYPE_PATH
#include YSF_COMPONENT_BUFFER_PATH
#include YSF_COMPONENT_SINGLE_LIST_PATH
#include YSF_COMPONENT_MEMORY_PATH
#include YSF_COMPONENT_DEBUG_PATH

/* Private define ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       calculate events use memory size
 *******************************************************************************
 */
#define YSF_EVENT_SIZE_CAL(event) CalTypeByteSize(event)

/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       event component auto config
 *******************************************************************************
 */
#if USE_YSF_EVENT_API
static int16_t buffer[YSF_EVENT_MAX];
static struct  ysf_rb_t evt_queue;
#endif

/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
///**
// *******************************************************************************
// * @brief       empty event handler
// * @param       [in/out]  event              events
// * @return      [in/out]  YSF_ERR_NONE       init finish
// * @note        None
// *******************************************************************************
// */
//static ysf_err_t ysf_empty_event_handler(uint16_t event)
//{
//    return YSF_ERR_NONE;
//}

/* Exported functions --------------------------------------------------------*/
#if USE_YSF_EVENT_API
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
//    uint16_t i;
//    
//    for( i=0; i<YSF_EVENT_MAX; i++ )
//    {
//        evt_hander[i].next    = NULL;
//        evt_hander[i].handler = NULL;
//    }
//    
//    ysf_event_writeoff(YSF_EVENT_NONE, ysf_empty_event_handler);
//    
    ysf_rbInit(&evt_queue, (uint8_t *)buffer, YSF_EVENT_SIZE_CAL(buffer));
    
	return YSF_ERR_NONE;
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
ysf_err_t ysf_event_post( uint16_t event )
{
    ysf_rbWrite( &evt_queue, (uint8_t *)&event, YSF_EVENT_SIZE_CAL(int16_t) );
    
	return YSF_ERR_NONE;
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
ysf_err_t ysf_event_read( uint16_t *event )
{
    ysf_rbRead( &evt_queue, (uint8_t *)event, YSF_EVENT_SIZE_CAL(int16_t) );
	
    return YSF_ERR_NONE;
}

#endif

/** @}*/     /** ysf event component  */

/**********************************END OF FILE*********************************/
