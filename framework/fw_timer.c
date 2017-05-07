/**
 *******************************************************************************
 * @file       fw_timer.c
 * @author     yearnext
 * @version    1.0.0
 * @date       2016-07-09
 * @brief      framework timer component source files
 * @par        paltform
 *                  Windows
 * @par        compiler
 *                  GCC
 *******************************************************************************
 * @note
 * 1.XXXXX
 *******************************************************************************
 */

/**
 * @defgroup framework timer component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "fw_timer.h"
#include "fw_event.h"
#include "fw_debug.h"

/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       framework timer structure
 *******************************************************************************
 */
#if USE_FRAMEWORK_TIMER_COMPONENT
struct
{
	uint8_t  Status;
    uint8_t  TaskId;
    uint16_t Time;
}static Timer[USE_FRAMEWORK_TIMER_NUM];
#endif

/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_FRAMEWORK_TIMER_COMPONENT
/**
 *******************************************************************************
 * @brief       timer component init
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void InitTimerComponent(void)
{
    uint8_t i;
    
    for( i=0; i<USE_FRAMEWORK_TIMER_NUM; i++ )
    {
        Timer[i].TaskId = 0;
        Timer[i].Time   = 0;
        Timer[i].Status = 0;
    }
    
    RegisterEvent(FW_TICK_TASK, PollTimerComponent);
}

/**
 *******************************************************************************
 * @brief       timer component arm
 * @param       [in/out]  taskId      task id
 * @param       [in/out]  time        timing
 * @return      [in/out]  fw_err_t    arm status
 * @note        None
 *******************************************************************************
 */
fw_err_t ArmTimerModule(uint8_t taskId, uint16_t time)
{
    uint8_t i;
    
    for( i=0; i<USE_FRAMEWORK_TIMER_NUM; i++ )
    {
        if( Timer[i].Status == 0 )
        {
            Timer[i].Status = 1;
            Timer[i].Time   = time;
            Timer[i].TaskId = taskId;
            
            return FW_ERR_NONE;
        }
    }
    
    return FW_ERR_FAIL;
}

/**
 *******************************************************************************
 * @brief       timer component handler
 * @param       [in/out]  event    trigger event
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void PollTimerComponent(uint8_t event)
{
    uint32_t tick;
    uint8_t i;
    
//    log("tick handle! \n");
    
    _ATOM_CODE_BEGIN();
    tick = GetTick();
    _ATOM_CODE_END();
    
    for( i=0; i<USE_FRAMEWORK_TIMER_NUM; i++ )
    {
        if( Timer[i].Status )
        {
            if( Timer[i].Time > tick )
            {
                Timer[i].Time -= tick;
            }
            else
            {
                Timer[i].Status = 0;
                PostEvent(Timer[i].TaskId, FW_DELAY_EVENT);
            }
        }
    }
}
#endif

/** @}*/    /** framework event component */

/**********************************END OF FILE*********************************/
