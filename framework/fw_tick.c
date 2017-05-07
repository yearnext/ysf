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
#include <intrinsics.h>

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       framework tick
 *******************************************************************************
 */
static volatile uint32_t Tick = 0;

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
}

/**
 *******************************************************************************
 * @brief       tick update
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
inline
void IncTick(void)
{
    Tick++;

    PostEvent(FW_TICK_TASK, FW_TICK_EVENT);
}

/**
 *******************************************************************************
 * @brief       get tick
 * @param       [in/out]  void
 * @return      [in/out]  uint32_t    tick
 * @note        None
 *******************************************************************************
 */
inline
uint32_t GetTick(void)
{
    uint32_t calTick;
    
_ATOM_CODE_BEGIN();
    
    calTick = Tick;
    
	Tick = 0;
    
_ATOM_CODE_END();

	return calTick;
}

/** @}*/     /** framework tick component */

/**********************************END OF FILE*********************************/
