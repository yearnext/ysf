#include "ysf.h"

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

int main( void )
{
    ysf.init();
    
    hal.gpio.map.init(&led1);
    hal.gpio.msp.init(led2.port);

    hal.gpio.map.config(&led1);
    hal.gpio.msp.config(led2.port, led2.pin, led2.mode);
    
    while(1)
    {
        hal.gpio.map.set(&led1);
//        hal.gpio.msp.set(led2.port, led2.pin);
        
//        hal.gpio.map.clr(&led1);
        hal.gpio.msp.clr(led2.port, led2.pin);
    }
}
