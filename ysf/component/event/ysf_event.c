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
#include YSF_COMMTOOLS_DIR
#include YSF_COMPONENT_EVENT_DIR
#include YSF_TYPE_DIR
#include YSF_COMPONENT_BUFFER_DIR
#include YSF_COMPONENT_SINGLE_LIST_DIR
#include YSF_COMPONENT_MEMORY_DIR
#include YSF_COMPONENT_DEBUG_DIR

/* Private define ------------------------------------------------------------*/
#define YSF_EVENT_SIZE_CAL(event) (sizeof(event)/sizeof(char))

/* Private typedef -----------------------------------------------------------*/
typedef ysf_err_t (*ysf_evt_handler)(uint16_t);

#if defined(USE_YSF_MEMORY_API) && USE_YSF_MEMORY_API
struct ysf_evt_handler_t
{
    void *next;
    ysf_evt_handler handler;
};
#endif

/* Private variables ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       event component auto config
 *******************************************************************************
 */
#if USE_YSF_EVENT_API
static int16_t buffer[YSF_EVENT_MAX];
static struct  ysf_rb_t QCB;

#if defined(USE_YSF_MEMORY_API) && USE_YSF_MEMORY_API
static struct ysf_evt_handler_t *evt_hander[YSF_EVENT_MAX]; 
#else
static ysf_evt_handler evt_hander[YSF_EVENT_MAX]; 
#endif

#endif

/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static ysf_err_t ysf_empty_event_handler(uint16_t event)
{
    return YSF_ERR_NONE;
}

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
    uint16_t i;
    
    for( i=0; i<YSF_EVENT_MAX; i++ )
    {
        evt_hander[i] = NULL;
    }
    
    ysf_event_handler_register(YSF_EVENT_NONE, ysf_empty_event_handler);
    
    ysf_rbInit(&QCB, (uint8_t *)&buffer, YSF_EVENT_SIZE_CAL(buffer));
    
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
    ysf_rbWrite( &QCB, (uint8_t *)&event, YSF_EVENT_SIZE_CAL(int16_t) );
    
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
    ysf_rbRead( &QCB, (uint8_t *)event, YSF_EVENT_SIZE_CAL(int16_t) );
	
    return YSF_ERR_NONE;
}

#if defined(USE_YSF_MEMORY_API) && USE_YSF_MEMORY_API
static bool ysf_event_walk(void **node, void **ctx, void **expand)
{
    struct ysf_evt_handler_t *evt_handler_node = (struct ysf_evt_handler_t *)*node;
    uint16_t events = *((uint16_t *)ctx);
    
    if( *node == NULL )
    {
        return true;
    }
    
    evt_handler_node->handler(events);
    
    return false;
}

static bool ysf_event_handler_delte(void **node, void **ctx, void **expand)
{
    ysf_assert(IS_PTR_NULL(*ctx));
    
    struct ysf_evt_handler_t *now  = (struct ysf_evt_handler_t *)(*node);
    struct ysf_evt_handler_t *last = (struct ysf_evt_handler_t *)(*expand);
    ysf_evt_handler condition = (ysf_evt_handler)(*ctx);
    
    if( now == NULL )
    {
        return false;
    }

    if( now->handler == condition )
    {
        if( now != last )
        {
            now->handler = NULL;
            last->next = now->next;
            now->next = NULL;
            ysf_memory_free(now);
            now = last;
        }
        else
        {
            now->handler = NULL;
            now = now->next;
            last->next = NULL;
            ysf_memory_free(last);
            last = now;
        }
    }
    
    return false;
}

ysf_err_t ysf_event_handler_register( uint16_t event, ysf_err_t (*handler)(uint16_t) )
{
    struct ysf_evt_handler_t *evt_handler_node = (struct ysf_evt_handler_t *)ysf_memory_malloc(YSF_CalTypeByteSize(struct ysf_evt_handler_t));
    
    evt_handler_node->handler = handler;
    evt_handler_node->next    = NULL;
    
    return ysf_slist_add((void**)&evt_hander[event], (void **)&evt_handler_node);
}

ysf_err_t ysf_event_handler_writeoff( uint16_t event, ysf_err_t (*handler)(uint16_t) )
{
    ysf_assert(event>=YSF_EVENT_MAX);
    struct ysf_evt_handler_t *head = evt_hander[event];

    return ysf_slist_walk( (void **)&evt_hander[event], ysf_event_handler_delte, (void **)handler, (void **)&head );
}

ysf_err_t ysf_event_handler(void)
{
    uint16_t event = YSF_EVENT_NONE;
    ysf_event_read(&event);
    
    ysf_slist_walk( (void **)&evt_hander[event], ysf_event_walk, (void **)((ysf_addr_t)&event), NULL );
    
    return YSF_ERR_NONE;
}
#else

ysf_err_t ysf_event_handler_register( uint16_t event, ysf_err_t (*handler)(uint16_t) )
{
    ysf_assert(IS_PTR_NULL(handler));
    ysf_assert(event>=YSF_EVENT_MAX);
    
    evt_hander[event] = handler;

    return YSF_ERR_NONE;
}

ysf_err_t ysf_event_handler_writeoff( uint16_t event, ysf_err_t (*handler)(uint16_t) )
{
    ysf_assert(event>=YSF_EVENT_MAX);
    
    evt_hander[event] = NULL;

    return YSF_ERR_NONE;
}

ysf_err_t ysf_event_handler( void )
{
    uint16_t event = YSF_EVENT_NONE;
    ysf_event_read(&event);
    
    if( IS_PTR_NULL(evt_hander[event]))
    {
        evt_hander[event](event);
    }
    
    return YSF_ERR_NONE;
}
#endif

#endif

/** @}*/     /* ynf_event component  */

/**********************************END OF FILE*********************************/
