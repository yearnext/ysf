/**
 *******************************************************************************
 * @file       demo.c                                                          *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-04-19                                                      *
 * @brief      demo source files                                               *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         * 
 *******************************************************************************
 * @note                                                                       *
 * 1.XXXXX                                                                     *
 *******************************************************************************
 */
 
/**
 * @defgroup key control demo
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "fw_core.h"
#include "hal_core.h"
#include "map_uart.h"

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       device port define
 *******************************************************************************
 */  
static Hal_GPIO_Handle Led = 
{
    .Port = MCU_PORT_D,
    .Pin  = MCU_PIN_13,
    .Dir  = GPIO_DIR_HS_OUTPUT,
    .Mode = GPIO_PUSH_PULL_MODE,
};

/**
 *******************************************************************************
 * @brief       timer variable define
 *******************************************************************************
 */ 
static struct Fw_Task        LedTask;
static struct Fw_Timer       LedTimer;

static struct Fw_Timer       PutTimer;

/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       led1 blink function
 *******************************************************************************
 */
void Led_Task_Handle(uint32_t event, void *param);

void App_Led_Init(void)
{
    Hal_GPIO_Init(&Led);
    
    Fw_Task_Init(&LedTask, "Led Task", 1, (void *)Led_Task_Handle, FW_MESSAGE_HANDLE_TYPE_TASK);
    
    Fw_Timer_Init(&LedTimer, "Led Timer");
    Fw_Timer_SetEvent(&LedTimer, &LedTask, LED_BLINK_EVENT, (void *)&Led);
    Fw_Timer_Start(&LedTimer, 500, -1);
}

void Led_Task_Handle(uint32_t event, void *param)
{
    Hal_GPIO_Handle *drv = (Hal_GPIO_Handle *)param;
    
    switch(event)
    {
        case LED_ON_EVENT:
            Hal_GPIO_Set(drv);
            break;
        case LED_OFF_EVENT:
            Hal_GPIO_Clr(drv);
            break;
        case LED_BLINK_EVENT:
            Hal_GPIO_Toggle(drv);
            break;
        default:
            break;
    }
}

void App_Put_Callback(void *param)
{
    log("Hello World!\r\n");
}

void App_Put_Init(void)
{
    Fw_Timer_Init(&PutTimer, "Put User Message Timer");
    Fw_Timer_SetCallback(&PutTimer, App_Put_Callback, NULL);
    Fw_Timer_Start(&PutTimer, 1000, -1);
}

/**
 *******************************************************************************
 * @brief       user init function
 *******************************************************************************
 */
void App_User_Init(void)
{
    App_Led_Init();
    App_Put_Init();
}

/** @}*/     /* key control demo  */

/**********************************END OF FILE*********************************/
