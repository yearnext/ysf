/**
 *******************************************************************************
 * @file       fw_debug.c
 * @author     yearnext
 * @version    1.0.0
 * @date       2017-01-10
 * @brief      framework debug component source files
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
 * @defgroup framework debug component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "fw_debug.h"
#include "fw_tick.h"
#include "fw_event.h"
#include "fw_timer.h"
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

/* Private define ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       config debug buffer num
 *******************************************************************************
 */
#define FW_DEBUG_PIPELINE_NUM                                                (3)

/**
 *******************************************************************************
 * @brief       config debug buffer size
 *******************************************************************************
 */
#define FW_DEBUG_BUFFER_SIZE                                                (64)

/**
 *******************************************************************************
 * @brief       debug timer function
 *******************************************************************************
 */
#define InitDebugTimer()         _ST(Fw_Timer_Init(FW_DEBUG_TIMER, FW_DEBUG_TASK, FW_TIMEOUT_EVENT, NULL);)
#define StartDebugTimer(time)    _ST(Fw_Timer_ForceStart(FW_DEBUG_TIMER, 1, FW_TIME_SET(time));)
#define StopDebugTimer()         _ST(Fw_Timer_Stop(FW_DEBUG_TIMER);)

/* Private typedef -----------------------------------------------------------*/
#if USE_FRAMEWORK_DEBUG_COMPONENT
/**
 *******************************************************************************
 * @brief      define buffer status
 *******************************************************************************
 */
enum _BUFFER_STATUS
{
	BUFFER_INIT_STATUS,
	
	BUFFER_WAIT_WRITE_STATUS,
	BUFFER_WRITE_STATUS,
	BUFFER_WAIT_TRANSFER_STATUS,
	BUFFER_TRANSFER_STATUS,
	BUFFER_WAIT_TRANSFER_COMPLET_STATUS,
	BUFFER_TRANSFER_COMPLET_STATUS,
	
	BUFFER_WAIT_TIMEOUT_STATUS,
	
	BUFFER_FINI_STATUS,
};

/**
 *******************************************************************************
 * @brief      define buffer block
 *******************************************************************************
 */
struct _BUFFER_BLOCK
{
	uint32_t Tick;
	
	enum _BUFFER_STATUS Status;
	
	uint8_t Size;
	uint8_t Buffer[FW_DEBUG_BUFFER_SIZE];
};

/**
 *******************************************************************************
 * @brief      define now debug block status
 *******************************************************************************
 */
enum _DEBUG_BLOCK_CHANNEL_STATUS
{
	DEBUG_BLOCK_CHANNEL_IDLE_STATUS,
	DEBUG_BLOCK_CHANNEL_WAIT_STATUS,
	DEBUG_BLOCK_CHANNEL_BUSY_STATUS,
};

/**
 *******************************************************************************
 * @brief      define debug block device output type
 *******************************************************************************
 */
enum _DEBUG_DEVICE_OUTPUT_TYPE
{
	DEBUG_DEVICE_OUTPUT_INVAILD_TYPE,
	DEBUG_DEVICE_OUTPUT_STREAM_TYPE,
    DEBUG_DEVICE_OUTPUT_SINGLE_ISR_TYPE,
	DEBUG_DEVICE_OUTPUT_SINGLE_TYPE,
};

/**
 *******************************************************************************
 * @brief      define now debug block status
 *******************************************************************************
 */
struct _DEBUG_MANAGEMENT_BLOCK
{
	union
	{
		void *Check;
		void (*Write)(uint8_t*, uint8_t);
		void (*ISRSend)(uint8_t);
        fw_err_t (*Send)(uint8_t);
	}Device;
	
	struct _BUFFER_BLOCK Pipeline[FW_DEBUG_PIPELINE_NUM];
	
 	enum _DEBUG_DEVICE_OUTPUT_TYPE Type;

	enum _DEBUG_BLOCK_CHANNEL_STATUS ChannelStatus;
	uint8_t Channel;
	
	uint8_t Indicator;
};

#endif

/* Private variables ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       event handler
 * @note        user config
 *******************************************************************************
 */
#if USE_FRAMEWORK_DEBUG_COMPONENT
static struct _DEBUG_MANAGEMENT_BLOCK DebugBlock;

#endif

/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static void DebugComponentEventHandle(uint8_t);

/* Exported functions --------------------------------------------------------*/
#if USE_FRAMEWORK_DEBUG_COMPONENT
/**
 *******************************************************************************
 * @brief       debug component init
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void InitDebugComponent(void)
{
	memset(&DebugBlock, 0, sizeof(DebugBlock));
	
	RegisterEvent(FW_DEBUG_TASK, DebugComponentEventHandle);	
	
	InitDebugTimer();
}

/**
 *******************************************************************************
 * @brief       login debug component send byte function
 * @param       [in/out]  sendByte       send byte call back function
 * @return      [in/out]  FW_ERR_FAIL    login failed
 * @return      [in/out]  FW_ERR_NONE    login success
 * @note        None
 *******************************************************************************
 */
fw_err_t LoginDebugISRSendByteCallBack(void (*sendByte)(uint8_t))
{
	_PARAM_CHECK(IS_PTR_NULL(sendByte));
	
	DebugBlock.Device.ISRSend = sendByte;
	DebugBlock.Type           = DEBUG_DEVICE_OUTPUT_SINGLE_ISR_TYPE;
	
	return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       login debug component send byte function
 * @param       [in/out]  sendByte       send byte call back function
 * @return      [in/out]  FW_ERR_FAIL    login failed
 * @return      [in/out]  FW_ERR_NONE    login success
 * @note        None
 *******************************************************************************
 */
fw_err_t LoginDebugSendByteCallBack(fw_err_t (*sendByte)(uint8_t))
{
	_PARAM_CHECK(IS_PTR_NULL(sendByte));
	
	DebugBlock.Device.Send = sendByte;
	DebugBlock.Type        = DEBUG_DEVICE_OUTPUT_SINGLE_TYPE;
	
	return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       register debug component send data call back function
 * @param       [in/out]  write          send data call back function
 * @return      [in/out]  FW_ERR_FAIL    login failed
 * @return      [in/out]  FW_ERR_NONE    login success
 * @note        None
 *******************************************************************************
 */
fw_err_t LoginDebugSendDataCallBack(void (*write)(uint8_t*, uint8_t))
{
	_PARAM_CHECK(IS_PTR_NULL(write));
	
	DebugBlock.Device.Write = write;
	DebugBlock.Type         = DEBUG_DEVICE_OUTPUT_STREAM_TYPE;
	
	return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       find now idle channel
 * @param       [in/out]  void
 * @return      [in/out]  -1        find error
 * @return      [in/out]  channel   find channel
 * @note        None
 *******************************************************************************
 */
static inline
struct _BUFFER_BLOCK *FindIdleChannel(void)
{
	uint8_t nowChannel = DebugBlock.Channel;
	struct _BUFFER_BLOCK *nowPipeLine = NULL;

	while(1)
	{
		nowPipeLine = &DebugBlock.Pipeline[nowChannel];

		//< detect now channel idle status
		if(nowPipeLine->Status == BUFFER_INIT_STATUS || nowPipeLine->Status == BUFFER_WAIT_WRITE_STATUS)
		{
			return nowPipeLine;
		}

		//< traversal channel
		if(++nowChannel >= FW_DEBUG_PIPELINE_NUM)
		{
			nowChannel = 0;
		}
		
		//< break traversal
		if(nowChannel == DebugBlock.Channel)
		{
			return NULL;
		}
	}
}

/**
 *******************************************************************************
 * @brief       filling debug head info
 * @param       [in/out]  *pipeLine pipeline
 * @param       [in/out]  type      debug output info type
 * @return      [in/out]  0         filling error
 * @return      [in/out]  uint8_t   filling num
 * @note        None
 *******************************************************************************
 */
static inline 
uint8_t FillingDebugHeadInfo(struct _BUFFER_BLOCK *pipeLine, enum _DEBUG_MESSAGE_TYPE type)
{
	if (IS_PTR_NULL(pipeLine))
	{
		return 0;
	}

	pipeLine->Tick = GetTick();

	if(type == DEBUG_OUTPUT_ERROR_MESSAGE)
	{
		return (uint8_t)sprintf((char *)&pipeLine->Buffer, "[Error][Tick:%ld]", pipeLine->Tick);
	}
	else if(type == DEBUG_OUTPUT_WARNING_MESSAGE)
	{
		return (uint8_t)sprintf((char *)&pipeLine->Buffer, "[Warning][Tick:%ld]", pipeLine->Tick);
	}
	else
	{
		return (uint8_t)sprintf((char *)&pipeLine->Buffer, "[Tick:%ld]", pipeLine->Tick);
	}
	
}

/**
 *******************************************************************************
 * @brief       write debug message
 * @param       [in/out]  *str      output string
 * @param       [in/out]  args      string param
 * @param       [in/out]  type      debug output message type
 * @return      [in/out]  0         filling error
 * @return      [in/out]  uint8_t   filling num
 * @note        None
 *******************************************************************************
 */
#if USE_DEBUG_COMPONENT_FILLING_MODE 
void WriteDebugMessage(enum _DEBUG_MESSAGE_TYPE type, const char *str, ...)
{
	struct _BUFFER_BLOCK *pipeLine = FindIdleChannel();
	uint8_t bufferLen = 0;
	va_list args;
	
	if (IS_PTR_NULL(pipeLine) || IS_PTR_NULL(str))
	{
		return;
	}

	switch(pipeLine->Status)
	{
		//< filling debug info
		case BUFFER_INIT_STATUS:
		case BUFFER_WAIT_WRITE_STATUS:
			va_start(args, cmd);
			bufferLen  = FillingDebugHeadInfo(pipeLine, type);
			bufferLen += vsprintf((char *)&pipeLine->Buffer[bufferLen], str, args);
			va_end(args);
			
			pipeLine->Size = bufferLen;
			pipeLine->Status = BUFFER_WAIT_TRANSFER_STATUS;
		//< start transfer	
		case BUFFER_WAIT_TRANSFER_STATUS:
			if(DebugBlock.ChannelStatus == DEBUG_BLOCK_CHANNEL_IDLE_STATUS)
			{
                DebugBlock.ChannelStatus = DEBUG_BLOCK_CHANNEL_BUSY_STATUS;
                
				PostEvent(FW_DEBUG_TASK, FW_TRANSFER_START_EVENT);
			}
			break;	
		default:
			break;
	}
}

#else
static inline 
void WriteDebugMessage(enum _DEBUG_MESSAGE_TYPE type, const char *str, va_list args)
{
	struct _BUFFER_BLOCK *pipeLine = FindIdleChannel();
	uint8_t bufferLen = 0;

	if (IS_PTR_NULL(pipeLine) || IS_PTR_NULL(str))
	{
		return;
	}

	switch(pipeLine->Status)
	{
		//< filling debug info
		case BUFFER_INIT_STATUS:
		case BUFFER_WAIT_WRITE_STATUS:
			bufferLen = FillingDebugHeadInfo(pipeLine, type);
			bufferLen = vsprintf((char *)&pipeLine->Buffer[bufferLen], str, args);

			pipeLine->Size = bufferLen;
			pipeLine->Status = BUFFER_WAIT_TRANSFER_STATUS;
		//< start transfer	
		case BUFFER_WAIT_TRANSFER_STATUS:
			if(DebugBlock.ChannelStatus == DEBUG_BLOCK_CHANNEL_IDLE_STATUS)
			{
				PostEvent(FW_DEBUG_TASK, FW_TRANSFER_START_EVENT);
			}
			break;	
		default:
			break;
	}
}

/**
 *******************************************************************************
 * @brief       log output message
 * @param       [in/out]  *str      output string
 * @param       [in/out]  ...       string param
 * @return      none
 * @note        None
 *******************************************************************************
 */
void log(const char *str, ...)
{
	if(IS_PTR_NULL(str))
	{
		return;
	}

	va_list args;
	
	va_start(args, cmd);
	WriteDebugMessage(DEBUG_OUTPUT_NORMAL_MESSAGE, str, args);
	va_end(args);
}

/**
 *******************************************************************************
 * @brief       log output message
 * @param       [in/out]  *str      output string
 * @param       [in/out]  ...       string param
 * @return      none
 * @note        None
 *******************************************************************************
 */
void log_e(const char *str, ...)
{
	if(IS_PTR_NULL(str))
	{
		return;
	}

	va_list args;
	
	va_start(args, cmd);
	WriteDebugMessage(DEBUG_OUTPUT_ERROR_MESSAGE, str, args);
	va_end(args);
}

/**
 *******************************************************************************
 * @brief       log output message
 * @param       [in/out]  *str      output string
 * @param       [in/out]  ...       string param
 * @return      none
 * @note        None
 *******************************************************************************
 */
void log_w(const char *str, ...)
{
	if(IS_PTR_NULL(str))
	{
		return;
	}

	va_list args;
	
	va_start(args, cmd);
	WriteDebugMessage(DEBUG_OUTPUT_WARNING_MESSAGE, str, args);
	va_end(args);
}

/**
 *******************************************************************************
 * @brief       log output message
 * @param       [in/out]  *str      output string
 * @param       [in/out]  ...       string param
 * @return      none
 * @note        None
 *******************************************************************************
 */
void log_d(const char *str, ...)
{
	if(IS_PTR_NULL(str))
	{
		return;
	}

	va_list args;
	
	va_start(args, cmd);
	WriteDebugMessage(DEBUG_OUTPUT_NORMAL_MESSAGE, str, args);
	va_end(args);
}
#endif

/**
 *******************************************************************************
 * @brief       debug message transfer function
 * @param       [in/out]  *pipeline                 tranfer pipeline
 * @param       [in/out]  enum _BUFFER_STATUS       buffer status
 * @return      none
 * @note        None
 *******************************************************************************
 */
static inline 
enum _BUFFER_STATUS TransferFunction(struct _BUFFER_BLOCK *pipeline)
{
    //< buffer interrupt transfer
    if(DebugBlock.Type == DEBUG_DEVICE_OUTPUT_SINGLE_ISR_TYPE)
	{
        DebugBlock.Device.ISRSend(pipeline->Buffer[DebugBlock.Indicator++]);
        
        //< transfer complet
        if(DebugBlock.Indicator >= pipeline->Size)
        {
            return BUFFER_TRANSFER_STATUS;
        }

//        PostEvent(FW_DEBUG_TASK, FW_TRANSFER_COMPLET_EVENT);
        return BUFFER_WAIT_TRANSFER_COMPLET_STATUS;
	}
    //< buffer dma transfer
	else if(DebugBlock.Type == DEBUG_DEVICE_OUTPUT_STREAM_TYPE)
	{
		DebugBlock.Device.Write((uint8_t *)&pipeline->Buffer, pipeline->Size);
        
        return BUFFER_WAIT_TRANSFER_COMPLET_STATUS;
	}
    //< buffer backstage transfer
	else if(DebugBlock.Type == DEBUG_DEVICE_OUTPUT_SINGLE_TYPE)
	{
        if(DebugBlock.Device.Send(pipeline->Buffer[DebugBlock.Indicator]) == FW_ERR_NONE)
        {
            //< transfer complet
            if(++DebugBlock.Indicator >= pipeline->Size)
            {
//                PostEvent(FW_DEBUG_TASK, FW_TRANSFER_COMPLET_EVENT);
                
                return BUFFER_WAIT_TRANSFER_COMPLET_STATUS;
            }
            
            return BUFFER_TRANSFER_STATUS;
        }
        else
        {
            //< wait now byte transfer complex
            PostEvent(FW_DEBUG_TASK, FW_TRANSFER_WAIT_EVNET);
            
            return BUFFER_TRANSFER_STATUS;
        }
	}
    //< device transfer function is not register 
	else
	{
	    return BUFFER_INIT_STATUS;
	}
}

/**
 *******************************************************************************
 * @brief       debug component transfer event handle
 * @param       [in/out]  event     trigger event
 * @return      [in/out]  none
 * @note        None
 *******************************************************************************
 */
static inline
void TransferEventHandle(uint8_t event)
{
    uint32_t tick = 0;
    struct _BUFFER_BLOCK *pipeline = &DebugBlock.Pipeline[DebugBlock.Channel];
    
	switch(pipeline->Status)
	{
		case BUFFER_WAIT_TIMEOUT_STATUS:
			//< wait time out event
			if(event == FW_TIMEOUT_EVENT)
			{
				//< transfer send process
				goto _DEBUG_SEND_PROCESS;
			}
			break;
		case BUFFER_WAIT_TRANSFER_STATUS:
            //< wait transfer event
            if(event == FW_TRANSFER_START_EVENT)
            {
				//< transfer send process
				goto _DEBUG_SEND_PROCESS;
            }
            break;
		case BUFFER_TRANSFER_STATUS:
		_DEBUG_SEND_PROCESS:
			pipeline->Status = TransferFunction(pipeline);
			
            if(pipeline->Status != BUFFER_WAIT_TRANSFER_COMPLET_STATUS)
            {
                break;
            }
		case BUFFER_WAIT_TRANSFER_COMPLET_STATUS:
            //< wait transfer complet (stream transfer complet trigger by transfer complet event)
            if(DebugBlock.Type == DEBUG_DEVICE_OUTPUT_STREAM_TYPE && event != FW_TRANSFER_COMPLET_EVENT)
            {
                break;
            }
            
            //< load start tick value
            tick = pipeline->Tick;
            
            //< init now channel
            pipeline->Status = BUFFER_WAIT_WRITE_STATUS;

            //< switch channel
            if (++DebugBlock.Channel >= FW_DEBUG_PIPELINE_NUM)
            {
                DebugBlock.Channel = 0;
            }
            
            pipeline = &DebugBlock.Pipeline[DebugBlock.Channel];
		case BUFFER_TRANSFER_COMPLET_STATUS:
            if(pipeline->Status == BUFFER_WAIT_TRANSFER_STATUS)
            {
                tick = CalPastTick(tick, pipeline->Tick);
                
                if(tick == 0)
                {
                    pipeline->Status = BUFFER_TRANSFER_STATUS;
                    event = FW_ERR_NONE;
                    
                    goto _DEBUG_SEND_PROCESS;
                }
                else
                {
                    pipeline->Status = BUFFER_WAIT_TIMEOUT_STATUS;
                    
                    //< start timeout timer
                    StartDebugTimer(tick);
                }
            }
            else
            {
                pipeline->Status         = BUFFER_WAIT_WRITE_STATUS;
                DebugBlock.ChannelStatus = DEBUG_BLOCK_CHANNEL_IDLE_STATUS;
            }
			break;
		default:
			break;
	}
}

/**
 *******************************************************************************
 * @brief       debug component event handle
 * @param       [in/out]  event     trigger event
 * @return      [in/out]  none
 * @note        None
 *******************************************************************************
 */
static void DebugComponentEventHandle(uint8_t event)
{
	switch(event)
	{
		case FW_TRANSFER_START_EVENT:
        case FW_TRANSFER_EVENT:
        case FW_TRANSFER_WAIT_EVNET:
        case FW_TRANSFER_COMPLET_EVENT:
        case FW_TIMEOUT_EVENT:
            TransferEventHandle(event);
			break;
	}
}
 
/**
 *******************************************************************************
 * @brief       debug component device isr handle call back function
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void DebugComponentISRCallBack(void)
{
        //< buffer interrupt transfer
    if(DebugBlock.Type == DEBUG_DEVICE_OUTPUT_SINGLE_ISR_TYPE)
	{
        PostEvent(FW_DEBUG_TASK, FW_TRANSFER_EVENT);
	}
    //< buffer dma transfer
	else if(DebugBlock.Type == DEBUG_DEVICE_OUTPUT_STREAM_TYPE)
	{
        PostEvent(FW_DEBUG_TASK, FW_TRANSFER_COMPLET_EVENT);
	}
    //< device transfer function is not register 
	else
	{
	    //< do nothing!
	}
}

/**
 *******************************************************************************
 * @brief       assert failed function
 * @param       [in/out]  *file    file name
 * @param       [in/out]  len      code line
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Fw_AssertFailed(uint8_t *file, uint32_t line)
{
    log_e("Assert Failed At %s, %ld! \n", file, line);
}

#endif

/** @}*/     /** framework debug component */

/**********************************END OF FILE*********************************/
