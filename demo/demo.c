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
#include "core.h"

/* Private define ------------------------------------------------------------*/                                                        
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
///**
// *******************************************************************************
// * @brief       device port define
// *******************************************************************************
// */  
//static struct HalGPIOBlock Led1 = 
//{
//    .Port = MCU_PORT_D,
//    .Pin  = MCU_PIN_13,
//    .Mode = GPIO_PIN_O_PP_LS_MODE,
//};

//static struct HalGPIOBlock Led2 = 
//{
//    .Port = MCU_PORT_G,
//    .Pin  = MCU_PIN_14,
//    .Mode = GPIO_PIN_O_PP_LS_MODE,
//};

//static struct HalGPIOBlock Key1 = 
//{
//    .Port = MCU_PORT_E,
//    .Pin  = MCU_PIN_0,
//    .Mode = GPIO_PIN_I_UD_MODE,
//};

//static struct HalGPIOBlock Key2 = 
//{
//    .Port = MCU_PORT_C,
//    .Pin  = MCU_PIN_13,
//    .Mode = GPIO_PIN_I_UD_MODE,
//};

///**
// *******************************************************************************
// * @brief       timer variable define
// *******************************************************************************
// */ 
//static struct TimerBlock   *led1Timer;
//static struct ProtoThreads Led2Threads;

///**
// *******************************************************************************
// * @brief       signal variable define
// *******************************************************************************
// */
//static struct SignalBlock  KeySignal1;
//static struct SignalBlock *KeySignal2;

/////* Exported variables --------------------------------------------------------*/
/////* Private functions ---------------------------------------------------------*/
/////* Exported functions --------------------------------------------------------*/
///**
// *******************************************************************************
// * @brief       led1 blink function
// *******************************************************************************
// */
//static fw_err_t led1_blink_handler( void *param )
//{   
//    Core.Hal.GPIO.Output.Toggle(&Led1);
//    
//    return FW_ERR_NONE;
//}

///**
// *******************************************************************************
// * @brief       led2 blink function
// *******************************************************************************
// */
//static _PT_THREAD(bsp_led2_blink)
//{
//    _pt_begin();
//    
//    while(1)
//    {
//        Core.Hal.GPIO.Output.Toggle(&Led2);
//        
//        _pt_delay(250); 
//    }
//    
//    _pt_end();
//}

///**
// *******************************************************************************
// * @brief       led application function
// *******************************************************************************
// */
//static void app_led1_init(void)
//{
//    led1Timer = Core.Component.Timer.Create.CallBackEx(led1_blink_handler, NULL);
//    Core.Component.Timer.Arm(led1Timer, TIME_2_TICK(1000), TIMER_CYCLE_MODE);
//}

//static void app_led1_deinit(void)
//{
//    Core.Component.Timer.Disarm(led1Timer);
//}

//static void app_led2_init(void)
//{
//    _pt_init(&Led2Threads, bsp_led2_blink);
//    _pt_ex_arm(&Led2Threads);
//}

//static void app_led2_deinit(void)
//{
//    _pt_disarm(&Led2Threads);
//}

///**
// *******************************************************************************
// * @brief       key1 scan function
// *******************************************************************************
// */
//static uint8_t key1_scan(void)
//{
//    uint8_t status;
//    
//    Core.Hal.GPIO.Input.Get(&Key1, &status);
//    
//    return !status;
//}

///**
// *******************************************************************************
// * @brief       key2 scan function
// *******************************************************************************
// */
//static uint8_t key2_scan(void)
//{
//    uint8_t status;
//    
//    Core.Hal.GPIO.Input.Get(&Key2, &status);
//    
//    return !status;
//}

///**
// *******************************************************************************
// * @brief       key1 handler function
// *******************************************************************************
// */
//static fw_err_t key1_handler(uint16_t status)
//{
//    switch(status)
//    {
//        case SIGNAL_STATUS_PRESS_EDGE:
//            app_led1_deinit();
//            app_led2_deinit();
//            break;
//        case SIGNAL_STATUS_PRESS:
//            Core.Hal.GPIO.Output.Clr(&Led1);
//            Core.Hal.GPIO.Output.Clr(&Led1);
//            break;
//        case SIGNAL_STATUS_RELEASE_EDGE:
//            app_led1_init();
//            app_led2_init();
//            break;
//        default:
//            break;
//    }
//    
//    return FW_ERR_NONE;
//}

///**
// *******************************************************************************
// * @brief       key2 handler function
// *******************************************************************************
// */
//static fw_err_t key2_handler(uint16_t status)
//{
//    switch(status)
//    {
//        case SIGNAL_STATUS_PRESS_EDGE:
//            app_led1_deinit();
//            app_led2_deinit();
//            break;
//        case SIGNAL_STATUS_PRESS:
//            Core.Hal.GPIO.Output.Set(&Led1);
//            Core.Hal.GPIO.Output.Set(&Led2);
//            break;
//        case SIGNAL_STATUS_RELEASE_EDGE:
//            app_led1_init();
//            app_led2_init();
//            break;
//        default:
//            break;
//    }
//    
//    return FW_ERR_NONE;
//}

///**
// *******************************************************************************
// * @brief       device led init function
// *******************************************************************************
// */
//static void bsp_led_init( void )
//{
//    Core.Hal.GPIO.Enable(&Led1);
//    Core.Hal.GPIO.Output.Init(&Led1);

//    Core.Hal.GPIO.Enable(&Led2);
//    Core.Hal.GPIO.Output.Init(&Led2);
//}

///**
// *******************************************************************************
// * @brief       device key init function
// *******************************************************************************
// */
//static void bsp_key_init(void)
//{
//    Core.Hal.GPIO.Enable(&Key1);
//    Core.Hal.GPIO.Input.Init(&Key1);
//    Core.Component.Signal.Create.Simple(&KeySignal1, key1_scan, key1_handler);
//    Core.Component.Signal.Arm(&KeySignal1, TIME_2_TICK(20),SIGNAL_CYCLE_MODE);
//    
//    Core.Hal.GPIO.Enable(&Key2);
//    Core.Hal.GPIO.Input.Init(&Key2);
//    KeySignal2 = Core.Component.Signal.Create.SimpleEx(key2_scan, key2_handler);
//    Core.Component.Signal.Arm(KeySignal2, TIME_2_TICK(20),SIGNAL_CYCLE_MODE);
//}

///**
// *******************************************************************************
// * @brief       user init function
// *******************************************************************************
// */
//static fw_err_t user_init( void )
//{
//    bsp_led_init();
//    bsp_key_init();
//    
//    app_led1_init();
//    app_led2_init();

//    return FW_ERR_NONE;
//}

/**
 *******************************************************************************
 * @brief       main function
 *******************************************************************************
 */
int main( void )
{   
    Core.Init();
    
//    user_init();
    
    Core.Start();
    
    return 0;
}

/** @}*/     /* key control demo  */

/**********************************END OF FILE*********************************/
