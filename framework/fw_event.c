/**
 *******************************************************************************
 * @file       fw_event.c
 * @author     yearnext
 * @version    1.0.0
 * @date       2017-01-10
 * @brief      framework event component source files
 * @par        paltform                                  
 *                 Windows
 * @par        compiler									                         
 * 				GCC
 *******************************************************************************
 * @note
 * 1.XXXXX                  						                     
 *******************************************************************************
 */

/**
 * @defgroup framework event component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "fw_event.h"

// user head files
#include "fw_timer.h"
#include "fw_signal.h"

/* Private define ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       task size
 *******************************************************************************
 */
#define FW_TASK_MAX_SIZE       (2*(sizeof(evtHandleFunction)/sizeof(evtHandle)))

/* Private typedef -----------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       event handler
 *******************************************************************************
 */
typedef void (*evtHandle)(uint8_t event);

/* Private variables ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       event handler
 * @note        user config
 *******************************************************************************
 */
#if USE_FRAMEWORK_EVENT_COMPONENT
static evtHandle evtHandleFunction[] = 
{
	/** framework task handler function */
	fw_timer_handler,
	fw_signal_handler,
	
	/** user task handler function */
};
#endif

/**
 *******************************************************************************
 * @brief       framework event block
 *******************************************************************************
 */
#if USE_FRAMEWORK_EVENT_COMPONENT
static struct
{
    struct
    {
        uint8_t Task;
        uint8_t Event;
    }Pool[FW_TASK_MAX_SIZE];
    
    uint8_t Tail;
    uint8_t Head;
}EventQueue;
#endif

/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_FRAMEWORK_EVENT_COMPONENT
/**
 *******************************************************************************
 * @brief       event component init
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void fw_event_init(void)
{
    EventQueue.Tail = 0;
    EventQueue.Head = 0;
}

/**
 *******************************************************************************
 * @brief       event post
 * @param       [in/out]  task     task
 * @param       [in/out]  event    event
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
inline
void fw_event_post(uint8_t task, uint8_t event)
{
	if(EventQueue.Tail < FW_TASK_MAX_SIZE)
	{
		EventQueue.Pool[EventQueue.Tail].Task  = task;
		EventQueue.Pool[EventQueue.Tail].Event = event;
		
		EventQueue.Tail++;
	}
}

/**
 *******************************************************************************
 * @brief       event read
 * @param       [in/out]  void
 * @return      [in/out]  evt      event
 * @note        None
 *******************************************************************************
 */
inline
void fw_event_poll(void)
{
	while(1)
	{
		while(EventQueue.Head < EventQueue.Tail)
		{
			evtHandleFunction[EventQueue.Pool[EventQueue.Head].Task](EventQueue.Pool[EventQueue.Head].Event);
			
			_ATOM_CODE_BEGIN();
			if(++EventQueue.Head >= EventQueue.Tail)
			{
				EventQueue.Tail = 0;
				EventQueue.Head = 0;
			}
			_ATOM_CODE_END();
		}
	}
}
#endif

/** @}*/     /** framework event component */

/**********************************END OF FILE*********************************/
