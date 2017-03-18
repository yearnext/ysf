/**
 ******************************************************************************
 * @file       key_control.c
 * @author     yearnext
 * @version    1.0.0
 * @date       2017Äê3ÔÂ4ÈÕ
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
/**
 *******************************************************************************
 * @brief       device port define
 *******************************************************************************
 */  
static struct ysf_map_gpio_t led1 = 
{
    .port = MCU_PORT_D,
    .pin  = MCU_PIN_13,
    .mode = GPIO_PIN_O_PP_LS_MODE,
};

static struct ysf_map_gpio_t led2 = 
{
    .port = MCU_PORT_G,
    .pin  = MCU_PIN_14,
    .mode = GPIO_PIN_O_PP_LS_MODE,
};

static struct ysf_map_gpio_t key1 = 
{
    .port = MCU_PORT_E,
    .pin  = MCU_PIN_0,
    .mode = GPIO_PIN_I_UD_MODE,
};

static struct ysf_map_gpio_t key2 = 
{
    .port = MCU_PORT_C,
    .pin  = MCU_PIN_13,
    .mode = GPIO_PIN_I_UD_MODE,
};

/**
 *******************************************************************************
 * @brief       timer variable define
 *******************************************************************************
 */ 
static struct ysf_timer_t *led1Timer;
static struct ysf_timer_t led2Timer;

/**
 *******************************************************************************
 * @brief       signal variable define
 *******************************************************************************
 */
static struct ysf_signal_t key1Signal;

/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/**
 *******************************************************************************
 * @brief       led1 blink function
 *******************************************************************************
 */
static ysf_err_t led1_blink_event_handler( uint16_t event )
{   
    if( hal.map.gpio.get(&led1) == true )
    {
        hal.map.gpio.clr(&led1);
    }
    else
    {
        hal.map.gpio.set(&led1);
    }
    
    return YSF_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       led2 blink function
 *******************************************************************************
 */
static ysf_err_t bsp_led2_blink( void *param )
{   
    if( hal.msp.gpio.get(led2.port, led2.pin) == true )
    {
        hal.msp.gpio.clr(led2.port, led2.pin);
    }
    else
    {
        hal.msp.gpio.set(led2.port, led2.pin);
    }
    
    return YSF_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       device led init function
 *******************************************************************************
 */
static void bsp_led_init( void )
{
    hal.map.gpio.init(&led1);
    hal.map.gpio.config(&led1);    
    ysf.event.reg(LED1_BLINK_EVENT, led1_blink_event_handler);
    led1Timer = ysf.timer.simple.evt_arm(YSF_TIME_2_TICK(500), 0, LED1_BLINK_EVENT);

    hal.msp.gpio.init(led2.port);
    hal.msp.gpio.config(led2.port, led2.pin, led2.mode);
    ysf.timer.ex.cb_init(&led2Timer, bsp_led2_blink, NULL);
    ysf.timer.ex.arm(&led2Timer, YSF_TIME_2_TICK(1000), 0);
}

/**
 *******************************************************************************
 * @brief       key1 scan function
 *******************************************************************************
 */
static enum ysf_signal_status_t key1_scan( void )
{
    return ( hal.map.gpio.get(&key1) == true ) ? (SIGNAL_STATUS_RELEASE) : (SIGNAL_STATUS_PRESS);
}

/**
 *******************************************************************************
 * @brief       key2 scan function
 *******************************************************************************
 */
static enum ysf_signal_status_t key2_scan( void )
{
    return ( hal.map.gpio.get(&key2) == true ) ? (SIGNAL_STATUS_RELEASE) : (SIGNAL_STATUS_PRESS);
}

/**
 *******************************************************************************
 * @brief       key1 handler function
 *******************************************************************************
 */
static void key1_handler(enum ysf_signal_status_t status)
{
    switch(status)
    {
        case SIGNAL_STATUS_PRESS_EDGE:
            ysf.timer.simple.disarm(led1Timer);
            ysf.timer.ex.disarm(&led2Timer);
            break;
        case SIGNAL_STATUS_PRESS:
            hal.map.gpio.clr(&led1);
            hal.map.gpio.clr(&led2);
            break;
        case SIGNAL_STATUS_RELEASE_EDGE:
            ysf.event.reg(LED1_BLINK_EVENT, led1_blink_event_handler);
            led1Timer = ysf.timer.simple.evt_arm(YSF_TIME_2_TICK(500), 0, LED1_BLINK_EVENT);

            ysf.timer.ex.cb_init(&led2Timer, bsp_led2_blink, NULL);
            ysf.timer.ex.arm(&led2Timer, YSF_TIME_2_TICK(1000), 0);
            break;
        default:
            break;
    }
}

/**
 *******************************************************************************
 * @brief       key2 handler function
 *******************************************************************************
 */
static void key2_handler(enum ysf_signal_status_t status)
{
    switch(status)
    {
        case SIGNAL_STATUS_PRESS_EDGE:
            ysf.timer.simple.disarm(led1Timer);
            ysf.timer.ex.disarm(&led2Timer);
            break;
        case SIGNAL_STATUS_PRESS:
            hal.map.gpio.set(&led1);
            hal.map.gpio.set(&led2);
            break;
        case SIGNAL_STATUS_RELEASE_EDGE:
            ysf.event.reg(LED1_BLINK_EVENT, led1_blink_event_handler);
            led1Timer = ysf.timer.simple.evt_arm(YSF_TIME_2_TICK(500), 0, LED1_BLINK_EVENT);
            
            ysf.timer.ex.cb_init(&led2Timer, bsp_led2_blink, NULL);
            ysf.timer.ex.arm(&led2Timer, YSF_TIME_2_TICK(1000), 0);
            break;
        default:
            break;
    }
}

/**
 *******************************************************************************
 * @brief       device key init function
 *******************************************************************************
 */
static void bsp_key_init(void)
{
    hal.map.gpio.init(&key1);
    hal.map.gpio.config(&key1);
    ysf.signal.simple.arm(key1_scan, key1_handler);
    
    hal.map.gpio.init(&key2);
    hal.map.gpio.config(&key2);
    ysf.signal.ex.arm(&key1Signal, key2_scan, key2_handler);
}

/**
 *******************************************************************************
 * @brief       user init function
 *******************************************************************************
 */
static ysf_err_t user_init( void )
{
    bsp_led_init();
    bsp_key_init();
    
    return YSF_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       main function
 *******************************************************************************
 */
int main( void )
{   
    ysf.init(user_init);
    ysf.start();
}

/** @}*/     /* key control demo  */

/**********************************END OF FILE*********************************/
