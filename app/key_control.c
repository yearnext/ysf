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
//static struct ysf_map_gpio_t led1 = 
//{
//    .port = MCU_PORT_D,
//    .pin  = MCU_PIN_13,
//};

static struct ysf_map_gpio_t led2 = 
{
    .port = MCU_PORT_G,
    .pin  = MCU_PIN_14,
};

//static struct ysf_map_gpio_t key1 = 
//{
//    .port = MCU_PORT_E,
//    .pin  = MCU_PIN_0,
//};

static struct ysf_map_gpio_t key2 = 
{
    .port = MCU_PORT_C,
    .pin  = MCU_PIN_13,
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
    if( msp.gpio.pin.get(MCU_PORT_D, MCU_PIN_13) == true )
    {
        msp.gpio.pin.clr(MCU_PORT_D, MCU_PIN_13);
    }
    else
    {
        msp.gpio.pin.set(MCU_PORT_D, MCU_PIN_13);
    }
    
    return YSF_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       led2 blink function
 *******************************************************************************
 */
//static ysf_err_t bsp_led2_blink( void *param )
//{   
//    if( msp.gpio.pin.get(led2.port, led2.pin) == true )
//    {
//        msp.gpio.pin.clr(led2.port, led2.pin);
//    }
//    else
//    {
//        msp.gpio.pin.set(led2.port, led2.pin);
//    }
//    
//    return YSF_ERR_NONE;
//}

static YSF_PT_THREAD(bsp_led2_blink)
{
    ysf_pt_init(bsp_led2_blink);
    ysf_pt_begin();
    
    while(1)
    {
        msp.gpio.pin.clr(led2.port, led2.pin);
        ysf_pt_delay(500);
        
        msp.gpio.pin.set(led2.port, led2.pin);
        ysf_pt_delay(500);
    }
    
    ysf_pt_end();
}

/**
 *******************************************************************************
 * @brief       device led init function
 *******************************************************************************
 */
static void bsp_led_init( void )
{
    msp.gpio.port.config.init(MCU_PORT_D);
    msp.gpio.pin.config.output(MCU_PORT_D, MCU_PIN_13, GPIO_PIN_O_PP_LS_MODE);    
    ysf.event.reg(LED1_BLINK_EVENT, led1_blink_event_handler);
    led1Timer = ysf.timer.simple.evt_arm(YSF_TIME_2_TICK(500), 0, LED1_BLINK_EVENT);

    map.gpio.port.config.init(&led2);
    map.gpio.pin.config.output(&led2, GPIO_PIN_O_PP_LS_MODE);  
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
    return ( msp.gpio.pin.get(MCU_PORT_E, MCU_PIN_0) == true ) ? (SIGNAL_STATUS_RELEASE) : (SIGNAL_STATUS_PRESS);
}

/**
 *******************************************************************************
 * @brief       key2 scan function
 *******************************************************************************
 */
static enum ysf_signal_status_t key2_scan( void )
{
    return ( map.gpio.pin.get(&key2) == true ) ? (SIGNAL_STATUS_RELEASE) : (SIGNAL_STATUS_PRESS);
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
            msp.gpio.pin.clr(MCU_PORT_D, MCU_PIN_13);
            map.gpio.pin.clr(&led2);
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
            msp.gpio.pin.set(MCU_PORT_D, MCU_PIN_13);
            map.gpio.pin.set(&led2);
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
    msp.gpio.port.config.init(MCU_PORT_E);
    msp.gpio.pin.config.input(MCU_PORT_E, MCU_PIN_0, GPIO_PIN_I_UD_MODE);
    ysf.signal.simple.arm(key1_scan, key1_handler);
    
    map.gpio.port.config.init(&key2);
    map.gpio.pin.config.input(&key2, GPIO_PIN_I_UD_MODE);
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
