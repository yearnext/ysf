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
static volatile uint32_t FwCoreTick = 0;

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
void fw_tick_init( void )
{
	FwCoreTick = 0;
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
void fw_tick_inc(void)
{
    FwCoreTick++;

    fw_event_post(FW_TICK_TASK, FW_TICK_EVENT);
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
uint32_t fw_tick_get(void)
{
    uint32_t tick;
    
_ATOM_CODE_BEGIN();
    
	 tick = FwCoreTick;
    
	FwCoreTick = 0;
    
_ATOM_CODE_END();

	return tick;
}

/** @}*/     /** framework tick component */

/**********************************END OF FILE*********************************/
