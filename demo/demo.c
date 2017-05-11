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
#include "fw_interface.h"

/* Private define ------------------------------------------------------------*/                                                        
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       device port define
 *******************************************************************************
 */  
static struct Hal_GPIO_Block Led1 = 
{
    .Port = MCU_PORT_D,
    .Pin  = MCU_PIN_13,
    .Mode = GPIO_MODE_PARAM(GPIO_LOW_SPEED_OUTPUT, GPIO_OUT_PUSH_PULL_MODE),
};

static struct Hal_GPIO_Block Led2 = 
{
    .Port = MCU_PORT_G,
    .Pin  = MCU_PIN_14,
    .Mode = GPIO_MODE_PARAM(GPIO_LOW_SPEED_OUTPUT, GPIO_OUT_PUSH_PULL_MODE),
};

static struct Hal_GPIO_Block Key1 = 
{
    .Port = MCU_PORT_E,
    .Pin  = MCU_PIN_0,
    .Mode = GPIO_MODE_PARAM(GPIO_INPUT, GPIO_IN_PULL_UP_MODE),
};

static struct Hal_GPIO_Block Key2 = 
{
    .Port = MCU_PORT_C,
    .Pin  = MCU_PIN_13,
    .Mode = GPIO_MODE_PARAM(GPIO_INPUT, GPIO_IN_PULL_UP_MODE),
};

/**
 *******************************************************************************
 * @brief       timer variable define
 *******************************************************************************
 */ 
static struct TimerBlock   led1Timer;
static struct ProtoThreads Led2Threads;

/**
 *******************************************************************************
 * @brief       signal variable define
 *******************************************************************************
 */
static struct SignalBlock KeySignal1;
static struct SignalBlock KeySignal2;

/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       led1 blink function
 *******************************************************************************
 */
static fw_err_t led1_blink_handler(void)
{   
    Hal.GPIO.Output.Toggle(Led1.Port, Led1.Pin);
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       led2 blink function
 *******************************************************************************
 */
static _PT_THREAD(bsp_led2_blink)
{
    fw_pt_begin();
    
    while(1)
    {
        Hal.GPIO.Output.Toggle(Led2.Port, Led2.Pin);
        
        fw_pt_delay(250); 
    }
    
    fw_pt_end();
}

/**
 *******************************************************************************
 * @brief       led application function
 *******************************************************************************
 */
static void app_led1_init(void)
{
    Framework.Timer.Init.Simple(&led1Timer, led1_blink_handler);
    Framework.Timer.Start(&led1Timer, CAL_SET_TIME(1000), TIMER_CYCLE_MODE);
}

static void app_led1_deinit(void)
{
    Framework.Timer.Stop(&led1Timer);
    Hal.GPIO.Output.Clr(Led1.Port, Led1.Pin);
}

static void app_led2_init(void)
{
    fw_pt_init(&Led2Threads, bsp_led2_blink);
    fw_pt_arm(NULL, &Led2Threads);
}

static void app_led2_deinit(void)
{
    fw_pt_disarm(&Led2Threads);
    Hal.GPIO.Output.Clr(Led2.Port, Led2.Pin);
}

/**
 *******************************************************************************
 * @brief       key1 scan function
 *******************************************************************************
 */
static uint8_t key1_scan(void)
{
    uint8_t status;
    
    Hal.GPIO.Input.Get(Key1.Port, Key1.Pin, &status);
    
    return !status;
}

/**
 *******************************************************************************
 * @brief       key2 scan function
 *******************************************************************************
 */
static uint8_t key2_scan(void)
{
    uint8_t status;
    
    Hal.GPIO.Input.Get(Key2.Port, Key2.Pin, &status);
    
    return !status;
}

/**
 *******************************************************************************
 * @brief       key1 handler function
 *******************************************************************************
 */
static fw_err_t key1_handler(uint16_t status)
{
    switch(status)
    {
        case SIGNAL_STATUS_PRESS_EDGE:
            app_led1_deinit();
            app_led2_deinit();
            break;
        case SIGNAL_STATUS_PRESS:
            Hal.GPIO.Output.Clr(Led1.Port, Led1.Pin);
            Hal.GPIO.Output.Clr(Led2.Port, Led2.Pin);
            break;
        case SIGNAL_STATUS_RELEASE_EDGE:
            app_led1_init();
            app_led2_init();
            break;
        default:
            break;
    }
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       key2 handler function
 *******************************************************************************
 */
static fw_err_t key2_handler(uint16_t status)
{
    switch(status)
    {
        case SIGNAL_STATUS_PRESS_EDGE:
            app_led1_deinit();
            app_led2_deinit();
            break;
        case SIGNAL_STATUS_PRESS:
            Hal.GPIO.Output.Set(Led1.Port, Led1.Pin);
            Hal.GPIO.Output.Set(Led2.Port, Led2.Pin);
            break;
        case SIGNAL_STATUS_RELEASE_EDGE:
            app_led1_init();
            app_led2_init();
            break;
        default:
            break;
    }
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       device led init function
 *******************************************************************************
 */
static void bsp_led_init( void )
{
    Hal.GPIO.Open(Led1.Port);
    Hal.GPIO.Init(Led1.Port, Led1.Pin, Led1.Mode);

    Hal.GPIO.Open(Led2.Port);
    Hal.GPIO.Init(Led2.Port, Led2.Pin, Led2.Mode);
}

/**
 *******************************************************************************
 * @brief       device key init function
 *******************************************************************************
 */
static void bsp_key_init(void)
{
    Hal.GPIO.Open(Key1.Port);
    Hal.GPIO.Init(Key1.Port, Key1.Pin, Key1.Mode);
    Framework.Signal.Start(&KeySignal1, key1_scan, key1_handler);
    
    Hal.GPIO.Open(Key2.Port);
    Hal.GPIO.Init(Key2.Port, Key2.Pin, Key2.Mode);
    Framework.Signal.Start(&KeySignal2, key2_scan, key2_handler);
}

/**
 *******************************************************************************
 * @brief       user init function
 *******************************************************************************
 */
static fw_err_t user_init( void )
{
    bsp_led_init();
    bsp_key_init();
    
    app_led1_init();
    app_led2_init();

    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       main function
 *******************************************************************************
 */
int main( void )
{   
    fw_core_init();
    
    user_init();
    
    fw_core_start();
    
    return 0;
}

/** @}*/     /* key control demo  */

/**********************************END OF FILE*********************************/
