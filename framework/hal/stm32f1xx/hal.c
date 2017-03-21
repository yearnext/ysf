/**
 ******************************************************************************
 * @file       hal.c
 * @author     yearnext
 * @version    1.0.0
 * @date       2017Äê3ÔÂ4ÈÕ
 * @brief      hal source file
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
 * @defgroup hal component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "ysf_hal_conf.h"

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
#if USE_HAL_API
const struct YSF_MSP_API msp = 
{
#if defined(USE_MSP_GPIO_API) && USE_MSP_GPIO_API
    .gpio.port.config.init       = msp_gpio_init,
    .gpio.port.config.fini       = msp_gpio_fini,
    
    .gpio.pin.config.fini        = msp_gpio_pin_fini,
    .gpio.pin.config.input       = msp_gpio_config,
    .gpio.pin.config.output      = msp_gpio_config,
    
    .gpio.pin.set                = msp_gpio_set,
    .gpio.pin.clr                = msp_gpio_clr,
    .gpio.pin.get                = msp_gpio_get,
#endif
        
#if defined(USE_MSP_TIMER_API) && USE_MSP_TIMER_API
    .timer.enable                = msp_timer_init,
    .timer.disable               = msp_timer_fini,
    .timer.tick.init             = msp_tick_timer_init,
#endif
};
    
const struct YSF_MAP_API map = 
{
#if defined(USE_MAP_GPIO_API) && USE_MAP_GPIO_API
    .gpio.port.config.init       = map_gpio_init,
    .gpio.port.config.fini       = map_gpio_fini,
    
    .gpio.pin.config.fini        = map_gpio_pin_fini,
    .gpio.pin.config.input       = map_gpio_config,
    .gpio.pin.config.output      = map_gpio_config,
    
    .gpio.pin.set                = map_gpio_set,
    .gpio.pin.clr                = map_gpio_clr,
    .gpio.pin.get                = map_gpio_get,
#endif
        
#if defined(USE_MAP_TIMER_API) && USE_MAP_TIMER_API
    .timer.enable                = map_timer_init,
    .timer.disable               = map_timer_fini,
#endif
};

#endif

/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @}*/     /* hal component  */

/**********************************END OF FILE*********************************/
