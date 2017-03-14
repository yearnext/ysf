/**
 ******************************************************************************
 * @file       key_control.c
 * @author     yearnext
 * @version    1.0.0
 * @date       2017年3月4日
 * @brief      gpio source file
 * @par        work paltform                                  
 *                 Windows
 * @par        compiler paltform									                         
 *                 GCC
 ******************************************************************************
 * @note
 * 1.XXXXX                  						                     
 ******************************************************************************
 */

/**
 * @defgroup key control demo
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "ysf.h"

/* Private define ------------------------------------------------------------*/                                                        
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static struct ysf_msp_gpio_t led1 = 
{
    .port = MCU_PORT_D,
    .pin  = MCU_PIN_13,
    .mode = GPIO_PIN_O_PP_LS_MODE,
};

static struct ysf_msp_gpio_t led2 = 
{
    .port = MCU_PORT_G,
    .pin  = MCU_PIN_14,
    .mode = GPIO_PIN_O_PP_LS_MODE,
};

static struct ysf_msp_gpio_t key1 = 
{
    .port = MCU_PORT_C,
    .pin  = MCU_PIN_13,
    .mode = GPIO_PIN_I_UD_MODE,
};

static struct ysf_msp_gpio_t key2 = 
{
    .port = MCU_PORT_E,
    .pin  = MCU_PIN_0,
    .mode = GPIO_PIN_I_UD_MODE,
};

static struct ysf_timer_t *led1Timer;
static struct ysf_timer_t led2Timer;
static struct ysf_signal_t key1Signal;
/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       LED 驱动相关
 *******************************************************************************
 */
static ysf_err_t led1_blink_event_handler( uint16_t event )
{   
    if( hal.gpio.map.get(&led1) == true )
    {
        hal.gpio.map.clr(&led1);
    }
    else
    {
        hal.gpio.map.set(&led1);
    }
    
    return YSF_ERR_NONE;
}

static ysf_err_t bsp_led2_blink( void *param )
{   
    if( hal.gpio.msp.get(led2.port, led2.pin) == true )
    {
        hal.gpio.msp.clr(led2.port, led2.pin);
    }
    else
    {
        hal.gpio.msp.set(led2.port, led2.pin);
    }
    
    return YSF_ERR_NONE;
}

static void bsp_led_init( void )
{
    hal.gpio.map.init(&led1);
    hal.gpio.map.config(&led1);
    led1Timer = ysf.timer.simple.evt_arm(YSF_TIME_2_TICK(500), 0, LED1_BLINK_EVENT);
    ysf.event.evt_register(LED1_BLINK_EVENT, led1_blink_event_handler);
    
    hal.gpio.msp.init(led2.port);
    hal.gpio.msp.config(led2.port, led2.pin, led2.mode);
    ysf.timer.ex.cb_init(&led2Timer, bsp_led2_blink, NULL);
    ysf.timer.ex.arm(&led2Timer, YSF_TIME_2_TICK(1000), 0);
}

/**
 *******************************************************************************
 * @brief       key 控制相关
 *******************************************************************************
 */
static enum ysf_signal_status_t key1_scan( void )
{
    return ( hal.gpio.map.get(&key1) == true ) ? (SIGNAL_STATUS_RELEASE) : (SIGNAL_STATUS_PRESS);
}

static enum ysf_signal_status_t key2_scan( void )
{
    return ( hal.gpio.map.get(&key2) == true ) ? (SIGNAL_STATUS_RELEASE) : (SIGNAL_STATUS_PRESS);
}

static void key1_handler(enum ysf_signal_status_t status)
{
    switch(status)
    {
        case SIGNAL_STATUS_PRESS_EDGE:
            ysf.timer.simple.disarm(led1Timer);
            ysf.timer.ex.disarm(&led2Timer);
            break;
        case SIGNAL_STATUS_PRESS:
            hal.gpio.map.clr(&led1);
            hal.gpio.map.clr(&led2);
            break;
        case SIGNAL_STATUS_RELEASE_EDGE:
            led1Timer = ysf.timer.simple.evt_arm(YSF_TIME_2_TICK(500), 0, LED1_BLINK_EVENT);
            ysf.event.evt_register(LED1_BLINK_EVENT, led1_blink_event_handler);
        
            ysf.timer.ex.cb_init(&led2Timer, bsp_led2_blink, NULL);
            ysf.timer.ex.arm(&led2Timer, YSF_TIME_2_TICK(1000), 0);
            break;
        default:
            break;
    }
}

static void key2_handler(enum ysf_signal_status_t status)
{
    switch(status)
    {
        case SIGNAL_STATUS_PRESS_EDGE:
            ysf.timer.simple.disarm(led1Timer);
            ysf.timer.ex.disarm(&led2Timer);
            break;
        case SIGNAL_STATUS_PRESS:
            hal.gpio.map.set(&led1);
            hal.gpio.map.set(&led2);
            break;
        case SIGNAL_STATUS_RELEASE_EDGE:
            led1Timer = ysf.timer.simple.evt_arm(YSF_TIME_2_TICK(500), 0, LED1_BLINK_EVENT);
            ysf.event.evt_register(LED1_BLINK_EVENT, led1_blink_event_handler);
        
            ysf.timer.ex.cb_init(&led2Timer, bsp_led2_blink, NULL);
            ysf.timer.ex.arm(&led2Timer, YSF_TIME_2_TICK(1000), 0);
            break;
        default:
            break;
    }
}

static void bsp_key_init(void)
{
    hal.gpio.map.init(&key1);
    hal.gpio.map.init(&key1);
    ysf.signal.simple.arm(key1_scan, key1_handler);
    
    hal.gpio.map.init(&key2);
    hal.gpio.map.init(&key2);
    ysf.signal.ex.arm(&key1Signal, key2_scan, key2_handler);
}

static ysf_err_t user_init( void )
{
    bsp_led_init();
    bsp_key_init();
    
    return YSF_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       主函数
 *******************************************************************************
 */
int main( void )
{   
    ysf.init(user_init);
    ysf.start();
}

/** @}*/     /* key control demo  */

/**********************************END OF FILE*********************************/
