/**
 *******************************************************************************
 * @file       fw_tick.c
 * @author     yearnext
 * @version    1.0.0
 * @date       2017-01-10
 * @brief      framework tick component source files
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
 * @defgroup framework tick component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "fw_tick.h"
#include "fw_event.h"
#include "fw_queue.h"
#include "fw_debug.h"

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       framework tick
 *******************************************************************************
 */
static volatile uint32_t Tick = 0;

/**
 *******************************************************************************
 * @brief       framework tick
 *******************************************************************************
 */
//static uint32_t TickBuffer[10];

/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       tick component init
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void InitTickComponent( void )
{
	Tick = 0;
    
//	Fw_Queue_Init(FW_TICK_QUEUE, (uint8_t *)&TickBuffer, CalTypeByteSize(TickBuffer));
}

/**
 *******************************************************************************
 * @brief       tick update
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void IncTick(void)
{
//    _ATOM_ACTIVE_BEGIN();
    
    Tick++;
    
    PostEvent(FW_TICK_TASK, FW_TICK_EVENT);
    
//    if(Fw_Queue_PutData(FW_TICK_QUEUE, (uint8_t *)&Tick, CalTypeByteSize(Tick)) == FW_ERR_FAIL)
//    {
//        log("Write Tick To Fifo Is Fail! \n");
//    }
    
//    _ATOM_ACTIVE_END();
}

/**
 *******************************************************************************
 * @brief       get tick
 * @param       [in/out]  void
 * @return      [in/out]  uint32_t    tick
 * @note        None
 *******************************************************************************
 */
uint32_t GetTick(void)
{
	return Tick;
}

/**
 *******************************************************************************
 * @brief       cal past tick
 * @param       [in/out]  uint32_t    lastTick
 * @return      [in/out]  uint32_t    tick
 * @note        None
 *******************************************************************************
 */
uint32_t CalPastTick(uint32_t lastTick, uint32_t nowTick)
{
    uint32_t calTick;

    if (nowTick < lastTick)
    {
        calTick = UINT32_MAX - lastTick;
        calTick = calTick + nowTick;
    }
    else
    {
        calTick = nowTick - lastTick;
    }
    
    return calTick;
}


/** @}*/     /** framework tick component */

/**********************************END OF FILE*********************************/
