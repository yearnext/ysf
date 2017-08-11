/**
 *******************************************************************************
 *                       Copyright (C) 2017  yearnext                          *
 *                                                                             *
 *    This program is free software; you can redistribute it and/or modify     *
 *    it under the terms of the GNU General Public License as published by     *
 *    the Free Software Foundation; either version 2 of the License, or        *
 *    (at your option) any later version.                                      *
 *                                                                             *
 *    This program is distributed in the hope that it will be useful,          *
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of           *
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            *
 *    GNU General Public License for more details.                             *
 *                                                                             *
 *    You should have received a copy of the GNU General Public License along  *
 *    with this program; if not, write to the Free Software Foundation, Inc.,  *
 *    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.              *
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
static struct HalGPIODevice Led1 = 
{
    .Port = MCU_PORT_D,
    .Pin  = MCU_PIN_13,
    .IO   = GPIO_HS_OUTPUT,
    .Mode = GPIO_PUSH_PULL_MODE,
};

static struct HalGPIODevice Led2 = 
{
    .Port = MCU_PORT_G,
    .Pin  = MCU_PIN_14,
    .IO   = GPIO_HS_OUTPUT,
    .Mode = GPIO_PUSH_PULL_MODE,
};

static struct HalGPIODevice Key1 = 
{
    .Port = MCU_PORT_E,
    .Pin  = MCU_PIN_0,
    .IO   = GPIO_INTPUT,
    .Mode = GPIO_PULL_UP_DOWN_MODE,
};

static struct HalGPIODevice Key2 = 
{
    .Port = MCU_PORT_C,
    .Pin  = MCU_PIN_13,
    .IO   = GPIO_INTPUT,
    .Mode = GPIO_PULL_UP_DOWN_MODE,
};

/**
 *******************************************************************************
 * @brief       timer variable define
 *******************************************************************************
 */ 
static struct Fw_Task        Led1Task;
static struct Fw_Timer       Led1Timer;

static struct Fw_ProtoThread Led2Task;

static struct Fw_Task        KeyTask;

/**
 *******************************************************************************
 * @brief       signal variable define
 *******************************************************************************
 */
static struct Fw_Signal Key1Signal;
static struct Fw_Signal Key2Signal;

/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       led1 blink function
 *******************************************************************************
 */
void Led1_Task_Handle(uint32_t event, void *param);

void App_Led1_Init(void)
{
    Hal_GPIO_Open(&Led1);
    Hal_GPIO_Init(&Led1);
    
    Fw_Task_Init(&Led1Task, "Led1 Task", 1, (void *)Led1_Task_Handle, FW_MESSAGE_HANDLE_TYPE_TASK);
    
    Fw_Timer_Init(&Led1Timer, "Led1 Timer");
    Fw_Timer_SetEvent(&Led1Timer, &Led1Task, LED_BLINK_EVENT, (void *)&Led1);
    Fw_Timer_Start(&Led1Timer, 1000, -1);
}

void Led1_Task_Handle(uint32_t event, void *param)
{
    struct HalGPIODevice *drv = (struct HalGPIODevice *)param;
    
    switch(event)
    {
        case LED_ON_EVENT:
            Hal_GPIO_Set(drv);
            break;
        case LED_OFF_EVENT:
            Hal_GPIO_Clear(drv);
            break;
        case LED_BLINK_EVENT:
            Hal_GPIO_Toggle(drv);
            break;
        default:
            break;
    }
}

/**
 *******************************************************************************
 * @brief       led2 blink function
 *******************************************************************************
 */
_PT_THREAD(Led2_Task_Handle);

void App_Led2_Init(void)
{
    Hal_GPIO_Open(&Led2);
    Hal_GPIO_Init(&Led2);

    Fw_PT_Init(&Led2Task, "Led2 Task", Led2_Task_Handle, 1);
    Fw_PT_Open(&Led2Task);
}

_PT_THREAD(Led2_Task_Handle)
{
    Fw_PT_Begin();
    
    while(1)
    {
        Hal_GPIO_Toggle(&Led2);
        
        Fw_PT_Delay(500); 
    }
    
    Fw_PT_End();
}

/**
 *******************************************************************************
 * @brief       key scan function
 *******************************************************************************
 */
uint8_t Key1_Scan_Function(void)
{
    uint16_t status = 0;
    
    Hal_GPIO_GetIntputStatus(&Key1, &status);
    
    return (status) ? (DEMO_KEY1_SIGNAL) : (0);
}

uint8_t Key2_Scan_Function(void)
{
    uint16_t status = 0;
    
    Hal_GPIO_GetIntputStatus(&Key2, &status);
    
    return (status) ? (DEMO_KEY2_SIGNAL) : (0);
}

/**
 *******************************************************************************
 * @brief       key init function
 *******************************************************************************
 */
void App_Key1_Init(void)
{
    Hal_GPIO_Open(&Key1);
    Hal_GPIO_Init(&Key1);
    
    Fw_Signal_Init(&Key1Signal, "Key1 Signal", &KeyTask, Key1_Scan_Function);
    Fw_Signal_Open(&Key1Signal, REG_RELEASE_EDGE_STATE, 50);
}

void App_Key2_Init(void)
{
    Hal_GPIO_Open(&Key2);
    Hal_GPIO_Init(&Key2);
    
    Fw_Signal_Init(&Key2Signal, "Key2 Signal", &KeyTask, Key2_Scan_Function);
    Fw_Signal_Open(&Key2Signal, REG_RELEASE_EDGE_STATE, 50);
}

void App_KeyTask_Handle(uint32_t event, void *param);
void App_KeyTask_Init(void)
{
    Fw_Task_Init(&Led1Task, "Key Task", 1, (void *)App_KeyTask_Handle, FW_MESSAGE_HANDLE_TYPE_TASK);
}

/**
 *******************************************************************************
 * @brief       key handle function
 *******************************************************************************
 */
void App_KeyTask_Handle(uint32_t event, void *param)
{
    switch(event)
    {
        //< signal event handle
        case FW_SIGNAL_HANDLE_EVENT:
        {
            struct Fw_Signal *signal = (struct Fw_Signal *)param;
            
            //< key handle
            switch(signal->Value)
            {
                case DEMO_KEY1_SIGNAL:
                    if(signal->State == SIGNAL_RELEASE_EDGE_STATE)
                    {
                        
                    }
                    break;
                case DEMO_KEY2_SIGNAL:
                    if(signal->State == SIGNAL_RELEASE_EDGE_STATE)
                    {
                        
                    }
                    break;
                default:
                    break;
            }
            
            break;
        }
        default:
            break;
    }
}

/**
 *******************************************************************************
 * @brief       user init function
 *******************************************************************************
 */
void App_User_Init(void)
{
    App_Led1_Init();
    App_Led2_Init();
    
    App_KeyTask_Init();
    App_Key1_Init();
    App_Key2_Init();
}

/** @}*/     /* key control demo  */

/**********************************END OF FILE*********************************/
