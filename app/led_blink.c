/**
 ******************************************************************************
 * @file       led_blink.c
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
 * @defgroup led blink demo
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

static struct ysf_timer_t led2Timer;
/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
static ysf_err_t bsp_led1_blink( void *param )
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
    ysf.timer.simple.cb_arm(YSF_TIME_2_TICK(500), 0, bsp_led1_blink, NULL);
    
    hal.gpio.msp.init(led2.port);
    hal.gpio.msp.config(led2.port, led2.pin, led2.mode);
    ysf.timer.ex.cb_init(&led2Timer, bsp_led2_blink, NULL);
    ysf.timer.ex.arm(&led2Timer, YSF_TIME_2_TICK(1000), 0);
}

static ysf_err_t user_init( void )
{
    bsp_led_init();
    
    return YSF_ERR_NONE;
}

int main( void )
{   
    ysf.init(user_init, NULL);
}

/** @}*/     /* led blink demo  */

/**********************************END OF FILE*********************************/
