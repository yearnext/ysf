/**
 *******************************************************************************
 * @file       fw_signal.c
 * @author     yearnext
 * @version    1.0.0
 * @date       2017-01-10
 * @brief      framework signal source files
 * @par        paltform                                  
 *                 Windows
 * @par        compiler									                         
 * 				   GCC
 *******************************************************************************
 * @note
 * 1.XXXXX                  						                     
 *******************************************************************************
 */

/**
 * @defgroup framework signal component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "fw_signal.h"
#include "fw_timer.h"
#include "fw_event.h"
#include "fw_debug.h"

/* Private define ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      detect signal status
 *******************************************************************************
 */
#define IS_SIGNAL_INFO_CHANGED(signal, nowInfo) ((signal)->Info != (nowInfo))

/**
 *******************************************************************************
 * @brief      update signal status
 *******************************************************************************
 */
#define TRANSFER_SIGNAL_STATUS(signal, status)  ((signal)->Status = (status))
#define UPDATE_SIGNAL_INFO(signal, info)        ((signal)->Info = (info))   

/* Private typedef -----------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        defien signal block type
 *******************************************************************************
 */
typedef struct
{
    uint8_t         (*Scan)(void);
    signal_status_t Status;
    uint8_t         Info;
    uint8_t         TaskId;
}fw_signal_t;

/* Private variables ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        defien signal block
 *******************************************************************************
 */
#if USE_FRAMEWORK_SIGNAL_COMPONENT
static fw_signal_t Signal[SIGNAL_MAX];
#endif

/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
#if USE_FRAMEWORK_SIGNAL_COMPONENT
/**
 *******************************************************************************
 * @brief       signal detection functon
 * @param       [in/out]  signal         signal
 * @param       [in/out]  nowSignal->Status        signal status
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
static inline
void SignalDetection(fw_signal_t *nowSignal)
{
    uint8_t nowInfo;
   
    nowInfo = nowSignal->Scan();
    
    switch( nowSignal->Status )
    {
        case SIGNAL_STATUS_INIT:
            if(IS_SIGNAL_INFO_CHANGED(nowSignal, nowInfo))
            {
                UPDATE_SIGNAL_INFO(nowSignal, nowInfo);
                
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
                }
            }
            else
            {
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
                }
            }
            break;
        case SIGNAL_STATUS_PRESS_FILTER_STEP1:
            if(IS_SIGNAL_INFO_CHANGED(nowSignal, nowInfo))
            {
                UPDATE_SIGNAL_INFO(nowSignal, nowInfo);
                
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
                }
            }
            else
            {
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_PRESS_FILTER_STEP2);
                }
            }
            break;
        case SIGNAL_STATUS_PRESS_FILTER_STEP2:
            if(IS_SIGNAL_INFO_CHANGED(nowSignal, nowInfo))
            {
                UPDATE_SIGNAL_INFO(nowSignal, nowInfo);
                
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
                }
            }
            else
            {
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_PRESS_FILTER_STEP3);
                }
            }
            break;
        case SIGNAL_STATUS_PRESS_FILTER_STEP3:
            if(IS_SIGNAL_INFO_CHANGED(nowSignal, nowInfo))
            {
                UPDATE_SIGNAL_INFO(nowSignal, nowInfo);
                
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
                }
            }
            else
            {
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_PRESS_EDGE);
                    PostEvent(nowSignal->TaskId, nowSignal->Status);
                }
            }
            break;
        case SIGNAL_STATUS_RELEASE_FILTER_STEP1:
            if(IS_SIGNAL_INFO_CHANGED(nowSignal, nowInfo))
            {
                UPDATE_SIGNAL_INFO(nowSignal, nowInfo);
                
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
                }
            }
            else
            {
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_RELEASE_FILTER_STEP2);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
                }
            }
            break;
        case SIGNAL_STATUS_RELEASE_FILTER_STEP2:
            if(IS_SIGNAL_INFO_CHANGED(nowSignal, nowInfo))
            {
                UPDATE_SIGNAL_INFO(nowSignal, nowInfo);
                
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
                }
            }
            else
            {
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_RELEASE_FILTER_STEP3);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
                }
            }
            break;
        case SIGNAL_STATUS_RELEASE_FILTER_STEP3:
            if(IS_SIGNAL_INFO_CHANGED(nowSignal, nowInfo))
            {
                UPDATE_SIGNAL_INFO(nowSignal, nowInfo);
                
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
                }
            }
            else
            {
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_RELEASE_EDGE);
                    PostEvent(nowSignal->TaskId, nowSignal->Status);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
                }
            }
            break;
        case SIGNAL_STATUS_RELEASE_EDGE:
            if(IS_SIGNAL_INFO_CHANGED(nowSignal, nowInfo))
            {
                UPDATE_SIGNAL_INFO(nowSignal, nowInfo);
                
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
                }
            }
            else
            {
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_RELEASE);
                    PostEvent(nowSignal->TaskId, nowSignal->Status);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
                }
            }
            break;
        case SIGNAL_STATUS_RELEASE:
            if(IS_SIGNAL_INFO_CHANGED(nowSignal, nowInfo))
            {
                UPDATE_SIGNAL_INFO(nowSignal, nowInfo);
                
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
                }
            }
            else
            {
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_RELEASE);
                    PostEvent(nowSignal->TaskId, nowSignal->Status);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
                }
            }
            break;
        case SIGNAL_STATUS_PRESS_EDGE:
            if(IS_SIGNAL_INFO_CHANGED(nowSignal, nowInfo))
            {
                UPDATE_SIGNAL_INFO(nowSignal, nowInfo);
                
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
                }
            }
            else
            {
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_PRESS);
                    PostEvent(nowSignal->TaskId, nowSignal->Status);
                }
            }
            break;
        case SIGNAL_STATUS_PRESS:
            if(IS_SIGNAL_INFO_CHANGED(nowSignal, nowInfo))
            {
                UPDATE_SIGNAL_INFO(nowSignal, nowInfo);
                
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
                }
            }
            else
            {
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(nowSignal, SIGNAL_STATUS_PRESS);
                    PostEvent(nowSignal->TaskId, nowSignal->Status);
                }
            }
            break;
        default:
            break;
    }
}

/* Exported functions --------------------------------------------------------*/

/**
 *******************************************************************************
 * @brief       signal component init 
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void InitSignalComponent(void)
{
    uint8_t i = 0;

    for( i=0; i<SIGNAL_MAX; i++ )
    {
        Signal[i].Scan   = NULL;
        Signal[i].TaskId = 0;
        Signal[i].Status = SIGNAL_STATUS_INIT;
    }
    RegisterEvent(FW_SIGNAL_TASK, PollSignalComponent);
    
    ArmTimerModule(FW_SIGNAL_TASK, FW_SIGNAL_SCAN_PREIOD);
    
    PostEvent(FW_SIGNAL_TASK, FW_SIGNAL_EVENT);
}

/**
 *******************************************************************************
 * @brief       signal component register
 * @param       [in/out]  task                     task id
 * @param       [in/out]  signal                   signal id
 * @param       [in/out]  *scan                    signal scan function
 * @return      [in/out]  fw_err_t                 register status
 * @note        None
 *******************************************************************************
 */
fw_err_t RegisterSignal(uint8_t taskId, uint8_t signalId, uint8_t (*scan)(void))
{
    if( signalId > SIGNAL_MAX )
    {
        return FW_ERR_FAIL;
    }
    
    if( taskId > FW_TASK_MAX )
    {
        return FW_ERR_FAIL;
    }
    
    if(scan == NULL)
    {
        return FW_ERR_FAIL;
    }

    Signal[signalId].Scan   = scan;
    Signal[signalId].TaskId = taskId;
    Signal[signalId].Status = SIGNAL_STATUS_INIT;
    Signal[signalId].Info   = 0;
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       get signal info
 * @param       [in/out]  taskId    task id
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
uint8_t GetSignalInfo(uint8_t taskId)
{
    uint8_t i;
    uint8_t info = 0;
    
    if( taskId > FW_TASK_MAX )
    {
        return FW_ERR_FAIL;
    }
    
    for( i=0; i<SIGNAL_MAX; i++ )
    {
        if(Signal[i].TaskId == taskId)
        {
            info = Signal[i].Info;
        }
    }
    
    return info;
}

/**
 *******************************************************************************
 * @brief       signal handler 
 * @param       [in/out]  event         trigger events
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void PollSignalComponent(uint8_t event)
{
    uint8_t i = 0;
        
//    log("signal handle! \n");
        
    for( i=0; i<SIGNAL_MAX; i++ )
    {
        if( !IS_PTR_NULL(Signal[i].Scan) )
        {
            SignalDetection(&Signal[i]);
        }
    }
    
    ArmTimerModule(FW_SIGNAL_TASK, FW_SIGNAL_SCAN_PREIOD);
}
#endif

/** @}*/     /* ysf signal ÅäÖÃ  */

/**********************************END OF FILE*********************************/
