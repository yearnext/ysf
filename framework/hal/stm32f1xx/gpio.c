/**
 ******************************************************************************
 * @file       gpio.c
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
 * @defgroup gpio component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "ysf_hal_conf.h"
#include "ysf_path.h"
#include YSF_COMPONENT_DEBUG_PATH
#include YSF_COMPILER_PATH

/* Private define ------------------------------------------------------------*/
#if defined(STM32F100xB)
    #define MCU_USE_PORT_NUM (5) 
    #define PORT_USE_PIN_NUM (16)
#elif defined(STM32F100xE)
    #define MCU_USE_PORT_NUM (7) 
    #define PORT_USE_PIN_NUM (16)
#elif defined(STM32F101x6)
    #define MCU_USE_PORT_NUM (4) 
    #define PORT_USE_PIN_NUM (16)
#elif defined(STM32F101xB)
    #define MCU_USE_PORT_NUM (5) 
    #define PORT_USE_PIN_NUM (16)
#elif defined(STM32F101xE)
    #define MCU_USE_PORT_NUM (7) 
    #define PORT_USE_PIN_NUM (16)
#elif defined(STM32F101xG)
    #define MCU_USE_PORT_NUM (7) 
    #define PORT_USE_PIN_NUM (16)
#elif defined(STM32F102x6)
    #define MCU_USE_PORT_NUM (4) 
    #define PORT_USE_PIN_NUM (16)
#elif defined(STM32F102xB)
    #define MCU_USE_PORT_NUM (4) 
    #define PORT_USE_PIN_NUM (16)
#elif defined(STM32F103x6)
    #define MCU_USE_PORT_NUM (4) 
    #define PORT_USE_PIN_NUM (16)
#elif defined(STM32F103xB)
    #define MCU_USE_PORT_NUM (5) 
    #define PORT_USE_PIN_NUM (16)
#elif defined(STM32F103xE)
    #define MCU_USE_PORT_NUM (7) 
    #define PORT_USE_PIN_NUM (16)
#elif defined(STM32F103xG)
    #define MCU_USE_PORT_NUM (7) 
    #define PORT_USE_PIN_NUM (16)
#elif defined(STM32F105xC)
    #define MCU_USE_PORT_NUM (5) 
    #define PORT_USE_PIN_NUM (16)
#elif defined(STM32F107xC)
    #define MCU_USE_PORT_NUM (5) 
    #define PORT_USE_PIN_NUM (16)
#else
    #define MCU_USE_PORT_NUM (0) 
    #define PORT_USE_PIN_NUM (0)
#endif

#define IS_PORT_NUM_INVAILD(num) ( (num) >= MCU_USE_PORT_NUM )
#define IS_PIN_NUM_INVAILD(num)  ( (num) >= PORT_USE_PIN_NUM )

#define RCC_GPIO_CONFIG_HEAD ((uint32_t)0x00000004)
#define GPIO_PIN_CONFIG_HEAD ((uint16_t)0x0001)

#define DEFINE_GPIO_PORT(name) GPIO_TypeDef *name[] = \
                               {                      \
                                   GPIOA,             \
                                   GPIOB,             \
                                   GPIOC,             \
                                   GPIOD,             \
                                   GPIOE,             \
                                   GPIOF,             \
                                   GPIOG,             \
                               }
                                   
#define DEFINE_PIN_MODE(name)  uint8_t name[] =                                            \
                               {                                                           \
                                    0x04,                                                  \
                                    PIN_INPUT_MODE              | PIN_ANALOG_INPUT,        \
                                    PIN_INPUT_MODE              | PIN_FLOAT_INPUT,         \
                                    PIN_INPUT_MODE              | PIN_UP_DOWN_INPUT,       \
                                                                                           \
                                    PIN_LOW_SPEED_OUTPUT_MODE   | PIN_PUSH_PULL_OUTPUT,    \
                                    PIN_LOW_SPEED_OUTPUT_MODE   | PIN_OPEN_DNAIN_INPUT,    \
                                    PIN_LOW_SPEED_OUTPUT_MODE   | PIN_AF_PUSH_PULL_INPUT,  \
                                    PIN_LOW_SPEED_OUTPUT_MODE   | PIN_AF_OPEN_DNAIN_INPUT, \
                                                                                           \
                                    PIN_MEDIUM_SPEED_INPUT_MODE | PIN_PUSH_PULL_OUTPUT,    \
                                    PIN_MEDIUM_SPEED_INPUT_MODE | PIN_OPEN_DNAIN_INPUT,    \
                                    PIN_MEDIUM_SPEED_INPUT_MODE | PIN_AF_PUSH_PULL_INPUT,  \
                                    PIN_MEDIUM_SPEED_INPUT_MODE | PIN_AF_OPEN_DNAIN_INPUT, \
                                                                                           \
                                    PIN_HIGH_SPEED_INPUT_MODE   | PIN_PUSH_PULL_OUTPUT,    \
                                    PIN_HIGH_SPEED_INPUT_MODE   | PIN_OPEN_DNAIN_INPUT,    \
                                    PIN_HIGH_SPEED_INPUT_MODE   | PIN_AF_PUSH_PULL_INPUT,  \
                                    PIN_HIGH_SPEED_INPUT_MODE   | PIN_AF_OPEN_DNAIN_INPUT, \
                               }

#define STM32F1_GPIO_RORT_OFFSET ((uint32_t)(GPIOB_BASE - GPIOA_BASE))                               
#define STM32F1_PORT_ADDR(port)  ((GPIO_TypeDef *)(GPIOA_BASE + (uint32_t)(STM32F1_GPIO_RORT_OFFSET * (uint32_t)port)))                                                         
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
__STATIC_INLINE
void gpio_enable(uint8_t port)
{
    ysf_assert(IS_PORT_NUM_INVAILD(port));
    
    RCC->APB2ENR  |= RCC_GPIO_CONFIG_HEAD << port;
}

__STATIC_INLINE
void gpio_disable(uint8_t port)
{
    ysf_assert(IS_PORT_NUM_INVAILD(port));
    
    RCC->APB2ENR  |= RCC_GPIO_CONFIG_HEAD << port;
    RCC->APB2RSTR |= RCC_GPIO_CONFIG_HEAD << port;
    RCC->APB2RSTR &= ~(RCC_GPIO_CONFIG_HEAD << port);
    RCC->APB2ENR  &= ~(RCC_GPIO_CONFIG_HEAD << port);
}

__STATIC_INLINE
void msp_gpio_mode_config_clr( uint32_t *reg, uint8_t offset )
{
    uint8_t i;
    uint8_t shift = offset;
    
    for( i=0; i<4; i++ )
    {
        shift = offset + i;
        
        *reg &= (uint32_t)(~(1 << shift));
    }
}

__STATIC_INLINE
void msp_gpio_mode_config_set( uint32_t *reg, uint8_t offset, uint8_t mode )
{
    uint8_t i;
    uint8_t temp = mode;
    uint8_t shift = offset;
    
    for( i=0; i<4; i++ )
    {
        temp = (mode >> i) & 0x01;
        shift = offset + i;
        
        *reg |= (uint32_t)(temp << shift);
    }
}

__STATIC_INLINE
ysf_err_t gpio_config(uint8_t port, uint8_t pin, uint8_t mode)
{
    ysf_assert(IS_PORT_NUM_INVAILD(port));
    ysf_assert(IS_PIN_NUM_INVAILD(pin));
    
//    DEFINE_GPIO_PORT(GPIO);
//    GPIO_TypeDef *GPIO =  (GPIO_TypeDef *)(GPIOA_BASE + ((uint32_t)0x0400 * (uint32_t)port))
//    uint32_t gpio_crl  = GPIO[port]->CRL;
//    uint32_t gpio_crh  = GPIO[port]->CRH;
    GPIO_TypeDef *GPIO = STM32F1_PORT_ADDR(port);
    uint32_t gpio_crl  = GPIO->CRL;
    uint32_t gpio_crh  = GPIO->CRH;
    uint8_t  offset    = (pin % 8)*4;
    
    if( pin >= (PORT_USE_PIN_NUM/2) )
    {
        msp_gpio_mode_config_clr(&gpio_crh, offset);
        msp_gpio_mode_config_set(&gpio_crh, offset, mode);
    }
    else
    {
        msp_gpio_mode_config_clr(&gpio_crl, offset);
        msp_gpio_mode_config_set(&gpio_crl, offset, mode);
    }
    
    GPIO->CRL = gpio_crl;
    GPIO->CRH = gpio_crh;
    
    return YSF_ERR_NONE;
}

__STATIC_INLINE
ysf_err_t gpio_set( uint8_t port, uint8_t pin )
{
    ysf_assert(IS_PORT_NUM_INVAILD(port));
    ysf_assert(IS_PIN_NUM_INVAILD(pin));
    
//    DEFINE_GPIO_PORT(GPIO);
    GPIO_TypeDef *GPIO = STM32F1_PORT_ADDR(port);
    
//    GPIO[port]->BSRR |= GPIO_PIN_CONFIG_HEAD << pin;
    GPIO->BSRR |= GPIO_PIN_CONFIG_HEAD << pin;
        
    return YSF_ERR_NONE;
}

__STATIC_INLINE
ysf_err_t gpio_clr( uint8_t port, uint8_t pin )
{
    ysf_assert(IS_PORT_NUM_INVAILD(port));
    ysf_assert(IS_PIN_NUM_INVAILD(pin));
    
//    DEFINE_GPIO_PORT(GPIO);
    GPIO_TypeDef *GPIO = STM32F1_PORT_ADDR(port);
    
//    GPIO[port]->BRR |= GPIO_PIN_CONFIG_HEAD << pin;
    GPIO->BRR |= GPIO_PIN_CONFIG_HEAD << pin;
    
    return YSF_ERR_NONE;
}

__STATIC_INLINE
bool gpio_get(uint8_t port, uint8_t pin)
{
    ysf_assert(IS_PORT_NUM_INVAILD(port));
    ysf_assert(IS_PIN_NUM_INVAILD(pin));
    
//    DEFINE_GPIO_PORT(GPIO);
    GPIO_TypeDef *GPIO = STM32F1_PORT_ADDR(port);
    
//    return ((GPIO[port]->IDR & (GPIO_PIN_CONFIG_HEAD << pin)) ? (true) : (false));
    return ((GPIO->IDR & (GPIO_PIN_CONFIG_HEAD << pin)) ? (true) : (false));
}

ysf_err_t msp_gpio_init(uint8_t port)
{
    ysf_assert(IS_PORT_NUM_INVAILD(port));

    gpio_disable(port);
    gpio_enable(port);
    
    return YSF_ERR_NONE;
}

ysf_err_t msp_gpio_fini(uint8_t port)
{
    ysf_assert(IS_PORT_NUM_INVAILD(port));
    
    gpio_disable(port);
    
    return YSF_ERR_NONE;
}

ysf_err_t msp_gpio_pin_fini(uint8_t port, uint8_t pin)
{
    return gpio_config(port, pin, GPIO_PIN_INIT_MODE);
}

ysf_err_t msp_gpio_config(uint8_t port, uint8_t pin, uint8_t mode)
{
    return gpio_config(port, pin, mode);
}

ysf_err_t msp_gpio_set(uint8_t port, uint8_t pin)
{
    return gpio_set(port, pin);
}

ysf_err_t msp_gpio_clr(uint8_t port, uint8_t pin)
{
    return gpio_clr(port, pin);
}

bool msp_gpio_get(uint8_t port, uint8_t pin)
{
    return gpio_get(port, pin);
}

ysf_err_t map_gpio_init(struct ysf_map_gpio_t *gpio)
{
    ysf_assert(IS_PTR_NULL(gpio));

//    gpio_disable(gpio->port);
    gpio_enable(gpio->port);
    
    return YSF_ERR_NONE;
}

ysf_err_t map_gpio_fini(struct ysf_map_gpio_t *gpio)
{
    ysf_assert(IS_PTR_NULL(gpio));
    
    gpio_disable(gpio->port);
    
    return YSF_ERR_NONE;
}

ysf_err_t map_gpio_config(struct ysf_map_gpio_t *gpio, uint8_t mode)
{
    ysf_assert(IS_PTR_NULL(gpio));
    
    return gpio_config(gpio->port, gpio->pin, mode);
}

ysf_err_t map_gpio_pin_fini(struct ysf_map_gpio_t *gpio)
{
    ysf_assert(IS_PTR_NULL(gpio));
    
    return gpio_config(gpio->port, gpio->pin, GPIO_PIN_INIT_MODE);
}

ysf_err_t map_gpio_set(struct ysf_map_gpio_t *gpio)
{
    ysf_assert(IS_PTR_NULL(gpio));
    
    return gpio_set(gpio->port, gpio->pin);
}

ysf_err_t map_gpio_clr(struct ysf_map_gpio_t *gpio)
{
    ysf_assert(IS_PTR_NULL(gpio));
    
    return gpio_clr(gpio->port, gpio->pin);
}

bool map_gpio_get(struct ysf_map_gpio_t *gpio)
{
    ysf_assert(IS_PTR_NULL(gpio));
    
    return gpio_get(gpio->port, gpio->pin);
}

/** @}*/     /* gpio component  */

/**********************************END OF FILE*********************************/
