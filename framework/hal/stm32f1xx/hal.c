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
    .gpio.enable                 = msp_gpio_init,
    .gpio.disable                = msp_gpio_fini,
    
    .gpio.input.init             = msp_gpio_config,
    .gpio.input.get              = msp_gpio_get_input,
    
    .gpio.output.init            = msp_gpio_config,
    .gpio.output.get             = msp_gpio_get_output,
    .gpio.output.set             = msp_gpio_set,
    .gpio.output.clr             = msp_gpio_clr,
    
    .gpio.multi.init             = msp_gpio_config,   
#endif
        
#if defined(USE_MSP_TIMER_API) && USE_MSP_TIMER_API
    .timer.enable                = msp_timer_init,
    .timer.disable               = msp_timer_fini,
    .timer.init.tick             = tick_timer_init,
#endif
};
    
const struct YSF_MAP_API map = 
{
#if defined(USE_MAP_GPIO_API) && USE_MAP_GPIO_API
    .gpio.enable                 = map_gpio_init,
    .gpio.disable                = map_gpio_fini,
    
    .gpio.input.init             = map_gpio_config,
    .gpio.input.get              = map_gpio_get_input,
    
    .gpio.output.init            = map_gpio_config,
    .gpio.output.get             = map_gpio_get_output,
    .gpio.output.set             = map_gpio_set,
    .gpio.output.clr             = map_gpio_clr,
    
    .gpio.multi.init             = map_gpio_config,   
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
